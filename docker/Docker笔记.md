- [1 初识 docker](#1-初识-docker)
  - [1.1 安装 docker](#11-安装-docker)
  - [1.2 更新用户组](#12-更新用户组)
  - [1.3 镜像加速](#13-镜像加速)
- [2 Docker 命令](#2-docker-命令)
  - [2.1 镜像相关命令](#21-镜像相关命令)
  - [2.2 容器相关命令](#22-容器相关命令)
  - [2.3 容器网络与端口相关命令](#23-容器网络与端口相关命令)
  - [2.4 Docker 导入导出相关命令](#24-docker-导入导出相关命令)
- [3 Docker 容器的数据卷](#3-docker-容器的数据卷)
  - [3.1 数据卷的概念和作用](#31-数据卷的概念和作用)
  - [3.2 配置数据卷](#32-配置数据卷)
  - [3.3 数据卷容器](#33-数据卷容器)
    - [3.3.1 配置数据卷容器](#331-配置数据卷容器)
- [4 Docker 的应用部署](#4-docker-的应用部署)
  - [4.1 MySQL 部署](#41-mysql-部署)
- [5 DockerFile](#5-dockerfile)
  - [5.1 Docker 镜像原理](#51-docker-镜像原理)
    - [5.1.1 Linux 文件系统](#511-linux-文件系统)
    - [5.1.2 Docker 镜像](#512-docker-镜像)
  - [5.2 Docker 镜像制作](#52-docker-镜像制作)
    - [5.2.1 容器转为镜像](#521-容器转为镜像)
    - [5.2.2 Dockerfile](#522-dockerfile)
      - [5.2.2.1 Dockerfile 概念](#5221-dockerfile-概念)
      - [5.2.2.2 自定义 Ubuntu](#5222-自定义-ubuntu)
- [6 服务编排](#6-服务编排)
  - [6.1 服务编排的概念](#61-服务编排的概念)
  - [6.2 Docker Compose](#62-docker-compose)
    - [6.2.1 Docker Compose 的安装](#621-docker-compose-的安装)
    - [6.2.2 Docker Compose 的使用](#622-docker-compose-的使用)
      - [6.2.2.1 编排 开机自启动 ssh 服务的 Ubuntu 系统](#6221-编排-开机自启动-ssh-服务的-ubuntu-系统)
      - [6.2.2.2 编排 Ubuntu + MySQL](#6222-编排-ubuntu--mysql)
- [7 docker compose 相关命令](#7-docker-compose-相关命令)
- [8 Docker 私有仓库](#8-docker-私有仓库)
  - [8.1 私有仓库搭建](#81-私有仓库搭建)
  - [8.2 将镜像上传至私有仓库](#82-将镜像上传至私有仓库)
  - [8.3 从私有仓库拉取镜像](#83-从私有仓库拉取镜像)


# 1 初识 docker
## 1.1 安装 docker
```shell
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh --mirror Aliyun    # 其中--mirror Aliyun为可选
```

- 弹窗如下：
![98009494d24e4163004a06f208c1aed](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/98009494d24e4163004a06f208c1aed.png)

- [WSL 2 上的 Docker 远程容器入门](https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-containers)

> Desktop版本占用空间过大，但可以应用到所有的系统，包括windows系统。不建议使用。

## 1.2 更新用户组
```bash
sudo groupadd docker     #添加docker用户组
sudo gpasswd -a $USER docker     #将登陆用户加入到docker用户组中
newgrp docker     #更新用户组
docker ps    #测试docker命令是否可以不使用sudo正常使用
```

## 1.3 镜像加速

直接使用阿里云的镜像加速，[容器镜像服务/镜像加速器](https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors)

![20240426132543](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240426132543.png)

修改 `daemon` 配置文件 `/etc/docker/daemon.json` 来使用加速器
```bash
sudo mkdir -p /etc/docker
sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://vkfhxzlo.mirror.aliyuncs.com"]
}
EOF
sudo systemctl daemon-reload
sudo systemctl restart docker
```

# 2 Docker 命令
## 2.1 镜像相关命令
- `docker images`: 列出本地所有镜像。
- `docker search <image_name>`: 在 Docker Hub 上搜索镜像。
- `docker pull <image_name>`: 下载镜像到本地。
- `docker rmi <image_name>`: 删除本地的镜像。
- `docker images -q`: 列出所有镜像的 ID。
- `docker rmi \`docker images -q\``: 删除所有本地的镜像。
- `docker build -t <image_name> <path_to_dockerfile>`: 根据 Dockerfile 构建镜像。

## 2.2 容器相关命令
- `docker run <options> <image_name>`: 创建容器。

例如：`docker run -d -it --name kodbox -p 10080:80 -v /data/docker/kodbox:/var/www/html --restart=always tznb/kodbox:1.15`
   - `-d`: 表示在后台运行容器。在这种模式下，容器将在后台启动并运行，而不会将输出显示到终端。这对于需要长时间运行的容器或不需要与容器进行交互的情况非常有用。
   - `-i`: 表示以交互模式运行容器。在这种模式下，容器的标准输入（STDIN）将连接到终端，可以直接与容器内运行的程序进行交互。这对于调试容器或需要从容器内输入数据的情况非常有用。
   - `-t`: 表示分配一个伪终端给容器。这意味着容器将拥有自己的终端，可以使用 `docker attach` 命令附加到该终端并与之交互。
   - `-it` 创建的容器一般称为**交互式容器**。
   - `-id` 创建的容器一般称为**守护式容器**。
   - `--name kodbox` 或者 `--name=kodbox`: 用于指定容器的名称为 "kodbox"。
   - `-p 10080:80`: 这个选项指定将容器的 80 端口映射到主机的 10080 端口。这样，通过访问 `http://localhost:10080`，你就可以访问到容器内部的 Web 服务。
   - `-v /data/docker/kodbox:/var/www/html`: 这个选项用于将主机上的 `/data/docker/kodbox` 目录挂载到容器内的 `/var/www/html` 目录。
   - `--restart` 参数用于指定容器的重启策略。这对于需要在容器退出后自动重启容器的情况非常有用。**以下是一些有效的 `--restart` 值：**
      - `no`：容器在退出后不会重启。这是默认值。
      - `on-failure`：容器在非正常退出时（退出状态非 0）才会重启。
      - `always`：容器在退出时总是重启。
      - `unless-stopped`：容器在退出时总是重启，但不会考虑在 Docker 守护进程启动时就已经停止的容器。
   - `tznb/kodbox:1.15`: 这是要运行的 Docker 镜像的名称及标签。在这里使用的是 `tznb/kodbox` 镜像的版本标签为 `1.15`。

- `docker ps`: 列出正在运行的容器。
- `docker ps -a`: 列出所有容器，包括停止的。
- `docker ps -aq`: 列出所有容器的 ID。
- `docker exec`: 在运行的容器中执行命令。它允许以交互模式或非交互模式运行命令，**并可以设置环境变量和工作目录。**
- `docker stop <container_id_or_name>`: 停止运行中的容器。
- `docker start <container_id_or_name>`: 启动已经停止的容器。
- `docker restart <container_id_or_name>`: 重启容器。
- `docker rm <container_id_or_name>`: 删除停止的容器。
- `docker rm /`docker ps -aq`/`: 删除所有容器。
- `docker inspect <container_id_or_name>`: 查看容器的详细信息
- `docker logs <container_id_or_name>`: 查看容器的日志。
- `docker stats`: 查看容器的资源占用情况。
- `docker stats <container_id_or_name>`: 查看指定容器的资源占用情况。


## 2.3 容器网络与端口相关命令
- `docker network ls`: 列出 Docker 网络。
- `docker port <container_id_or_name>`: 显示容器的端口映射。
- `docker inspect <container_id_or_name>`: 查看容器的详细信息，包括网络配置。

## 2.4 Docker 导入导出相关命令
- `docker commit <container_id> <image_name:tag>`: 将容器保存为镜像。**数据卷不会被保存**。
- `docker save -o <image_name>.tar <image_name:tag>`: 将镜像保存为压缩文件。
- `docker load -i <image_name>.tar`: 从压缩文件导入镜像。

- `docker export <container_id> -o <container_name>.tar`: 将容器保存为压缩文件。
- `docker import <container_name>.tar <image_name:tag>`: 从压缩文件导入容器。

# 3 Docker 容器的数据卷
## 3.1 数据卷的概念和作用

- **数据卷是宿主机中的一个目录或文件**

- **一个数据卷可以被多个容器挂载**

**作用：**

- 容器数据持久化

- 外部机器和容器间接通信

- 容器之间数据交换

## 3.2 配置数据卷

- 创建容器时，使用 `-v` 参数设置数据卷
```bash
docker run ... -v 宿主机目录（文件）:容器内目录（文件） ...
```

- 注意事项：
   - **目录必须是绝对路径**
   - 如果目录不存在，**会自动创建**
   - 可以挂载多个数据卷

## 3.3 数据卷容器

对于多容器进行数据交换，当容器很多时，这将会变得很复杂，每次都需要单独挂载数据卷。**此时可以使用数据卷容器**。

- 创建一个容器，挂在一个目录，让其他容器继承自该容器（`--volume-from`）
- 数据卷容器挂掉，不会影响其他容器

![20240426144017](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240426144017.png)

### 3.3.1 配置数据卷容器

1. 创建启动 `c3` 数据卷容器，使用 `-v` 参数设置数据卷
```bash
docker run -it --name=c3 -v /volume centos:7 /bin/bash
```

docker 会自动创建一个目录作为`/volume`的`soure`，并将其挂载到容器的`/volume`目录下。

2. 创建启动 `c1, c2` 容器，使用 `--volumes-from` 参数设置数据卷容器
```bash
docker run -it --name=c1 --volumes-from c3 centos:7 /bin/bash

docker run -it --name=c2 --volumes-from c3 centos:7 /bin/bash
```

此时，`c1, c2` 容器就可以共享`c3`数据卷容器的数据卷。**此时 `c3` 挂掉也不会影响 `c1, c2` 容器的数据卷**。详细原因可以通过 `docker inspect` 查看。

# 4 Docker 的应用部署
## 4.1 MySQL 部署

在 Docker 容器中部署 MySQL，并通过外部 mysql 客户端操作 MySQL Server。

```bash
docker pull mysql

mkdir -p ~/mysql
cd ~/mysql

docker run -id \
-p 3307:3306 \
--name=c_mysql \
-v $PWD/conf:/etc/mysql/conf.d \
-v $PWD/logs:/logs \
-v $PWD/data:/var/lib/mysql \
-e MYSQL_ROOT_PASSWORD=123456 \
mysql
```

`-e` 是 `--env` 的缩写，用于设置环境变量。

- 进入容器：`docker exec -it c_mysql /bin/bash`

- 连接 MySQL：`mysql -uroot -p123456`

# 5 DockerFile

## 5.1 Docker 镜像原理

### 5.1.1 Linux 文件系统

Linux 文件系统由 bootfs 和 rootfs 两部分组成
- bootfs：包含 bootloader(引导加载程序) 和 kernel(内核)

- rootfs：root 文件系统，包含的就是典型 Linux 系统中的 /dev, /proc, /bin, /etc 等标准目录和文件

- 不同的 Linux 发行版，rootfs 的内容会有所不同，但是 bootfs 基本是不变的

<img src="https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240426162030.png" alt="20240426162030" width="50%" height="auto">

### 5.1.2 Docker 镜像

- Docker 镜像是由特殊的文件系统叠加而成

- 最底端是 bootfs，并使用宿主机的 bootfs

- 第二层是 root 文件系统 rootfs，称为 base image

- 然后再往上可以叠加其他的镜像文件

- 统一文件系统（Union File System）技术能够将不同的层整合成一个文件系统，为这些层提供一个统一的视角，这样就隐藏了多层的存在，在用户的角度看来，只存在一个文件系统

- **一个镜像可以放在另一个镜像的上面**。位于下面的镜像称为父镜像，最底部的镜像称为基础镜像

- 当从一个镜像启动容器时，Docker 会在最顶层加载一个读写文件系统作为容器

![20240426164545](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240426164545.png)

1. Docker 镜像的本质是什么？
   - 是一个分层文件系统
2. Docker 中的一个 centos 镜像为什么只有 200 MB，而一个 Centos 操作系统的 iso 文件要几个 G？
   -  Centos 的 iso 镜像文件包含 bootfs 和 rootfs，而 Docker 的 centos 镜像复用操作系统的 bootfs，只有 rootfs 和其他镜像层
3. Docker 中的一个 tomcat 镜像为什么有 500 MB，而一个 tomcat 安装包只有 70 多 MB？
   - 由于 docker 中镜像是分层的，tomcat 虽然只有 70 多 MB，但他需要依赖父镜像和基础镜像，所以整个对外暴露的 tomcat 镜像大小 500 多 MB

> 可以通过 `docker inspect` 查看镜像的详细信息，是分层的，而且下载的时候也是一层一层下载的

## 5.2 Docker 镜像制作

### 5.2.1 容器转为镜像

1. 制作镜像：`docker commit 容器id 镜像名称:版本号`

> 其中的挂载目录（数据卷）不会被保存

2. 镜像转为压缩文件：`docker save -o 压缩文件名称 镜像名称:版本号`

3. 压缩文件转为镜像：`docker load -i 压缩文件名称`


### 5.2.2 Dockerfile

#### 5.2.2.1 Dockerfile 概念
- Dockerfile 是一个文本文件
- 包含了一条条的指令
- 每一条指令构建一层，基于基础镜像，最终构建出一个新的镜像
- 对于开发人员：可以为开发团队提供一个完全一致的开发环境
- 对于测试人员：可以直接拿开发时所构建的镜像或者通过 Dockerfile 文件构建一个新的镜像开始工作了
- 对于运维人员：在部署时，可以实现应用的无缝移植

**直接去读 hub.docker.com 的 Dockerfile 文件**

| 关键字 | 作用 | 备注 |
| :--- | :--- | :--- |
| `FROM` | 指定父镜像 | 指定 `dockerfile` 基于哪个 `image` 构建 |
| `MAINTAINER` | 作者信息 | 用来标明这个 `dockerfile` 谁写的 |
| `LABEL` | 标签 | 用来标明 `dockerfile` 的标签，可以使用 `Label` 代替 `Maintainer`，最终都是在 `docker image` 基本信息中可以查看 |
| `RUN` | 执行命令 | 执行一段命令，默认是 `/bin/sh`，格式：`RUN command` 或者 `RUN ["command","param1","param2"]` |
| `CMD` | 容器启动命令 | 提供启动容器时的默认命令，和 `ENTRYPOINT` 配合使用。格式：`CMD command param1 param2` 或者 `CMD['command','param1','param2']`|
| `ENTRYPOINT` | 入口 | 一般在制作一些执行就关闭的容器中会使用 |
| `COPY` | 复制文件 | `build` 的时候复制文件到 `image` 中 |
| `ADD` | 添加文件 | `build` 的时候添加文件到 `image` 中，不仅局限于当前 `build` 上下文，可以来源于远程服务 |
| `ENV` | 环境变量 | 指定 `build` 时的环境变量，可以在启动的容器时通过 `-e` 覆盖，格式：`ENV name=value` |
| `ARG` | 构建参数 | 只在构建的时候使用的参数，如果有 `ENV`，那么 `ENV` 的相同名字的值始终覆盖 `ARG` 的参数 |
| `VOLUME` | 定义外部可以挂载的数据卷 | 指定 `build` 的 `image` 那些目录，可以启动的时候挂载到文件系统中，启动容器的时候使用 `-v` 绑定。格式：`VOLUME["目录"]` |
| `EXPOSE` | 暴露端口 | 定义容器运行的时候监听的端口，启动容器的时候使用 `-p` 来绑定。格式：`EXPOSE 8080` 或者 `EXPOSE 8080/udp` |
| `WORKDIR` | 工作目录 | 指定容器内部的工作目录，如果没有创建则自动创建，如果指定 `/`，使用的是绝对地址，如果不是 `/` 开头，那么是在上一条 `WORKDIR` 的路径的相对路径 |
| `USER` | 指定执行用户 | 指定 `build` 或者启动的时候的用户，在 `RUN CMD ENTRYPOINT` 执行的时候的用户 |
| `HEALTHCHECK` | 健康检查 | 指定监测当前容器的健康监测的命令，基本上没用，因为很多时候，应用本身有健康监测机制 |
| `ONBUILD` | 触发器 | 当存在 `ONBUILD` 关键字的镜像作为基础镜像的时候，当执行 `FROM` 完成之后，会执行 `ONBUILD` 的命令，但是不影响当前镜像，用处也不怎么大 |
| `STOPSIGNAL` | 发送信号量到宿主机 | 该 `STOPSIGNAL` 指令设置将发送到容器的系统调用信号以退出 |
| `SHELL` | 指定执行脚本的 `shell` | 指定 `RUN CMD ENTRYPOINT` 执行命令的时候使用的 `shell` |

#### 5.2.2.2 自定义 Ubuntu

- 自定义 Ubuntu 22.04 镜像
   - 安装 vim, build-essential, gdb, cmake, openssh-server
   - 定义作者信息：corner，tag 为 1.0
   - 开启 ssh，**并设置开机自启动**，允许 root 密码登录，并设置密码为 1
   - 共享 /root/project 目录，并设置为工作目录
   - 端口转发 20022:22

本地创建 **start_ssh.sh**
```sh
#!/bin/bash
 
LOGTIME=$(date "+%Y-%m-%d %H:%M:%S")
echo "[$LOGTIME] startup run..." >>/root/start_ssh.log
service ssh start >>/root/start_ssh.log
```

本地创建**bashrc**文件
```bash

# startup run
if [ -f /root/start_ssh.sh ]; then
    . /root/start_ssh.sh
fi
```

**Dockerfile**

```Dockerfile
# 使用 Ubuntu 22.04 镜像作为基础镜像
FROM ubuntu:22.04

# 定义作者信息
LABEL author="corner" version="1.0"

# 工作目录
WORKDIR /root/project

# 安装所需软件包
RUN apt update && \
   DEBIAN_FRONTEND=noninteractive apt-get install -y \
   vim \
   build-essential \
   gdb \
   cmake \
   openssh-server

# ssh，允许 root 密码登录，并设置密码为 1
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
   sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
   echo 'root:1' | chpasswd

# 拷贝 ssh 启动脚本
COPY start_ssh.sh /root/start_ssh.sh

# 增加可执行权限
RUN chmod +x /root/start_ssh.sh

# 写追加到 .bashrc 文件
ADD bashrc /root/bashrc  
RUN echo "$(cat /root/bashrc)" >> /root/.bashrc
RUN rm -f /root/bashrc

# 默认启动 /bin/bash
CMD ["/bin/bash"]
```

1. 构建镜像：`docker build -t custom_ubuntu .`
2. 创建容器：`docker run -p 20022:22 -v /home/corner/project:/root/project -d custom_ubuntu`

开机自启动是很麻烦的一个操作，共以下三种方案

- `docker run ... --privileged=true ...` 就可以使用 `systemd` 了，**亲测没用**

- `init` 脚本开机自启（未尝试）

- 写一个启动脚本，将脚本运行写入 `.bashrc` 中
  - 需要运行的服务在 `/etc/init.d/` 目录下，使用 `service` 命令启动，或者 `/etc/init.d/xxx start` 启动，这些文件有 `{start|stop|reload|force-reload|restart|try-restart|status}` 方法

# 6 服务编排

## 6.1 服务编排的概念

- 微服务架构的应用系统中一般包含若干个微服务，每个微服务一般都会部署多个实例，如果每个微服务都要手动启停，维护的工作量会很大。
   - 要从 *Dockerfile build image* 或者 *dockerhub* 拉取 *image*
   - 要创建多个 *container*
   - 要管理这些 *container*（启动、停止、删除）

**服务编排：按照一定的业务规则批量管理容器**

## 6.2 Docker Compose

[Docker Compose 快速入门](https://docs.docker.com/compose/gettingstarted/)

*Docker Compose* 是一个编排多容器分布式部署的工具，提供命令集管理容器化应用的完整开发周期，包括服务构建，启动和停止。使用步骤：

1. 利用 *Dockerfile* 定义运行环境镜像
2. 使用 `docker-compose.yml` 定义组成应用的各服务
3. 运行 `docker-compose up` 启动应用

![20240426202205](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240426202205.png)

### 6.2.1 Docker Compose 的[安装](https://docs.docker.com/compose/install/linux/)

**按照 1.1 安装 Docker 的方式安装之后，Docker Compose 也会一起安装。**

查看版本：`docker compose version`

### 6.2.2 Docker Compose 的使用

- 一般会将**网络信息，端口映射，数据卷挂载**等信息写入 `docker-compose.yml` 文件中，然后通过 `docker-compose up` 启动应用。

**注意**

- 新版本 `docker compose` 不需要指定 `version`。

- 注意要写 `tty: true`，否则容器启动后立即退出。

#### 6.2.2.1 编排 开机自启动 ssh 服务的 Ubuntu 系统
在 **5.2.2.2 的基础上**，添加 `docker-compose.yml` 文件

```yml
services:
  ubuntu:
    tty: true # docker run -t 不加会导致容器启动后立即退出
    build:
      context: ./ubuntu
      dockerfile: Dockerfile
    ports:
      - "20022:22"
    volumes:
      - ~/project:/root/project
```

#### 6.2.2.2 编排 Ubuntu + MySQL

- 使用 dockerfile 自定义 Ubuntu 22.04 镜像
  - `ubuntu/Dockerfile`，**参照 5.2.2.2**
    - 使用 Ubuntu 22.04 镜像作为基础镜像
    - 安装 `vim, build-essential, gdb, cmake, openssh-server`
    - 开启 ssh，并设置开机自启动，允许 root 密码登录，并设置密码为 1
    - 设置 `/root/project` 为工作目录
    - 默认启动 `/bin/bash`
  - `compose.yaml`
    - ubuntu 的 `/root/project` 目录挂载到本地的 `~/project` 目录
    - ubuntu 的 端口转发 `20022:22`
    - 使用 mysql latest 镜像作为基础镜像
    - 设置 mysql root 密码为 1
    - mysql 的 端口转发 `23306:3306`
    - `mysql` 数据库的数据目录挂载到本地的 `~/mysql/data` 目录
    - `mysql` 配置文件挂载到本地的 `~/mysql/conf` 目录
    - `mysql` 日志文件挂载到本地的 `~/mysql/logs` 目录
    - `ubuntu` 和 `mysql` 使用同一个网络

**docker-compose.yml**

```yaml
services:
  ubuntu:
    tty: true # docker run -t
    build:
      context: ./ubuntu
      dockerfile: Dockerfile
    ports:
      - "20022:22"
    volumes:
      - ~/project:/root/project
    networks:
      - my_network

  mysql:
    image: mysql:latest
    ports:
      - "23306:3306"
    environment:
      MYSQL_ROOT_PASSWORD: 1
    volumes:
      - ~/project/mysql/data:/var/lib/mysql
      - ~/project/mysql/conf:/etc/mysql/conf.d
      - ~/project/mysql/logs:/var/log/mysql
    networks:
      - my_network

networks:
  my_network:
```

# 7 docker compose 相关命令

命令格式：`docker compose [OPTIONS] COMMAND`

```bash
Options:
      --compatibility              以向后兼容模式运行compose
  -f, --file stringArray           Compose配置文件
  -p, --project-name string        项目名称

Commands:
  build       构建或重新构建服务
  cp          在服务容器和本地文件系统之间复制文件/文件夹
  create      为服务创建容器
  down        停止和删除容器、网络
  exec        在运行中的容器中执行命令
  images      列出由创建的容器使用的镜像
  logs        查看容器的输出
  ls          列出运行中的compose项目
  port        打印端口绑定的公共端口
  ps          列出容器
  restart     重启服务容器
  rm          移除已停止的服务容器
  run         在服务上运行一次性命令
  start       启动服务
  stats       显示容器的资源使用统计信息的实时流
  stop        停止服务
  top         显示运行中的进程
  unpause     恢复服务
  up          创建并启动容器
  version     显示Docker Compose的版本信息
```

# 8 Docker 私有仓库

> 一般要单独拿一台做私有仓库，不要和其他服务混合在一起

## 8.1 私有仓库搭建

```bash
# 1. 拉取私有仓库镜像
docker pull registry

# 2. 启动私有仓库容器
docker run -id --name=registry -p 5000:5000 registry

# 3. 打开浏览器 输入地址 http://私有仓库服务器ip:5000/v2/_catalog，看到{"repositories":[]}表示私有仓库搭建成功

# 4. 修改 daemon.json
vim /etc/docker/daemon.json

# 在上述文件中添加一个 key, 保存退出。此步用于让 docker 信任私有仓库地址；注意将私有仓库服务器 ip 修改为自己私有仓库服务器真实 ip
{
  "insecure-registries": ["私有仓库服务器ip:5000"]
}

# 5. 重启 docker 服务
systemctl restart docker
docker start registry
```

## 8.2 将镜像上传至私有仓库

```bash
# 1. 标记镜像为私有仓库的镜像
docker tag centos:7 私有仓库服务器ip:5000/centos:7

# 2. 上传标记的镜像
docker push 私有仓库服务器ip:5000/centos:7
```

## 8.3 从私有仓库拉取镜像

```bash
# 从私有仓库拉取镜像
docker pull 私有仓库服务器ip:5000/centos:7
```