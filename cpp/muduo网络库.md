## 1 目的

1. 理解阻塞、非阻塞、同步、异步
2. 理解 Unix/Linux 上的五种 IO 模型
3. `epoll` 的原理以及优势
4. 深刻理解 Reactor 模型
5. 从开源 C++ 网络库，学习优秀的代码设计
6. 掌握基于事件驱动和事件回调的 `epoll` + 线程池面向对象编程
7. 通过深入理解 `muduo` 源码，加深对于相关项目的深刻理解
8. 改造 `muduo`，不依赖 `boost`，用 C++11 重构

## 2 知识储备

1. TCP 协议和 UDP 协议
2. TCP 编程和 UDP 编程步骤
3. IO 复用接口编程 `select`、`poll`、`epoll` 编程
4. Linux 的多线程编程 `pthread`、进程和线程模型。 C++20 标准加入了协程的支持

**推荐阅读**：《Linux 高性能服务器编程》《UNIX 环境高级编程》《鸟哥的 Linux 私房菜》

## 3 IO 复用

> `select`，`poll`，`epoll` 都是 IO 多路复用的机制。**I/O 多路复用就通过一种机制，可以监视多个描述符**，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作。
>
> **但 `select`，`poll`，`epoll` 本质上都是同步 I/O**，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步 I/O 则无需自己负责进行读写，异步 I/O 的实现会负责把数据从内核拷贝到用户空间。

### 3.1 IO 多路复用之 `select`

使用 `select` 可以实现同时处理多个网络连接的 IO 请求。其基本原理是程序调用 `select` 后，**程序进入阻塞状态**，此时 `kernel`（内核）会轮询检查所有 `select` 负责的文件描述符 `fd`。当找到其中某个文件描述符的数据已准备好时，`select` 返回该文件描述符并通知系统调用，**将数据从内核复制到进程的缓存区**。

![20240617124845](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240617124845.png)

**缺点：**

- 进程可以打开的 `fd` 有限制（32 位机 1024 个，64 位 2048 个），因为 `fd` 存储在一个固定大小的数组中。
- 对 `socket` 进行扫描是线性扫描，即采用轮询方法，效率较低。
- 用户空间和内核空间之间复制数据非常消耗资源。

#### 3.1.1 常用函数

**`select`**

> **函数原型**
>
> ```cpp
> int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);
> ```
>
> **参数**
>
> - `int maxfdp1`
>   - 指定监视的文件描述符范围是 `0` 到 `maxfdp1 - 1`。
>   - 通常，`maxfdp1` 是所有文件描述符中最大的一个加一。
> - `fd_set *readset`
>   - 指向一个文件描述符集合，表示需要监视是否有数据可读的文件描述符。
>   - 使用 `FD_ZERO`、`FD_SET`、`FD_CLR`、`FD_ISSET` 宏来操作这个集合。
> - `fd_set *writeset`
>   - 指向一个文件描述符集合，表示需要监视是否可以写入数据的文件描述符。
> - `fd_set *exceptset`
>   - 指向一个文件描述符集合，表示需要监视是否有异常情况（如带外数据）的文件描述符。
> - `const struct timeval *timeout`
>   - 指向一个 `timeval` 结构体，用于指定超时时间。
>   - `timeval` 结构体包含两个成员：
>     ```cpp
>     struct timeval {
>         long tv_sec; // seconds
>         long tv_usec; // microseconds
>     };
>     ```
>   - 如果 `timeout` 为 `NULL`，`select` 会一直阻塞，直到有文件描述符准备就绪。
>   - 如果 `timeout` 设置为零秒（`tv_sec` 和 `tv_usec` 都为 `0`），`select` 会立即返回，进行非阻塞检查。
>   - 如果 `timeout` 设置为一个有效的时间，`select` 会阻塞最多指定的时间。
>
> **返回值**
>
> - 成功时，返回就绪的文件描述符总数（可以是 `0`，表示超时）。
> - 失败时，返回 `-1` 并设置 `errno` 以指示错误类型。

**`FD` 宏定义**

> - `FD_ZERO(fd_set *set)`: 初始化文件描述符集合，将其清零。
> - `FD_SET(int fd, fd_set *set)`: 将文件描述符 `fd` 添加到集合 `set` 中。
> - `FD_CLR(int fd, fd_set *set)`: 从集合 `set` 中移除文件描述符 `fd`。
> - `FD_ISSET(int fd, fd_set *set)`: 检查文件描述符 `fd` 是否在集合 `set` 中，如果在则返回非零值。

**其他常用函数**

- `struct sockaddr_in`

  ```cpp
  struct sockaddr_in {
      short int sin_family;    // Address family (AF_INET for IPv4)
      unsigned short int sin_port;    // Port number
      struct in_addr sin_addr;    // Internet address
      unsigned char sin_zero[8];    // Padding to make struct the same size as struct sockaddr
  };
  ```

- `socket` 函数

  ```cpp
  int socket(int domain, int type, int protocol);
  ```

  - 创建一个新的套接字。
  - `domain`: 通信域（如 `AF_INET` 表示 IPv4 协议）。
  - `type`: 套接字类型（如 `SOCK_STREAM` 表示流式套接字）。
  - `protocol`: 协议（通常为 `0`，让系统选择适合的协议）。

- `setsockopt` 函数

  ```cpp
  int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
  ```

  - 设置套接字选项。

- `bind` 函数

  ```cpp
  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  ```

  - 将套接字绑定到一个地址和端口。

- `listen` 函数

  ```cpp
  int listen(int sockfd, int backlog);
  ```

  - 监听套接字上的连接请求。

- `accept` 函数

  ```cpp
  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  ```

  - 接受连接请求。

- `send` 函数

  ```cpp
  ssize_t send(int sockfd, const void *buf, size_t len, int flags);
  ```

  - 发送数据。

- `close` 函数

  ```cpp
  int close(int fd);
  ```

  - 关闭文件描述符。

- `read` 函数

  ```cpp
  ssize_t read(int fd, void *buf, size_t count);
  ```

  - 从文件描述符读取数据，返回读取的字节数。

- `connect` 函数
  ```cpp
  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  ```
  - 连接到服务器。

#### 3.1.2 示例代码

运行这个代码后，会按照以下步骤进行客户端和服务器之间的通信：

**服务器端**

1. **初始化和设置**：

   - 创建一个服务器 `socket` 文件描述符。
   - 设置 `socket` 选项以允许地址和端口重用。
   - 将 `socket` 绑定到特定的 IP 地址（`INADDR_ANY`表示任意本地地址）和端口（8080）。
   - 开始监听连接，最大连接数为 3。

2. **接受客户端连接**：

   - **阻塞并等待客户端连接**。
   - 一旦有客户端连接，接受连接并创建一个新的 `socket` 文件描述符。

3. **处理客户端通信**：
   - 在一个循环中使用 `select` 函数监视客户端 `socket` 文件描述符，检查是否有可读数据。
   - 如果有数据可读，读取数据并打印到控制台，然后将相同的数据发送回客户端。
   - 如果读取到的数据长度为 0，表示客户端断开连接，关闭客户端 `socket` 并跳出循环。

**客户端**

1. **初始化和设置**：

   - 创建一个客户端 `socket` 文件描述符。
   - 设置服务器的 IP 地址和端口号（127.0.0.1:8080）。

2. **连接到服务器**：

   - 尝试连接到服务器的指定地址和端口。
   - 如果连接失败，打印错误消息并退出。

3. **发送和接收数据**：
   - 发送一条消息（"Hello from client"）给服务器。
   - 等待接收服务器的回复。
   - 如果成功接收到数据，打印数据到控制台。
   - 如果读取到的数据长度为 0，表示服务器关闭连接。
   - 关闭客户端 `socket`。

- **预期的输出和行为**
  - 服务器端：
  ```sh
  $ ./server
  Received from client: Hello from client
  ```
  - 客户端：
  ```sh
  $ ./client
  Hello message sent
  Message from server: Hello from client
  ```

> **注意事项**
>
> - 服务器端在接收到客户端的数据并发送回去后，会继续等待客户端发送新数据。如果客户端没有发送新数据，服务器会继续阻塞在 `select` 调用中。
> - 客户端在接收到服务器的回复后，程序会终止。如果需要持续通信，可以将客户端逻辑改为在一个循环中发送和接收数据。
> - 如果希望更复杂的通信，比如支持多个客户端，可以在服务器端添加更多逻辑来处理多个客户端连接。
>
> 总的来说，这个代码实现了一个简单的客户端-服务器通信模型，客户端发送消息给服务器，服务器接收并原样发送回客户端，客户端显示收到的消息。两边都能正常处理消息并显示相应的输出。

```cpp
// server.cpp
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, new_socket; // 服务器socket文件描述符 和 新的socket文件描述符
  struct sockaddr_in address;     // 服务器地址 结构体
  int addrlen = sizeof(address);  // 地址长度
  char buffer[BUFFER_SIZE] = {0}; // 缓冲区

  fd_set readfds; // 读文件描述符集合

  // 创建socket文件描述符
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置socket选项
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听socket
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // 接受客户端连接
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  while (true) {
    FD_ZERO(&readfds);
    FD_SET(new_socket, &readfds);
    int activity = select(new_socket + 1, &readfds, NULL, NULL, NULL);

    if ((activity < 0) && (errno != EINTR)) { // 调用失败且不是中断
      perror("select error");
    }

    if (FD_ISSET(new_socket, &readfds)) { // 检查 new_socket 是否在 readfds 中
      int valread = read(new_socket, buffer, BUFFER_SIZE);
      if (valread > 0) {
        buffer[valread] = '\0';
        std::cout << "Received from client: " << buffer << std::endl;
        send(new_socket, buffer, valread, 0);
        memset(buffer, 0, BUFFER_SIZE);
      } else if (valread == 0) {
        std::cout << "Client disconnected" << std::endl;
        close(new_socket);
        break;
      } else {
        perror("read");
      }
    }
  }

  close(server_fd);
  return 0;
}
```

```cpp
// client.cpp
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock = 0, valread; // 客户端socket文件描述符 和 读取的字节数
  struct sockaddr_in serv_addr;            // 服务器地址 结构体
  char buffer[BUFFER_SIZE] = {0};          // 缓冲区
  const char *hello = "Hello from client"; // 发送给服务器的消息

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // 创建socket文件描述符
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;   // 设置地址族
  serv_addr.sin_port = htons(PORT); // 设置端口号

  // 转换IP地址
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported" << std::endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << std::endl;
    return -1;
  }

  send(sock, hello, strlen(hello), 0);
  std::cout << "Hello message sent" << std::endl;

  valread = read(sock, buffer, BUFFER_SIZE);
  if (valread > 0) {
    buffer[valread] = '\0';
    std::cout << "Message from server: " << buffer << std::endl;
  } else if (valread == 0) {
    std::cout << "Server closed the connection" << std::endl;
  } else {
    perror("read");
  }

  close(sock);
  return 0;
}
```

### 3.2 IO 多路复用之 `poll`

`poll` 的基本原理与 `select` 非常类似，但 `poll` 使用链表来存储文件描述符（`fd`），并且不会修改文件描述符。相比于 `select`，`poll` 提供了更多的事件类型，对文件描述符的重复利用率也更高。与 `select` 不同，`poll` 没有最大文件描述符数量的限制。

虽然 `poll` 和 `select` 的机制类似，都是通过轮询来管理多个描述符，根据描述符的状态进行处理，但它们都存在一个缺点：**包含大量文件描述符的数组会整体复制于用户态和内核的地址空间之间，无论这些文件描述符是否就绪**，这样的开销会随着文件描述符数量的增加而线性增大。

#### 3.2.1 `poll` 函数

> **函数原型**
>
> ```cpp
> #include <poll.h>
> int poll(struct pollfd *fds, nfds_t nfds, int timeout);
> ```

**参数**

- `struct pollfd *fds`
  - 指向一个 `pollfd` 结构体数组，用于指定被监视的文件描述符。
- `nfds_t nfds`
  - `fds` 数组的大小，即被监视的文件描述符数量。
- `int timeout`
  - 等待的毫秒数：
    - 负数表示无限超时，`poll` 会一直阻塞直到有指定事件发生。
    - `0` 表示 `poll` 调用立即返回并列出准备好 IO 的文件描述符。
    - 正数表示 `poll` 会阻塞最多指定的毫秒数。

**`pollfd` 结构体**

```cpp
struct pollfd {
    int fd;         /* 文件描述符 */
    short events;   /* 等待的事件 */
    short revents;  /* 实际发生的事件 */
};
```

- `fd`: 被监视的文件描述符。
- `events`: 由用户设置，表示要监视的事件类型。
- `revents`: 由内核设置，表示实际发生的事件类型。

**事件类型**

- `POLLIN`: 有数据可读。
- `POLLRDNORM`: 有普通数据可读。
- `POLLRDBAND`: 有优先数据可读。
- `POLLPRI`: 有紧迫数据可读。
- `POLLOUT`: 写数据不会导致阻塞。
- `POLLWRNORM`: 写普通数据不会导致阻塞。
- `POLLWRBAND`: 写优先数据不会导致阻塞。
- `POLLMSGSIGPOLL`: 消息可用。
- `POLLER`: 指定的文件描述符发生错误。
- `POLLHUP`: 指定的文件描述符挂起事件。
- `POLLNVAL`: 指定的文件描述符非法。

这些事件在 `events` 域中无意义，因为它们在合适的时候总是会从 `revents` 中返回。

使用 `poll` 和 `select` 不一样，不需要显式地请求异常情况报告。`POLLIN | POLLPRI` 等价于 `select` 的读事件，`POLLOUT | POLLWRBAND` 等价于 `select` 的写事件。`POLLIN` 等价于 `POLLRDNORM | POLLRDBAND`，而 `POLLOUT` 则等价于 `POLLWRNORM`。例如，要同时监视一个文件描述符是否可读和可写，可以设置 `events` 为 `POLLIN | POLLOUT`。在 `poll` 返回时，可以检查 `revents` 中的标志，对应于文件描述符请求的 `events` 结构体。如果 `POLLIN` 事件被设置，则文件描述符可以被读取而不阻塞。如果 `POLLOUT` 被设置，则文件描述符可以写入而不导致阻塞。这些标志并不是互斥的：它们可能被同时设置，表示这个文件描述符的读取和写入操作都会正常返回而不阻塞。

**返回值和错误代码**

成功时，`poll` 返回 `pollfd` 结构体中 `revents` 域不为 `0` 的文件描述符个数；如果在超时前没有任何事件发生，`poll` 返回 `0`；失败时，`poll` 返回 `-1` 并设置 `errno` 为下列值之一：

- `EBADF`: 一个或多个结构体中指定的文件描述符无效。
- `EFAULT`: `fds` 指针指向的地址超出进程的地址空间。
- `EINTR`: 请求的事件之前产生一个信号，调用可以重新发起。
- `EINVAL`: `nfds` 参数超出 `PLIMIT_NOFILE` 值。
- `ENOMEM`: 可用内存不足，无法完成请求。

#### 3.2.2 示例代码

**服务器**

1. 初始化和设置：

   - 创建一个服务器 `socket` 文件描述符。
   - 设置 `socket` 选项以允许地址和端口重用。
   - 将 `socket` 绑定到指定的 IP 地址和端口。
   - 开始监听连接。

2. 使用 `poll` 处理连接：

   - 创建一个 `pollfd` 结构体向量，用于存储所有需要监控的文件描述符。
   - 将服务器 `socket` 添加到 `pollfd` 结构体向量中。
   - 在主循环中使用 `poll` 函数等待文件描述符的事件。
   - 如果服务器 `socket` 有新的连接请求，接受新的连接并将新的客户端 `socket` 添加到 `pollfd` 结构体向量中。
   - 如果客户端 `socket` 有可读数据，读取数据并将其发送回客户端。如果客户端断开连接，关闭对应的 `socket` 并将其从 `pollfd` 结构体向量中移除。

**客户端**

1. 初始化和设置：

   - 创建一个客户端 `socket` 文件描述符。
   - 设置服务器的 IP 地址和端口号。

2. 连接到服务器：

   - 连接到服务器的指定地址和端口。
   - 如果连接失败，打印错误消息并退出。

3. 发送和接收数据：

   - 发送消息给服务器。
   - 接收服务器的回复并打印到控制台。
   - 关闭客户端 `socket`。

```cpp
// server.cpp
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE];

  // 创建socket文件描述符
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置socket选项
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听socket
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  std::vector<struct pollfd> poll_fds;
  poll_fds.push_back({server_fd, POLLIN, 0});

  while (true) {
    int activity = poll(poll_fds.data(), poll_fds.size(), -1);

    if (activity < 0) {
      perror("poll error");
      exit(EXIT_FAILURE);
    }

    if (poll_fds[0].revents & POLLIN) {
      // 接受新的客户端连接
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                               (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }

      std::cout << "New connection: socket fd is " << new_socket << std::endl;
      poll_fds.push_back({new_socket, POLLIN, 0});
    }

    for (size_t i = 1; i < poll_fds.size(); ++i) {
      if (poll_fds[i].revents & POLLIN) {
        int valread = read(poll_fds[i].fd, buffer, BUFFER_SIZE);
        if (valread > 0) {
          buffer[valread] = '\0';
          std::cout << "Received from client: " << buffer << std::endl;
          send(poll_fds[i].fd, buffer, valread, 0);
        } else if (valread == 0) {
          std::cout << "Client disconnected: socket fd is " << poll_fds[i].fd
                    << std::endl;
          close(poll_fds[i].fd);
          poll_fds.erase(poll_fds.begin() + i);
          --i;
        } else {
          perror("read");
        }
      }
    }
  }

  close(server_fd);
  return 0;
}
```

```cpp
// client.cpp
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE] = {0};
  const char *hello = "Hello from client";

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported" << std::endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << std::endl;
    return -1;
  }

  send(sock, hello, strlen(hello), 0);
  std::cout << "Hello message sent" << std::endl;

  valread = read(sock, buffer, BUFFER_SIZE);
  if (valread > 0) {
    buffer[valread] = '\0';
    std::cout << "Message from server: " << buffer << std::endl;
  } else if (valread == 0) {
    std::cout << "Server closed the connection" << std::endl;
  } else {
    perror("read");
  }

  close(sock);
  return 0;
}
```

### 3.3 IO 多路复用之 `epoll`

![20240617162510](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240617162510.png)

#### 3.3.1 `epoll` 提供的三个主要函数

1. `int epoll_create1(int flags)`：

   - 用于创建一个`epoll`实例，并返回一个文件描述符。
   - `flags`参数是一个位掩码，可以是 0 或者`EPOLL_CLOEXEC`。如果使用`EPOLL_CLOEXEC`标志，则`epoll`实例会在`exec`调用时自动关闭。
   - 如果成功，返回一个非负整数作为`epoll`实例的文件描述符；失败时返回-1，并设置`errno`。

2. `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)`：

   - 用于向`epoll`实例中添加、修改或删除事件。
   - `epfd`是`epoll`实例的文件描述符；`op`是操作类型，可以是`EPOLL_CTL_ADD`（添加事件）、`EPOLL_CTL_MOD`（修改事件）或`EPOLL_CTL_DEL`（删除事件）；`fd`是要操作的文件描述符；`event`是指向`epoll_event`结构体的指针，包含要关注的事件类型和相关数据。
   - 如果成功，返回 0；失败时返回-1，并设置`errno`。

3. `int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)`：
   - 用于等待事件的发生。
   - `epfd`是`epoll`实例的文件描述符；`events`是一个数组，用于存储发生的事件；`maxevents`是`events`数组的大小，表示最多可以存储多少个事件；`timeout`是超时时间，单位为毫秒，传入-1 表示阻塞直到有事件发生。
   - 函数会阻塞，直到有事件发生或超时。如果有事件发生，则将事件存储在`events`数组中，并返回发生事件的数量；如果超时，则返回 0；如果出错，则返回-1，并设置`errno`。

#### 3.3.2 `epoll` 的优势

1. **文件描述符数量没有限制**

   - `epoll` 对文件描述符的数量没有限制，因此最大数量与系统能够打开的文件描述符数量有关。

2. **不需要每次调用都从用户空间复制到内核**

   - `epoll` 不再需要每次调用都将 `fd_set` 复制到内核，这减少了内核与用户空间之间的数据传输开销。

3. **被动触发机制**

   - 与 `select` 和 `poll` 的主动轮询不同，`epoll` 采用被动触发的方式。为每个文件描述符注册相应的事件和回调函数，当数据准备好后，就会将就绪的文件描述符加入到就绪队列中。`epoll_wait` 的工作方式是查看这个就绪队列中是否有就绪的文件描述符，如果有，就唤醒等待者并调用回调函数。

4. **精准的文件描述符就绪通知**
   - `select` 和 `poll` 只能通知有文件描述符已经就绪，但无法知道具体哪个文件描述符就绪，因此需要主动轮询找到就绪的文件描述符。而 `epoll` 可以直接知道就绪的文件描述符编号，避免了不必要的轮询，提高了效率。

#### 3.3.3 `epoll` 的触发模式

1. **LT（水平触发）模式：内核数据没被读完，就会一直上报数据**

   - 当 `epoll_wait` 检查到描述符事件到达时，会通知进程。进程可以不立即处理该事件，下次调用 `epoll_wait` 时会再次通知进程。此模式是默认模式，支持阻塞和非阻塞操作。

2. **ET（边缘触发）模式：内核数据只上报一次**

   - 与 LT 模式不同，通知进程后，进程必须立即处理事件。下次调用 `epoll_wait` 时不会再得到事件通知。ET 模式减少了事件重复触发的次数，因此效率更高。此模式只支持非阻塞操作，以避免由于一个文件描述符的阻塞读/写操作导致处理多个文件描述符的任务被饿死。

> muduo 采用的是 LT

- 不会丢失数据或者消息
  - 应用没有读取完数据，内核是会不断上报的
- 低延迟处理
  - 每次读数据只需要一次系统调用；照顾了多个连接的公平性，不会因为某个连接上的数据量过大而影响其他连接处理消息
- 跨平台处理
  - 像 `select` 一样可以跨平台使用

#### 3.3.4 示例代码

```cpp
// epoll_server.cpp
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAX_EVENTS 10

int main() {
  int server_fd, new_socket;     // 服务器套接字和新连接套接字
  struct sockaddr_in address;    // 服务器地址
  int opt = 1;                   // 套接字选项
  int addrlen = sizeof(address); // 地址长度
  char buffer[1024] = {0};       // 用来存储客户端消息
  const char *hello = "Hello from server"; // 服务器消息

  // 创建套接字
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置套接字选项，允许重用地址和端口
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;         // 使用 IPv4 地址
  address.sin_addr.s_addr = INADDR_ANY; // 使用任意地址
  address.sin_port = htons(PORT);       // 设置端口号

  // 绑定套接字到端口
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听端口，最大连接数为 3
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int epoll_fd = epoll_create1(0); // 创建 epoll 实例
  if (epoll_fd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  struct epoll_event event, events[MAX_EVENTS]; // epoll 事件
  event.events = EPOLLIN;                       // 监听读事件
  event.data.fd = server_fd;                    // 监听服务器套接字

  // 将服务器套接字加入 epoll 事件中
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
    perror("epoll_ctl");
    exit(EXIT_FAILURE);
  }

  while (true) {
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (num_events == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_events; ++i) {
      if (events[i].data.fd == server_fd) {
        // 接受新连接
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0) {
          perror("accept");
          exit(EXIT_FAILURE);
        }

        // 将新连接加入 epoll 事件中
        event.events = EPOLLIN;
        event.data.fd = new_socket;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &event) == -1) {
          perror("epoll_ctl");
          exit(EXIT_FAILURE);
        }
      } else {
        // 处理客户端消息
        int valread = read(events[i].data.fd, buffer, 1024);
        if (valread == 0) {
          // 客户端断开连接，从 epoll 事件中删除，并关闭套接字
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
          close(events[i].data.fd);
        } else {
          // 回复客户端消息
          send(events[i].data.fd, hello, strlen(hello), 0);
        }
      }
    }
  }

  close(server_fd);
  return 0;
}
```

```cpp
// epoll_client.cpp
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_ADDR "127.0.0.1"

int main() {
  int sock = 0, valread;                   // 客户端套接字和读取的值
  struct sockaddr_in serv_addr;            // 服务器地址
  const char *hello = "Hello from client"; // 客户端消息
  char buffer[1024] = {0}; // 用来存储服务器返回的消息

  // 创建套接字
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "\nSocket creation error \n";
    return -1;
  }

  serv_addr.sin_family = AF_INET;   // 使用 IPv4 地址
  serv_addr.sin_port = htons(PORT); // 设置端口号

  // 将点分十进制的 IP 地址转换为网络字节序的二进制值
  if (inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr) <= 0) {
    std::cerr << "\nInvalid address/ Address not supported \n";
    return -1;
  }

  // 连接到服务器
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "\nConnection Failed \n";
    return -1;
  }

  // 发送消息到服务器
  send(sock, hello, strlen(hello), 0);
  std::cout << "Hello message sent\n";

  // 读取服务器返回的消息
  valread = read(sock, buffer, 1024);
  std::cout << "Message from server: " << buffer << std::endl;

  // 关闭套接字
  close(sock);
  return 0;
}
```

### 3.4 总结

#### 3.4.1 `select`、`poll` 和 `epoll` 的比较

**`select` 和 `poll` 的缺点**：

1. 单个进程能够监视的文件描述符的数量存在最大限制，通常是 1024，当然可以更改数量，但由于 `select` 采用轮询的方式扫描文件描述符，文件描述符数量越多，性能越差；在 linux 内核头文件中，有这样的定义：`#define __FD_SETSIZE 1024`
2. 内核 `/` 用户空间内存拷贝问题，`select` 需要复制大量的句柄数据结构，产生巨大的开销
3. `select` 返回的是含有整个句柄的数组，应用程序需要遍历整个数组才能发现哪些句柄发生了事件
4. `select` 的触发方式是水平触发，应用程序如果没有完成对一个已经就绪的文件描述符进行 IO 操作，那么之后每次 `select` 调用还是会将这些文件描述符通知进程

相比 `select` 模型，`poll` 使用链表保存文件描述符，因此没有了监视文件数量的限制，但其他三个缺点依然存在。

以 `select` 模型为例，假设服务器需要支持 100 万的并发连接，则在 `__FD_SETSIZE` 为 1024 的情况 下，至少需要开辟 1k 个进程才能实现 100 万的并发连接。除了进程间上下文切换的时间消耗外，从 内核/用户 空间大量的句柄结构内存拷贝、数组轮询等，是系统难以承受的。因此，基于 `select` 模型的服务器程序，要达到 100 万级别的并发访问，是一个很难完成的任务。

**`epoll` 原理以及优势**

`epoll` 的实现机制与 `select/poll` 机制完全不同，它们的缺点在 `epoll` 上不复存在。

**设想一下如下场景**：有 100 万个客户端同时与一个服务器进程保持着 TCP 连接。而每一时刻，通常只有几百上千个 TCP 连接是活跃的(事实上大部分场景都是这种情况)。如何实现这样的高并发?

在 `select/poll` 时代，服务器进程每次都把这 100 万个连接告诉操作系统(从用户态复制句柄数据结构到内核态)，让操作系统内核去查询这些套接字上是否有事件发生，轮询完成后，再将句柄数据复制到用户态，让服务器应用程序轮询处理已发生的网络事件，这一过程资源消耗较大，因此，`select/poll` 一般只能处理几千的并发连接。

`epoll` 的设计和实现与 `select` 完全不同。`epoll` 通过在 Linux 内核中申请一个简易的文件系统(文件系统一般用 B+ 树实现，磁盘 IO 消耗低，效率很高)。把原先的 `select/poll` 调用分成以下 3 个部分：

1. 调用 `epoll_create()` 建立一个 `epoll` 对象（在 `epoll` 文件系统中为这个句柄对象分配资源）
2. 调用 `epoll_ctl` 向 `epoll` 对象中添加这 100 万个连接的套接字
3. 调用 `epoll_wait` 收集发生的事件的 `fd` 资源

如此一来，要实现上面说是的场景，只需要在进程启动时建立一个 `epoll` 对象，然后在需要的时候向这个 `epoll` 对象中添加或者删除事件。同时，`epoll_wait` 的效率也非常高，因为调用 `epoll_wait` 时，并没有向操作系统复制这 100 万个连接的句柄数据，内核也不需要去遍历全部的连接。

`epoll_create` 在内核上创建的 `eventpoll` 结构如下:

```cpp
struct eventpoll {
  ....
  /*红黑树的根节点，这颗树中存储着所有添加到 epoll 中的需要监控的事件*/
  struct rb_root rbr;

  /*双链表中则存放着将要通过epoll_wait返回给用户的满足条件的事件*/
  struct list_head rdlist;
  ....
};
```

## 4 阻塞、非阻塞、同步、异步

一个典型的网络 IO 接口调用可以分为两个阶段：**数据准备和数据读写**

### 4.1 数据准备

#### 4.1.1 阻塞

在阻塞 IO 中，调用 IO 方法的线程会一直等待，直到数据准备就绪。这意味着线程会被阻塞，不能执行其他任务。常见的阻塞 IO 函数调用如下：

```cpp
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
int size = recv(fd, buf, 1024, 0);
```

#### 4.1.2 非阻塞

在非阻塞 IO 中，调用 IO 方法的线程不会等待数据准备就绪，而是立即返回。线程可以继续执行其他任务，**并通过返回值判断数据是否已经准备好**。如果数据未准备好，通常会返回一个特定的错误码（例如`EAGAIN`或`EWOULDBLOCK`）。

### 4.2 数据读写

#### 4.2.1 同步

> **通过 `man recv` 查看相关函数的文档**

同步 IO 表示数据的读写操作是由调用者（请求方）自己来完成的，无论是阻塞还是非阻塞。在同步 IO 中，调用者必须等待数据读写操作的完成。

#### 4.2.2 异步

> **通过 `man aio_read` 和 `man air_write` 查看相关函数的文档**

异步 IO 则是调用者发出请求后，可以立即继续执行其他任务，不需要等待数据读写操作完成。当数据准备好或读写操作完成后，会通过回调函数、信号等方式通知调用者。异步 IO 通常需要特殊的 API 支持，例如`aio_read`和`aio_write`。

**陈硕大神原话：在处理 IO 的时候，阻塞和非阻塞都是同步 IO。只有使用了特殊的 API 才是异步 IO**

![20240616171557](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616171557.png)

### 4.3 四种 IO 模型

- 同步阻塞 IO
- 同步非阻塞 IO
- 异步阻塞 IO
- 异步非阻塞 IO

Node.js 采用的是异步非阻塞 IO 模型，这是一种典型的 IO 模型。

```cpp
/****************** 同步阻塞 *****************/

// 在同步阻塞模型中，线程会等待数据准备好，然后进行数据读写操作。
// 这是最简单的模型，也是最常见的 IO 操作方式。
int size = recv(fd, buf, 1024, 0); // 阻塞等待数据


/****************** 同步非阻塞 *****************/

// 在同步非阻塞模型中，线程不会等待数据准备好，而是立即返回。
// 并通过轮询或其他机制检查数据是否准备好。
int flags = fcntl(fd, F_GETFL, 0);
fcntl(fd, F_SETFL, flags | O_NONBLOCK);

int size = recv(fd, buf, 1024, 0);
if (size == -1 && errno == EAGAIN) {
    // 数据未准备好，稍后再试
}


/****************** 异步阻塞 *****************/

// 虽然概念上存在，但实际上异步阻塞组合是矛盾的，因为异步操作本质上应该是非阻塞的。
// 异步 IO 意味着调用者不会等待数据准备或读写操作的完成。


/****************** 异步非阻塞 *****************/

// 在异步非阻塞模型中，调用者发出 IO 请求后立即返回，不等待数据读写操作的完成。
// 当操作完成后，通过回调或信号通知调用者。
struct aiocb cb;
cb.aio_fildes = fd;
cb.aio_buf = buf;
cb.aio_nbytes = 1024;
cb.aio_offset = 0;
cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
cb.aio_sigevent.sigev_signo = SIGUSR1;

// 发出异步读请求
aio_read(&cb);

// 处理其他逻辑，等待读写操作完成的通知
```

## 5 Unix/Linux 上的五种 IO 模型

### 5.1 阻塞 blocking

![20240616171924](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616171924.png)

### 5.2 非阻塞 non-blocking

```cpp
int opt = 1;
setsockopt(sockfd, SOL_SOCKET, SO_NONBLOCK, &opt, sizeof(opt));
```

![20240616171956](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616171956.png)

### 5.3 IO 复用（IO multiplexing）

在 IO 复用模型中，使用 `select`、`poll` 或 `epoll` 等系统调用，可以同时监视多个文件描述符，当其中一个或多个文件描述符准备好时，通知应用程序进行处理。这种模型常用于处理高并发连接。

![20240616172046](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616172046.png)

### 5.4 信号驱动(signal-driven)

在信号驱动 IO 模型中，应用程序为文件描述符设置信号驱动模式，当数据准备好时，内核会向应用程序发送信号，通知其进行数据处理。应用程序不需要频繁轮询。

设置信号驱动模式：

```cpp
fcntl(sockfd, F_SETFL, O_ASYNC);
signal(SIGIO, signal_handler);
```

![20240616172109](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616172109.png)

内核在第一个阶段是异步，在第二个阶段是同步；与非阻塞 IO 的区别在于它提供了消息通知机制，不需要用户进程不断的轮询检查，减少了系统 API 的调用次数，提高了效率。

### 5.5 异步(asynchronous)

在异步 IO 模型中，应用程序发起 IO 请求后立即返回，内核会在数据准备好并完成读写操作后，**通过回调函数或信号通知应用程序**。应用程序可以在等待 IO 完成的同时执行其他任务。

定义异步 IO 控制块：

```cpp
struct aiocb {
  int aio_fildes;             // 文件描述符
  off_t aio_offset;           // 偏移量
  volatile void *aio_buf;     // 缓冲区
  size_t aio_nbytes;          // 传输字节数
  int aio_reqprio;            // 请求优先级
  struct sigevent aio_sigevent; // 信号事件
  int aio_lio_opcode;         // 操作码
};
```

![20240616172210](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616172210.png)

## 6 好的网络服务器设计

在这个多核时代，服务端网络编程如何选择线程模型呢? 赞同 _libev_ 作者的观点：_one loop per thread is usually a good model_，这样多线程服务端编程的问题就转换为如何设计一个高效且易于使 用的 `event loop`，然后每个线程 **_run_** 一个 `event loop` 就行了(当然线程间的同步、互斥少不了，还有其它的耗时事件需要起另外的线程来做)。

`event loop` 是 `non-blocking` 网络编程的核心，在现实生活中，**`non-blocking` 几乎总是和 `IO-multiplexing` 一起使用**，原因有两点:

- 没有人真的会用轮询 (`busy-pooling`) 来检查某个 `non-blocking` IO 操作是否完成，这样太浪费 CPU 资源了。
- `IO-multiplex` 一般不能和 `blocking` IO 用在一起，因为 `blocking` IO 中 `read()/write()/accept()/connect()` 都有可能阻塞当前线程，这样线程就没办法处理其他 socket 上的 IO 事件了。

所以，当我们提到 `non-blocking` 的时候，实际上指的是 `non-blocking` + `IO-multiplexing`，单用其中任何一个都没有办法很好的实现功能。

---

> `epoll` + `fork` 不如 `epoll` + `pthread`?

强大的 nginx 服务器采用了 `epoll` + `fork` 模型作为网络模块的架构设计，实现了简单好用的负载算法，使各个 `fork` 网络进程不会忙的越忙、闲的越闲，并且通过引入一把乐观锁解决了该模型导致的**服务器惊群**现象，功能十分强大。

## 7 Reactor 模型

Reactor 设计模式是一种用于处理服务请求的事件处理模式，它能够并发地处理来自一个或多个输入的服务请求。服务处理器（service handler）对传入的请求进行多路分解（demultiplexing），并将它们同步分派给相关的请求处理器（request handlers）。

### 7.1 重要组件

1. **Event（事件）**: 代表一个需要处理的操作，比如读取数据、写入数据或处理连接请求。
2. **Reactor（反应堆）**: 核心组件，负责等待并分发事件给相应的事件处理器。
3. **Demultiplexer（事件分发器）**: 一种多路分解机制，通常是操作系统提供的功能（如`select`、`poll`、`epoll`），用来监视多个事件源并将就绪的事件通知给 Reactor。
4. **Event Handler（事件处理器）**: 处理具体事件的逻辑组件，每个事件类型都有一个对应的事件处理器。

![20240616173348](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616173348.png)

### 7.2 Reactor 模型工作流程

1. **事件注册**: 应用程序将需要监视的事件注册到 Reactor 中。
2. **事件等待**: Reactor 使用事件分发器（如`epoll`）等待事件的发生。
3. **事件分派**: 当一个或多个事件发生时，事件分发器将它们通知 Reactor。
4. **事件处理**: Reactor 将这些事件分派给相应的事件处理器进行处理。

### 7.3 单线程 Reactor 模型

在单线程 Reactor 模型中，Reactor 和所有事件处理器都在一个线程中运行。适用于处理连接数量较少且每个连接处理时间较短的场景。

### 7.4 多线程 Reactor 模型

在多线程 Reactor 模型中，Reactor 运行在一个线程中，事件处理器运行在多个工作线程中。这种模型适用于处理大量连接或每个连接处理时间较长的场景。

### 7.5 Muduo 库中的 Multiple Reactors 模型

![Muduo库的Multiple Reactors模型](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240616173428.png)

**主要特点**

1. **主 Reactor**: 负责接收新连接，并将连接分发给子 Reactor。
2. **子 Reactor**: 负责处理已建立连接的读写事件。
3. **线程池**: 主 Reactor 和多个子 Reactor 各自运行在独立的线程中，子 Reactor 通过线程池进行管理。

**工作流程**

1. **主 Reactor**: 主线程运行主 Reactor，接收新连接并将连接分派给子 Reactor。
2. **子 Reactor**: 每个子 Reactor 运行在一个独立的线程中，处理具体的读写事件。
3. **线程池**: 线程池管理多个子 Reactor 的线程，实现高并发处理。

通过这种模型，Muduo 库能够高效地处理大规模并发连接，适用于高性能服务器的开发。

## 9 `muduo` 网络库的核心代码模块

### 9.1 Channel

fd、events、revents、callbacks
两种 channel
listenfd-acceptorChannel
connfd-connectionChannel

### 9.2 Poller 和 EPollPoller - Demultiplex

`std::unordered*map<int, Channel*> channels`

### 9.3 EventLoop - Reactor

```cpp
ChannelList activeChannels*;
std::unique*ptr poller*;
int wakeupFd -> loop;
std::unique_ptr wakeupChannel;
```

### 9.4 Thread 和 EventLoopThread

### 9.5 EventLoopThreadPool

`getNextLoop()`：通过轮询算法获取下一个 `subloop` `baseLoop`
一个 `thread` 对应一个 `loop` => one loop per thread

### 9.6 Socket

### 9.7 Acceptor

主要封装了 `listenfd` 相关的操作 socket bind listen baseLoop

### 9.8 Buffer

缓冲区 应用写数据 -> 缓冲区 -> Tcp 发送缓冲区 -> send
prependable readeridx writeridx

### 9.9 TcpConnection

一个连接成功的客户端对应一个 TcpConnection Socket Channel 各种回调 发送和接收缓冲区

### 9.10 TcpServer

Acceptor EventLoopThreadPool
ConnectionMap connections\_;

## 10 扩展

1. TcpClient 编写客户端类
2. 支持定时事件 TimerQueue 链表/队列 时间轮(libevent) nginx 定时器(红黑树)
3. DNS、HTTP、RPC
4. 丰富的使用示例 examples 目录
5. 服务器性能测试 - QPS 涉及 linux 上进程 socketfd 的设置相关
   - wrk linux 上，需要单独编译安装 只能测试 http 服务的性能
   - Jmeter JDK Jmeter 测试 http 服务 tcp 服务 生成聚合报告
