- [1 三块核心内容](#1-三块核心内容)
  - [1.1 进程的虚拟地址空间内存划分和布局](#11-进程的虚拟地址空间内存划分和布局)
  - [1.2 函数调用堆栈详细过程](#12-函数调用堆栈详细过程)
  - [1.3 程序编译链接原理](#13-程序编译链接原理)
- [2 基础部分](#2-基础部分)
  - [2.1 `new/delete`, `malloc/free`](#21-newdelete-mallocfree)
  - [2.2 引用和指针](#22-引用和指针)
  - [2.3 `const`](#23-const)
  - [2.4 `const` 和指针的结合](#24-const-和指针的结合)
    - [2.4.1 `const` 和一级指针的结合](#241-const-和一级指针的结合)
    - [2.4.2 `const` 和 二级指针的结合](#242-const-和-二级指针的结合)
    - [2.3.3 应用（面试题）](#233-应用面试题)
  - [2.5 `const`, 指针, 引用相结合](#25-const-指针-引用相结合)
  - [2.6 函数重载](#26-函数重载)
  - [2.7 `C++` 和 `C` 互相调用](#27-c-和-c-互相调用)
  - [2.8 `inline` 函数](#28-inline-函数)
    - [2.8.1 函数对象和函数指针](#281-函数对象和函数指针)
  - [2.9 参数带默认值的函数](#29-参数带默认值的函数)
  - [2.10 运行时类型信息 (`RTTI`)](#210-运行时类型信息-rtti)
  - [2.11 C++ 四种类型转换](#211-c-四种类型转换)
- [3 内存分配和管理](#3-内存分配和管理)
  - [3.1 `operator new` 和 `operator delete`](#31-operator-new-和-operator-delete)
  - [3.2 区别总结](#32-区别总结)
- [4 模板](#4-模板)
  - [4.1 函数模板和类模板](#41-函数模板和类模板)
    - [4.1.1 函数模板](#411-函数模板)
    - [4.1.2 类模板](#412-类模板)
    - [4.1.3 模板的偏特化与全特化](#413-模板的偏特化与全特化)
  - [4.2 容器空间配置器 `allocator`](#42-容器空间配置器-allocator)
    - [4.2.1 `vector` 容器的实现](#421-vector-容器的实现)
- [5 STL](#5-stl)
  - [5.1 迭代器失效](#51-迭代器失效)
  - [5.2 顺序容器](#52-顺序容器)
  - [5.3 适配器](#53-适配器)
  - [5.4 关联容器](#54-关联容器)
    - [5.4.1 无序关联容器（链式哈希表）](#541-无序关联容器链式哈希表)
    - [5.4.2 有序关联容器（红黑树）](#542-有序关联容器红黑树)
  - [5.5 绑定器 和 `lambda` 表达式](#55-绑定器-和-lambda-表达式)
- [6 面向对象](#6-面向对象)
  - [6.1 封装](#61-封装)
  - [6.2 继承](#62-继承)
  - [6.3 多态](#63-多态)
    - [6.3.1 静态多态（编译期/早绑定）](#631-静态多态编译期早绑定)
    - [6.3.2 动态多态（运行期期/晚绑定）](#632-动态多态运行期期晚绑定)
  - [6.4 `this` 指针](#64-this-指针)
  - [6.5 初始化列表](#65-初始化列表)
  - [6.6 `static` 关键字](#66-static-关键字)
- [7 虚函数](#7-虚函数)
  - [7.1 虚函数基本概念](#71-虚函数基本概念)
  - [7.2 虚函数、纯虚函数](#72-虚函数纯虚函数)
  - [7.3 虚基类和虚继承](#73-虚基类和虚继承)
  - [7.4 虚继承、虚函数](#74-虚继承虚函数)
  - [7.5 哪些函数不能实现成虚函数](#75-哪些函数不能实现成虚函数)
  - [7.6 什么时候需要虚析构函数](#76-什么时候需要虚析构函数)
  - [7.7 继承多态常见面试题分享](#77-继承多态常见面试题分享)
    - [7.7.1 问题一](#771-问题一)
    - [7.7.2 问题二](#772-问题二)
    - [7.7.3 问题三](#773-问题三)
    - [7.7.4 问题四](#774-问题四)
- [8 大厂 C++ 开发面试问题](#8-大厂-c-开发面试问题)

# 1 三块核心内容

- [《深入理解计算机系统》第 7 章 链接 笔记](https://github.com/Corner430/study-notes/blob/main/cpp/深入理解计算机系统笔记.md)

- [《程序员的自我修养》第 2, 3, 4, 6, 10 章](https://github.com/Corner430/study-notes/blob/main/cpp/程序员的自我修养笔记.md)

## 1.1 进程的虚拟地址空间内存划分和布局

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

---

# 2 基础部分

## 2.1 `new/delete`, `malloc/free`

- `malloc` 和 `free`, 称作 C 的库函数
- `new` 和 `delete`, 称作 C++ 的运算符

```cpp
#include <stdlib.h>

int main() {
  int *p = (int *)malloc(sizeof(int));

  // malloc 开辟内存失败，是通过返回值为 `NULL` 来判断的
  // 而 `new` 开辟内存失败，是通过抛出异常来判断的
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

[引用](https://github.com/Corner430/study-notes/blob/main/cpp/cpp入门笔记.md#23-引用)

- 左值引用
- 右值引用
  - 右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值。
  - 定义一个引用变量，来引用 `array` 数组：`int(&q)[5] = array;`
  - 右值引用可实现**转移语义**（Move Sementics）和**精确传递**（Perfect Forwarding），它的主要目的有两个方面：
    - 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
    - 能够更简洁明确地定义泛型函数。
- 引用折叠

**引用和指针的区别？**

1. 本质: 指针是一个变量，存储内容是一个地址，指向内存的一个存储单元。而引用是原变量的一个别名，实质上和原变量是一个东西，是某块内存的别名。
2. 指针的值可以为空，且非 `const` 指针可以被重新赋值以指向另一个不同的对象。而引用的值不能为空，并且引用在定义的时候必须初始化，一旦初始化，就和原变量“绑定”，不能更改这个绑定关系。
3. 对指针执行 `sizeof()` 操作得到的是指针本身的大小（32 位系统为 4, 64 位系统为 8）。而对引用执行 `sizeof()` 操作得到的是所绑定的对象的所占内存大小。
4. 指针的自增（`++`）运算表示对地址的自增，自增大小要看所指向单元的类型。而引用的自增（`++`）运算表示对值的自增。
5. **引用只有一级引用，没有多级引用**；指针可以有一级指针，也可以有多级指针
6. 定义一个引用变量和定义一个指针变量，其汇编指令时一模一样的；通过引用变量修改所引用内存的值和通过指针解引用修改指针指向的内存的值，其底层指令也是一模一样的
7. 在作为函数参数进行传递时的区别:
   1. 指针：传递时，**函数内部的指针形参是指针实参的一个副本**，改变指针形参并不能改变指针实参的值，通过解引用 `*` 运算符来更改指针所指向的内存单元里的数据。
   2. 引用：传递时，实质上传递的是实参本身，即传递进来的不是实参的一个拷贝，因此对形参的修改其实是对实参的修改，**所以在用引用进行参数传递时，不仅节约时间，而且可以节约空间**

## 2.3 `const`

[c++ 那些事之 `const` 那些事](https://light-city.github.io/stories_things/basic_content/const/)

- **修饰变量**，说明该变量不可以被改变；

- **修饰指针**，指针常量和常量指针

- **修饰引用**，指向常量的引用（reference to const），用于形参类型，即避免了拷贝，又避免了函数对值的修改；

- **修饰成员函数**，说明该成员函数内不能修改成员变量。

**`const` 的指针与引用**

- 指针
  - 指向常量的指针（pointer to const）
  - 自身是常量的指针（常量指针，const pointer）
- 引用
  - 指向常量的引用（reference to const）
  - 没有 `const reference`，因为引用只是对象的别名，引用不是对象，不能用 `const` 修饰

**宏定义 `#define` 和 `const` 的区别**

| 宏定义 `#define`       | `const` 常量   |
| ---------------------- | -------------- |
| 宏定义，相当于字符替换 | 常量声明       |
| 预处理器处理           | 编译器处理     |
| 无类型安全检查         | 有类型安全检查 |
| 不分配内存             | 要分配内存     |
| 存储在代码段           | 存储在数据段   |
| 可通过 `#undef` 取消   | 不可取消       |

**C 和 C++ 中 `const` 的区别是什么？**

- `const` 的编译方式不同，C 中，`const` 就是当作一个变量来编译生成指令的。C++ 中，所有出现 `const` 常量名字的地方，**都被常量的初始化替换了**！！！
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

**使用示例**

```cpp
// 类
class A {
private:
  const int a; // 常对象成员，可以使用初始化列表或者类内初始化

public:
  // 构造函数
  A() : a(0){};
  A(int x) : a(x){}; // 初始化列表

  // const 可用于对重载函数的区分
  int getValue(); // 普通成员函数
  int getValue() const; // 常成员函数，不得修改类中的任何数据成员的值
};

void function() {
  // 对象
  A b;             // 普通对象，可以调用全部成员函数
  const A a;       // 常对象，只能调用常成员函数
  const A *p = &a; // 指针变量，指向常对象
  const A &q = a;  // 指向常对象的引用

  // 指针
  char greeting[] = "Hello";
  char *p1 = greeting; // 指针变量，指向字符数组变量
  const char *p2 = greeting; // 指针变量，指向字符数组常量（const 后面是
                             // char，说明指向的字符（char）不可改变）
  char *const p3 = greeting; // 自身是常量的指针，指向字符数组变量（const 后面是
                             // p3，说明 p3 指针自身不可改变）
  const char *const p4 = greeting; // 自身是常量的指针，指向字符数组常量
}

// 函数
void function1(const int Var);   // 传递过来的参数在函数内不可变
void function2(const char *Var); // 参数指针所指内容为常量
void function3(char *const Var); // 参数指针为常量
void function4(const int &Var);  // 引用参数在函数内为常量

// 函数返回值
const int function5(); // 返回一个常数
const int * function6(); // 返回一个指向常量的指针变量，使用：const int *p = function6();
int *const function7(); // 返回一个指向变量的常指针，使用：int* const p = function7();
```

## 2.4 `const` 和指针的结合

`const` 修饰的量常出现的错误是：

1. 常量不能再作为左值 <= 直接修改常量的值
2. 不能把常量的地址泄露给一个普通的指针或者普通的引用变量 <= 可以间接修改常量的值

### 2.4.1 `const` 和一级指针的结合

**C++ 的语言规范：`const` 修饰的是离它最近的类型**

```cpp
const int *p; // => *p = 20; 是错误的.  p = &b; 是正确的
int const *p; // 同上

int * const p;  // => p = &b; 是错误的. *p = 20; 是正确的
const int *const p; // p 和 *p 都不可以修改

// -------------示例 1------------------
int main() {
  const int a = 10;
  // int *p = &a; // 错误, 可以通过 *p 间接修改 a 的值
  // int *const p = &a;  // 错误, 同上
  const int *p = &a; // 正确, 不能通过 *p 间接修改 a 的值
  return 0;
}

// -------------示例 2------------------
int main() {
  int a = 10;
  int *p1 = &a;
  const int *p2 = &a; // 合法, const int * <= int *
  int *const p3 = &a; // 合法, int * <= int *
  int *p4 = p3; // 合法, int * <= int *
  return 0;
}

// -------------示例 3------------------
int main() {
  int *q1 = nullptr;

  // const 如果右边没有指针 * 的话，const 是不参与类型的
  // 这里作用是不能让 q2 当作左值传给二级指针
  int *const q2 = nullptr;
  cout << typeid(q1).name() << endl; // int *
  cout << typeid(q2).name() << endl; // int *

  return 0;
}

// -------------示例 4 （面试题）---------
int main() {
  int a = 10;
  const int *p = &a;
  // int *q = p; // 不合法, int * <= const int *
  // 问：q 指向 a, a 可以改动，有什么问题？
  // 答：这和 a 没关系，问题在于 p 是 const int * 类型，不能赋值给 int * 类型，会导致间接修改 const 类型的值
  a = 12; // 合法
  return 0;
}
```

**总结 `const` 和一级指针的类型转换公式**

```cpp
int *  <=  const int *     // 错误
const int *  <=  int *     // 正确

int **  <=  int *const *   // 错误
int *const *  <=  int **   // 正确
```

### 2.4.2 `const` 和 二级指针的结合

**`const` 修饰的是离它最近的类型**

```cpp
int main() {
  int a = 10;
  int *p = &a;
  // const int **q = &p; // 错误, const int ** <= int **

  // 同样的和 a 没关系 , 原因如下:

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

**总结 `const` 和二级指针的类型转换公式**

```cpp
int ** <= const int ** // 错误
const int ** <= int ** // 错误
```

> **两边必须都要有 `const`**

### 2.3.3 应用（面试题）

```cpp
int a = 10;
const int *p = &a;
int *q = p; // 错误, int * <= const int *

/*********************************/

int a = 10;
int *const p = &a;
int *q = p; // 正确, int * <= int *

/*********************************/

int a = 10;
int *const p = &a;
int *const q = p; // 正确, int * <= int *

/*********************************/

int a = 10;
int *const p = &a;
const int *q = p; // 正确, const int * <= int *

/*********************************/

int a = 10;
int *p = &a;
const int **q = &p; // 错误, const int ** <= int **

/*********************************/

int a = 10;
int *p = &a;
int *const *q = &p; // int * const * <= int **  等价于  const * <= int * 正确

/*********************************/

int a = 10;
int *p = &a;
int **const q = &p; // int ** <= int **  正确

/*********************************/

int a = 10;
int *const p = &a; // int * <= int *
int **q = &p; // int ** <= int * const *  等价于 int * <= const int *  错误

/*********************************/

int a = 10;
const int *p = &a;  // const int * <= int *
int *const *q = &p; // int * const * <= const int **
// 两步分析
// 1. const * <= int *  正确
// 2. int * <= const int *  错误
```

## 2.5 `const`, 指针, 引用相结合

```cpp
int main() {
  // 在内存的 0x0018ff44 处写一个 4 字节的 10
  int *p = (int *)0x0018ff44;
  int *&&p = (int *)0x0018ff44;
  int *const &p = (int *)0x0018ff44;

  new (p) int(10);

  // ----------------------------------

  int a = 10;
  int *p = &a;
  int *&q = p; // 正确, int **q = &p;
  // const int *&q = p; // 错误, const int **q = &p; => const int ** = int **

  // --------------------------------

  int a = 10;
  int *const p = &a;
  int *&q = p; // int **q = &p; => int ** <= int * const *  错误
  // *q 会修改 p 的值

  // ---------------------------------

  int a = 10;
  const int *p = &a; // 正确, const int * <= int *
  int *&q = p;       // 错误, int ** <= const int **

  // ---------------------------------

  int a = 10;
  int *p = &a;
  const int *&q = p; // 错误, const int ** <= int **

  return 0;
}
```

## 2.6 函数重载

> **重载必须要在同一个作用域中**，子类和父类的成员函数不在同一个作用域中，所以不能重载

**为什么 `C++` 支持函数重载，而 `C` 不支持**？

- `C++` 代码产生函数符号是由**函数名 + 参数列表类型**组成
- `C` 代码产生函数符号是由**函数名**来决定

## 2.7 `C++` 和 `C` 互相调用

**在 `CPP` 源码中，把 `C` 函数的声明放在 `extern "C"` 里面**

> `C` 编译器不识别 `extern`

**C++ 调用 C**

**_main.cpp_**

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

**_test.c_**

```c
int sum(int a, int b) { // .text  sum
  return a + b;
}
```

如果得到链接错误，无法解析的外部符号，是因为各自编译时候，产生的符号不一样，`C++` 产生的符号是 `_Z3sumii`，而 `C` 产生的符号是 `sum`，所以需要在 `C++` 文件中通过 `extren "C"` 关键字声明一下 `sum` 函数

```cpp
extern "C" {
  int sum(int a, int b);
}
```

**`C` 调用 `C++`**

**_main.c_**

```c
#include <stdio.h>

int sum(int, int);  // UND sum

int main() {
  int ret = sum(10, 20);
  printf("ret: %d\n", ret);
  return 0;
}
```

**_test.cpp_**

```cpp
extern "C" {
int sum(int a, int b) { // .text  sum_int_int
  return a + b;
}
}
```

**面试题**

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

## 2.8 `inline` 函数

- **特征**

  - 相当于把内联函数里面的内容写在调用内联函数处；
  - 相当于不用执行进入函数的步骤，直接执行函数体；
  - 相当于宏，却比宏多了类型检查，真正具有函数特性；
  - 编译器一般不内联包含循环、递归、switch 等复杂操作的内联函数；
  - **在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数**。

- 使用

  ```cpp
  // 声明1（加 inline，建议使用）
  inline int functionName(int first, int second, ...);

  // 声明2（不加 inline）
  int functionName(int first, int second, ...);

  // 定义
  inline int functionName(int first, int second, ...) { /****/ };

  // 类内定义，隐式内联
  class A {
    int doA() { return 0; } // 隐式内联
  };

  // 类外定义，需要显式内联
  class A {
    int doA();
  };
  inline int A::doA() { return 0; } // 需要显式内联
  ```

- **编译器对 `inline` 函数的处理步骤**

  1. 将 `inline` 函数体复制到 `inline` 函数调用点处；
  2. 为所用 `inline` 函数中的局部变量分配内存空间；
  3. 将 `inline` 函数的的输入参数和返回值映射到调用方法的局部变量空间中；
  4. 如果 `inline` 函数有多个返回点，将其转变为 `inline` 函数代码块末尾的分支（使用 GOTO）。

- 优缺点

  - 优点
    1. 内联函数同宏函数一样将在被调用处进行代码展开，省去了参数压栈、栈帧开辟与回收，结果返回等，从而提高程序运行速度。
    2. 内联函数相比宏函数来说，在代码展开时，会做安全检查或自动类型转换（同普通函数），而宏定义则不会。
    3. 在类中声明同时定义的成员函数，自动转化为内联函数，因此内联函数可以访问类的成员变量，宏定义则不能。
    4. 内联函数在运行时可调试，而宏定义不可以。
  - 缺点
    1. **代码膨胀**。内联是以代码膨胀（复制）为代价，消除函数调用带来的开销。如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少。另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。
    2. `inline` 函数无法随着函数库升级而升级。`inline` 函数的改变需要重新编译，不像 `non-inline` 可以直接链接。
    3. **是否内联，程序员不可控**。内联函数只是对编译器的建议，是否对函数内联，决定权在于编译器。

- `inline` 内联函数 和 普通函数的区别？

  - `inline` 内联函数：在编译过程中，就没有函数的调用开销了，在函数的调用点直接把函数的代码进行展开处理了
  - `incline` 函数不再生成相应的函数符号

- **虚函数（`virtual`）可以是内联函数（`inline`）吗**？
  - **虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联**。
  - 内联是在编译期建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此**虚函数表现为多态性时（运行期）不可以内联**。
  - `inline virtual` 唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如 `Base::who()`），这只有在编译器具有实际对象而不是对象的指针或引用时才会发生。

```cpp
class Base {
public:
  inline virtual void who() { cout << "Base\n"; }
  virtual ~Base() {}
};

class Derived : public Base {
public:
  inline void who() { cout << "Derived\n"; }
};

int main() {
  // 此处的虚函数 who()
  // 是通过类（Base）的具体对象（b）来调用的，编译期间就能确定了
  // 所以它可以是内联的，但最终是否内联取决于编译器。
  Base b;
  b.who();

  // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能为内联。
  Base *ptr = new Derived();
  ptr->who();

  // 因为 Base 有虚析构函数，所以 delete 时，会先调用派生类（Derived）析构函数
  // 再调用基类（Base）析构函数，防止内存泄漏。
  delete ptr;
  ptr = nullptr;

  return 0;
}
```

### 2.8.1 函数对象和函数指针

- 通过**函数指针**调用函数，无法实现内联，因此会有函数调用的开销
- 通过**函数对象**调用函数，可以实现内联

## 2.9 参数带默认值的函数

传参时候如果直接传输的**立即数**，从汇编的角度，会比传变量少一次 `mov` 指令

```cpp
int sum(int a, int b = 20);
int sum(int a = 10, int b);
// 这是合法的，等价于：
int sum(int a = 10, int b = 20);
```

## 2.10 运行时类型信息 (`RTTI`)

**`dynamic_cast`**

- 用于多态类型的转换

**`typeid`**

- `typeid` 运算符允许在运行时确定对象的类型
- `type_id` 返回一个 `type_info` 对象的引用
- 如果想通过基类的指针获得派生类的数据类型，基类必须带有虚函数
- 只能获取对象的实际类型

**`type_info`**

- `type_info` 类描述编译器在程序中生成的类型信息。此类的对象可以有效存储指向类型的名称的指针。`type_info` 类还可存储适合比较两个类型是否相等或比较其排列顺序的编码值。类型的编码规则和排列顺序是未指定的，并且可能因程序而异。
- 头文件：`typeinfo`

**`typeid`、`type_info` 使用**

```cpp
class Flyable {
public:
  virtual void takeoff() = 0;
  virtual void land() = 0;
};

class Bird : public Flyable {
public:
  void foraging() { cout << "Bird foraging" << endl; }
  virtual void takeoff() { cout << "Bird takeoff" << endl; }
  virtual void land() { cout << "Bird land" << endl; }
  virtual ~Bird() { cout << "~Bird" << endl; }
};

class Plane : public Flyable {
public:
  void carry() { cout << "Plane carry" << endl; }
  virtual void takeoff() { cout << "Plane takeoff" << endl; }
  virtual void land() { cout << "Plane land" << endl; }
};

class type_info {
public:
  const char *name() const;
  bool operator==(const type_info &rhs) const;
  bool operator!=(const type_info &rhs) const;
  int before(const type_info &rhs) const;
  virtual ~type_info();

private:
};

void doSomething(Flyable *obj) {
  obj->takeoff();

  cout << typeid(*obj).name()
       << endl; // 输出传入对象类型（"class Bird" or "class Plane"）

  if (typeid(*obj) == typeid(Bird)) {       // 判断对象类型
    Bird *bird = dynamic_cast<Bird *>(obj); // 对象转化
    bird->foraging();
  }

  obj->land();
}

int main() {
  Bird *b = new Bird();
  doSomething(b);
  delete b;
  b = nullptr;
  return 0;
}
```

## 2.11 C++ 四种类型转换

- `C` 风格的强制类型转换很简单，均用 `Type b = (Type)a` 形式转换。
- `C++` 风格的类型转换提供了 `4` 种类型转换操作符来应对不同场合的应用，如下表：
  | **转换类型操作符** | **作用** |
  | ------------------ | -------- |
  | `const_cast` | 去掉类型的 `const` 或 `volatile` 属性 |
  | `static_cast` | 无条件转换，静态类型转换 |
  | `dynamic_cast` | 有条件转换，动态类型转换，运行时检查类型安全（转换失败返回 `NULL`） |
  | `reinterpret_cast` | 仅重新解释类型，但没有进行二进制的转换 |

- `static_cast`

  - `static_cast` 用来强迫隐式转换，允许执行任意的隐式转换和相反转换动作
  - 可将 `non-const` 对象转为 `const` 对象，将 `int` 转为 `double`，将 `void*` 指针转为 `typed` 指针，将 `pointer-to-base` 转为 `pointer-to-derived`
  - 无法将 `const` 转为 `non-const`，这个只有 `const-cast` 才可办到

  ```cpp
  int n = 6;
  double d = static_cast<double>(n);

  class Base {};
  class Derived : public Base {};

  Base *a = new Base;
  Derived *b = static_cast<Derived *>(
      a); // 把父类指针转换为子类指针,但是不推荐，访问子类成员会越界
  ```

- `dynamic_cast`

  - `dynamic_cast` 只用于对象的指针和引用。
  - 主要用于执行**安全向下转型**（safe downcasting），也就是用来决定某对象是否归属继承体系中的某个类型。它是唯一不能由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作
  - **当用于多态类型时，它允许任意的隐式类型转换以及相反过程**。
  - 与 `static_cast` 不同的是在隐式转换的相反过程中， `dynamic_cast` 会检查操作是否有效，它会检查转换是否会返回一个被请求的有效的完整对象。检查在运行时进行，如果被转换的指针不是一个被请求的有效完整的对象指针，返回值为 `NULL`;

  ```cpp
  class Base {
  public:
    virtual void dummy() {}
  };
  class Derived : public Base {};

  int main() {
    Base *b1 = new Derived;
    Base *b2 = new Base;

    Derived *d1 = dynamic_cast<Derived *>(b1); // 成功
    Derived *d2 = dynamic_cast<Derived *>(b2); // 失败，返回NULL
    return 0;
  }
  ```

- `const_cast`
  - 用于删除 `const`, `volatile` 和 `__unaligned` 特性（如将 `const int` 类型转换为 `int` 类型 ）
  ```cpp
  class C {};
  const C *a = new C;
  C *b = const_cast<C *>(a);
  ```
- `reinterpret_cast`

  - 用于位的简单重新解释
  - 滥用 `reinterpret_cast` 运算符可能很容易带来风险。除非所需转换本身是低级别的，否则应使用其他强制转换运算符之一。
  - **允许将任何指针转换为任何其他指针类型**（如 `char*` 到 `int*` 或 `One_class*` 到 `Unrelated_class*` 之类的转换，但其本身并不安全）
  - **也允许将任何整数类型转换为任何指针类型以及反向转换**。
  - `reinterpret_cast` 运算符不能丢掉 `const`, `volatile` 或 `__unaligned` 特性。
  - `reinterpret_cast` 的一个实际用途是在哈希函数中，即，通过让两个不同的值几乎不以相同的索引结尾的方式将值映射到索引。

  ```cpp
  class A {};
  class B {};

  A *a = new A;
  B *b = reinterpret<B *>(
      a); // reinterpret_cast就像传统的类型转换一样对待所有指针的类型转换
  ```

---

# 3 内存分配和管理

**`malloc`, `calloc`, `realloc`, `alloca`**

- `malloc`：申请指定字节数的内存。申请到的内存中的初始值不确定。
- `calloc`：为指定长度的对象，分配能容纳其指定个数的内存。申请到的内存的每一位（`bit`）都初始化为 `0`。
- `realloc`：更改以前分配的内存长度（增加或减少）。当增加长度时，可能需将以前分配区的内容移到另一个足够大的区域，而新增区域内的初始值则不确定。
- `alloca`：在栈上申请内存。程序在出栈的时候，会自动释放内存。但是需要注意的是，`alloca` 不具可移植性, 而且在没有传统堆栈的机器上很难实现。`alloca` 不宜使用在必须广泛移植的程序中。C99 中支持变长数组 (`VLA`)，可以用来替代 `alloca`。

**`malloc`, `free`**

```cpp
char *str = (char*) malloc(100);
assert(str != nullptr);// 确认是否申请成功

free(p);
p = nullptr;
```

**`new`, `delete`**

1. `new / new[]`：完成两件事，先底层调用 `malloc` 分配了内存，然后调用构造函数（创建对象）。
2. `delete/delete[]`：也完成两件事，先调用析构函数（清理资源），然后底层调用 `free` 释放空间。
3. `new` 在申请内存时会自动计算所需字节数，而 `malloc` 则需我们自己输入申请内存空间的字节数。

## 3.1 `operator new` 和 `operator delete`

> **`new` 和 `delete` 也是函数，可以重载**

```cpp
_GLIBCXX_NODISCARD void* operator new(std::size_t) _GLIBCXX_THROW (std::bad_alloc)
  __attribute__((__externally_visible__));
_GLIBCXX_NODISCARD void* operator new[](std::size_t) _GLIBCXX_THROW (std::bad_alloc)
  __attribute__((__externally_visible__));
void operator delete(void*) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete[](void*) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
```

**`operator new` 和 `operator delete` 重载实现对象池**

```cpp
#include <iostream>
using namespace std;

template <typename T> class Queue {
public:
  Queue() { _front = _rear = new QueueItem(); }
  ~Queue() {
    QueueItem *cur = _front;
    while (cur != nullptr) {
      QueueItem *next = cur->_next;
      delete cur;
      cur = next;
    }
  }

  void push(const T &val) {
    QueueItem *item = new QueueItem(val);
    _rear->_next = item;
    _rear = item;
  }

  void pop() {
    if (empty())
      return;
    QueueItem *first = _front->_next;
    _front->_next = first->_next;
    if (_front->_next == nullptr)
      _rear = _front;
    delete first;
  }

  T front() const {
    if (empty())
      throw out_of_range("Queue is empty");
    return _front->_next->_data;
  }

  bool empty() const { return _front == _rear; }

private:
  struct QueueItem {
    QueueItem(T data = T()) : _data(data), _next(nullptr) {}
    T _data;
    QueueItem *_next;

    static QueueItem *_itemPool;
    static const int POOL_ITEM_SIZE = 10000;

    void *operator new(size_t size) {
      if (_itemPool == nullptr) {
        _itemPool = (QueueItem *)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
        QueueItem *p = _itemPool;
        for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p)
          p->_next = p + 1;
        p->_next = nullptr;
      }
      QueueItem *p = _itemPool;
      _itemPool = _itemPool->_next;
      return p;
    }

    void operator delete(void *ptr) {
      QueueItem *p = (QueueItem *)ptr;
      p->_next = _itemPool;
      _itemPool = p;
    }
  };

  QueueItem *_front;
  QueueItem *_rear;
};

template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

int main() {
  Queue<int> que;
  for (int i = 0; i < 20000; i++) {
    que.push(i);
    que.pop();
  }
  cout << que.empty() << endl;

  return 0;
}
```

## 3.2 区别总结

- `malloc` 和 `new` 的区别
  - `malloc` 是按字节开辟内存，`new` 开辟内存时需要指定类型，所以 `malloc` 返回的都是 `void *` 类型
  - `malloc` 只负责开辟内存，`new` 还负责对象的构造
  - `malloc` 开辟内存失败返回 `nullptr`，`new` 开辟内存失败抛出异常 `std::bad_alloc`
- `free` 和 `delete` 的区别
  - `delete`: 调用析构函数，之后 `free` 内存
- `new` 和 `delete` 能混用吗？
  - `new` 和 `delete` 能否混用，取决于是否会调用构造和析构函数
- `C++` 为什么区分单个元素和数组的内存分配和释放？

  - > 自定义的类 类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，**会自动多开辟 `4` 个字节，用来存储对象的个数**

  ```cpp
  try { // 此时没有任何问题，因为不涉及到对象的析构
    int *p = new int;
    delete[] p;

    int *q = new int[10];
    delete q;
  } catch (const bad_alloc &err) {
    cerr << err.what() << endl;
  }
  ```

  ```cpp
  class Test {
  public:
    Test(int data = 10) : ptr(new int(data)) { cout << "Test()" << endl; }
    ~Test() {
      delete ptr;
      cout << "~Test()" << endl;
    }

  private:
    int *ptr;
  };

  int main() {
    Test *p1 = new Test();
    delete p1;
    // delete[] p1; // 可能会疯狂析构，之后段错误

    Test *p2 = new Test[5];
    delete[] p2;
    // delete p2;  // Test[0] 对象析构，直接 free，段错误(没有正确析构)
    return 0;
  }
  ```

---

# 4 模板

## 4.1 函数模板和类模板

### 4.1.1 函数模板

[函数模板](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#312-%E5%87%BD%E6%95%B0%E6%A8%A1%E6%9D%BF)

- 函数模板是不进行编译的，因为类型不知道。
- 在函数调用点，编译器用用户指定的类型，从原模板**实例化一份**函数代码出来，仅会有**一份**
- 模板的特例化（专用化/具体化）：对于某些特定的类型，需要特殊处理，可以通过特例化来实现，**即模板的重载，本质上并不是重载，编译产生的函数名符号不一致**

> 1. 模板代码是不能在一个文件中定义，在另外一个文件中使用的。
>
> 2. **模板代码调用之前，一定要看到模板定义的地方**，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码
>
> 3. 模板代码放在头文件中，在源代码进行 `include`
>
> 4. 可以提前告诉编译器，进行指定类型的模板实例化，这样可以分文件编写（**不推荐**）
>
> ```cpp
> template bool compare<int>(int, int);
> template bool compare<double>(double, double);
> ```

### 4.1.2 类模板

[类模板](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#3131-%E7%B1%BB%E6%A8%A1%E6%9D%BF%E8%AF%AD%E6%B3%95)

> 构造和析构函数名不用加 `<T>`, 其它出现模板的地方都加上类型参数列表

### 4.1.3 模板的偏特化与全特化

特化必须在同一命名空间下进行，可以特化类模板也可以特化函数模板，但类模板可以偏特化和全特化，而函数模板只能全特化。

```cpp
// 类模板
template <class T1, class T2> class A {
  T1 data1;
  T2 data2;
};

// 函数模板
template <class T> T max(const T lhs, const T rhs) {
  return lhs > rhs ? lhs : rhs;
}

/*************** 全特化 ***************/
template <> class A<int, double> {
  int data1;
  double data2;
};

template <> int max<int>(const int lhs, const int rhs) {
  return lhs < rhs ? lhs : rhs;
}

/*************** 偏例化 ***************/
template <class T2> class A<int, T2> {
  int data1;
  T2 data2;
};
```

注意类模板的**全特化**时在类名后给出了**模板实参**，但函数模板的函数名后没有给出**模板实参**。 这是因为编译器根据 `int max(const int, const int)` 的函数签名可以推导出来它是 `T max(const T, const T)` 的特化。

```cpp
template <class T> void f() { T d; }

// template <> void f() { int d; }  // 特化的歧义
template <> void f<int>() { int d; }
```

- 此时编译器不知道 `f()` 是从 `f<T>()` 特化来的，编译时会有错误：_template-id 'f<>' for 'void f()' does not match any template declaration_

## 4.2 容器空间配置器 `allocator`

1. **`allocator` 解决的问题**
   1. 把内存开辟和对象构造分开处理
   2. 析构容器有效的元素，然后释放 `_first` 指针指向的堆内存
   3. 只析构对象。要把对象的析构和内存释放分离开

> 定义容器时，希望只开辟内存，不进行对象的构造。现在都是开辟内存和对象构造一起的，这样当需要添加元素时就变成了赋值操作。删除元素时，就变成了析构操作，并且调用 `delete` 释放内存，而我们并不想要释放这块内存，只想要释放该对象指向的外部堆内存

2. **容器空间配置器 `allocator` 的使用**
   - 内存开辟
   - 内存释放
   - 对象构造
   - 对象析构

```cpp
template <typename T> struct Allocator {
  T *allocate(size_t size) { // 负责内存开辟
    return (T *)malloc(sizeof(T) * size);
  }

  void deallocate(void *p) { // 负责内存释放
    free(p);
  }

  void construct(T *p, const T &val) { // 负责对象构造
    new (p) T(val);                    // 定位 new
  }

  void destroy(T *p) { // 负责对象析构
    p->~T();           // ~T() 析构函数
  }
};
```

### 4.2.1 `vector` 容器的实现

```cpp
#include <cstdlib> // for the 'rand()' function
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

---

---

# 5 STL

## 5.1 迭代器失效

- 容器迭代器 `iterator`
  - 迭代器的功能：提供一种统一的方式，来透明的遍历容器
  - `for each` 底层调用的是 `begin()` 和 `end()` 函数，迭代器
  - 前置`++` 效率高于 后置`++`, 因为后置`++` 需要返回一个临时对象
  - `auto` 关键字可以自动推导类型
  - 不同容器的迭代器是不能相互比较的，这是因为迭代器迭代的容器对象不同
- 迭代器失效
  1. 删除、增加、扩容操作都会导致迭代器失效
  2. 当容器调用 `erase` 或 `insert` 方法后，**当前位置到容器末尾元素的迭代器都会失效，前面的正常**
  3. 如果操作导致了容器扩容，**那么原来的迭代器都会失效**，因为容器重新分配了内存

**解决方案**：

```cpp
iterator
insert(const_iterator __position, value_type&& __x)
{ return _M_insert_rval(__position, std::move(__x)); }

// 使用 it 接住返回值
it = vec.insert(it, *it - 1);
it = vec.erase(it);
```

## 5.2 顺序容器

- [vector](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#332-vector%E5%AE%B9%E5%99%A8)
  - `vector`: 向量容器
  - 底层数据结构：动态开辟的数组，每次以原来空间大小的 2 倍进行扩容

---

- [deque](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#333-deque%E5%AE%B9%E5%99%A8)
  - `deque`：双端队列容器
  - 底层数据结构：动态开辟的二维数组，一维数组从 `2` 开始，以 `2` 倍的方式扩容，每次扩容后，原来第二维的数组，从新的一维数组的中间开始（`oldsize/2`）存放，上下都预留相同的空行，方便支持 `deque` 的首尾元素添加

> -` deque` **底层内存是否连续**？
>
> - 不连续，因为 deque 是由多个一维数组组成的，每个一维数组都是连续的，但是一维数组之间不连续

---

- [list](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#337-list%E5%AE%B9%E5%99%A8)
  - `list`: 链表容器
  - 底层数据结构：双向的循环列链表

## 5.3 适配器

1. 适配器底层没有自己的数据结构，它是另外一个容器的封装，它的方法，全部由底层依赖的容器进行实现
2. 没有实现自己的迭代器

**示例**

```cpp
template <typename T, typename Container = deque<T>> class Stack {
public:
  void push(const T &val) { con.push_back(val); }
  void pop() { con.pop_back(); }
  T top() const { return con.back(); }

private:
  Container con;
};
```

---

- [stack](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#335-stack%E5%AE%B9%E5%99%A8), **底层依赖于 `deque`**

- [queue](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#336-queue-%E5%AE%B9%E5%99%A8), **底层依赖于 `deque`**

- `priority_queue`, **底层依赖于 `vector`**

> **为什么这样设计**？
>
> 1. `vector` 的**初始内存效率**太低了！扩容时：1->2->4->8->16..., 而 `deque` 的每一个一维数组的大小是 `4096/sizeof(T)`
> 2. `queue` 需要 `deque` 支持首尾元素的添加和删除的效率
> 3. `vector` 需要大片的连续内存，而 `deque` 只需要分段的内存，当存储大量数据时，`deque` 的利用率更高
> 4. `priority_queue` 底层默认把数据组成一个大根堆结构，在一个**内存连续的数组**上进行操作，所以选择 `vector`，方便进行随机访问

## 5.4 关联容器

### 5.4.1 无序关联容器（链式哈希表）

- `unordered_set/unordered_multiset`
- `unordered_map/unordered_multimap`

- `map` 的 `operator[]`
  1. 查询
  2. 如果 `key` 不存在，会自动插入一个 `key-value` 对，**其中 `value` 是默认构造**

### 5.4.2 有序关联容器（红黑树）

- [set/multiset](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#338-setmultiset-%E5%AE%B9%E5%99%A8)
- [map/multimap](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#339-mapmultimap%E5%AE%B9%E5%99%A8)

- [map 容器排序](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#3396-map%E5%AE%B9%E5%99%A8%E6%8E%92%E5%BA%8F)

## 5.5 绑定器 和 `lambda` 表达式

**绑定器 + 二元函数对象 =>> 一元函数对象**

- `bind1st`: 把二元函数对象的 `operator()(a, b)` 的第一个形参绑定为一个固定值
- `bind2nd`: 把二元函数对象的 `operator()(a, b)` 的第二个形参绑定为一个固定值

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v = {1, 12, 14, 21, 23, 34, 45, 56, 67, 78, 89, 90};
  // 把 48 插入到 v 中
  auto it =
      find_if(v.begin(), v.end(), [](int val) -> bool { return val > 48; });
  v.insert(it, 48);
  for (auto i : v)
    cout << i << " ";
  cout << endl;
  for_each(
      v.begin(), v.end(),
      [](int val) -> void { // void 可以省略, lambda 表达式
        if (val % 2 == 0)
          cout << val << " ";
      });

  return 0;
}
```

---

# 6 面向对象

面向对象程序设计（Object-oriented programming，OOP）是种具有对象概念的程序编程典范，同时也是一种程序开发的抽象方针。

![20240704155212](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240704155212.png)

面向对象三大特征 —— 封装、[继承](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#256-%E7%BB%A7%E6%89%BF)、[多态](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#257--%E5%A4%9A%E6%80%81)

## 6.1 封装

把客观事物封装成抽象的类，并且类可以把自己的数据和方法只让可信的类或者对象操作，对不可信的进行信息隐藏。关键字：`public`, `protected`, `private`。不写默认为 `private`。

- `public` 成员：可以被任意实体访问
- `protected` 成员：只允许被子类及本类的成员函数访问
- `private` 成员：只允许被本类的成员函数、友元类或友元函数访问

## 6.2 继承

- `class` 定义派生类，默认继承方式是 `private`
- `struct` 定义派生类，默认继承方式是 `public`

[继承同名成员-隐藏](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2565-%E7%BB%A7%E6%89%BF%E5%90%8C%E5%90%8D%E6%88%90%E5%91%98%E5%A4%84%E7%90%86%E6%96%B9%E5%BC%8F)

**在继承结构中进行上下的类型转换，默认只支持从派生类到基类的转换，不支持从基类到派生类的转换。除非使用类型强转**

```cpp
class Base {
public:
  int m_a;
};

class Derived : public Base {
public:
  int m_b;
};

int main() {
  Base b;
  Derived d;
  d.m_a = 100;
  d.m_b = 200;

  b = d; // 派生类对象可以赋值给基类对象
  // d = b;      // 基类对象不能赋值给派生类对象
  Base *p = &d; // 派生类对象的地址可以赋值给基类指针
  // Derived *pd = &b; // 基类对象的地址不能赋值给派生类指针

  cout << b.m_a << endl; // 100
  // cout << b.m_b << endl; // error: 'class Base' has no member named 'm_b'
  return 0;
}
```

## 6.3 多态

- 多态，即多种状态（形态）。简单来说，我们可以将多态定义为消息以多种形式显示的能力。
- 多态是以封装和继承为基础的。
- `C++` 多态分类及实现：
  1. 重载多态（Ad-hoc Polymorphism，编译期）：函数重载、运算符重载
  2. 子类型多态（Subtype Polymorphism，运行期）：虚函数
  3. 参数多态性（Parametric Polymorphism，编译期）：类模板、函数模板
  4. 强制多态（Coercion Polymorphism，编译期/运行期）：基本类型转换、自定义类型转换

### 6.3.1 静态多态（编译期/早绑定）

函数重载

```cpp
class A
{
public:
    void do(int a);
    void do(int a, int b);
};
```

### 6.3.2 动态多态（运行期期/晚绑定）

- 虚函数：用 `virtual` 修饰成员函数，使其成为虚函数
- 动态绑定：当使用基类的引用或指针调用一个虚函数时将发生动态绑定

**注意**

- 可以将派生类的对象赋值给基类的指针或引用，反之不可
- 普通函数（非类成员函数）不能是虚函数
- 静态函数（static）不能是虚函数
- **构造函数不能是虚函数**（因为在调用构造函数时，虚表指针并没有在对象的内存空间中，必须要构造函数调用完成后才会形成虚表指针）
- **内联函数不能是表现多态性时的虚函数**

## 6.4 `this` 指针

**[`this` 指针](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2532-this%E6%8C%87%E9%92%88%E6%A6%82%E5%BF%B5)**

1. 类的成员方法一经编译，所有的方法参数，都会加一个 `this` 指针，接收调用该方法的对象的地址
2. `this` 指针是一个隐含于每一个非静态成员函数中的特殊指针。它指向调用该成员函数的那个对象。
3. 当对一个对象调用成员函数时，编译程序先将对象的地址赋给 `this` 指针，然后调用成员函数，每次成员函数存取数据成员时，都隐式使用 `this` 指针。
4. 当一个成员函数被调用时，自动向它传递一个隐含的参数，该参数是一个指向这个成员函数所在的对象的指针。
5. **`this` 指针被隐含地声明为: `ClassName *const this`，这意味着不能给 `this` 指针赋值；在 `ClassName` 类的 `const` 成员函数中，`this` 指针的类型为：`const ClassName* const`，这说明不能对 `this` 指针所指向的这种对象是不可修改的（即不能对这种对象的数据成员进行赋值操作**）；
6. `this` 并不是一个常规变量，而**是个右值**，所以不能取得 `this` 的地址（不能 `&this`）。

## 6.5 初始化列表

- [初始化列表](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2526-%E5%88%9D%E5%A7%8B%E5%8C%96%E5%88%97%E8%A1%A8)

**写在初始化列表和写在函数体内的区别：**

```cpp
// 写在初始化列表等价于
B A_c(c);   // 指定构造

// 写在函数体内等价于
B A_c;  // 默认构造
A_c = c;  // 赋值操作
```

**成员变量的初始化和它们定义的顺序有关，和构造函数初始化列表中出现的先后顺序无关**

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
  Test t1;
  Test *p = new Test;
  t1.show(); // 输出为： ma: 未知   mb: 10
  p->show(); // 输出为： ma: 0   mb: 10
  return 0;
}
```

## 6.6 `static` 关键字

- **修饰普通变量**，修改变量的存储区域和生命周期，使变量存储在静态区，在 `main` 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。

- **修饰普通函数**，表明函数的作用范围，**仅在定义该函数的文件内才能使用**。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 `static`。
- **修饰成员变量**，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。
- **修饰成员函数**，修饰成员函数使得不需要生成对象就可以访问该函数，**但是在 `static` 函数内不能访问非静态成员**。

---

**`static` 指针**

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
  Test *p1 = new Test();

  /**********************************指向成员变量的指针******************************/

  // int *p = &Test::ma; //  cannot convert 'int Test::*' to 'int*' in initialization
  int Test::*p = &Test::ma; // 类外定义一个 Test 作用域的指针
  int *q = &Test::mb; // static 可以用普通指针指向

  t1.*p = 20; // 依赖于对象
  p1->*p = 30;
  cout << t1.ma << endl << p1->ma << endl;

  *q = 40; // 不依赖于对象
  cout << Test::mb << endl;

  /********************************指向成员方法的指针********************************/

  // void (*pfunc)() = &Test::func; // error: cannot convert 'void (Test::*)()'
  // to 'void (*)()' in initialization
  void (Test::*pfunc)() = &Test::func;
  void (*qfunc)() = &Test::static_func; // 不依赖于对象

  (t1.*pfunc)();
  (p1->*pfunc)();
  (*qfunc)(); // 不依赖于对象

  delete p1;
  return 0;
}
```

---

# 7 虚函数

## 7.1 虚函数基本概念

- **虚函数指针**：在含有虚函数类的对象中，指向虚函数表，**在运行时确定**。
- **虚函数表**：在程序只读数据段（`.rodata section`），存放虚函数指针，如果派生类实现了基类的某个虚函数，则在虚表中覆盖原本基类的那个虚函数指针，**在编译时**根据类的声明创建。

---

**一个类中添加了虚函数，对这个类有什么影响**？

1. **编译阶段**，编译器为带有虚函数的类产生一个唯一的 `vftable` ，`vftable` 中存放的是 `RTTI` 指针和虚函数的地址
2. **程序运行时**，每一张 `vftable` 都会加载到内存的 `.rodata` 段
3. **带有虚函数的类对象在运行时**，会在内存地址向上偏移处多存储一个 `vfptr`，指向相应类型的 `vftable`。

**注意**

- 一个类型定义的 `n` 个对象，它们的 `vfptr` 指向的都是同一个 `vftable`
- **一个类里面虚函数的个数，不影响对象内存大小，影响的是 `vftable` 的大小**

**纯虚函数**

纯虚函数是一种特殊的虚函数，在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，它的实现留给该基类的派生类去做。

```cpp
virtual int A() = 0;
```

## 7.2 虚函数、纯虚函数

- 类里如果声明了虚函数，这个函数是实现的，哪怕是空实现，它的作用就是为了能让这个函数在它的子类里面可以被覆盖（override），这样的话，编译器就可以使用后期绑定来达到多态了。纯虚函数只是一个接口，是个函数的声明而已，它要留到子类里去实现。
- **虚函数在子类里面可以不重写；但纯虚函数必须在子类实现才可以实例化子类**。
- 虚函数的类用于 “实作继承”，继承接口的同时也继承了父类的实现。纯虚函数关注的是接口的统一性，实现由子类完成。
- **带纯虚函数的类叫[抽象类](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2573-%E7%BA%AF%E8%99%9A%E5%87%BD%E6%95%B0%E5%92%8C%E6%8A%BD%E8%B1%A1%E7%B1%BB)，这种类不能直接生成对象**，而只有被继承，并重写其虚函数后，才能使用。抽象类被继承后，子类可以继续是抽象类，也可以是普通类。
- 虚基类是虚继承中的基类

## 7.3 虚基类和虚继承

- `virtual` 修饰成员方法是虚函数
- `virtual` 修饰继承方式，是虚继承。被虚继承的类，称作虚基类

**虚继承用于解决多继承条件下的菱形继承问题**（浪费存储空间、存在二义性）。

底层实现原理与编译器相关，**一般通过虚基类指针和虚基类表实现**，每个虚继承的子类都有一个虚基类指针（占用一个指针的存储空间，4 字节）和虚基类表（不占用类对象的存储空间）

> 需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了；当虚继承的子类被当做父类继承时，虚基类指针也会被继承。

实际上，`vbptr` 指的是虚基类表指针（virtual base table pointer），该指针指向了一个虚基类表（virtual table），虚表中记录了虚基类与本类的偏移地址；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间。

```cpp
// 32 位系统

#include <iostream>
using namespace std;

class A {
public:
  virtual void func() { cout << "A::func()" << endl; }

  void operator delete(void *p) {
    cout << "operator delete p: " << p << endl;
    free(p);
  }

private:
  int m_a;
};

// class B : public A { // sizeof(B) = 12
class B : virtual public A { // sizeof(B) = 16
public:
  void func() { cout << "B::func()" << endl; }

  void *operator new(size_t size) {
    void *p = malloc(size);
    cout << "operator new p: " << p << endl;
    return p;
  }

private:
  int m_b;
};

int main() {
  A a;
  B b;
  cout << "sizeof(a) = " << sizeof(a) << endl; // sizeof(a) = 8
  cout << "sizeof(b) = " << sizeof(b) << endl;

  // 基类指针指向派生类对象，永远指向的是派生类中基类部分的起始地址
  A *p = new B();                  // operator new p: 0x560a864892c0
  cout << "main p: " << p << endl; // main p: 0x560a864892d0
  p->func();                       // 可以调用
  // delete p; // operator delete p: 0x56058ce402d0   // free(): invalid pointer
  // 派生类内存布局
  //    派生类的虚基类指针（vbptr）：如果派生类虚继承了一个基类，则包含指向虚基类的指针。
  //    派生类的数据成员：首先是派生类自身的数据成员。
  //    派生类的虚指针（vptr）：然后是派生类指向其虚函数表的虚指针。
  //    虚基类的子对象
  return 0;
}
```

## 7.4 虚继承、虚函数

- 相同之处：都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）
- 不同之处：
  - 虚继承
    - 虚基类依旧存在继承类中，只占用存储空间
    - 虚基类表存储的是虚基类相对直接继承类的偏移
  - 虚函数
    - 虚函数不占用存储空间
    - 虚函数表存储的是虚函数地址

## 7.5 哪些函数不能实现成虚函数

**虚函数依赖**

1. **虚函数能产生地址**，存储在 `vftable` 虚函数表中
2. **对象必须存在**（`vfptr` -> `vftable` -> 虚函数地址）

---

- 构造函数
  1. `virtual` 不能修饰构造函数
  2. 构造函数中调用的虚函数，不会产生多态，因为对象还没有构造完成
- `static` 修饰的成员函数
  1. `static` 修饰的成员函数，不依赖于对象，所以不能实现成虚函数

## 7.6 什么时候需要虚析构函数

当基类指针指向派生类时，若基类析构函数不声明为虚函数，则析构时，只会调用基类而不会调用派生类的析构函数，**可能会导致内存泄漏**。

> **基类的虚构函数是 `virtual` 的，那么派生类的析构函数也是 `virtual` 的**

## 7.7 继承多态常见面试题分享

### 7.7.1 问题一

```cpp
class Base {
public:
  virtual void print() { cout << "Base" << endl; }
};

class Derived1 : public Base {
public:
  void print() { cout << "Derived1" << endl; }
};

class Derived2 : public Base {
public:
  void print() { cout << "Derived2" << endl; }
};

int main() {
  Base *p1 = new Derived1();
  Base *p2 = new Derived2();

  int *p11 = (int *)p1;
  int *p22 = (int *)p2;
  swap(p11[0], p22[0]); // swap vptr
  p1->print();  // Derived2
  p2->print();  // Derived1
  delete p1;
  delete p2;
  return 0;
}
```

### 7.7.2 问题二

```cpp
class Base {
public:
  virtual void show(int i = 10) {
    cout << "Base::show(int) called " << i << endl;
  }
};

class Derived : public Base {
public:
  void show(int i = 20) { // 默认参数值不会被使用
    cout << "Derived::show(int) called " << i << endl;
  };
};

int main() {
  Base *p = new Derived();
  // 函数调用，参数压栈是在编译期间确定的，而不是运行期间
  p->show(); // Derived::show(int) called 10
  return 0;
}
```

### 7.7.3 问题三

```cpp
class Base {
public:
// private:
  virtual void show() { cout << "Base::show(int) called " << endl; }
};

class Derived : public Base {
private:
// public:
  void show() { // 默认参数值不会被使用
    cout << "Derived::show(int) called " << endl;
  };
};

int main() {
  Base *p = new Derived();
  // 最终能够调用到Derived::show(int)函数，是在运行时期动态绑定的
  // 方法是否是 public 是在编译阶段就确定的
  // 所以，如果放开上面的注释，就会报错
  p->show(); // Derived::show(int) called
  return 0;
}
```

### 7.7.4 问题四

```cpp
class Base {
public:
  Base() {
    cout << "call Base()" << endl;
    clear();
  }
  void clear() { memset(this, 0, sizeof(*this)); } // 将this指向的内存清零
  virtual void show() { cout << "call Base::show()" << endl; }
};

class Derived : public Base {
public:
  Derived() { cout << "call Derived()" << endl; }
  void show() { cout << "call Derived::show()" << endl; }
};

int main() {
  // Base *pb1 = new Base();
  // pb1->show();  // 段错误  // vfptr指向的虚函数表为空
  // delete pb1;

  Base *pb2 = new Derived(); // call Base()  call Derived()
  // Base 的构造虽然把 vfptr 指向了 0，但是 Derived 的 构造又把 vfptr 指向了 Derived
  // 的虚函数表
  pb2->show(); // call Derived::show()
  delete pb2;
  return 0;
}
```

---

# 8 大厂 C++ 开发面试问题

1. 程序的内存布局
   答： [1.1 进程的虚拟地址空间内存划分和布局](#11-进程的虚拟地址空间内存划分和布局)
2. 堆和栈的区别
3. 函数调用参数是怎么传递的？
4. 函数调用的参数什么顺序压栈？
5. 为什么函数调用的参数要从右往左压栈？
6. 依照代码执行顺序分析一下调用了什么构造函数和顺序，以及析构函数的调用顺序。如果 `fun` 中改成 `return s1 + s1;` 呢？

```cpp
string fun(string s1, string s2) {
  string tmp = s1 + s2;
  return tmp;
}

int main() {
  // 任意的 C++ 编译器都会去做优化：
  //    如果用临时对象拷贝构造新对象
  //    那么临时对象就不产生了，会直接构造新对象
  string s = fun("hello ", "world");
  return 0;
}
```

7. 内存对齐

```cpp
struct Data {
  // char c;
  // char c1;
  // char c2;
  // double d;
};

int main() {
  Data d;
  cout << sizeof(d) << endl;
  return 0;
}
```

8. [leetcode 772. 基本计算器 III 🔒](https://leetcode.cn/problems/basic-calculator-iii/description/)
