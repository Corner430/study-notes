- [1 三块核心内容](#1-三块核心内容)
  - [1.1 进程的虚拟地址空间内存划分和布局](#11-进程的虚拟地址空间内存划分和布局)
  - [1.2 函数调用堆栈详细过程](#12-函数调用堆栈详细过程)
  - [1.3 程序编译链接原理](#13-程序编译链接原理)
- [2 基础部分](#2-基础部分)
  - [2.1 new/delete, malloc/free](#21-newdelete-mallocfree)
  - [2.2 引用和指针](#22-引用和指针)
  - [2.3 const, 指针和引用的结合](#23-const-指针和引用的结合)
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

- [《程序员的自我修养》第 2, 3, 4, 6 章](https://github.com/Corner430/study-notes/blob/main/cpp/程序员的自我修养笔记.md) 

## 1.1 进程的虚拟地址空间内存划分和布局





![20240505222654](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240505222654.png)

- `.text`: 已编译程序的机器代码
- `.rodata`: **只读数据**，比如 `printf` 语句中的格式串和开关语句的跳转表
- `.data`: **已初始化的全局和静态 C 变量。局部 C 变量在运行时被保存在栈中**，既不在 `.data` 也不在 `.bss` 中
- `.bss`: **未初始化的全局和静态 C 变量，以及所有被初始化为 0 的全局或静态变量**。不需要占用实际的磁盘空间


```cpp
#include <iostream>

using namespace std;

int gdata1 = 10; // .data
int gdata2 = 0;  // .bss
int gdata3;      // .bss

static int gdata4 = 11; // .data
static int gdata5 = 0;  // .bss
static int gdata6;      // .bss

int main() {
  int a = 12;
  int b = 0;
  int c;

  static int e = 13; // .data
  static int f = 0;  // .bss
  static int g;      // .bss
  return 0;
}
```

## 1.2 函数调用堆栈详细过程

## 1.3 程序编译链接原理

------------

# 2 基础部分

## 2.1 new/delete, malloc/free

## 2.2 引用和指针

## 2.3 const, 指针和引用的结合

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