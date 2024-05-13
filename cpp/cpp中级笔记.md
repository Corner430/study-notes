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
      - [2.3.2.1 const 和一级指针的结合](#2321-const-和一级指针的结合)
      - [2.3.2.2 总结 `const` 和一级指针的类型转换公式：](#2322-总结-const-和一级指针的类型转换公式)
      - [2.3.2.3 const 和 二级指针的结合](#2323-const-和-二级指针的结合)
      - [2.3.2.4 应用（面试题）](#2324-应用面试题)
      - [2.3.2.5 总结 `const` 和二级指针的类型转换公式：](#2325-总结-const-和二级指针的类型转换公式)
    - [2.3.3 const, 指针, 引用相结合](#233-const-指针-引用相结合)
  - [2.4 函数重载, inline函数, 参数带默认值的函数](#24-函数重载-inline函数-参数带默认值的函数)
    - [2.4.1 函数重载](#241-函数重载)
    - [2.4.2 C++ 和 C 语言代码之间如果互相调用？](#242-c-和-c-语言代码之间如果互相调用)
      - [2.4.2.1 C++ 调用 C](#2421-c-调用-c)
      - [2.4.2.2 C 调用 C++](#2422-c-调用-c)
      - [2.4.2.3 面试题](#2423-面试题)
    - [2.4.3 inline 函数](#243-inline-函数)
    - [2.4.4 参数带默认值的函数](#244-参数带默认值的函数)
- [3 面向对象](#3-面向对象)
  - [3.1 this 指针](#31-this-指针)
  - [3.2 对象构造和深浅拷贝](#32-对象构造和深浅拷贝)
  - [3.3 初始化列表](#33-初始化列表)
  - [3.4 普通，static，const三类成员方法](#34-普通staticconst三类成员方法)
  - [3.5 指向类成员（成员变量和成员方法）的指针](#35-指向类成员成员变量和成员方法的指针)
- [4 模板](#4-模板)
  - [4.1 函数模板和类模板](#41-函数模板和类模板)
    - [4.1.1 函数模板](#411-函数模板)
    - [4.1.2 类模板](#412-类模板)
  - [4.2 容器空间配置器allocator](#42-容器空间配置器allocator)
    - [4.2.1 allocator 解决的问题](#421-allocator-解决的问题)
    - [4.2.2 容器空间配置器 allocator 的使用](#422-容器空间配置器-allocator-的使用)
    - [4.2.3 RAII(Resource Acquisition Is Initialization, 资源获取即初始化)](#423-raiiresource-acquisition-is-initialization-资源获取即初始化)
    - [4.2.4 三法则和零法则](#424-三法则和零法则)
    - [4.2.6 vector 容器的实现](#426-vector-容器的实现)
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
1. 常量不能再作为左值 <= 直接修改常量的值
2. 不能把常量的地址泄露给一个普通的指针或者普通的引用变量 <= 可以间接修改常量的值

#### 2.3.2.1 const 和一级指针的结合

**共两种情况**

**C++ 的语言规范：`const` 修饰的是离它最近的类型**

```cpp
// 距离const最近的是 int, 所以后面的 *p 是常量表达式

const int *p; // => *p = 20; 是错误的.  p = &b; 是正确的

int const *p; // 同上

// -------------------------

// 距离 const 最近的是 int *, 所以后面的 p 是常量表达式

int * const p;  // => p = &b; 是错误的. *p = 20; 是正确的

const int *const p; // p 和 *p 都不可以修改

// -------------------------------
// 示例 1
int main(){
  const int a = 10;
  // int *p = &a;  // 错误
  const int *p = &a;  // 正确, 因为 *p 是常量表达式
  // int *const p = &a;  // 错误, 因为 p 是常量表达式, 而 *p 不是
}

// -------------------------------
// 示例 2
int main() {
  int a = 10;
  int *p1 = &a;
  const int *p2 = &a; // 这是合法的 const int * <= int *
  int *const p3 = &a; // 这是合法的 int * <= int * , 此处原因参见示例 3
  
  int *p4 = p3; // int * <= int * , 原因同上
  return 0;
}

// -------------------------------
// 示例 3
int main() {
  int *q1 = nullptr;

  // const 如果右边没有指针 * 的话，const 是不参与类型的, 这里作用是不能让 q2 当作左值传给二级指针
  int *const q2 = nullptr;
  cout << typeid(q1).name() << endl;  // int *
  cout << typeid(q2).name() << endl;  // int *

  return 0;
}

// 示例 4 （面试题）
int main() {
  int a = 10;
  cosnt int *p = &a;
  int *q = p; // int * <= const int *
  // 问：q 指向 a, a 可以改动，有什么问题？
  // 答：这和 a 没关系，你就是去掉 a 那一行，让 p 指 nullptr, 这也一样不行
}
```

#### 2.3.2.2 总结 `const` 和一级指针的类型转换公式：

```cpp
int *    <=     const int * // 错误
const int *     <=      int * // 正确

int ** <= int * const * // 错误
int * const * <= int ** // 正确
```

#### 2.3.2.3 const 和 二级指针的结合

**共三种情况**

```cpp
const int **q;  // const 最近的类型是 int, 那么 修饰的常量表达式是 **q

int *const* q;  // const 最近的类型是 int *, 那么 修饰的常量表达式是 *q

int **const q;  // const 最近的类型是 int **, 那么 修饰的常量表达式是 q
```


```cpp
int main() {
  int a = 10;
  int *p = &a;
  const int **q = &p;  // const int ** <= int ** 错误, 同样的和 a 没关系 , 原因如下: 
  /*
  const int **q = &p;
    *q <=> p    // 这是一块内存
    const int b = 20;
    *q = &b;    // const int * <= const int *
    这就把 p 指向了 b, 这样就可以通过 p 间接修改 b 的值了
  */
   
  // 改为 const int *p = &a; 就是正确的
  // 或者改为 const int *const *q = &p; 也是正确的
  return 0;
}
```


#### 2.3.2.4 应用（面试题）

1. 选择错误的代码

```cpp
// A.
int a = 10;
const int *p = &a;
int *q = p;

// 分析：int * <= const int * // 错误

// B.
int a = 10;
int *const p = &a;
int *q = p;

// 分析：int * <= int * // 正确

// C.
int a = 10;
int *const p = &a;
int *const q = p;

// 分析：int * <= int * // 正确

// D.
int a = 10;
int *const p = &a;
const int *q = p;

// 分析：const int * <= int * // 正确
```

2. 选择错误的代码

```cpp
// A.
int a = 10;
int *p = &a;        // int * <= int *
const int **q = &p; // const int ** <= int **         错误

// B.
int a = 10;
int *p = &a;          // int * <= int *
int *const *q = &p;   // int * const * <= int **  等价于 const * <= int *       正确

// C.
int a = 10;
int *p = &a;
int **const q = &p;  // int ** <= int **  正确

// D.
int a = 10;
int *const p = &a;  // int * <= int *
int **q = &p;       // int ** <= int * const *  等价于 int * <= const int *  错误

// E.
int a = 10;
const int *p = &a;    // const int * <= int *
int *const *q = &p;   // int * const * <= const int **

// 两步分析
// 1. const * <= int *  正确
// 2. int * <= const int *  错误
```


#### 2.3.2.5 总结 `const` 和二级指针的类型转换公式：

```cpp
int ** <= const int ** // 错误
const int ** <= int ** // 错误
```

**两边必须都要有 `const`**

### 2.3.3 const, 指针, 引用相结合

```cpp
int main(){
  // 写一句代码，在内存的 0x0018ff44 处写一个 4 字节的 10
  int *p = (int *)0x0018ff44;
  int *&&p = (int *)0x0018ff44;
  int *const &p = (int *)0x0018ff44;

// ----------------------------------

  int a = 10;
  int *p = &a;
  int *&q = p; // 等价于 int **q = &p; 
  // const int *&q = p; // 等价于 const int **q = &p;   const int ** = int **   错误

// --------------------------------
  int a = 10;
  int *const p = &a;
  int *&q = p; // 等价于 int **q = &p;
              // int ** <= int * const * 等价于 int * <= const *  错误
      // *q 会修改 p 的值

// ---------------------------------
  int a = 10;
  const int *p = &a;
  int *&q = p;  // int ** <= const int **  错误

// ---------------------------------
  int a = 10;
  int *p = &a;
  const int *&q = p;  // const int ** <= int **  错误

  return 0;
}
```

## 2.4 函数重载, inline函数, 参数带默认值的函数

### 2.4.1 函数重载

1. 为什么 C++ 支持函数重载，而 C 不支持？
  - C++ 代码产生函数符号的时候，函数名+参数列表类型组成的！
  - C 代码产生函数符号的时候，函数名来决定！
2. 函数重载需要注意些什么？
  - **作用域**, 如果有局部的函数声明，就不会再调用外部其它参数类型的重载，就会覆盖！！！**一组函数要称得上重载，一定先是处在同一个作用域当中的**
  - `const` 或者 `volatile` 修饰的参数，如何影响形参类型？
    ```cpp
    #include<typeinfo>
    int a = 10;
    const int b = 10;
    cout << typeid(a).name() << endl;  // int
    cout << typeid(b).name() << endl;  // int
    ```
### 2.4.2 C++ 和 C 语言代码之间如果互相调用？

**在 CPP 源码中，把 C 函数的声明放在 `extern "C"` 里面**

> C 编译器不识别 `extern`

#### 2.4.2.1 C++ 调用 C

***main.cpp***

```cpp
#include <iostream>

using namespace std;

int sum(int a, int b);    // *UND* _Z3sumii

int main() {
  int ret = sum(10, 20);
  cout << "ret: " << ret << endl;
  return 0;
}
```

***test.c***
```c
int sum(int a, int b) { // .text  sum
  return a + b;
}
```

如果得到链接错误，无法解析的外部符号，是因为各自编译时候，产生的符号不一样，C++ 产生的符号是 `_Z3sumii`，而 C 产生的符号是 `sum`，所以需要在 C++ 文件中通过 `extren "C"` 关键字声明一下 `sum` 函数

```cpp
extern "C" {
  int sum(int a, int b);
}
```

#### 2.4.2.2 C 调用 C++

***main.c***

```c
#include <stdio.h>

int sum(int, int);  // UND sum

int main() {
  int ret = sum(10, 20);
  printf("ret: %d\n", ret);
  return 0;
}
```

***test.cpp***

```cpp
extern "C" {
int sum(int a, int b) { // .text  sum_int_int
  return a + b;
}
}
```

#### 2.4.2.3 面试题

```cpp
#ifdef __cplusplus
extern "C" {
#endif

int sum(int a, int b) { return a + b; }

#ifdef __cplusplus
}
#endif

/*
只要是 C++ 编译器，都内置 __cplusplus 宏定义

如果是 C 编译器，没有 __cplusplus 宏定义

只要是 C++ 编译器进行编译，就会把 sum 函数放在 extern "C" 里面，更加灵活
*/
```

### 2.4.3 inline 函数

- `inline` 内联函数 和 普通函数的区别？
  - `inline` 内联函数：在编译过程中，就没有函数的调用开销了，在函数的调用点直接把函数的代码进行展开处理了
  - `incline` 函数不再生成相应的函数符号

> inline只是建议编译器把函数处理为 内联函数，并不是所有的 inline 都会被编译器内联，例如递归

> debug 版本上，inline 是不起作用的；只有在 release 版本才能出现。例如：`g++ -c run main.cpp -O2 && objdump -t main.o` 可以看到 `sum` 函数的符号已经没有了！

```cpp
int sum (int a, int b) { // *.o sum_int_int .text
  return a + b;
}

int main(){
  int a = 10;
  int b = 20;
  
  int ret = sum(a, b);  // a + b
  // 此处有标准的函数调用过程  参数压栈，函数栈帧的开辟和回退过程
  // 有函数调用的开销，如果循环10000次，就会有10000次的函数调用开销，函数代码越少，越吃亏
  // a + b : mov add mov
}
```

### 2.4.4 参数带默认值的函数

传参时候如果直接传输的**立即数**，从汇编的角度，会比传变量少一次 `mov` 指令

```cpp
int sum(int a, int b = 20);
int sum(int a = 10, int b);
// 这是合法的，等价于：
int sum(int a = 10, int b = 20);
```

--------------

# 3 面向对象

OOP 语言的四大特征：
- 抽象
- 封装/隐藏
- 继承
- 多态

> 类体内实现的方法，自动处理成 `inline` 内联函数

> 对象的内存大小，只和成员变量有关，所有对象共享一套成员方法

## 3.1 this 指针

[`this` 指针](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2532-this%E6%8C%87%E9%92%88%E6%A6%82%E5%BF%B5)

类的成员方法一经编译，所有的方法参数，都会加一个 `this` 指针，接收调用该方法的对象的地址

## 3.2 对象构造和深浅拷贝

- [构造函数和析构函数](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2521-%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%E5%92%8C%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0)
  - 构造函数可以提供重载，但析构不可以，因为析构函数是不带参数的
  - 析构函数可以自行调用（但不建议）
  - `new obj` 进行 `delete obj` 的时候会自行先进行 `obj->~ClassName()`，之后进行 `free(obj)`
- [深拷贝与浅拷贝](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2525-%E6%B7%B1%E6%8B%B7%E8%B4%9D%E4%B8%8E%E6%B5%85%E6%8B%B7%E8%B4%9D)
- [赋值运算符重载](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2554-%E8%B5%8B%E5%80%BC%E8%BF%90%E7%AE%97%E7%AC%A6%E9%87%8D%E8%BD%BD)

C++11 中可以删除默认的拷贝构造函数和赋值运算符重载函数

```cpp
class A {
public:
  A() = default;
  A(const A&) = delete;   // 删除
  A& operator=(const A&) = delete;   // 删除
};
```

## 3.3 初始化列表

- [初始化列表](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2526-%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8)

```cpp
class B {
public:
  B(int a) : B_a(a) {}

private:
  int B_a;
};

class A {
public:
  A(int a, int b, int c) : A_a(a), A_b(b), A_c(c) {}  // 并初始化成员对象

private:
  int A_a;
  int A_b;
  B A_c;  // 成员对象
};

int main() {
  A a(1, 2, 3);
  return 0;
}
```

**写在初始化列表和写在函数体内的区别：**

```cpp
// 写在初始化列表等价于
B A_c(c);   // 指定构造

// 写在函数体内等价于
B A_c;  // 默认构造
A_c = c;  // 赋值操作
```

**成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关**！示例

```cpp
class Test {
public:
  Test(int data = 10) : mb(data), ma(mb) {}
  void show() { cout << "ma: " << ma << "\tmb: " << mb << endl; }

private:
  int ma;
  int mb;
};

int main() {
  est t;T
  t.show();
  return 0;
}

// 输出为： ma: 0   mb: 10
```

## 3.4 普通，static，const三类成员方法

[静态成员 static](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2528-%E9%9D%99%E6%80%81%E6%88%90%E5%91%98)

通过静态成员，**可以实现查看所有通过这个类所做的事情**，例如一共创建了多少个对象，只需要在构造函数中设定 `++` 就好了。**但这样并不直观，这必须通过对象名来调用，而不能通过类名调用，所以还要结合静态函数，就可以通过类名来调用**

> 普通成员方法和静态成员方法的区别：
> - 静态成员方法没有 `this` 指针
> - 所以**不可能**访问依赖当前对象的成员变量
> - 用类名调用静态成员方法，用对象名调用普通成员方法

--------------------

[const 常对象](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2534-const%E4%BF%AE%E9%A5%B0%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)

- 可以进行重载，因为本质上参数列表不同
- 常对象只能调用常函数，原因详见[2.3.2 const 和指针的结合](#232-const-和指针的结合)

```cpp
const className *this // 常成员方法
className *this // 非常成员方法
```

> 只要是只读操作的成员方法，一律实现成 `const` 常成员方法

## 3.5 指向类成员（成员变量和成员方法）的指针

```cpp
class Test {
public:
  void func() { cout << "call Test::func" << endl; };
  static void static_func() { cout << "Test::static_func" << endl; };
  int ma;
  static int mb;
};

int Test::mb;

int main() {
  Test t1;
  Test *t2 = new Test();

#if 0
  // 指向成员变量的指针
  // int *p = &Test::ma; // 报错："int Test::*" 类型的值不能用于初始化 "int *"
  // 类型的实体
  int Test::*p = &Test::ma; // 类外定义一个 Test 作用域的指针
  int *q = &Test::mb;       // static 可以用普通指针指向

  t1.*p = 20; // 依赖于对象
  t2->*p = 30;
  cout << t1.ma << endl << t2->ma << endl;

  *q = 40; // 不依赖于对象
  cout << Test::mb << endl;
#endif

  // 指向成员方法的指针
  // void (*pfunc)() = &Test::func; // 报错 "void (Test::*)()"
  // 类型的值不能用于初始化 "void (*)()" 类型的实体
  void (Test::*pfunc)() = &Test::func;
  void (*qfunc)() = &Test::static_func; // 不依赖于对象

  (t1.*pfunc)();
  (t2->*pfunc)();
  (*qfunc)(); // 不依赖于对象

  delete t2;
  return 0;
}
```

---------------

# 4 模板

## 4.1 函数模板和类模板

### 4.1.1 函数模板

[函数模板](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#312-%E5%87%BD%E6%95%B0%E6%A8%A1%E6%9D%BF)

- 函数模板是不进行编译的，因为类型不知道。模板函数才是要被编译器所编译的
- 在函数调用点，编译器用用户指定的类型，从原模板**实例化一份**函数代码出来，仅会有**一份**
- 模板的实参推演：自动类型推导
- 模板的特例化（专用化/具体化）：对于某些特定的类型，需要特殊处理，可以通过特例化来实现，**即模板的重载，本质上并不是重载，编译产生的函数名符号不一致**
- 重载时：普通函数 > 特例化 > 函数模板

> 模板代码是不能在一个文件中定义，在另外一个文件中使用的。
> **模板代码调用之前，一定要看到模板定义的地方**，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码
> - 所以模板代码都是放在头文件当中的，然后在源代码进行 `include`
> - 也并非不能解决，可以提前告诉编译器，进行指定类型的模板实例化，这样可以分文件编写（**不推荐**）
>   ```cpp
>   template bool compare<int>(int, int);
>   template bool compare<double>(double, double);
>   ```


**模板的非类型参数示例**

```cpp
template <typename T, int SIZE>
void print(T arr) {
  for (int i = 0; i < SIZE; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  int arr[] = {1, 34, 5, 6, 7};
  print<const int *, sizeof(arr) / sizeof(arr[0])>(arr);
  return 0;
}
```

### 4.1.2 类模板

[类模板](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#3131-%E7%B1%BB%E6%A8%A1%E6%9D%BF%E8%AF%AD%E6%B3%95)

- 构造和析构函数名不用加 `<T>`, 其它出现模板的地方都加上类型参数列表
- 类模板可以加**默认类型参数**，例如：
  ```cpp
  template <typename T = int>
  class Test {
  public:
    Test(T a) : ma(a) {}
    void show() { cout << "ma: " << ma << endl; }

  private:
    T ma;
  };
  int main(){
    Test<> t(10);  // 默认类型参数
    t.show();
    return 0;
  }
  ```

## 4.2 容器空间配置器allocator

### 4.2.1 allocator 解决的问题

[类模板案例](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#3139-%E7%B1%BB%E6%A8%A1%E6%9D%BF%E6%A1%88%E4%BE%8B)

**需求：**
1. 需要把内存开辟和对象构造分开处理
2. 析构容器有效的元素，然后释放 `_first` 指针指向的堆内存
3. 只需要析构对象。要把对象的析构和内存释放分离开

> 定义容器时候，希望只是开辟内存，不进行对象的构造。现在都是开辟内存和对象构造一起的，这样当需要添加元素时就变成了赋值操作。删除元素时，就变成了析构操作，并且调用 `delete` 释放内存，而我们并不想要释放这块内存，只想要释放该对象指向的外部堆内存

### 4.2.2 容器空间配置器 allocator 的使用

- 内存开辟
- 内存释放
- 对象构造
- 对象析构

```cpp
template <typename T>
struct Allocator {
  T* allocate(size_t size) {  // 负责内存开辟
    return (T *)malloc(sizeof(T) * size);
  }

  void deallocate(void *p) {  // 负责内存释放
    free(p);
  }

  void construct(T *p, const T &val) {  // 负责对象构造
    new (p) T(val); // 定位 new
  }

  void destroy(T *p) {  // 负责对象析构
    p->~T();  // ~T() 析构函数
  }
};
```

### 4.2.3 RAII(Resource Acquisition Is Initialization, 资源获取即初始化)

```cpp
void process(int *arr) noexcept(false); // 声明，不抛出异常

// 1. 内存泄漏
/*
void array_test(const size_t size) {
  int *arr = new int[size];
  process(arr); // 异常
  delete[] arr; // 跳过，内存泄漏
}
*/

// 2. try-catch 捕获异常释放内存
/*
void array_test(const size_t size) {
  int *arr = new int[size];
  try {
    process(arr);
  } catch (...) {
    delete[] arr;
    return;
  }
  delete[] arr;
}
*/

// 3.
// 如果同时有好几个资源需要释放，为了节省下来代码行数甚至可能需要用上让代码逻辑更凌乱的
// goto 语句。

/* ------------------------------------------------------
# RAII(Resource Acquisition Is Initialization, 资源获取即初始化), 即
作用域界定的资源管理 (Scope-Bound Resource Management，SBRM)

可以利用C++的对象生存期概念以及析构函数这两个工具来实现
*/

// 示例 动态数组
struct dyn_array {
  size_t size = 0;
  int *ptr = nullptr;

  dyn_array() = default; // Default(empty) initialization
  explicit dyn_array(const size_t size)
      : size(size), ptr(new int[size]) {} // Initialize with a given size
  ~dyn_array() noexcept {
    cout << "~dyn_array()" << endl;
    delete[] ptr;
  } // Free the memory, noexcept 表示该函数不会抛出异常
};

void array_test(const size_t size) {
  dyn_array darr(size);
  process(darr.ptr);
} // Memory freed no matter how this function exits

/*
用这样的抽象就可以简化资源管理的操作。
因为C++对象有明确的生存期，
这个函数无论是正常退出还是因抛出异常而退出，
对象darr的作用域（生存期）都将结束，
导致其析构函数被调用，资源成功释放，省去了各种手动判断释放资源的步骤。
*/

int main() {
  array_test(3);
  return 0;
}
```

### 4.2.4 三法则和零法则

- **三法则**：如果手动实现了析构函数，那么很有可能编译器自动生成的复制构造/复制赋值运算符并不能达到想要的效果，所以需要三个函数全都实现（**析构，拷贝构造，赋值运算符重载**）
- **零法则**：如果你并不需要自己实现析构函数，那么就一个特殊函数都不要实现，让编译器帮你做完所有事情。

### 4.2.6 vector 容器的实现

```cpp
#include <cstdlib> // Include the <cstdlib> header for the 'rand()' function
#include <iostream>

using namespace std;

// 定义一个模板类 Allocator，负责内存的开辟和释放，对象的构造和析构
template <typename T> class Allocator {
public:
  T *allocate(int size) { // 负责开辟内存
    return (T *)malloc(sizeof(T) * size);
  }
  void deallocator(void *ptr) { // 负责释放内存
    free(ptr);
  }
  void construct(T *ptr, const T &val) { // 负责对象构造
    new (ptr) T(val);                    // 定位 new
  }
  void destroy(T *ptr) { // 负责对象析构
    ptr->~T();           // 显式调用析构函数
  }
};

template <typename T, typename Alloc = Allocator<T>> class vector {
public:
  vector(int size = 10) {
    // 需要把内存开辟和对象构造分开
    // _first = new T[size];
    _first = _allocator.allocate(size);
    _last = _first;
    _end = _first + size;
  }

  ~vector() {
    // 析构容器有效的元素，然后释放 _first 指向的堆内存
    // delete[] _first;
    for (T *p = _first; p != _last; ++p) // 把有效元素析构
      _allocator.destroy(p);
    _allocator.deallocator(_first); // 释放堆内存
    _first = _last = _end = nullptr;
  }

  vector(const vector<T> &rhs) { // 拷贝构造
    int size = rhs._end - rhs._first;
    _first = _allocator.allocate(size);
    int len = rhs._last - rhs._first;
    for (int i = 0; i < len; i++)
      // _first[i] = rhs._first[i];
      _allocator.construct(_first + i, rhs._first[i]);
    _last = _first + len;
    _end = _first + size;
  }

  vector<T> &operator=(const vector<T> &rhs) { // 赋值运算符重载
    if (this == &rhs)                          // 防止自赋值
      return *this;
    // delete[] _first;
    for (T *p = _first; p != _last; ++p) // 把有效元素析构
      _allocator.destroy(p);
    _allocator.deallocator(_first); // 释放堆内存

    int size = rhs._end - rhs._first;
    _first = _allocator.allocate(size);
    int len = rhs._last - rhs._first;
    for (int i = 0; i < len; i++)
      // _first[i] = rhs._first[i];
      _allocator.construct(_first + i, rhs._first[i]);
    _last = _first + len;
    _end = _first + size;
    return *this;
  }

  void push_back(const T &val) { // 尾插
    if (full())
      expand();
    // *_last++ = val;
    _allocator.construct(_last++, val);
  }

  void pop_back() { // 尾删
    if (empty())
      return;
    // --_last;
    --_last;
    _allocator.destroy(_last);
  }

  T back() const { // 返回尾元素
    return *(_last - 1);
  }

  bool full() const { return _last == _end; }
  bool empty() const { return _last == _first; }
  int size() const { return _last - _first; }

private:
  T *_first;        // 指向数组的第一个元素
  T *_last;         // 指向数组的最后一个元素的后继位置
  T *_end;          // 指向数组空间的后继位置
  Alloc _allocator; // 容器的空间配置器对象

  void expand() { // 容器的二倍扩容接口
    int size = _end - _first;
    // T *new_first = new T[size * 2];
    T *new_first = _allocator.allocate(size * 2);
    for (int i = 0; i < size; i++)
      // new_first[i] = _first[i];
      _allocator.construct(new_first + i, _first[i]);
    // delete[] _first;
    for (T *p = _first; p != _last; ++p)
      _allocator.destroy(p);
    _allocator.deallocator(_first);

    _first = new_first;
    _last = _first + size;
    _end = _first + size * 2;
  }
};

class Test {
public:
  Test() { cout << "Test()" << endl; }
  ~Test() { cout << "~Test()" << endl; }
  Test(const Test &) { cout << "Test(const Test&)" << endl; }
};

int main() {
  Test t1, t2, t3;
  cout << "--------------------------------------" << endl;
  vector<Test> vec;
  vec.push_back(t1);
  vec.push_back(t2);
  vec.push_back(t3);
  cout << "--------------------------------------" << endl;
  vec.pop_back(); // 只需要析构对象，把析构对象和释放内存分开
  cout << "--------------------------------------" << endl;
  return 0;
}
```

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