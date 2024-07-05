- [1 优化](#1-优化)
  - [1.1 临时对象](#11-临时对象)
  - [1.2 返回局部对象](#12-返回局部对象)
  - [1.3 对象优化规则](#13-对象优化规则)
  - [1.4 右值引用优化](#14-右值引用优化)
  - [1.5 万能引用](#15-万能引用)
  - [1.6 `move` 语义 和 `forward` 类型完美转发](#16-move-语义-和-forward-类型完美转发)
    - [1.6.1 `move` 语义](#161-move-语义)
      - [1.6.1.1 关键函数](#1611-关键函数)
      - [1.6.1.2 示例代码](#1612-示例代码)
    - [1.6.2 `forward` 和 完美转发](#162-forward-和-完美转发)
      - [1.6.2.1 问题背景](#1621-问题背景)
      - [1.6.2.2 `std::forward`的工作原理](#1622-stdforward的工作原理)
      - [1.6.2.3 如何实现完美转发：](#1623-如何实现完美转发)
      - [1.6.2.4 示例代码](#1624-示例代码)
    - [1.6.3 总结](#163-总结)
- [2 智能指针](#2-智能指针)
  - [2.1 智能指针介绍](#21-智能指针介绍)
  - [2.2 实现智能指针](#22-实现智能指针)
  - [2.3 不带引用计数的智能指针](#23-不带引用计数的智能指针)
    - [2.3.1 `auto_ptr`](#231-auto_ptr)
    - [2.3.2 `scoped_ptr`](#232-scoped_ptr)
    - [2.3.3 `unique_ptr`](#233-unique_ptr)
  - [2.4 带引用计数的智能指针 `shared_ptr` 和 `weak_ptr`](#24-带引用计数的智能指针-shared_ptr-和-weak_ptr)
  - [2.5 智能指针的交叉引用（循环引用）问题](#25-智能指针的交叉引用循环引用问题)
  - [2.6 解决多线程访问共享对象问题](#26-解决多线程访问共享对象问题)
  - [2.7 自定义删除器](#27-自定义删除器)
- [3 绑定器和函数对象、`lambda` 表达式](#3-绑定器和函数对象lambda-表达式)
  - [3.1 bind1st 和 bind2nd 实现原理](#31-bind1st-和-bind2nd-实现原理)
  - [3.2 函数对象](#32-函数对象)
  - [3.3 模版的完全特例化和部分特例化](#33-模版的完全特例化和部分特例化)
  - [3.4 `function` 函数对象类型的实现原理](#34-function-函数对象类型的实现原理)
  - [3.5 `bind` 和 `function` 的使用](#35-bind-和-function-的使用)
  - [3.6 lambda 表达式](#36-lambda-表达式)
- [4 C++11 内容汇总、多线程应用实践](#4-c11-内容汇总多线程应用实践)
  - [4.1 常用知识点总结](#41-常用知识点总结)
  - [4.2 多线程类 `thread`](#42-多线程类-thread)
  - [4.3 线程互斥锁 `mutex`](#43-线程互斥锁-mutex)
  - [4.4 线程间同步通信-----生产者消费者模型](#44-线程间同步通信-----生产者消费者模型)
  - [4.5 `lock_guard` 和 `unique_lock`](#45-lock_guard-和-unique_lock)
  - [4.6 基于 CAS 操作的 atomic 原子类型](#46-基于-cas-操作的-atomic-原子类型)
- [5 设计模式](#5-设计模式)
  - [5.1 单例模式](#51-单例模式)
    - [5.1.1 饿汉式和懒汉式单例模式](#511-饿汉式和懒汉式单例模式)
    - [5.1.2 嵌套类和静态对象的方式解决单例模式的资源释放问题](#512-嵌套类和静态对象的方式解决单例模式的资源释放问题)
    - [5.1.3 线程安全的单例模式](#513-线程安全的单例模式)
  - [5.2 简单工厂、工厂方法、抽象工厂](#52-简单工厂工厂方法抽象工厂)
    - [5.2.1 简单工厂模式（Simple Factory）](#521-简单工厂模式simple-factory)
    - [5.2.2 工厂方法模式（Factory Method）](#522-工厂方法模式factory-method)
    - [5.2.3 抽象工厂模式（Abstract Factory）](#523-抽象工厂模式abstract-factory)
  - [5.3 代理（Proxy）模式](#53-代理proxy模式)
  - [5.4 装饰器（Decorator）模式](#54-装饰器decorator模式)
  - [5.5 适配器（Adapter）模式](#55-适配器adapter模式)
  - [5.6 观察者-监听者（Observer）/发布-订阅 模式](#56-观察者-监听者observer发布-订阅-模式)
    - [5.6.1 观察者模式简介](#561-观察者模式简介)
    - [5.6.2 简述 MVC 模式](#562-简述-mvc-模式)
    - [5.6.3 观察者模式的 UML 图](#563-观察者模式的-uml-图)
    - [5.6.4 观察者模式的代码实现](#564-观察者模式的代码实现)
    - [5.6.5 多线程中的观察者模式](#565-多线程中的观察者模式)
- [6 C++11 容器 `emplace` 方法原理剖析](#6-c11-容器-emplace-方法原理剖析)

# 1 优化

## 1.1 临时对象

> - `C++` 编译器对于对象构造的优化：用临时对象生成新对象时，不产生临时对象，直接构造新对象
> - 临时对象的生存周期：表达式结束时
> - **可以使用引用来引用临时对象, 但是不能使用指针来指向临时对象**
> - 赋值操作, 产生临时对象
> - 显式生成临时对象: `Test(20)`
> - 隐式生成临时对象: `t2 = 30`

```cpp
#include <iostream>
using namespace std;

class Test {
public:
  Test() { cout << "默认无参构造" << endl; }
  Test(int i) { cout << "有参构造" << endl; }
  Test(const Test &t) { cout << "拷贝构造" << endl; }
  ~Test() { cout << "析构函数" << endl; }
  Test &operator=(const Test &t) {
    cout << "赋值运算符重载" << endl;
    return *this;
  }
};

int main() {
  Test t1;      // 默认无参构造
  Test t2(t1);  // 拷贝构造
  Test t3 = t1; // 拷贝构造
  Test(20);     // 显式生成临时对象, 生存周期: 表达式结束时

  /*
   * C++ 编译器对于对象构造的优化：
   * 用临时对象生成新对象时，不产生临时对象，直接构造新对象
   */

  Test t4 = Test(20); // 有参构造, 等价于 Test t4(20);

  cout << "----------------" << endl;

  t4 = t2;       // 赋值运算符重载
  t4 = Test(30); // 有参构造, 赋值运算符重载, 析构函数

  cout << "------显式生成临时对象--------" << endl;

  t4 = (Test)30; // 有参构造, 赋值运算符重载, 析构函数
                 // 这是一个显式的强制类型转换: int -> Test(int)

  cout << "------隐式生成临时对象--------" << endl;

  t4 = 30; // 有参构造, 赋值运算符重载, 析构函数
           // 这是一个隐式的强制类型转换 int -> Test(int)

  cout << "-------指针和引用 && 临时对象-------" << endl;

  // Test *p = &Test(40); // 有参构造, 指针指向临时对象, 临时对象析构
  // 报错 taking address of rvalue [-fpermissive]

  const Test &r = Test(50); // 有参构造

  // > 可以使用引用来引用临时对象, 但是不能使用指针来指向临时对象

  return 0;
}
```

```cpp
#include <iostream>
using namespace std;

class Test {
public:
  Test(int a = 5, int b = 5) : ma(a), mb(b) {
    cout << "Test(int, int)" << endl;
  }
  ~Test() { cout << "~Test()" << endl; }

  Test(const Test &src) : ma(src.ma), mb(src.mb) {
    cout << "Test(const Test &src)" << endl;
  }

  Test &operator=(const Test &src) {
    cout << "operator=" << endl;
    ma = src.ma;
    mb = src.mb;
    return *this;
  }

private:
  int ma;
  int mb;
};

Test t1(10, 20); // 1 Test(int, int)
int main() {
  Test t2(20, 30);               // 3 Test(int, int)
  Test t3 = t2;                  // 4 Test(const Test &src)
  static Test t4 = Test(30, 30); // 5 Test(int, int), 不产生临时对象

  cout << "-------赋值操作, 产生临时对象--------" << endl;
  t2 = Test(40, 40); // 6 Test(int, int), operator=, ~Test()
  cout << "----------------" << endl;
  t2 = (Test)(50, 50); // 7 Test(int, int), operator=, ~Test()
  cout << "----------------" << endl;
  t2 = 60; // 8 Test(int, int), operator=, ~Test()

  cout << "--------指针和引用--------" << endl;
  Test *p1 = new Test(70, 80); // 9 Test(int, int)
  Test *p2 = new Test[2];      // 10 Test(int, int), Test(int, int)
  // Test *p3 = &Test(80, 90);    // 11 Test(int, int), ~Test().
  // 报错 taking address of rvalue [-fpermissive]

  const Test &p4 = Test(90, 100); // 12 Test(int, int), ~Test(

  delete p1;   // 13 ~Test()
  delete[] p2; // 14 ~Test(), ~Test()

  cout << "--------结束--------" << endl;
  return 0;
}
Test t5(40, 50); // 2 Test(int, int)
```

## 1.2 返回局部对象

```cpp
#include <iostream>
using namespace std;

class Test {
public:
  Test(int data = 10) : ma(data) { cout << "Test(int)" << endl; }
  ~Test() { cout << "~Test()" << endl; }
  Test(const Test &rhs) : ma(rhs.ma) { cout << "Test(const Test &)" << endl; }
  Test &operator=(const Test &rhs) {
    cout << "operator=" << endl;
    if (this != &rhs)
      ma = rhs.ma;
    return *this;
  }

  int getData() const { return ma; }

private:
  int ma;
};

Test GetObject(Test t) { // 参数传递，会调用拷贝构造函数
  cout << "-------------------" << endl;
  int val = t.getData();
  Test tmp(val);
  return tmp;
  // > tmp 是一个局部对象，函数返回时会调用拷贝构造函数在 main 函数中创建一个新的临时对象
  // return Test(val); // 优化: 直接返回一个临时对象
}

int main() {
  Test t1(20);
  cout << "-------------------" << endl;
  // Test t2 = GetObject(t1);
  Test t2;
  t2 = GetObject(t1);
  cout << "-------------------" << endl;
  return 0;
}

/****************** 优化后 ******************
Test GetObject(const Test &t) {
  int val = t.getData();
  return Test(val);
}

int main() {
  Test t1(20);
  Test t2 = GetObject(t1);
  return 0;
}
********************************************/
```

## 1.3 对象优化规则

1. 函数参数传递过程中，对象优先按引用传递，如果不行，再按值传递
2. 函数返回对象时，优先返回临时对象，而不是定义过的局部对象（这样会由于作用域问题，函数结束时再在上层函数构造一个临时对象）。
3. 接收返回值是对象的函数调用时，优先按初始化的方式接收，而不是赋值的方式接收

> **临时量属于右值!!!**

## 1.4 右值引用优化

> 如果**返回/传入的是一个临时对象**，那么可以使用右值引用来接收，这样可以避免拷贝构造函数的调用
> **注意要把不用的指针置为 `nullptr`**

```cpp
CMyString operator+(const CMyString &lhs, const CMyString &rhs) {
  char *ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
  strcpy(ptmp, lhs.mptr);
  strcat(ptmp, rhs.mptr);

  /* ------这会导致内存泄漏------ */
  return CMyString(ptmp);

  /******** 修复内存泄漏 **********/
  CMyString tmpStr(ptmp);
  delete[] ptmp;
  return tmpStr;

  /******** 效率优化 **********/
  CMyString tmpStr;
  tmpStr.mptr = new char[strlen(lhs.m_pstr) + strlen(rhs.m_pstr) + 1];
  ctrcpy(tmpStr.mptr, lhs.mptr);
  strcat(tmpStr.mptr, rhs.mptr);
  return tmpStr;
}

int main() {
  CMyString str1 = "Hello";
  CMyString str2 = " World";
  CMyString str3 =
      str1 + str2; // 优化: 重载 = 操作符 和 + 操作符, 使得 = 传入的参数是一个右值引用
  cout << str3 << endl;
  return 0;
}
```

## 1.5 万能引用

> 万能引用是右值引用的一种特殊形式，它可以接受任何类型的参数，包括左值和右值。万能引用的语法是`T&&`，其中`T`是一个模板参数。

```cpp
// template <typename T> void print(T &val) { cout << val << endl; }

/****************** 1. 模版重载可以解决问题 ******************/
/****************** 2. 模版参数类型万能引用，删除上面的，留这一个就 OK 了
 * ******************/
template <typename T> void print(T &&val) { cout << val << endl; }

int main() {
  int a = 5;
  print(a);
  print(10); // cannot bind non-const lvalue reference of type 'int&' to an
  // rvalue of type 'int'

  return 0;
}
```

之所以可以万能引用，依赖于**引用折叠**：

|                     | 引用折叠前 | 引用折叠后 |
| ------------------- | ---------- | ---------- |
| 左值引用 - 左值引用 | T& &       | T&         |
| 左值引用 - 右值引用 | T& &&      | T&         |
| 右值引用 - 左值引用 | T&& &      | T&         |
| 右值引用 - 右值引用 | T&& &&     | T&&        |

## 1.6 `move` 语义 和 `forward` 类型完美转发

### 1.6.1 `move` 语义

在 `C++11` 之前，对象的拷贝操作是通过拷贝构造函数和拷贝赋值运算符实现的，这对于性能要求高的场景（如容器类的实现）可能会造成不必要的性能开销。为了优化资源的管理，`C++11` 引入了移动语义。

**移动语义的核心概念**是将资源（如内存、文件句柄等）的所有权从一个对象转移到另一个对象，而不是复制资源。**这是通过引入右值引用（rvalue reference）来实现的**，右值引用使用 `&&` 表示。

#### 1.6.1.1 关键函数

1. **移动构造函数**：它接受一个右值引用作为参数，并将资源从参数对象移动到当前对象。
   ```cpp
   class MyClass {
   public:
       MyClass(MyClass&& other) noexcept {
           // 将other的资源移到当前对象
       }
   };
   ```
2. **移动赋值运算符**：它也接受一个右值引用作为参数，并将资源从参数对象移动到当前对象。

   ```cpp
   MyClass& operator=(MyClass&& other) noexcept {
       // 将other的资源移到当前对象
       return *this;
   }
   ```

3. **`std::move`**：`std::move`是一个标准库函数模板，它**将一个左值转换为右值引用**，从而允许该对象的资源被移动。
   ```cpp
   std::vector<int> v1 = {1, 2, 3};
   std::vector<int> v2 = std::move(v1); // 现在v1的资源被移动到v2，v1变为空
   ```

#### 1.6.1.2 示例代码

```cpp
#include <iostream>
#include <utility> // std::move

class MyClass {
public:
  // 构造函数
  MyClass(size_t size) : size(size), data(new int[size]) {
    std::cout << "Constructor: allocating " << size << " ints." << std::endl;
  }

  // 析构函数
  ~MyClass() {
    delete[] data;
    std::cout << "Destructor: releasing " << size << " ints." << std::endl;
  }

  // 移动构造函数
  MyClass(MyClass &&other) noexcept : size(other.size), data(other.data) {
    other.size = 0;
    other.data = nullptr;
    std::cout << "Move Constructor: moving resource." << std::endl;
  }

  // 移动赋值运算符
  MyClass &operator=(MyClass &&other) noexcept {
    if (this != &other) {
      delete[] data; // 释放已有资源
      size = other.size;
      data = other.data;
      other.size = 0;
      other.data = nullptr;
      std::cout << "Move Assignment: moving resource." << std::endl;
    }
    return *this;
  }

  // 禁用拷贝构造函数和拷贝赋值运算符
  MyClass(const MyClass &) = delete;
  MyClass &operator=(const MyClass &) = delete;

private:
  size_t size;
  int *data;
};

int main() {
  MyClass a(10);           // 正常构造对象a
  MyClass b(std::move(a)); // 移动构造对象b，a的资源被转移到b
  MyClass c(20);           // 正常构造对象c
  c = std::move(b);        // 移动赋值，将b的资源转移到c

  std::cout << "End of main." << std::endl;
  return 0;
}
```

### 1.6.2 `forward` 和 完美转发

完美转发是指在模板函数中，无论传递给模板函数的是左值还是右值，都能正确地将参数转发给另一个函数。这通过 `std::forward` 实现。

#### 1.6.2.1 问题背景

在编写模板函数时，我们希望能够保留传递给函数的参数的值类别（左值或右值），以便能够高效地调用其他函数。普通的参数传递会导致值类别的丢失。

#### 1.6.2.2 `std::forward`的工作原理

`std::forward`是一个函数模板，用于将参数**完美**地转发给另一个函数。它会根据传递给它的参数的值类别（左值或右值），决定是传递左值还是右值。

```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward确保arg的值类别被保留
    someFunction(std::forward<T>(arg));
}
```

#### 1.6.2.3 如何实现完美转发：

1. **模板参数**：使用万能引用（universal reference），即`T&&`，这是一个可以接受左值或右值的引用。
2. **`std::forward`**：在内部调用中使用 `std::forward`，它会根据模板参数的类型判断是左值还是右值，从而进行相应的转发。

#### 1.6.2.4 示例代码

```cpp
#include <utility>
#include <iostream>

void overloaded(int& x) {
    std::cout << "Left value overload\n";
}

void overloaded(int&& x) {
    std::cout << "Right value overload\n";
}

template<typename T>
void wrapper(T&& arg) {
    overloaded(std::forward<T>(arg));
}

int main() {
    int a = 5;
    wrapper(a); // 左值
    wrapper(5); // 右值
    return 0;
}
```

在这个例子中，`wrapper`函数会根据传入参数的值类别，调用对应的`overloaded`函数版本。

### 1.6.3 总结

- **移动语义**通过右值引用和 `std::move` 来实现资源的高效转移，避免不必要的拷贝。
- **完美转发**通过万能引用和 `std::forward` 来保持参数的值类别，从而高效地调用其他函数。

```cpp
#include <iostream>
#include <utility>
#include <string>

// 泛型工厂函数，使用完美转发和移动语义
template<typename T, typename... Args>
T createObject(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

class MyClass {
public:
    MyClass(const std::string& str) {
        std::cout << "Constructed with lvalue: " << str << std::endl;
    }

    MyClass(std::string&& str) {
        std::cout << "Constructed with rvalue: " << str << std::endl;
    }
};

int main() {
    std::string myStr = "Hello";

    // 传递左值
    MyClass obj1 = createObject<MyClass>(myStr);

    // 传递右值
    MyClass obj2 = createObject<MyClass>(std::move(myStr));

    return 0;
}
```

# 2 智能指针

## 2.1 智能指针介绍

**裸指针的问题：**

1. **资源泄漏**：忘记释放资源，导致资源无法回收。
2. **重复释放**：同一资源被释放多次，导致野指针的产生，进而引发程序崩溃。
3. **条件中断**：虽然在代码的后面编写了释放资源的逻辑，但由于程序逻辑中某些条件的满足，中途返回，导致资源释放的代码未被执行。
4. **异常处理**：在代码运行过程中发生异常，随着异常栈的展开，导致资源释放的代码未被执行。

智能指针的“智能”之处在于，它能够自动管理资源的释放，使用户无需手动处理资源回收。无论程序的执行路径如何，包括正常执行和异常抛出，**智能指针都能确保在资源不再需要时进行适当的释放**，从而避免上述裸指针的问题。智能指针通过这种方式，提供了更安全和可靠的资源管理机制。

## 2.2 实现智能指针

利用栈上对象出作用域会自动析构的特性，可以将资源释放的代码放在析构函数中执行，从而实现智能指针。

1. **使用裸指针**

```cpp
int main() {
    int *p = new int;
    /* 其它的代码... */
    /*
    如果这里忘记写delete，或者上面的代码段中程序return掉了，
    没有执行到这里，都会导致这里没有释放内存，内存泄漏
    */
    delete p;

    return 0;
}
```

2. **使用智能指针**

```cpp
template <typename T> class CSmartPtr {
public:
  CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}
  ~CSmartPtr() { delete mptr; }

private:
  T *mptr;
};

int main() {
  CSmartPtr<int> ptr(new int);
  /* 其它的代码... */
  /* 由于 ptr
  是栈上的智能指针对象，不管是函数正常执行完，还是运行过程中出现异常，
  栈上的对象都会自动调用析构函数，在析构函数中进行了 delete 操作，保证释放资源
  */
  return 0;
}
```

上面的代码是一个非常简单的智能指针，主要用了以下两点：

1. 智能指针通过将裸指针进行面向对象的封装，在构造函数中初始化资源地址，在析构函数中负责释放资源。
2. 利用栈上对象出作用域自动析构的特性，在智能指针的析构函数中保证释放资源。

因此，**智能指针通常定义在栈上**。有一个常见的面试问题是“**能不能在堆上定义智能指针**？”。例如，代码 `CSmartPtr *p = new CSmartPtr(new int);` 虽然定义了一个智能指针类型，但它实际上是一个裸指针，仍需要手动 `delete`，这样又回到了裸指针面临的问题。

要使智能指针的使用与裸指针相似，还需要提供裸指针常见的 `*` 和 `->` 运算符的重载函数，使用起来才真正像裸指针。代码扩展如下：

```cpp
template <typename T> class CSmartPtr {
public:
  CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}
  ~CSmartPtr() { delete mptr; }

  T &operator*() { return *mptr; }
  const T &operator*() const { return *mptr; }

  T *operator->() { return mptr; }
  const T *operator->() const { return mptr; }

private:
  T *mptr;
};

int main() {
  CSmartPtr<int> ptr(new int);
  *ptr = 20;
  std::cout << *ptr << std::endl;
  return 0;
}
```

上面的智能指针，使用起来就和普通的裸指针非常相似了，但它仍存在一些问题。例如：

```cpp
int main() {
  CSmartPtr<int> ptr1(new int);
  CSmartPtr<int> ptr2(ptr1);
  return 0;
}
```

这个 `main` 函数会导致程序崩溃，原因是默认的拷贝构造函数做的是浅拷贝，两个智能指针都持有同一个资源。`ptr2` 先析构释放资源后，`ptr1` 析构时会尝试删除已经被释放的资源，导致程序崩溃。因此，智能指针需要解决以下问题：

1. 如何解决智能指针的浅拷贝问题。
2. 当多个智能指针指向同一个资源时，如何保证资源只释放一次，而不是每个智能指针都释放一次，避免程序运行中出现不可预期的严重后果。

## 2.3 不带引用计数的智能指针

`C++` 标准库中提供了几种不带引用计数的智能指针，主要包括：`auto_ptr`，`scoped_ptr`，`unique_ptr`。

### 2.3.1 `auto_ptr`

```cpp
template <class _Ty>
class auto_ptr {
public:
  typedef _Ty element_type;

  // explicit 关键字表示该构造函数是显式的，禁止隐式转换
  // noexcept 关键字表示该函数不会抛出异常
  explicit auto_ptr(_Ty *_Ptr = nullptr) noexcept : _Myptr(_Ptr) {}

  auto_ptr(auto_ptr &_Right) noexcept : _Myptr(_Right.release()) {}

  _Ty *release() noexcept {
    _Ty *_Tmp = _Myptr;
    _Myptr = nullptr;
    return _Tmp;
  }

private:
  _Ty *_Myptr;
};
```

`auto_ptr` 的拷贝构造函数会将原来的指针置为 `nullptr`，只保留最后一个 `auto_ptr` 持有资源地址。例如：

```cpp
int main()
{
    auto_ptr<int> p1(new int);
    auto_ptr<int> p2 = p1; // p1 被置为 nullptr
    *p1 = 10; // 访问空指针，危险
    return 0;
}
```

由于 `auto_ptr` 会在拷贝时置原指针为 `nullptr`，因此不适合放在容器中。例如：

```cpp
int main()
{
    vector<auto_ptr<int>> vec;
    vec.push_back(auto_ptr<int>(new int(10)));
    vec.push_back(auto_ptr<int>(new int(20)));
    vec.push_back(auto_ptr<int>(new int(30)));
    cout << *vec[0] << endl; // 打印 10
    vector<auto_ptr<int>> vec2 = vec;
    cout << *vec[0] << endl; // 访问空指针，程序崩溃
    return 0;
}
```

**总结**：`auto_ptr` 通过将原指针置为 `nullptr` 来避免浅拷贝问题，然而由于其不安全性和局限性，`C++11` 引入了更好的替代品，不建议使用 `auto_ptr`。

### 2.3.2 `scoped_ptr`

```cpp
template <class T> class scoped_ptr {
private:
  T *px; // 指向管理的对象

  // 禁止复制和赋值
  scoped_ptr(scoped_ptr const &);
  scoped_ptr &operator=(scoped_ptr const &);

  // 禁止比较
  void operator==(scoped_ptr const &) const;
  void operator!=(scoped_ptr const &) const;

public:
  typedef T element_type; // 元素类型

  // 构造函数，接受一个指针，取得其所有权
  explicit scoped_ptr(T *p = 0) : px(p) {}

  // 析构函数，删除所管理的对象
  ~scoped_ptr() { boost::checked_delete(px); }
};
```

`scoped_ptr` 通过私有化拷贝构造函数和赋值运算符来杜绝浅拷贝，从根本上避免了多指针指向同一资源的问题。例如：

```cpp
int main()
{
    scoped_ptr<int> p1(new int);
    // scoped_ptr<int> p2 = p1; // 编译错误，禁止拷贝构造
    return 0;
}
```

由于 `scoped_ptr` 不允许拷贝构造和赋值，因此不能用于容器中，如果尝试容器拷贝或赋值，会导致编译错误。

**总结**：`scoped_ptr` 通过禁用拷贝构造和赋值操作，确保资源的唯一所有权，避免了浅拷贝问题。

### 2.3.3 `unique_ptr`

`unique_ptr` 是 C++11 引入的一种智能指针，它通过右值引用解决了所有权转移的问题，且不允许复制操作。部分源码如下：

```cpp
template <class _Ty, class _Dx = default_delete<_Ty>> class unique_ptr {
public:
  typedef _Ty element_type;                  // 所指向的对象的类型
  typedef _Dx deleter_type;                  // 删除器的类型
  typedef typename _Mybase::pointer pointer; // 指针的类型

  // 移动构造函数，接管 _Right 的所有权
  unique_ptr(unique_ptr &&_Right) noexcept
      : _Mybase(_Right.release(), std::forward<_Dx>(_Right.get_deleter())) {}

  // 移动赋值操作符，接管 _Right 的所有权
  unique_ptr &operator=(unique_ptr &&_Right) noexcept {
    if (this != std::addressof(_Right)) {
      reset(_Right.release());
      this->get_deleter() = std::forward<_Dx>(_Right.get_deleter());
    }
    return *this;
  }

  // 析构函数，删除所指向的对象
  ~unique_ptr() noexcept {
    if (get() != pointer()) {
      this->get_deleter()(get());
    }
  }

  // 重载 -> 操作符，返回所指向的对象
  pointer operator->() const noexcept { return this->_Myptr(); }

  // 获取所指向的对象
  pointer get() const noexcept { return this->_Myptr(); }

  // 转换为 bool，检查是否为空
  explicit operator bool() const noexcept { return get() != pointer(); }

  // 释放所有权，并返回所指向的对象
  pointer release() noexcept {
    pointer _Ans = get();
    this->_Myptr() = pointer();
    return _Ans;
  }

  // 重置，删除当前对象并接管 _Ptr 的所有权
  void reset(pointer _Ptr = pointer()) noexcept {
    pointer _Old = get();
    this->_Myptr() = _Ptr;
    if (_Old != pointer()) {
      this->get_deleter()(_Old);
    }
  }

  // 禁止复制
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;
};
```

`unique_ptr` 禁用了拷贝构造和赋值运算符，只允许通过右值引用进行所有权转移：

```cpp
int main() {
  unique_ptr<int> ptr1(new int);
  unique_ptr<int> ptr2 = std::move(ptr1); // 使用右值引用转移所有权
  ptr2 = std::move(ptr1);                 // 使用右值引用赋值操作
  return 0;
}

unique_ptr<int> test_uniqueptr() {
  unique_ptr<int> ptr1(new int);
  return ptr1; // 返回值使用右值引用转移所有权
}
```

`unique_ptr` 提供了 `reset`、`swap` 等方法，进一步增强了其灵活性和实用性。

**总结**：`unique_ptr` 是现代 C++ 推荐使用的不带引用计数的智能指针，提供了安全的所有权转移机制，同时避免了浅拷贝问题。

## 2.4 带引用计数的智能指针 `shared_ptr` 和 `weak_ptr`

> 1. 引用计数的概念
>    带引用计数的智能指针允许多个智能指针指向同一个资源，每一个智能指针都会增加资源的引用计数。当一个智能指针析构时，引用计数减少。最后一个智能指针将引用计数减少到 0 时，资源被释放。引用计数机制确保了资源在所有指针失效前不会被释放。
>
> 2. 线程安全
>    引用计数的增加和减少需要是线程安全的操作。`shared_ptr` 和 `weak_ptr` 底层通过 CAS（Compare-And-Swap）操作来保证引用计数的原子性，因此它们本身是线程安全的。
>
> 3. `shared_ptr` 智能指针的引用计数在哪里存放？
>
> ```cpp
> private:
> element_type* _Ptr{nullptr};
> _Ref_count_base* _Rep{nullptr};
> ```
>
> `shared_ptr` 有两个成员变量：`_Ptr` 指向内存资源，`_Rep` 指向堆上分配的计数器对象，该对象包含了资源的引用计数器。因此，`shared_ptr` 的引用计数器存储在堆内存中。
>
> 4. `shared_ptr` 和 `weak_ptr` 的应用场景
>
> `shared_ptr` 是一种强智能指针，确保资源的引用计数在所有 `shared_ptr` 对象失效前不会降为零。使用 `shared_ptr` 的场景包括：
>
> - **共享资源**：多个对象或线程需要共享同一个资源。
> - **生命周期管理**：确保资源在其所有者范围内有效。
>
> `weak_ptr` 是一种弱智能指针，不影响资源的引用计数。它主要用于解决循环引用问题，并且提供了一种安全访问 `shared_ptr` 所管理资源的方法。使用 `weak_ptr` 的场景包括：
>
> - **避免循环引用**：两个对象相互引用时，使用 `weak_ptr` 打破循环。
> - **缓存和观察者模式**：弱引用缓存或观察者模式中的观察者不需要拥有资源的所有权。

## 2.5 智能指针的交叉引用（循环引用）问题

在使用智能指针管理资源时，可能会遇到交叉引用（循环引用）的问题。下面通过一个示例代码来说明这个问题，并展示如何通过使用 `weak_ptr` 来解决。

```cpp
#include <iostream>
#include <memory>
using namespace std;

class B; // 前置声明类B
class A {
public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }
  shared_ptr<B> _ptrb; // 指向 B 对象的智能指针
};

class B {
public:
  B() { cout << "B()" << endl; }
  ~B() { cout << "~B()" << endl; }
  shared_ptr<A> _ptra; // 指向 A 对象的智能指针
};

int main() {
  shared_ptr<A> ptra(new A()); // ptra指向A对象，A的引用计数为1
  shared_ptr<B> ptrb(new B()); // ptrb指向B对象，B的引用计数为1
  ptra->_ptrb = ptrb; // A对象的成员变量_ptrb也指向B对象，B的引用计数为2
  ptrb->_ptra = ptra; // B对象的成员变量_ptra也指向A对象，A的引用计数为2

  cout << ptra.use_count() << endl; // 打印A的引用计数结果:2
  cout << ptrb.use_count() << endl; // 打印B的引用计数结果:2

  /*
  出main函数作用域，ptra和ptrb两个局部对象析构，分别给A对象和
  B对象的引用计数从2减到1，达不到释放A和B的条件（释放的条件是
  A和B的引用计数为0），因此造成两个new出来的A和B对象无法释放，
  导致内存泄露，这个问题就是“强智能指针的交叉引用(循环引用)问题”
  */
  return 0;
}

/*---代码输出---*/
A()
B()
2
2
```

可以看到，A 和 B 对象并没有析构。这是因为交叉引用导致它们的引用计数无法降为 0，导致内存泄漏。

**解决交叉引用问题**的关键在于使用 `weak_ptr`。弱智能指针 `weak_ptr` 不会改变资源的引用计数，只是一个观察者，通过观察 `shared_ptr` 来判定资源是否存在。`weak_ptr` 需要通过 `lock` 方法提升为 `shared_ptr` 才能访问资源。

```cpp
#include <iostream>
#include <memory>
using namespace std;

class B; // 前置声明类B
class A {
public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }
  void testA() { cout << "testA" << endl; }
  weak_ptr<B> _ptrb; // 指向B对象的弱智能指针。引用对象时，用弱智能指针
};

class B {
public:
  B() { cout << "B()" << endl; }
  ~B() { cout << "~B()" << endl; }
  void func() {
    // _ptra->testA(); // 运算符 -> 或 ->* 应用于 "std::weak_ptr<A>"
    // 而不是指针类型
    shared_ptr<A> ps =
        _ptra.lock(); // 通过lock()函数获取shared_ptr对象，提升为强智能指针
    if (ps)
      ps->testA(); // 通过强智能指针调用testA函数
  }
  weak_ptr<A> _ptra; // 指向A对象的弱智能指针。引用对象时，用弱智能指针
};

int main() {
  shared_ptr<A> ptra(new A()); // ptra指向A对象，A的引用计数为1
  shared_ptr<B> ptrb(new B()); // ptrb指向B对象，B的引用计数为1

  // A对象的成员变量_ptrb也指向B对象，B的引用计数为1，因为是弱智能指针，引用计数没有改变
  ptra->_ptrb = ptrb;
  // B对象的成员变量_ptra也指向A对象，A的引用计数为1，因为是弱智能指针，引用计数没有改变
  ptrb->_ptra = ptra;

  ptrb->func(); // 通过ptrb调用B对象的func函数,
                // func函数中通过弱智能指针调用A对象的testA函数

  cout << ptra.use_count() << endl; // 打印结果:1
  cout << ptrb.use_count() << endl; // 打印结果:1

  /*
  出main函数作用域，ptra和ptrb两个局部对象析构，分别给A对象和
  B对象的引用计数从1减到0，达到释放A和B的条件，因此new出来的A和B对象
  被析构掉，解决了“强智能指针的交叉引用(循环引用)问题”
  */
  return 0;
}


/*****修改后代码的输出*****/
A()
B()
testA
1
1
~B()
~A()
```

可以看到，A 和 B 对象正常析构，交叉引用问题得到解决。

> - 交叉引用（循环引用）问题会导致资源无法释放，造成内存泄漏。通过使用 `weak_ptr` 代替 `shared_ptr` 可以解决这个问题。**关键在于在定义对象时使用强智能指针 `shared_ptr`，而在引用对象时使用弱智能指针 `weak_ptr`**。这种方法确保了引用计数的正确管理，避免了循环引用问题。
> - 如果需要在 `weak_ptr` 指向的对象上调用成员函数，需要先通过 `lock` 方法将 `weak_ptr` 提升为 `shared_ptr`，然后再调用成员函数。

## 2.6 解决多线程访问共享对象问题

在多线程环境中，访问共享对象可能会引发线程安全问题。[Muduo](https://github.com/chenshuo/muduo)是一个开源的 C++网络库，其源代码中优雅地运用了 `shared_ptr` 和 `weak_ptr` 来解决这类问题。具体问题描述如下：当线程 A 正在析构一个对象时，线程 B 可能同时要调用该对象的成员方法。如果线程 B 在对象已经被析构的情况下仍然访问该对象，就会导致不可预期的错误。

```cpp
#include <iostream>
#include <thread>
using namespace std;

class Test {
public:
  Test() : _ptr(new int(20)) { cout << "Test()" << endl; }
  ~Test() {
    delete _ptr;
    _ptr = nullptr;
    cout << "~Test()" << endl;
  }
  void show() { cout << *_ptr << endl; }

private:
  int *volatile _ptr; // volatile 修饰指针，防止编译器优化
};

void threadProc(Test *p) {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // 等待2秒
  p->show(); // 在对象已析构的情况下尝试访问成员方法
}

int main() {
  Test *p = new Test();
  std::thread t1(threadProc, p); // 子线程访问对象
  delete p;                      // 主线程析构对象
  t1.join();                     // 等待子线程结束
  return 0;
}
```

在上述示例中，主线程在删除对象后，子线程仍然尝试访问该对象的成员方法，导致未定义行为。

> 通过使用 `shared_ptr` 和 `weak_ptr` 可以解决多线程访问共享对象的线程安全问题。

```cpp
/*****修改后的代码*****/
#include <iostream>
#include <memory>
#include <thread>
using namespace std;

class Test {
public:
  Test() : _ptr(new int(20)) { cout << "Test()" << endl; }
  ~Test() {
    delete _ptr;
    _ptr = nullptr;
    cout << "~Test()" << endl;
  }
  void show() { cout << *_ptr << endl; }

private:
  int *volatile _ptr;
};

void threadProc(weak_ptr<Test> pw) {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // 等待2s
  // 通过lock方法提升为shared_ptr，检查对象是否存活
  if (auto ps = pw.lock()) {
    ps->show();
  }
}

int main() {
  shared_ptr<Test> p(new Test);
  std::thread t1(threadProc, weak_ptr<Test>(p));
  t1.detach(); // 分离子线程
  return 0;
}
```

在修改后的代码中，使用了 `shared_ptr` 来管理共享对象，并在子线程中使用 `weak_ptr` 来观察对象。通过 `lock` 方法将 `weak_ptr` 提升为 `shared_ptr`，并检查对象是否存活，从而避免了在对象已经被析构的情况下访问成员方法的问题。

> 使用 `shared_ptr` 和 `weak_ptr` 可以有效解决多线程环境下访问共享对象的线程安全问题。**其中，`shared_ptr` 用于管理共享对象的生命周期，而 `weak_ptr` 则用于观察对象的状态，并通过 `lock` 方法提升为 `shared_ptr`，以确保安全地访问对象。**

## 2.7 自定义删除器

在使用智能指针管理资源时，通常情况下，智能指针会自动处理资源的释放，比如对于堆内存，智能指针会在析构时调用 `delete`。然而，有些资源的释放方式并不是简单的调用 `delete`，比如打开的文件，需要调用 `fclose` 来关闭文件指针。在这种情况下，需要使用自定义删除器来指定资源的释放方式。

在 C++中，可以使用自定义删除器来指定资源的释放方式。这种方式可以通过函数对象、`std::function` 或 lambda 表达式来实现。**如果使用函数对象，代码冗余，并产生了额外的类。所以通常应该使用 `std::function` 或 lambda 表达式。**

1. **函数对象方式：**

   ```cpp
   class FileDeleter {
   public:
       // 删除器负责删除资源的函数
       void operator()(FILE *pf) { fclose(pf); }
   };

   int main() {
       // 由于用智能指针管理文件资源，因此传入自定义的删除器类型 FileDeleter
       unique_ptr<FILE, FileDeleter> filePtr(fopen("data.txt", "w"));
       return 0;
   }
   ```

2. **使用 `std::function` 和 lambda 表达式：**

   ```cpp
   int main() {
       // 自定义智能指针删除器，关闭文件资源
       unique_ptr<FILE, function<void(FILE*)>>
           filePtr(fopen("data.txt", "w"), [](FILE *pf)->void{fclose(pf);});

       // 自定义智能指针删除器，释放数组资源
       unique_ptr<int, function<void(int*)>>
           arrayPtr(new int[100], [](int *ptr)->void {delete[]ptr; });

       return 0;
   }
   ```

无论是哪种方式，自定义删除器都可以确保在智能指针析构时正确释放资源，这样可以确保资源不会因为遗漏释放而导致内存泄漏或其他问题。

# 3 绑定器和函数对象、`lambda` 表达式

- [绑定器](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E4%B8%AD%E7%BA%A7%E7%AC%94%E8%AE%B0.md#661-%E7%BB%91%E5%AE%9A%E5%99%A8-%E5%92%8C-lambda-%E8%A1%A8%E8%BE%BE%E5%BC%8F)

```cpp
template<typename _Operation, typename _Tp>
  inline binder1st<_Operation>
  bind1st(const _Operation& __fn, const _Tp& __x)
  {
    typedef typename _Operation::first_argument_type _Arg1_type;
    return binder1st<_Operation>(__fn, _Arg1_type(__x));
  }

  // 示例
auto it = find_if(v.begin(), v.end(), bind1st(less<int>(), 3));
```

## 3.1 bind1st 和 bind2nd 实现原理

```cpp
template <typename Compare, typename T> class _mybind1st {
public:
  _mybind1st(Compare comp, T first) : comp(comp), first(first) {}

  bool operator()(const T &second) { return comp(first, second); }

private:
  Compare comp;
  T first;
};

template <typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, T first) {
  return _mybind1st<Compare, T>(comp, first);
}

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  auto it = find_if(v.begin(), v.end(), mybind1st(less<int>(), 3));
  cout << *it << endl;
  return 0;
}
```

## 3.2 函数对象

- `std::function`可以保存、复制和调用任何可以调用的目标，如普通函数、lambda 表达式、绑定表达式或其他可调用对象。
- `std::function` 是一个类模板，它定义在 `<functional>` 头文件中。

```cpp
int add(int a, int b) { return a + b; }

class MyClass {
public:
  int add(int a, int b) { return a + b; }
};

int main() {
  function<int(int, int)> f1 = add; // 包装普通函数
  cout << f1(1, 2) << endl;

  function<int(int, int)> f2 = [](int a, int b) {
    return a + b;
  }; // 包装lambda表达式
  cout << f2(1, 2) << endl;

  MyClass obj;
  function<int(MyClass &, int, int)> f3 = &MyClass::add; // 包装成员函数
  cout << f3(obj, 1, 2) << endl;
  return 0;
}
```

## 3.3 模版的完全特例化和部分特例化

- [模板的特例化](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E4%B8%AD%E7%BA%A7%E7%AC%94%E8%AE%B0.md#411-%E5%87%BD%E6%95%B0%E6%A8%A1%E6%9D%BF)
- [模版的局限性](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#3126-%E6%A8%A1%E6%9D%BF%E7%9A%84%E5%B1%80%E9%99%90%E6%80%A7)

部分特例化是指为模板参数的一部分提供不同的实现，而不是所有参数。**部分特例化只能用于类模板，不能用于函数模板。**

```cpp
// 通用模板
template <typename T, typename U> class MyClass {
public:
  void print() { std::cout << "Generic template" << std::endl; }
};

// 对于 T 为 int 的部分特例化
template <typename U> class MyClass<int, U> {
public:
  void print() { std::cout << "Partial specialization: T is int" << std::endl; }
};


int main() {
  MyClass<int, double> obj1;
  obj1.print(); // 输出：Partial specialization: T is int

  MyClass<double, int> obj2;
  obj2.print(); // 输出：Generic template

  return 0;
}
```

## 3.4 `function` 函数对象类型的实现原理

```cpp
template <typename T> class myfunction;

template <typename R, typename... A> class myfunction<R(A...)> {
public:
  using PFUNC = R (*)(A...);

  myfunction(PFUNC pfunc) : _pfunc(pfunc) {}

  R operator()(A... arg) const { return _pfunc(arg...); }

private:
  PFUNC _pfunc;
};

int add1(int x) { return x + 1; }
int sum(int x, int y) { return x + y; }

int main() {
  myfunction<int(int)> f1(add1);
  cout << f1(1) << endl;
  myfunction<int(int, int)> f2(sum);
  cout << f2(1, 2);

  return 0;
}
```

## 3.5 `bind` 和 `function` 的使用

`bind` 的返回结果是一个函数对象

```cpp
#include <functional>
#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test {
public:
  int sum(int a, int b) { return a + b; }
};

int main() {
  // bind 是函数模版，可以自动推导参数类型
  bind(hello, "Hello, bind!")();
  cout << bind(sum, 1, 2)() << endl;
  cout << bind(&Test::sum, Test(), 1, 2)() << endl; // 依赖于对象

  // 参数占位符
  bind(hello, _1)("Hello, placeholders!"); // 1 代表第一个参数，调用时传入
  cout << bind(sum, _1, _2)(1, 2) << endl; // 1 代表第一个参数，2 代表第二个参数

  // 函数对象
  function<void(string)> f = bind(hello, _1);
  f("Hello, function!");
  return 0;
}
```

## 3.6 lambda 表达式

`lambda` 表达式的语法：`[捕获外部变量](形参列表) -> 返回值类型 { 函数体 };`。如果 `lambda` 表达式没有返回值，可以省略 `-> 返回值类型`。

- `[捕获外部变量]`
  - `[]`：不捕获任何外部变量
  - `[=]`：以值的方式捕获所有外部变量
  - `[&]`：以引用的方式捕获所有外部变量
  - `[a, &b]`：以值的方式捕获 a，以引用的方式捕获 b
  - `[this]`：捕获当前对象的指针
  - `[=, &a]`：以值的方式捕获所有外部变量，但是 a 以引用的方式捕获

> `lambda` 的实现原理：`lambda` 表达式实际上是一个匿名函数对象，编译器会将 `lambda` 表达式转换为一个类，该类重载了 `operator()`，并且包含了 `lambda` 表达式中使用的外部变量。

```cpp
#include <iostream>
using namespace std;

int main() {
  // 搭配内置函数
  vector<int> v = {1, 3, 2, 4, 5};
  sort(v.begin(), v.end(), [](int a, int b) -> bool { return a > b; });
  for_each(v.begin(), v.end(), [](int a) { cout << a << " "; });
  cout << endl;

  // 捕获外部变量
  int a = 10, b = 20;
  auto func1 = [&]() {
    int temp = a;
    a = b;
    b = temp;
  };
  func1();
  cout << a << " " << b << endl;

  // 保留 lambda 表达式
  map<int, function<int(int, int)>> caculate;
  caculate[1] = [](int a, int b) { return a + b; };
  caculate[2] = [](int a, int b) { return a - b; };
  caculate[3] = [](int a, int b) { return a * b; };
  caculate[4] = [](int a, int b) { return a / b; };
  cout << caculate[1](1, 2) << endl;
  return 0;
}
```

# 4 C++11 内容汇总、多线程应用实践

## 4.1 常用知识点总结

1. **关键字和语法**

- `auto`：可以根据右值，推导右值的类型，进而推导左边的类型
- `nullptr`：给指针专用（能够和整数进行区别）
- `for_each`：可以遍历数组、容器等，底层通过指针或迭代器来实现
- **右值引用**：`move`移动语义函数和`forward`类型完美转发
- **模板的新特性**：`typename... A` 表示可变参（类型参数）

2. **[绑定器和函数对象](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E9%AB%98%E7%BA%A7%E7%AC%94%E8%AE%B0.md#3-%E7%BB%91%E5%AE%9A%E5%99%A8%E5%92%8C%E5%87%BD%E6%95%B0%E5%AF%B9%E8%B1%A1lambda-%E8%A1%A8%E8%BE%BE%E5%BC%8F)**
   - `function`：函数对象
   - `bind`：绑定器
   - `lambda`表达式
3. **智能指针**：可以自动管理资源，以防止代码不可预期的执行导致资源泄露、资源未释放。[`shared_ptr`和`weak_ptr`](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E9%AB%98%E7%BA%A7%E7%AC%94%E8%AE%B0.md#24-%E5%B8%A6%E5%BC%95%E7%94%A8%E8%AE%A1%E6%95%B0%E7%9A%84%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88-shared_ptr-%E5%92%8C-weak_ptr)
4. 容器

- `unordered_set` 和 `unordered_map`：哈希表
- `array`：数组，无法进行扩容
- `forward_list`：前向链表

5. C++语言级别支持多线程编程，增强了可移植性，代码可以跨平台运行。

## 4.2 多线程类 `thread`

C++语言层面的`thread`，其底层还是调用操作系统对象的多线程函数，例如 Windows 下调用`CreateThread`，Linux 下调用的是`pthread_create`。语言层面的支持就做到了跨平台运行。

1. 怎么创建启动一个新线程？
   使用`std::thread`定义一个线程对象，传入线程所需要的线程函数和参数，线程自动开启。
2. 子线程如何结束？
   子线程函数运行完成，线程就结束了。
3. 主线程如何处理子线程

- `t.join()`：等待 `t` 线程结束，当前线程继续往下运行。
- `t.detach()`：把 `t` 线程设置为分离线程，主线程结束，整个进程结束，所有子线程就自动结束。
- 示例代码

  ```cpp
  #include <iostream>
  #include <thread>
  using namespace std;

  void threadHandle(int time) {
    // 让子线程睡眠2秒
    // chrono:名词空间，定义了一些和时间有关的常量
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread!" << endl;
  }
  int main() {
    // 创建了一个线程对象，传入一个线程函数，新线程就开始运行了
    std::thread t1(threadHandle, 2);
    // 主线程等待子线程结束，主线程继续往下运行
    // t1.join();
    // 把子线程设置为分离线程，此时它跟主线程没有关系了
    t1.detach();
    cout << "main thread done" << endl;

    // 主线程运行完成，查看如果当前进程还有未运行完成的子进程，进程就会异常终止
    return 0;
  }
  ```

## 4.3 线程互斥锁 `mutex`

- 多线程互斥
  - **竞态条件**：多线程程序执行的结果是一致的，不会随着 CPU 对线程不同的调用顺序，而产生不同运行结果。

示例：C++ `thread` 模拟车站三个窗口卖票程序

```cpp
#include <iostream>
#include <list>
#include <thread>
using namespace std;

// C++ thread 模拟车站三个窗口卖票的程序
int ticketCount = 100; // 车站有 100 张车票，由三个窗口一起卖票

// 模拟卖票的线程函数
void sellTicket(int index) {
  while (ticketCount > 0) {
    // cout << "窗口" << index << "卖出第" << ticketCount << "张票" << endl;
    cout << ticketCount << endl;
    ticketCount--;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
int main() {
  list<std::thread> tlist;
  for (int i = 1; i <= 3; ++i)
    tlist.push_back(std::thread(sellTicket, i));

  for (std::thread &t : tlist)
    t.join();
  cout << "所有窗口卖票结束" << endl;
  return 0;
}
```

**加互斥锁实现线程安全：**

```cpp
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
using namespace std;

// C++ thread 模拟车站三个窗口卖票的程序
int ticketCount = 100; // 车站有100张车票，由三个窗口一起卖票
std::mutex mtx;        // 全局的一把互斥锁

// 模拟卖票的线程函数
void sellTicket(int index) {
  while (ticketCount > 0) {
    mtx.lock();
    // 不加 if 可能导致 ticketCount=1 时，两个线程同时进入 while 循环，
    // 导致 ticketCount 成为负数
    if (ticketCount > 0) {
      // 临界区代码段，需要保证原子操作，所以进行线程间互斥操作->mutex
      cout << "窗口" << index << "卖出第" << ticketCount << "张票" << endl;
      ticketCount--;
    }
    mtx.unlock();
    // 每卖出一张票，睡眠100ms，让每个窗口都有机会卖票
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
int main() {
  list<std::thread> tlist;
  for (int i = 1; i <= 3; ++i)
    tlist.push_back(std::thread(sellTicket, i));

  for (std::thread &t : tlist)
    t.join();

  cout << "所有窗口卖票结束" << endl;
  return 0;
}
```

**`lock_guard`自动释放锁**

由于互斥锁需要手动`lock()`，`unlock()`，可能导致`unlock()`调用不到。所以采用`lock_guard()`封装`mutex`，保证所有线程都能释放锁，**防止死锁的发生**。（就像智能指针一样，利用栈上的对象出作用域必须析构对象来释放空间）

```cpp
void sellTicket(int index) {
  while (ticketCount > 0) {
    lock_guard<std::mutex> lock(mtx); // 相当于scope_ptr
    if (ticketCount > 0) {
      // 临界区代码段,需要保证原子操作，所以进行线程间互斥操作->mutex
      cout << "窗口" << index << "卖出第" << ticketCount << "张票" << endl;
      ticketCount--;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
```

## 4.4 线程间同步通信-----生产者消费者模型

**生产者消费者问题**（英语：Producer-consumer problem），也称**有限缓冲问题**（Bounded-buffer problem），是一个**多进程同步**问题的经典案例。该问题描述了共享固定大小缓冲区的两个进程——即所谓的“生产者”和“消费者”——在实际运行时会发生的问题。生产者的主要作用是生成一定量的数据放到缓冲区中，然后重复此过程。与此同时，消费者也在缓冲区消耗这些数据。**该问题的关键就是要保证生产者不会在缓冲区满时加入数据，消费者也不会在缓冲区中空时消耗数据**。

```cpp
#include <condition_variable> //Linux平台下的condition_variable机制，用于解决线程间的同步通信问题
#include <iostream>
#include <mutex>
#include <queue> //C++ STL所有的容器都不是线程安全的
#include <thread>
using namespace std;

/*
notify_one:通知另外的一个线程的
notify_all:通知其他所有线程的
通知其他所有线程，我生产了一个物品，赶紧消费吧
其他线程得知，就会从等待=>阻塞=>获取互斥锁才能继续执行
*/
std::mutex mtx;             // 定义互斥锁，做线程间的互斥操作
std::condition_variable cv; // 定义条件变量，做线程间的同步通信操作

// 生产者生产一个物品，通知消费者消费一个；消费完了，消费者再通知生产者继续生产物品
class Queue {
public:
  void put(int val) // 生产物品
  {
    unique_lock<std::mutex> lck(mtx);
    while (!que.empty()) {
      // que不为空，生产者应该通知消费者去消费，消费完了，再继续生产
      // 生产者线程进入等待状态，并且把mtx互斥锁释放掉
      cv.wait(lck);
    }
    que.push(val);
    cv.notify_all();
    cout << "生产者 生产" << val << "号物品" << endl;
  }
  int get() // 消费物品
  {
    unique_lock<std::mutex> lck(mtx);
    while (que.empty()) {
      cv.wait(lck);
    }
    int val = que.front();
    que.pop();
    cv.notify_all(); // 通知其他线程我消费完了，赶紧生产吧
    cout << "消费者 消费" << val << "号物品" << endl;
    return val;
  }

private:
  queue<int> que;
};

void producer(Queue *que) // 生产线程
{
  for (int i = 0; i <= 10; i++) {
    que->put(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
void consumer(Queue *que) // 消费者线程
{
  for (int i = 0; i <= 10; i++) {
    que->get();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main() {
  Queue que;
  std::thread t1(producer, &que);
  std::thread t2(consumer, &que);

  t1.join();
  t2.join();
}
```

> `notify_all()` 方法会唤醒所有等待在该条件变量上的线程。**这些被唤醒的线程会从等待状态变为阻塞状态**，并尝试重新获取与条件变量关联的互斥锁。一旦某个线程成功获取到互斥锁，它就可以继续执行。

## 4.5 `lock_guard` 和 `unique_lock`

```cpp
/**************** mutex ****************/
// 写法类似于裸指针，可能出现获取但没释放的情况。
mutex mtx;

int main() {
  mtx.lock(); // 加锁
  mtx.unlock(); // 解锁
}

/**************** lock_guard ****************/
// lock_guard 类似于智能指针，构造函数获取锁，析构函数释放锁。
// 部分源码如下，禁止拷贝构造和赋值
lock_guard(const lock_guard&) = delete;
lock_guard& operator=(const lock_guard&) = delete;

// 用法：
lock_guard<std::thread> guard(mtx);

// lock_guard 不可能用在函数参数传递或者返回过程中，因为这些会用到拷贝构造或赋值函数，但 lock_guard 不能进行拷贝构造和赋值，只能用在简单的加锁和解锁临界区代码段中。


/**************** unique_lock ****************/
// 同样是构造函数获取锁，析构函数释放锁

// 删除了左值的拷贝构造和等号运算符重载，提供了右值的拷贝构造和等号运算符重载，unique_lock不仅可用于函数的参数传递以及返回过程中，还可用在简单的临界区代码段的互斥操作中。

// 底层也提供了互斥锁的 lock() 和 unlock() 方法

// 用法：
unique_lock<std::thread> lck(mtx);

// unique_lock 完全可以替代lock_guard，就像 unique_ptr 完全可以替代 scoped_ptr 一样。只是多了个条件变量的功能（线程同步通信）


/**************** condition_variable ****************/

// -----
// 通常和 unique_lock 搭配使用

unique_lock<mutex> lck(mtx);

// 1. 使线程进入等待状态
// 2. lck.unlock() 释放互斥锁 mtx
cv.wait(lck);
// -----

// 通知 cv 上等待的线程从等待状态进入阻塞状态，开始抢互斥锁
// 抢到互斥锁的线程从阻塞->运行
cv.notify_all();
```

## 4.6 基于 CAS 操作的 atomic 原子类型

- 互斥锁是比较重的，适合于临界区代码做的事情稍稍复杂的情形。而`++`, `--`操作使用 CAS 原子特性就足够了，是无锁操作。
- CAS 并不是不加锁，只不过加锁解锁不在软件层面。cpu 和内存之间通信通过系统总线进行。CAS 通过 `exchange/swap` 指令，相当于给总线加锁，当一个线程在做 cpu 和内存交换，不允许其他线程再使用总线，有助于提高多线程效率。
- `volatile`：防止多线程对共享变量进行缓存，访问的都是原始内存变量值。
  - 不加 `volatile` 的话，每个线程都会拷贝一份自己的线程栈上的变量，带到 CPU 的缓存，这样效率较高，但也可能出错。

```cpp
#include <atomic> // 包含很多原子操作的函数
#include <iostream>
#include <list>
#include <thread>

using namespace std;

volatile atomic_bool is_ready = false;
volatile atomic_int cnt = 0;

// task 函数，每个线程都会执行这个函数
void task() {
  // 如果 is_ready 变量为 false，当前线程让出时间片
  if (!is_ready)
    this_thread::yield();

  // 当 is_ready 变量为 true 时，每个线程都对 cnt 变量加 100 次
  for (int i = 0; i < 100; i++)
    cnt++;
}

int main() {
  // 创建一个线程列表
  list<thread> tlist;
  // 创建 10 个线程，每个线程都会执行 task 函数
  for (int i = 0; i < 10; i++)
    tlist.push_back(thread(task));

  // 主线程休眠 2 秒，让其他线程有机会先执行
  this_thread::sleep_for(chrono::seconds(2));
  // 将 is_ready 变量设置为 true，让其他线程开始执行任务
  is_ready = true;
  // 等待所有线程执行完毕
  for (thread &t : tlist)
    t.join();

  // 打印 cnt 变量的值，应该为 1000（10 个线程，每个线程加 100 次）
  cout << cnt << endl; // 1000
  return 0;
}
```

# 5 设计模式

## 5.1 单例模式

- 单例模式：**无论怎么获取，永远只能得到该类类型的唯一一个实例对象**，那么设计一个单例就必须要满足下面三个条件：
  - 构造函数私有化，这样用户就不能任意定义该类型的对象了
  - 定义该类型唯一的对象
  - 通过一个 `static` 静态成员方法返回唯一的对象实例

### 5.1.1 饿汉式和懒汉式单例模式

- **饿汉式单例模式**，顾名思义，**就是程序启动时就实例化了该对象**，并没有推迟到第一次使用该对象时再进行实例化；如果运行过程中没有使用到，该实例对象就被浪费掉了
- **懒汉式单例模式**，顾名思义，就是对象的实例化，延迟到第一次使用它的时候

```cpp
//----------- 饿汉式单例模式 ------------
class CSingleton {
public:
  static CSingleton *getInstance() { return &single; }

private:
  static CSingleton single;
  CSingleton() { cout << "CSingleton()" << endl; }
  ~CSingleton() { cout << "~CSingleton()" << endl; }
  CSingleton(
      const CSingleton &); // 防止外部使用拷贝构造产生新的对象
                           // 如 CSingleton s = *p1;
};
CSingleton CSingleton::single;

int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  cout << p1 << " " << p2 << " " << p3 << endl;
  return 0;
}

//----------- 懒汉式单例模式 ------------

class CSingleton {
public:
  static CSingleton *getInstance() {
    if (!instance)
      instance = new CSingleton();
    return instance;
  }

private:
  static CSingleton *instance;
  CSingleton() { cout << "CSingleton()" << endl; }
  ~CSingleton() { cout << "~CSingleton()" << endl; }
  CSingleton(const CSingleton &other) = delete;
};
CSingleton *CSingleton::instance = nullptr;

int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  cout << p1 << "\t" << p2 << "\t" << p3 << endl;
  // delete p1;  // ‘CSingleton::~CSingleton()’ is private within this context
  return 0;
}
```

### 5.1.2 嵌套类和静态对象的方式解决单例模式的资源释放问题

**上述释放资源的问题，可以通过嵌套类和静态对象的方式来解决**

```cpp
class CSingleton {
public:
  static CSingleton *getInstance() {
    if (nullptr == single)
      single = new CSingleton();
    return single;
  }

private:
  static CSingleton *single;
  CSingleton() { cout << "CSingleton()" << endl; }
  ~CSingleton() { cout << "~CSingleton()" << endl; }
  CSingleton(const CSingleton &);

  // 定义一个嵌套类，在该类的析构函数中，自动释放外层类的资源
  class CRelease {
  public:
    ~CRelease() { delete single; }
  };
  // 通过该静态对象在程序结束时自动析构的特点，来释放外层类的对象资源
  static CRelease release;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;

int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  cout << p1 << " " << p2 << " " << p3 << endl;
  return 0;
}
```

### 5.1.3 线程安全的单例模式

在开发服务器程序的时候，经常会用到多线程，多线程要考虑代码的线程安全特性，不能让代码在多线程环境下出现**竞态条件**，否则就要进行线程互斥操作

1. 饿汉单例模式的线程安全特性
   饿汉单例模式中，单例对象定义成了一个`static`静态对象，它是在程序启动时，`main`函数运行之前就初始化好的，因此不存在线程安全问题，可以放心的在多线程环境中使用。

2. 懒汉单例模式的线程安全特性
   懒汉单例模式，获取单例对象的方法如下

```cpp
static CSingleton *getInstance() {
  if (nullptr == single) {
    single = new CSingleton();
  }
  return single;
}
```

> 很明显，这个`getInstance`是个**不可重入函数**，也就它在多线程环境中执行，会出现竞态条件问题，首先搞清楚这句代码，`single = new CSingleton()`它会做三件事情，**开辟内存，调用构造函数，给`single`指针赋值**，那么在多线程环境下，就有可能出现如下问题：
>
> - 线程 A 先调用 `getInstance` 函数，由于 `single` 为 `nullptr`，进入 `if` 语句
> - `new` 操作先开辟内存，此时 A 线程的 CPU 时间片到了，切换到 B 线程
> - B 线程由于 `single` 为 `nullptr`，也进入 `if` 语句了，开始 `new` 操作

很明显，上面两个线程都进入了 `if` 语句，都试图 `new` 一个新的对象，不符合单例模式的设计，所有应该为`getInstance` 函数内部加锁，在线程间进行互斥操作。此处介绍 Linux 系统下，`pthread` 库中提供的线程互斥操作方法-`mutex`互斥锁，代码如下：

```cpp
#include <iostream>
#include <pthread.h>
using namespace std;

class CSingleton {
public:
  // 获取单例对象的方法
  static CSingleton *getInstance() {
    pthread_mutex_lock(&mutex); // 获取互斥锁，保证线程安全
    if (nullptr == single) {
      single = new CSingleton();
    }
    pthread_mutex_unlock(&mutex); // 释放互斥锁
    return single;                // 返回单例对象的指针
  }

private:
  static CSingleton *single; // 单例对象的指针
  // 私有构造函数，外部不能直接创建对象
  CSingleton() { cout << "CSingleton()" << endl; }
  // 析构函数，释放互斥锁
  ~CSingleton() {
    pthread_mutex_destroy(&mutex); // 释放锁
    cout << "~CSingleton()" << endl;
  }
  // 禁止拷贝构造
  CSingleton(const CSingleton &);

  // 内部类，用于在程序结束时释放单例对象
  class CRelease {
  public:
    // 在程序结束时，自动调用析构函数释放单例对象
    ~CRelease() { delete single; }
  };
  // 静态的 CRelease 对象，当程序结束时，它的析构函数会被调用
  static CRelease release;

  // 定义线程间的互斥锁
  static pthread_mutex_t mutex;
};

// 初始化单例对象的指针为 nullptr
CSingleton *CSingleton::single = nullptr;
// 创建 CRelease 对象
CSingleton::CRelease CSingleton::release;
// 初始化互斥锁
pthread_mutex_t CSingleton::mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  return 0;
}
```

上面的代码，是一个线程安全的懒汉单例模式，但是效率太低，因为每次调用 `getInstance` 都需要加锁解锁，除了第一次调用，后面对 `getInstance` 函数持续的加解锁完全没有必要，所以这里需要使用**锁 + 双重判断，也叫双重检验锁**，把上面的 `getInstance` 函数代码修改如下：

```cpp
// 获取单例对象的方法
static CSingleton *getInstance() {
  if (nullptr == single) {
    pthread_mutex_lock(&mutex); // 获取互斥锁，保证线程安全
    /*
    这里需要再添加一个 if 判断，否则当两个线程都进入这里，
    又会多次 new 对象，不符合单例模式的设计
    */
    if (nullptr == single)
      single = new CSingleton();
    pthread_mutex_unlock(&mutex); // 释放互斥锁
  }

  return single; // 返回单例对象的指针
}
```

将互斥锁封装成一个类，使用起来更加 OOP

```cpp
#include <iostream>
#include <pthread.h>
using namespace std;

// 对互斥锁操作的封装
class CMutex {
public:
  CMutex() { pthread_mutex_init(&mutex, NULL); }  // 初始化锁
  ~CMutex() { pthread_mutex_destroy(&mutex); }    // 销毁锁
  void lock() { pthread_mutex_lock(&mutex); }     // 获取锁
  void unlock() { pthread_mutex_unlock(&mutex); } // 释放锁
private:
  pthread_mutex_t mutex;
};

class CSingleton {
public:
  static CSingleton *getInstance() {
    if (nullptr == single) {
      // 获取互斥锁
      mutex.lock();

      /*
      这里需要再添加一个if判断，否则当两个线程都进入这里，
      又会多次new对象，不符合单例模式的设计
      */
      if (nullptr == single)
        single = new CSingleton();

      // 释放互斥锁
      mutex.unlock();
    }

    return single;
  }

private:
  static CSingleton *single;
  CSingleton() { cout << "CSingleton()" << endl; }
  ~CSingleton() { cout << "~CSingleton()" << endl; }
  CSingleton(const CSingleton &);

  class CRelease {
  public:
    ~CRelease() { delete single; }
  };
  static CRelease release;

  // 线程间的静态互斥锁
  static CMutex mutex;
};
CSingleton *CSingleton::single = nullptr;
CSingleton::CRelease CSingleton::release;
// 定义互斥锁静态对象
CMutex CSingleton::mutex;

int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  return 0;
}


/*
对于 static 静态局部变量的初始化，编译器会自动对它的初始化进行加锁和解锁控制，
使静态局部变量的初始化成为线程安全的操作，不用担心多个线程都会初始化静态局部变量，
因此这样的懒汉单例模式是线程安全的单例模式！
*/

#include <iostream>
using namespace std;

class CSingleton {
public:
  static CSingleton *getInstance() {
    static CSingleton single; // 懒汉式单例模式，定义唯一的对象实例
    return &single;
  }

private:
  static CSingleton *single;
  CSingleton() { cout << "CSingleton()" << endl; }
  ~CSingleton() { cout << "~CSingleton()" << endl; }
  CSingleton(const CSingleton &);
};
int main() {
  CSingleton *p1 = CSingleton::getInstance();
  CSingleton *p2 = CSingleton::getInstance();
  CSingleton *p3 = CSingleton::getInstance();
  return 0;
}
```

## 5.2 简单工厂、工厂方法、抽象工厂

- **简单工厂**：把对象的创建封装在一个借口函数里面，通过传入不同的标识，返回创建的对象。用户不用自己负责 `new` 对象，不需要了解对象创建的详细过程。
  - 提供创建对象实例的借口函数不闭合，不能对修改关闭，对扩展开放。
- **工厂方法**：Factory 基类，提供了一个纯虚函数（创建产品），定义派生类（具体工厂）负责创建对应的产品，可以做到不同的产品由不同的工厂创建。工厂方法模式是符合开闭原则的。
  - 一个工厂只能生产一种产品，如果需要生产多种产品，就需要多个工厂。
- **抽象工厂**：把有关联关系的，属于一个产品簇的所有产品创建的借口函数，放在一个抽象工厂（Abstract Factory）类里面，派生类（具体工厂）负责创建对应的产品。

### 5.2.1 简单工厂模式（Simple Factory）

简单工厂（Simple Factory）不属于标准的 OOP 设计模式中的一项，在编写大型 C++ 软件的时候，代码里面会出现很多的类，每次创建对象的时候，都需要通过 **`new` 类名称**的方式来生成对象，这样一来，用户需要记忆很多类的名称，暂且不管记不记得住，这样的设计使得代码很难维护，类名如果做了改变，那么所有使用类名称的地方都需要去修改，耦合性太强，不符合软件设计的思想，Simple Factory 就是在这样的需求下诞生的。

**简单工厂模式的 UML 设计类图：**

![20240610162335](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240610162335.png)

从上面的 UML 类图可以看出，所有对象的创建不再通过 **`new` 类名称**的方式进行了，而是**把对象的创建都封装在了 SimpleFactory 类的 `createProduct` 方法当中，通过传入一个事先设计好的枚举类型，然后返回一个对应的对象，既解耦了对象的创建，还不用再记忆那么多的类名**。

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Car {
public:
  Car(string name) : _name(name) {}
  virtual void show() = 0;

protected:
  string _name;
};

class Bmw : public Car {
public:
  Bmw(string name) : Car(name) {}
  void show() { cout << "Bmw: " << _name << endl; }
};

class Audi : public Car {
public:
  Audi(string name) : Car(name) {}
  void show() { cout << "Audi: " << _name << endl; }
};

enum CarType { BMW, AUDI };

class SimpleFactory {   // 不符合开闭原则
public:
  Car *createCar(CarType ct) {
    switch (ct) {
    case BMW:
      return new Bmw("X5");
    case AUDI:
      return new Audi("A6");
    default:
      cerr << "传入工厂的参数不正确：" << ct << endl;
      break;
    }
    return nullptr;
  }
};

int main() {
  // Car *p1 = new BMW("X5");
  // Car *p2 = new Audi("A6");
  // p1->show();
  // p2->show();
  unique_ptr<SimpleFactory> factory(new SimpleFactory());
  unique_ptr<Car> p1(factory->createCar(BMW));
  unique_ptr<Car> p2(factory->createCar(AUDI));
  p1->show();
  p2->show();
  return 0;
}
```

### 5.2.2 工厂方法模式（Factory Method）

工厂方法模式（Factory Method）是简单工厂模式的进一步抽象和推广，**工厂方法模式是定义一个创建对象的接口，让子类决定实例化哪一个类**，工厂方法使一个类的实例化延伸到其子类。**工厂方法模式是符合开闭原则的**。

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Car {
public:
  Car(string name) : _name(name) {}
  virtual void show() = 0;

protected:
  string _name;
};

class Bmw : public Car {
public:
  Bmw(string name) : Car(name) {}
  void show() { cout << "Bmw: " << _name << endl; }
};

class Audi : public Car {
public:
  Audi(string name) : Car(name) {}
  void show() { cout << "Audi: " << _name << endl; }
};

// 工厂方法
class Factory {
public:
  virtual Car *createCar(string name) = 0;
};

// 宝马工厂
class BmwFactory : public Factory {
public:
  Car *createCar(string name) { return new Bmw(name); }
};

// 奥迪工厂
class AudiFactory : public Factory {
public:
  Car *createCar(string name) { return new Audi(name); }
};

int main() {
  unique_ptr<Factory> bmwFactory(new BmwFactory());
  unique_ptr<Factory> audiFactory(new AudiFactory());
  unique_ptr<Car> p1(bmwFactory->createCar("X6"));
  unique_ptr<Car> p2(audiFactory->createCar("Q7"));
  p1->show();
  p2->show();
  return 0;
}
```

### 5.2.3 抽象工厂模式（Abstract Factory）

抽象工厂模式（Abstract Factory）是工厂方法模式的升级版本，**抽象工厂对于一组有关联关系的产品簇，提供产品对象的统一创建接口**

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 产品系列 1
class Car {
public:
  Car(string name) : _name(name) {}
  virtual void show() = 0;

protected:
  string _name;
};

class Bmw : public Car {
public:
  Bmw(string name) : Car(name) {}
  void show() { cout << "Bmw: " << _name << endl; }
};

class Audi : public Car {
public:
  Audi(string name) : Car(name) {}
  void show() { cout << "Audi: " << _name << endl; }
};

// 产品系列 2
class Light {
public:
  Light(string name) : _name(name) {}
  virtual void show() = 0;

protected:
  string _name;
};

class BmwLight : public Light {
public:
  BmwLight(string name) : Light(name) {}
  void show() { cout << "BmwLight: " << _name << endl; }
};

class AudiLight : public Light {
public:
  AudiLight(string name) : Light(name) {}
  void show() { cout << "AudiLight: " << _name << endl; }
};

// 抽象工厂类
class AbstractFactory {
public:
  virtual Car *createCar(string name) = 0;     // 工厂方法，创建汽车
  virtual Light *createLight(string name) = 0; // 工厂方法，创建汽车灯
};

// 宝马工厂
class BmwFactory : public AbstractFactory {
public:
  Car *createCar(string name) { return new Bmw(name); }
  Light *createLight(string name) { return new BmwLight(name); }
};

// 奥迪工厂
class AudiFactory : public AbstractFactory {
public:
  Car *createCar(string name) { return new Audi(name); }
  Light *createLight(string name) { return new AudiLight(name); }
};

int main() {
  unique_ptr<AbstractFactory> bmwFactory(new BmwFactory());
  unique_ptr<AbstractFactory> audiFactory(new AudiFactory());
  unique_ptr<Car> p1(bmwFactory->createCar("X6"));
  unique_ptr<Car> p2(audiFactory->createCar("Q7"));
  unique_ptr<Light> p3(bmwFactory->createLight("X6"));
  unique_ptr<Light> p4(audiFactory->createLight("Q7"));
  p1->show();
  p2->show();
  p3->show();
  p4->show();
  return 0;
}
```

## 5.3 代理（Proxy）模式

**代理**是一种结构型设计模式， 让你能提供真实服务对象的替代品给客户端使用。代理接收客户端的请求并进行一些处理（访问控制和缓存等）， 然后再将请求传递给服务对象。

![20240611131535](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240611131535.png)

> 代理对象拥有和服务对象相同的接口，这使得当其被传递给客户端时可与真实对象互换。

**使用示例**：尽管代理模式在绝大多数 C++ 程序中并不常见，但它在一些特殊情况下仍然非常方便。当你希望在无需修改客户代码的前提下于已有类的对象上增加额外行为时，该模式是无可替代的。

**识别方法**：代理模式会将所有实际工作委派给一些其他对象。除非代理是某个服务的子类，否则每个代理方法最后都应该引用一个服务对象。

```cpp
#include <iostream>
/**
 * Subject 接口声明了 RealSubject 和 Proxy 的共同操作。
 * 只要客户端使用这个接口与 RealSubject 交互，就可以传递一个代理而不是一个真实的对象。
 */
class Subject {
public:
  virtual void Request() const = 0;
};

/**
 * RealSubject 包含一些核心业务逻辑。通常，RealSubject 能够做一些有用的工作，
 * 这些工作可能非常缓慢或敏感，例如校正输入数据。
 * 代理可以在不改变 RealSubject 代码的情况下解决这些问题。
 */
class RealSubject : public Subject {
public:
  void Request() const override { std::cout << "RealSubject: 处理请求。\n"; }
};

/**
 * Proxy 拥有与 RealSubject 相同的接口。
 */
class Proxy : public Subject {
private:
  RealSubject *real_subject_;

  bool CheckAccess() const {
    // 这里应该进行一些实际的检查。
    std::cout << "Proxy: 在执行实际请求之前检查访问权限。\n";
    return true;
  }

  void LogAccess() const { std::cout << "Proxy: 记录请求的时间。\n"; }

public:
  /**
   * Proxy 保持对 RealSubject 类对象的引用。
   * 它可以是懒加载的，也可以由客户端传递给 Proxy。
   */
  Proxy(RealSubject *real_subject)
      : real_subject_(new RealSubject(*real_subject)) {}

  ~Proxy() { delete real_subject_; }

  /**
   * 代理模式最常见的应用是懒加载、缓存、控制访问、日志记录等。
   * 代理可以执行这些操作之一，然后根据结果将执行传递给链接的 RealSubject
   * 对象中的相同方法。
   */
  void Request() const override {
    if (this->CheckAccess()) {
      this->real_subject_->Request();
      this->LogAccess();
    }
  }
};

/**
 * 客户端代码应通过 Subject 接口与所有对象（包括真实对象和代理）交互，
 * 以支持真实对象和代理。在实际应用中，客户端主要与真实对象直接交互。
 * 在这种情况下，为了更容易实现模式，可以从真实对象的类扩展代理。
 */
void ClientCode(const Subject &subject) {
  // ...
  subject.Request();
  // ...
}

int main() {
  std::cout << "Client: 使用真实对象执行客户端代码：\n";
  RealSubject *real_subject = new RealSubject;
  ClientCode(*real_subject);
  std::cout << "\n";
  std::cout << "Client: 使用代理执行相同的客户端代码：\n";
  Proxy *proxy = new Proxy(real_subject);
  ClientCode(*proxy);

  delete real_subject;
  delete proxy;
  return 0;
}
```

## 5.4 装饰器（Decorator）模式

装饰器：主要是增加现有类的功能。而不增加新的子类。

![20240611133100](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240611133100.png)

为了增加现有类的功能，通过实现子类的方式重写接口，可以完成功能，但是会产生很多的子类。而装饰器模式，可以通过组合的方式，不断的增加功能，而不用增加子类。

![20240611133252](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240611133252.png)

```cpp
#include <iostream>
using namespace std;

class Car {
public:
  virtual void show() = 0;
};

class Bmw : public Car {
public:
  void show() { cout << "BMW, 配置：基类"; }
};

class Audi : public Car {
public:
  void show() { cout << "Audi, 配置：基类"; }
};

class Benz : public Car {
public:
  void show() { cout << "Bnze, 配置：基类"; }
};

// 装饰器 1 : 定速巡航
class ConcreteDecorator01 : public Car {
public:
  ConcreteDecorator01(Car *p) : pCar(p) {}
  void show() {
    pCar->show();
    cout << "，定速巡航";
  }

private:
  Car *pCar;
};

// 装饰器 2 : 定速刹车
class ConcreteDecorator02 : public Car {
public:
  ConcreteDecorator02(Car *p) : pCar(p) {}
  void show() {
    pCar->show();
    cout << "，定速刹车";
  }

private:
  Car *pCar;
};

// 装饰器 3 : 车道偏离
class ConcreteDecorator03 : public Car {
public:
  ConcreteDecorator03(Car *p) : pCar(p) {}
  void show() {
    pCar->show();
    cout << "，车道偏离";
  }

private:
  Car *pCar;
};

int main() {
  Car *p1 = new ConcreteDecorator01(new Bmw());
  p1 = new ConcreteDecorator01(p1);
  p1->show();
  cout << endl;

  Car *p2 = new ConcreteDecorator02(new Audi());
  p2->show();
  cout << endl;

  Car *p3 = new ConcreteDecorator03(new Benz());
  p3->show();
  cout << endl;

  return 0;
}
```

## 5.5 适配器（Adapter）模式

适配器模式（Adapter）是一种结构型设计模式，**它能使接口不兼容的对象能够相互合作**。

```cpp
#include <iostream>
#include <string>
using namespace std;

class VGA { // VGA 接口的抽象类
public:
  virtual void play() = 0;
};

class TV01 : public VGA { // VGA 接口的投影仪
public:
  void play() { cout << "VGA-----TV01" << endl; }
};

// 实现一个电脑类，它有一个接口，可以连接 VGA 设备
class Computer {
public:
  // 由于电脑只有一个 VGA 接口，所以只能连接一个 VGA 设备
  void playVideo(VGA *pVGA) { pVGA->play(); }
};

// 进了一批新的投影仪，但是它们都是 HDMI 接口的，不能直接连接到电脑上
class HDMI {
public:
  virtual void play() = 0;
};

class TV02 : public HDMI { // HDMI 接口的投影仪
public:
  void play() { cout << "HDMI-----TV02" << endl; }
};

// 适配器模式
class Adapter : public VGA {
public:
  Adapter(HDMI *pHDMI) : m_pHDMI(pHDMI) {}
  void play() { m_pHDMI->play(); }

private:
  HDMI *m_pHDMI;
};

int main() {
  Computer computer;
  computer.playVideo(new TV01());
  // computer.playVideo(new TV02()); // cannot convert ‘TV02*’ to ‘VGA*’
  /*
   * 接口不兼容，无法连接
   *   1. 换一个支持 HDMI 接口的电脑，即代码重构
   *   2. 买一个转接头，即适配器模式
   */
  computer.playVideo(new Adapter(new TV02()));
  return 0;
}
```

## 5.6 观察者-监听者（Observer）/发布-订阅 模式

### 5.6.1 观察者模式简介

观察者模式（Observer Pattern），也叫监听者模式（Listener Pattern）或发布-订阅模式（Publish-Subscribe Pattern），用于解耦事件的观察和事件最终的处理方式。

**例子**

假设有一组数据，生成了多个不同的界面来显示，如曲线图、圆饼图、柱状图等。当底层数据发生改变时，所有基于同一组数据的图像显示都需要修改。可以有**两种实现方式**：

1. 所有图形界面模块都去观察底层数据是否发生变化，如果变化，则读取数据，修改图像显示。
2. 一个类似 Observer 观察者的模块专门用来观察数据变化。对某组数据感兴趣的图形界面模块可以向 Observer 注册，表示对哪些数据的变化感兴趣。当 Observer 观察到数据变化时，会及时通知对这组数据变化感兴趣的图形界面模块执行相应的代码操作。

第二种方式解耦了事件的观察和事件的处理，各个图形界面模块相当于监听者（Listener）或订阅者（Subscriber），观察数据变化的模块称作观察者（Observer）或发布者（Publisher）。

### 5.6.2 简述 MVC 模式

MVC 模式（Model-View-Controller）起初用于 WEB 开发，通过模块的高内聚和低耦合，逐渐被广泛应用于各种软件开发领域。MVC 模式是一种软件整体的架构思想，不是 OOP 面向对象的设计模式。

- **M**：Model，数据模型层，表示系统底层的数据操作模块。
- **V**：View，视图显示层，表示系统的数据展示模块。
- **C**：Controller，控制层，表示监听用户事件交互和分发处理事件的模块。

MVC 模式通过 Controller 监听用户请求事件，通过访问 Model 数据层对数据进行增删改查操作，然后找到合适的 View 视图用相应的数据进行渲染生成最终的显示视图，并返回给用户。

### 5.6.3 观察者模式的 UML 图

观察者模式的类设计关系如下图所示：

![20240611171313](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240611171313.png)

- **Listener** 是对某些事件感兴趣的监听者。
- **Listener1** 和 **Listener2** 是监听者的具体实现类。
- **Observer** 是观察者，负责具体的事件观察并通知监听者处理已发生的事件。

### 5.6.4 观察者模式的代码实现

```cpp
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

// 定义监听者基类
class Listener {
public:
  // 基类构造函数
  Listener(string name) : _name(name) {}
  // 监听者处理消息事件的纯虚函数接口
  virtual void handleMessage(int msgid) = 0;

protected:
  string _name;
};

// 一个具体的监听者类 Listener1
class Listener1 : public Listener {
public:
  Listener1(string name) : Listener(name) {}
  // Listener1处理自己感兴趣的事件
  void handleMessage(int msgid) {
    cout << "listener:" << _name << " recv:" << msgid << " msg, handle it now!"
         << endl;
  }
};

// 一个具体的监听者类 Listener2
class Listener2 : public Listener {
public:
  Listener2(string name) : Listener(name) {}
  // Listener2 处理自己感兴趣的事件
  void handleMessage(int msgid) {
    cout << "listener:" << _name << " recv:" << msgid << " msg, handle it now!"
         << endl;
  }
};
// 实现观察者
class Observer {
public:
  /*
  params:
  1. Listener *pListener: 具体的监听者
  2. int msgid： 监听者感兴趣的事件
  该函数接口主要用于监听者向观察者注册感兴趣的事件
  */
  void registerListener(Listener *pListener, int msgid) {
    auto it = listenerMap.find(msgid);
    if (it == listenerMap.end()) {
      // 没人对 msgid 事件感兴趣过，第一次注册
      listenerMap[msgid].push_front(pListener);
    } else {
      // 直接把当前pListener添加到对msgid事件感兴趣的list列表中
      it->second.push_front(pListener);
    }
  }
  /*
  params:
  1. int msgid：观察到发生的事件 id
  该函数接口主要用于观察者观察到事件发生，并转发到对该事件感兴趣
  的监听者
  */
  void dispatchMessage(int msgid) {
    auto it = listenerMap.find(msgid);
    if (it != listenerMap.end()) {
      for_each(it->second.begin(), it->second.end(),
               [&msgid](Listener *pListener) -> void {
                 // 观察者派生事件到感兴趣的监听者，监听者通过handleMessage接口负责事件的具体处理操作
                 pListener->handleMessage(msgid);
               });
    }
  }

private:
  // 存储监听者注册的感兴趣的事件
  unordered_map<int, list<Listener *>> listenerMap;
};
int main() {
  Listener *p1 = new Listener1("高海山");
  Listener *p2 = new Listener2("冯丽婷");

  Observer obser;
  // 监听者p1注册1，2，3号事件
  obser.registerListener(p1, 1);
  obser.registerListener(p1, 2);
  obser.registerListener(p1, 3);
  // 监听者p2注册1，3号事件
  obser.registerListener(p2, 1);
  obser.registerListener(p2, 3);

  // 模拟事件的发生
  int msgid;
  for (;;) {
    cout << "输入事件id:";
    cin >> msgid;
    if (-1 == msgid)
      break;
    // 通过用户手动输入msgid模拟事件发生，此处观察者派发事件
    obser.dispatchMessage(msgid);
  }

  return 0;
}
```

**代码运行结果**

```cpp
输入事件id:1
listener:冯丽婷 recv:1 msg, handle it now!
listener:高海山 recv:1 msg, handle it now!
输入事件id:2
listener:高海山 recv:2 msg, handle it now!
输入事件id:3
listener:冯丽婷 recv:3 msg, handle it now!
listener:高海山 recv:3 msg, handle it now!
输入事件id:4
输入事件id:-1
```

> 通过代码可以看到，监听者 Listener 向观察者 Observer 事先注册好它需要处理的感兴趣的事件后，然后就可以做自己的事情，当 Observer 观察到有相应的事件发生时，会对事件进行派发，通知对该事件感兴趣的监听者处理该事件，这就是观察者模式。

### 5.6.5 多线程中的观察者模式

考虑观察者 Observer 独立运行在一个线程环境中，当它观察到事件发生时，通知监听者处理事件的代码如下：

```cpp
for_each(it->second.begin(), it->second.end(),
         [&msgid](Listener *pListener) -> void {
           // 观察者派生事件到感兴趣的监听者，监听者通过handleMessage接口负责事件的具体处理操作
           pListener->handleMessage(msgid);
         });
```

遍历一个 `list<Listener*>` 的列表，然后回调每一个监听者的 `handleMessage` 方法进行事件派发，那么这就涉及到在多线程环境中，共享对象的线程安全问题（解决方法就是使用智能指针）

上面代码通过访问 `Listener*`，**也就是指向监听者的指针，在调用 `handleMessage` 时，其实在多线程环境中，肯定不明确此时监听者对象是否还存活，或是已经在其它线程中被析构了，此时再去通知这样的监听者，肯定是有问题的**，也就是说，当 `Observer` 观察者运行在独立的线程中时，在通知监听者处理该事件时，应该先判断监听者对象是否存活，如果监听者对象已经析构，那么不用通知，并且需要从 `map` 表中删除这样的监听者对象。

**使用 `shared_ptr` 和 `weak_ptr` 智能指针，上面使用 `Listener*` 裸指针在多线程环境中肯定存在多线程访问共享对象的线程安全问题**

```cpp
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

// 定义监听者基类
class Listener {
public:
  // 基类构造函数
  Listener(string name) : _name(name) {}
  // 监听者处理消息事件的纯虚函数接口
  virtual void handleMessage(int msgid) = 0;

protected:
  string _name;
};
// 一个具体的监听者类Listener1
class Listener1 : public Listener {
public:
  Listener1(string name) : Listener(name) {}
  // Listener1处理自己感兴趣的事件
  void handleMessage(int msgid) {
    cout << "listener:" << _name << " recv:" << msgid << " msg, handle it now!"
         << endl;
  }
};
// 一个具体的监听者类Listener2
class Listener2 : public Listener {
public:
  Listener2(string name) : Listener(name) {}
  // Listener2处理自己感兴趣的事件
  void handleMessage(int msgid) {
    cout << "listener:" << _name << " recv:" << msgid << " msg, handle it now!"
         << endl;
  }
};
// 实现观察者用强弱智能指针，解决多线程访问共享对象的线程安全问题
class Observer {
public:
  /*
  params:
  1. Listener *pListener: 具体的监听者
  2. int msgid： 监听者感兴趣的事件
  该函数接口主要用于监听者向观察者注册感兴趣的事件
  */
  void registerListener(weak_ptr<Listener> pwListener, int msgid) {
    auto it = listenerMap.find(msgid);
    if (it == listenerMap.end()) {
      // 没人对msgid事件感兴趣过，第一次注册
      listenerMap[msgid].push_front(pwListener);
    } else {
      // 直接把当前pListener添加到对msgid事件感兴趣的list列表中
      it->second.push_front(pwListener);
    }
  }
  /*
  params:
  1. int msgid：观察到发生的事件id
  该函数接口主要用于观察者观察到事件发生，并转发到对该事件感兴趣
  的监听者
  */
  void dispatchMessage(int msgid) {
    auto it = listenerMap.find(msgid);
    if (it != listenerMap.end()) {
      for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1) {
        // 智能指针的提升操作，用来判断监听者对象是否存活
        shared_ptr<Listener> ps = it1->lock();
        // 监听者对象如果存活，才通知处理事件
        if (ps != nullptr) {
          ps->handleMessage(msgid);
        } else {
          // 监听者对象已经析构，从map中删除这样的监听者对象
          it1 = it->second.erase(it1);
        }
      }
    }
  }

private:
  // 存储监听者注册的感兴趣的事件
  unordered_map<int, list<weak_ptr<Listener>>> listenerMap;
};
int main() {
  shared_ptr<Listener> p1(new Listener1("高海山"));
  shared_ptr<Listener> p2(new Listener2("冯丽婷"));

  Observer obser;
  // 监听者p1注册1，2，3号事件
  obser.registerListener(p1, 1);
  obser.registerListener(p1, 2);
  obser.registerListener(p1, 3);
  // 监听者p2注册1，3号事件
  obser.registerListener(p2, 1);
  obser.registerListener(p2, 3);

  // 模拟事件的发生
  int msgid;
  for (;;) {
    cout << "输入事件id:";
    cin >> msgid;
    if (-1 == msgid)
      break;
    // 通过用户手动输入msgid模拟事件发生，此处观察者派发事件
    obser.dispatchMessage(msgid);
  }

  return 0;
}
```

# 6 C++11 容器 `emplace` 方法原理剖析

`emplace` 方法是 C++11 新增的一个方法，用于在容器中直接构造对象，而不是先构造一个临时对象，然后再调用拷贝构造函数。`emplace` 方法的使用方式和 `push_back` 方法类似，只是 `emplace` 方法的参数是直接传递给构造函数的，而 `push_back` 方法的参数是传递给拷贝构造函数的。

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Test {
public:
  Test(int a) { cout << "Test(int)" << endl; }
  Test(int a, int b) { cout << "Test(int, int)" << endl; }
  ~Test() { cout << "~Test()" << endl; }
  Test(const Test &t) { cout << "Test(const Test &)" << endl; }
  Test(Test &&) { cout << "Test(Test &&)" << endl; }
};

int main() {
  Test t1(10);
  vector<Test> v;
  v.reserve(100);

  cout << "=============直接插入对象，两个是没有区别的============" << endl;
  v.push_back(t1);
  v.emplace_back(t1);

  cout << "=============直接插入临时对象，两个也是没有区别的============"
       << endl;
  v.push_back(Test(20));
  v.emplace_back(Test(20));
  cout << "=============区别所在========" << endl;
  // 给 emplace_back 传递的参数，会直接传递给构造函数，
  // 而 push_back 会先构造一个临时对象，然后再调用拷贝构造函数
  v.emplace_back(30);
  v.emplace_back(30, 40);
  cout << "=====================" << endl;

  /*
   * map<int, string> m;
   * m.insert(pair<int, string>(1, "hello")); // 临时对象，拷贝构造
   * m.emplace(1, "hello"); // 直接传递参数，不需要拷贝构造
   */
  return 0;
}
```
