- [1 三块核心内容](#1-三块核心内容)
  - [1.1 进程的虚拟地址空间内存划分和布局](#11-进程的虚拟地址空间内存划分和布局)
  - [1.2 函数调用堆栈详细过程](#12-函数调用堆栈详细过程)
  - [1.3 程序编译链接原理](#13-程序编译链接原理)
- [2 基础部分](#2-基础部分)
  - [2.1 new/delete, malloc/free](#21-newdelete-mallocfree)
  - [2.2 引用和指针](#22-引用和指针)
  - [2.3 const, 指针和引用的结合](#23-const-指针和引用的结合)
    - [2.3.1 const 理解](#231-const-理解)
    - [2.3.2 const 和指针的结合](#232-const-和指针的结合)
    - [2.3.3 const, 指针, 引用相结合](#233-const-指针-引用相结合)
  - [2.4 函数重载, inline函数, 参数带默认值的函数](#24-函数重载-inline函数-参数带默认值的函数)
  - [2.5 函数模板](#25-函数模板)
- [3 面向对象](#3-面向对象)
  - [3.1 this 指针](#31-this-指针)
  - [3.2 对象深构造和浅构造](#32-对象深构造和浅构造)
  - [3.3 对象的声明周期，对象的应用优化](#33-对象的声明周期对象的应用优化)
  - [3.4 带右值引用参数的拷贝构造和operator=](#34-带右值引用参数的拷贝构造和operator)
  - [3.5 普通，static，const三类成员方法](#35-普通staticconst三类成员方法)
  - [3.6 OOP思想，面向对象语言特征描述](#36-oop思想面向对象语言特征描述)
- [4 模板](#4-模板)
  - [4.1 函数模板和类模板](#41-函数模板和类模板)
  - [4.2 vector容器模板实现](#42-vector容器模板实现)
  - [4.3 容器空间配置器allocator](#43-容器空间配置器allocator)
  - [4.4 SGI STL二级空间配置器allocator和内存池实现原理](#44-sgi-stl二级空间配置器allocator和内存池实现原理)
- [5 运算符重载](#5-运算符重载)
  - [5.1 string 类](#51-string-类)
  - [5.2 容器迭代器 iterator](#52-容器迭代器-iterator)
  - [5.3 智能指针](#53-智能指针)
  - [5.4 operator new 和 operator delete](#54-operator-new-和-operator-delete)
- [6 STL](#6-stl)
  - [6.1 顺序容器](#61-顺序容器)
  - [6.2 适配器](#62-适配器)
  - [6.3 有序关联容器](#63-有序关联容器)
  - [6.4 无序关联容器](#64-无序关联容器)
  - [6.5 大数据 top k和查重问题求解、布隆过滤器](#65-大数据-top-k和查重问题求解布隆过滤器)
  - [6.6 函数对象、function和 lambda表达式](#66-函数对象function和-lambda表达式)
  - [6.7 迭代器](#67-迭代器)
  - [6.8 泛型算法](#68-泛型算法)
- [7 继承与多态](#7-继承与多态)
  - [7.1 静态绑定和动态绑定](#71-静态绑定和动态绑定)
  - [7.2 多态](#72-多态)
  - [7.3 vfptr和vftable、vbptr和vbtable](#73-vfptr和vftablevbptr和vbtable)
  - [7.4 抽象类和虚基类](#74-抽象类和虚基类)
  - [7.5 四种类型强转](#75-四种类型强转)
- [8 C++11](#8-c11)
  - [8.1 auto、foreach、智能指针、lambda表达式](#81-autoforeach智能指针lambda表达式)
  - [8.2 右值引用、std::move移动语义、std::forward类型完美转发](#82-右值引用stdmove移动语义stdforward类型完美转发)
  - [8.3 std::thread线程池、线程互斥操作、线程同步通信操作](#83-stdthread线程池线程互斥操作线程同步通信操作)


# 1 三块核心内容

- [《深入理解计算机系统》第 7 章 链接 笔记](https://github.com/Corner430/study-notes/blob/main/cpp/深入理解计算机系统笔记.md)

- [《程序员的自我修养》第 2, 3, 4, 6, 10章](https://github.com/Corner430/study-notes/blob/main/cpp/程序员的自我修养笔记.md) 

## 1.1 进程的虚拟地址空间内存划分和布局

![20240506093458](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240506093458.png)

![20240505222654](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240505222654.png)

- `.text`(代码段): 已编译程序的机器代码
- `.rodata`(read only): **只读数据**，比如 `printf` 语句中的格式串和开关语句的跳转表
- `.data`: **已初始化的全局和静态 C 变量。局部 C 变量在运行时被保存在栈中**，既不在 `.data` 也不在 `.bss` 中
- `.bss`: **未初始化的全局和静态 C 变量，以及所有被初始化为 0 的全局或静态变量**。不需要占用实际的磁盘空间

> 每一个进程的用户空间是私有的，但是内核空间是共享的。进程之间的通信方式之一匿名管道通信就是用的这个特性

```cpp
#include <iostream>

using namespace std;

int gdata1 = 10; // .data
int gdata2 = 0;  // .bss
int gdata3;      // .bss

static int gdata4 = 11; // .data
static int gdata5 = 0;  // .bss
static int gdata6;      // .bss

int main() {    // .text
  int a = 12;   // 这三个局部变量产生的是 MOV 指令，在 .text 段，运行时，12 被加载到栈上
  int b = 0;
  int c;

  static int e = 13; // .data
  static int f = 0;  // .bss
  static int g;      // .bss
  return 0;     // .text
}
```

> 此时 `c` 一定不为 0，因为它是栈上的无效值，`g` 一定是 0，因为它是 `.bss` 段的变量

## 1.2 函数调用堆栈详细过程

- 参见《程序员的自我修养》第 10 章 内存
- 参见《深入理解计算机系统》7.8 ~ 7.9

![20240506132537](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240506132537.png)

## 1.3 程序编译链接原理

![20240506122507](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240506122507.png)


![1714977376306](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/1714977376306.jpg)



```cpp
// sum.cpp
int gdata = 10; // gdata .data

int sum(int a, int b) { // sum_int_int
    return a + b;
}

// ------------------
// main.cpp
// 引用 sum.cpp文件里面定义的全局变量 以及 函数
extern int gdata;   // gdata *UND*
int sum(int, int);  // sum *UND*

int data = 20;      // data .data

int main(){         // main .text
  int a = gdata;
  int b = data;

  int ret = sum(a, b);

  return 0;
}
```


```shell
# 1. 分别进行编译
g++ -c sum.cpp -g # 得到 sum.o 文件
g++ -c main.cpp -g # 得到 main.o 文件

# 2 符号表
objdump -t main.o
objdump -t sum.o

# 输出如下
main.o:     file format elf64-x86-64

SYMBOL TABLE:
000000000000 main.cpp
0000000000000000 l    d  .text  0000000000000000 .text00000000000000 l    df *ABS*  000000
0000000000000000 g     O .data  0000000000000004 data
0000000000000000 g     F .text  0000000000000033 main
0000000000000000         *UND*  0000000000000000 gdata
0000000000000000         *UND*  0000000000000000 _Z3sumii

#--------------------

sum.o:     file format elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 sum.cpp
0000000000000000 l    d  .text  0000000000000000 .text
0000000000000000 g     O .data  0000000000000004 gdata
0000000000000000 g     F .text  0000000000000014 _Z3sumii

# -------------

# 3 查看 ELF 可重定位目标文件
readelf -h main.o

# 输出如下：
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          600 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         12
  Section header string table index: 11

# ------------------
# 4 查看符号表
objdump -s main.o

# 输出如下：
main.o:     file format elf64-x86-64

Contents of section .text:
 0000 554889e5 4883ec10 8b050000 00008945  UH..H..........E
 0010 fc8b0500 00000089 45f88b55 f88b45fc  ........E..U..E.
 0020 89d689c7 e8000000 008945f4 b8000000  ..........E.....
 0030 00c9c3                               ...             
Contents of section .data:
 0000 14000000                             ....            
Contents of section .comment:
 0000 00474343 3a202844 65626961 6e203132  .GCC: (Debian 12
 0010 2e322e30 2d313429 2031322e 322e3000  .2.0-14) 12.2.0.
Contents of section .eh_frame:
 0000 14000000 00000000 017a5200 01781001  .........zR..x..
 0010 1b0c0708 90010000 1c000000 1c000000  ................
 0020 00000000 33000000 00410e10 8602430d  ....3....A....C.
 0030 066e0c07 08000000                    .n......  

#--------------------------------
# 5 查看所有的段
readelf -S main.o

# 输出如下:
There are 12 section headers, starting at offset 0x258:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000033  0000000000000000  AX       0     0     1
  [ 2] .rela.text        RELA             0000000000000000  00000198
       0000000000000048  0000000000000018   I       9     1     8
  [ 3] .data             PROGBITS         0000000000000000  00000074
       0000000000000004  0000000000000000  WA       0     0     4
  [ 4] .bss              NOBITS           0000000000000000  00000078
       0000000000000000  0000000000000000  WA       0     0     1
  [ 5] .comment          PROGBITS         0000000000000000  00000078
       0000000000000020  0000000000000001  MS       0     0     1
  [ 6] .note.GNU-stack   PROGBITS         0000000000000000  00000098
       0000000000000000  0000000000000000           0     0     1
  [ 7] .eh_frame         PROGBITS         0000000000000000  00000098
       0000000000000038  0000000000000000   A       0     0     8
  [ 8] .rela.eh_frame    RELA             0000000000000000  000001e0
       0000000000000018  0000000000000018   I       9     7     8
  [ 9] .symtab           SYMTAB           0000000000000000  000000d0
       00000000000000a8  0000000000000018          10     3     8
  [10] .strtab           STRTAB           0000000000000000  00000178
       000000000000001e  0000000000000000           0     0     1
  [11] .shstrtab         STRTAB           0000000000000000  000001f8
       0000000000000059  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), l (large), p (processor specific)

#----------------------
# 6 查看汇编代码
objdump -S main.o

# 输出如下：
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
extern int gdata;
int sum(int, int);

int data = 20;

int main(){
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   48 83 ec 10             sub    $0x10,%rsp
  int a = gdata;
   8:   8b 05 00 00 00 00       mov    0x0(%rip),%eax        # e <main+0xe>
   e:   89 45 fc                mov    %eax,-0x4(%rbp)
  int b = data;
  11:   8b 05 00 00 00 00       mov    0x0(%rip),%eax        # 17 <main+0x17>
  17:   89 45 f8                mov    %eax,-0x8(%rbp)

  int ret = sum(a, b);
  1a:   8b 55 f8                mov    -0x8(%rbp),%edx
  1d:   8b 45 fc                mov    -0x4(%rbp),%eax
  20:   89 d6                   mov    %edx,%esi
  22:   89 c7                   mov    %eax,%edi
  24:   e8 00 00 00 00          call   29 <main+0x29>
  29:   89 45 f4                mov    %eax,-0xc(%rbp)

  return 0;
  2c:   b8 00 00 00 00          mov    $0x0,%eax
  31:   c9                      leave
  32:   c3                      ret

#----------------------
# 7 链接
ld -e main *.o

# 查看 a.out 符号表
objdump -t a.out

# 输出如下：
a.out:     file format elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*  0000000000000000 main.cpp
0000000000000000 l    df *ABS*  0000000000000000 sum.cpp
0000000000401033 g     F .text  0000000000000014 _Z3sumii
0000000000403008 g       .data  0000000000000000 __bss_start
0000000000403000 g     O .data  0000000000000004 data
0000000000401000 g     F .text  0000000000000033 main
0000000000403004 g     O .data  0000000000000004 gdata
0000000000403008 g       .data  0000000000000000 _edata
0000000000403008 g       .data  0000000000000000 _end

#----------------------
# 8 查看 a.out 的汇编代码
objdump -S a.out
```

------------

# 2 基础部分

## 2.1 new/delete, malloc/free

- `malloc` 和 `free`, 称作 C 的库函数
- `new` 和 `delete`, 称作 C++ 的运算符

```cpp
#include <stdlib.h>

int main() {
  int *p = (int *)malloc(sizeof(int));

  // malloc 开辟内存失败，是通过返回值为 `NULL` 来判断的，而 `new`
  // 开辟内存失败，是通过抛出异常来判断的
  if (p == nullptr) {
    return -1;
  }

  *p = 20;
  free(p);

  // new 不仅可以做内存开辟，可以做内存初始化操作
  int *p1 = new int(20);
  delete p1;

  int *q = (int *)malloc(sizeof(int) * 20);
  if (q == nullptr) {
    return -1;
  }
  free(q);

  // int *q1 = new int[20]; // 不初始化，下面的会初始化为 0
  int *q1 = new int[20]();
  delete[] q1;

  return 0;
}
```

**面试问题**

```cpp
int main(){
  // new 有多少种?
  int *p1 = new int(20);

  int *p2 = new (nothrow) int;

  const int *p3 = new const int(40);

  // 定位 new
  int data = 0;
  int *p3 = new (&data) int(50);  // new 指定内存地址
}
```


## 2.2 引用和指针

**引用和指针的区别？**

1. 引用是一种更安全的指针
2. 引用只有一级引用，没有多级引用；指针可以有一级指针，也可以有多级指针
3. 定义一个引用变量和定义一个指针变量，其汇编指令时一模一样的；通过引用变量修改所引用内存的值和通过指针解引用修改指针指向的内存的值，其底层指令也是一摸一样的

**右值引用**

1. `int &&c = 20;` 专门用来引用右值类型，指令上，可以自动产生临时量，然后直接引用临时量 `c = 40;`
2. 右值引用变量本身是一个左值，不能用左值引用来引用它
3. 不能用一个右值引用变量，来引用一个左值

```cpp
int main() {
  int a = 10;
  int *p = &a;

  // 引用是必须初始化的，指针可以不初始化
  int &b = a;
  // int &c = 20; 是不合法的

  *p = 20;
  cout << a << " " << *p << " " << b << endl; // 20 20 20

  b = 30;
  cout << a << " " << *p << " " << b << endl; // 30 30 30

  // 通过 visual studio 的反汇编可以看到上面两种方式没有区别

// ------------------------
  int array[5] = {};
  int *p = array;
  
  // 定义一个引用变量，来引用 array 数组
  int(&q)[5] = array;

  cout << sizeof(array) << endl;  // 20
  cout << sizeof(p) << endl;  // 8
  cout << sizeof(q) << endl;  // 20

// ----------------------------
  int a = 10; // 左值，它有名字，有名字，值可以修改的
  int &b = a;

  // int &c  = 20; // 20 是右值：没内存，没名字
  const int &d = 20; // 等价 int temp = 20; int &d = temp;

  // C++11 提供了右值引用，汇编同上面的 const
  int &&c = 20;
  c = 30; // 但可以修改

  int &e = c; // 一个右值引用变量，本身是一个左值

  return 0;
}
```

## 2.3 const, 指针和引用的结合

### 2.3.1 const 理解

`const` 修饰的变量不能够再作为左值！！！初始化完成后，值不能被修改！！！

**C 和 C++ 中 `const` 的区别是什么？**

- `const` 的编译方式不同，c中，`const` 就是当作一个变量来编译生成指令的。C++ 中，所有出现 `const` 常量名字的地方，**都被常量的初始化替换了**！！！
- `cpp` 中初始化可以不用立即数，例如 `const int a = b;`, 编译时所有的 `a` 用 `b` 替换

```c
// c 中的 const
int main(){
  // const 修饰的常变量，可以不用初始化
  const int a;

  // 通过指针修改常变量的值
  int *p = (int *)&a;
  *p = 30;
  printf("%d %d %d \n", a, *p, *(&a));  // 30 30 30
}
```

```cpp
int main() {
  // c++ 中的 const 必须要初始化
  const int a = 20;
  int arr[a] = {}; // 这也是合法的  等价 int arr[20] = {};

  int *p = (int *)&a;
  *p = 30;  // 已经改了这片内存的值

  // 会把 a 直接替换成 20 去编译
  printf("%d %d %d \n", a, *p, *(&a));  // 20 30 20

  return 0;
}
```

### 2.3.2 const 和指针的结合

**`const` 修饰的量 叫常量**

和普通变量的区别是：
- 编译方式不同
- 不能作为左值

`const` 修饰的量常出现的错误是：
1. 常量不能再作为左值
2. 不能把常量的地址泄露给一个普通的指针或者普通的引用变量


### 2.3.3 const, 指针, 引用相结合

```cpp
int main(){
  // 写一句代码，在内存的 0x0018ff44 处写一个 4 字节的 10
  int *const &p = (int *)0x0018ff44;

// ----------------------------------

  int a = 10;
  int *p = &a;
  // const int *&q = p; // 不能这样写，因为 p 是一个int *, q 是一个 const int *
  int *&q = p; // 等价于 int **q = &p; 

// --------------------------------
  int a = 10;
  int *const p = &a;
  int *&q = p; // 这是错误的，不能把const
               // 修饰的指针泄露给别的指针，这样就可以间接修改const内容了
  // 把上一句可以转成 int **q = *p; 来分析

// ---------------------------------
  int a = 10;
  const int *p = &a;
  int *&q = p;  // 也是错误的
  // 分析: int **q = *p; int ** <= const int **

// ---------------------------------
  int a = 10;
  int *p = &a;
  const int *&q = p;  // 错误
  // const int **q = &p; // const int** <= int**

  return 0;
}
```


## 2.4 函数重载, inline函数, 参数带默认值的函数

## 2.5 函数模板

--------------

# 3 面向对象

## 3.1 this 指针

## 3.2 对象深构造和浅构造

## 3.3 对象的声明周期，对象的应用优化

## 3.4 带右值引用参数的拷贝构造和operator=

## 3.5 普通，static，const三类成员方法

## 3.6 OOP思想，面向对象语言特征描述


---------------

# 4 模板

## 4.1 函数模板和类模板

## 4.2 vector容器模板实现

## 4.3 容器空间配置器allocator

## 4.4 SGI STL二级空间配置器allocator和内存池实现原理


--------------------

# 5 运算符重载

## 5.1 string 类

## 5.2 容器迭代器 iterator

## 5.3 智能指针

## 5.4 operator new 和 operator delete

-----------------

# 6 STL

## 6.1 顺序容器

- `vector`
- `deque`
- `list`

## 6.2 适配器

- `stack`
- `queue`
- `priority_queue`

## 6.3 有序关联容器

- `set/multiset`
- `map/multimap`

## 6.4 无序关联容器

- `unordered_set/unordered_multiset`
- `unordered_map/unordered_multimap`

## 6.5 大数据 top k和查重问题求解、布隆过滤器

## 6.6 函数对象、function和 lambda表达式

## 6.7 迭代器

## 6.8 泛型算法

---------------

# 7 继承与多态

## 7.1 静态绑定和动态绑定

## 7.2 多态

## 7.3 vfptr和vftable、vbptr和vbtable

## 7.4 抽象类和虚基类

## 7.5 四种类型强转

-------------------

# 8 C++11

## 8.1 auto、foreach、智能指针、lambda表达式

## 8.2 右值引用、std::move移动语义、std::forward类型完美转发

## 8.3 std::thread线程池、线程互斥操作、线程同步通信操作