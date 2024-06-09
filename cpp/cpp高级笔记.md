# 1 对象的应用优化、右值引用的优化

## 1.1 临时对象、类方法的调用

> - C++ 编译器对于对象构造的优化：用临时对象生成新对象时，不产生临时对象，直接构造新对象
> - 临时对象的生存周期：表达式结束时
> - 可以使用引用来引用临时对象, 但是不能使用指针来指向临时对象
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
  // Test(20)         显式生成临时对象, 生存周期: 表达式结束时
  /*
   * C++
   * 编译器对于对象构造的优化：用临时对象生成新对象时，不产生临时对象，直接构造新对象
   */
  Test t4 = Test(20); // 有参构造, 等价于 Test t4(20);

  cout << "----------------" << endl;

  t4 = t2;       // 赋值运算符重载
  t4 = Test(30); // 有参构造, 赋值运算符重载, 析构函数

  cout << "------显式生成临时对象--------" << endl;

  t4 = (Test)30; // 有参构造, 赋值运算符重载, 析构函数,
                 // 这是一个显式的强制类型转换: int -> Test(int)

  cout << "------隐式生成临时对象--------" << endl;

  t4 = 30; // 有参构造, 赋值运算符重载, 析构函数, 这是一个隐式的强制类型转换
           // int -> Test(int)

  cout << "-------指针和引用 && 临时对象-------" << endl;

  // Test *p = &Test(40); // 有参构造, 指针指向临时对象, 临时对象析构
                          // 报错 taking address of rvalue [-fpermissive]

  const Test &r = Test(50); // 有参构造

  // > 可以使用引用来引用临时对象, 但是不能使用指针来指向临时对象

  cout << "----------------" << endl;

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

## 1.2 临时对象，局部对象返回

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
2. 函数返回对象时，优先返回临时对象，而不是定义过的局部对象（这样会由于作用域问题，函数结束时再在上层函数构造一个临时对象）。**其实对于聪明的编译器，都一样**
3. 接收返回值是对象的函数调用时，优先按初始化的方式接收，而不是赋值的方式接收

## 1.4 右值引用

- [引用和指针----右值引用](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E4%B8%AD%E7%BA%A7%E7%AC%94%E8%AE%B0.md#22-%E5%BC%95%E7%94%A8%E5%92%8C%E6%8C%87%E9%92%88)
  - **一个右值引用变量，本身是一个左值**
- [引用可以作为重载条件](https://github.com/Corner430/study-notes/blob/main/cpp/cpp%E5%85%A5%E9%97%A8%E7%AC%94%E8%AE%B0.md#2432-%E5%87%BD%E6%95%B0%E9%87%8D%E8%BD%BD%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9)，左值引用和右值引用也可以作为重载条件

> **临时量属于右值!!!**

## 1.5 右值引用优化

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

## 1.6 `move` 语义 和 `forward` 类型完美转发

### 1.6.1 `move` 语义

在 C++11 之前，对象的拷贝操作是通过拷贝构造函数和拷贝赋值运算符实现的，这对于性能要求高的场景（如容器类的实现）可能会造成不必要的性能开销。为了优化资源的管理，C++11 引入了移动语义。

**移动语义的核心概念**是将资源（如内存、文件句柄等）的所有权从一个对象转移到另一个对象，而不是复制资源。这是通过引入右值引用（rvalue reference）来实现的，右值引用使用`&&`表示。

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

3. **std::move**：`std::move`是一个标准库函数模板，它**将一个左值转换为右值引用**，从而允许该对象的资源被移动。
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

`std::forward`是一个函数模板，用于将参数“完美”地转发给另一个函数。它会根据传递给它的参数的值类别（左值或右值），决定是传递左值还是右值。

```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward确保arg的值类别被保留
    someFunction(std::forward<T>(arg));
}
```

#### 1.6.2.3 如何实现完美转发：

1. **模板参数**：使用万能引用（universal reference），即`T&&`，这是一个可以接受左值或右值的引用。
2. **`std::forward`**：在内部调用中使用`std::forward`，它会根据模板参数的类型判断是左值还是右值，从而进行相应的转发。

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

- **移动语义**通过右值引用和`std::move`来实现资源的高效转移，避免不必要的拷贝。
- **完美转发**通过万能引用和`std::forward`来保持参数的值类别，从而高效地调用其他函数。

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
int main()
{
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
template<typename T>
class CSmartPtr
{
public:
    CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}
    ~CSmartPtr() { delete mptr; }
private:
    T *mptr;
};

int main()
{
    CSmartPtr<int> ptr(new int);
    /* 其它的代码... */
    /* 由于ptr是栈上的智能指针对象，不管是函数正常执行完，还是运行过程中出现异常，
    栈上的对象都会自动调用析构函数，在析构函数中进行了delete操作，保证释放资源 */
    return 0;
}
```

上面的代码是一个非常简单的智能指针，主要用了以下两点：

1. 智能指针通过将裸指针进行面向对象的封装，在构造函数中初始化资源地址，在析构函数中负责释放资源。
2. 利用栈上对象出作用域自动析构的特性，在智能指针的析构函数中保证释放资源。

因此，**智能指针通常定义在栈上**。有一个常见的面试问题是“能不能在堆上定义智能指针？”。例如，代码`CSmartPtr *p = new CSmartPtr(new int);`虽然定义了一个智能指针类型，但它实际上是一个裸指针，仍需要手动`delete`，这样又回到了裸指针面临的问题。

要使智能指针的使用与裸指针相似，还需要提供裸指针常见的`*`和`->`运算符的重载函数，使用起来才真正像裸指针。代码扩展如下：

```cpp
template<typename T>
class CSmartPtr
{
public:
    CSmartPtr(T *ptr = nullptr) : mptr(ptr) {}
    ~CSmartPtr() { delete mptr; }

    T& operator*() { return *mptr; }
    const T& operator*() const { return *mptr; }

    T* operator->() { return mptr; }
    const T* operator->() const { return mptr; }
private:
    T *mptr;
};

int main()
{
    CSmartPtr<int> ptr(new int);
    *ptr = 20;
    std::cout << *ptr << std::endl;
    return 0;
}
```

上面的智能指针，使用起来就和普通的裸指针非常相似了，但它仍存在一些问题。例如：

```cpp
int main()
{
    CSmartPtr<int> ptr1(new int);
    CSmartPtr<int> ptr2(ptr1);
    return 0;
}
```

这个`main`函数会导致程序崩溃，原因是默认的拷贝构造函数做的是浅拷贝，两个智能指针都持有同一个资源。`ptr2`先析构释放资源后，`ptr1`析构时会尝试删除已经被释放的资源，导致程序崩溃。因此，智能指针需要解决以下问题：

1. 如何解决智能指针的浅拷贝问题。
2. 当多个智能指针指向同一个资源时，如何保证资源只释放一次，而不是每个智能指针都释放一次，避免程序运行中出现不可预期的严重后果。

## 2.3 不带引用计数的智能指针

C++标准库中提供了几种不带引用计数的智能指针，主要包括：`auto_ptr`，`scoped_ptr`，`unique_ptr`。

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

**总结**：`auto_ptr` 通过将原指针置为 `nullptr` 来避免浅拷贝问题，然而由于其不安全性和局限性，C++11 引入了更好的替代品，不建议使用 `auto_ptr`。

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

- 互斥锁是比较重的，适合于临界区代码做的事情稍稍复杂的情形。而`++`, `--`操作使用CAS原子特性就足够了，是无锁操作。
- CAS 并不是不加锁，只不过加锁解锁不在软件层面。cpu 和内存之间通信通过系统总线进行。CAS通过 `exchange/swap` 指令，相当于给总线加锁，当一个线程在做 cpu 和内存交换，不允许其他线程再使用总线，有助于提高多线程效率。
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

## 5.2 简单工厂、工厂方法、抽象工厂

## 5.3 迭代器模式

## 5.4 观察者模式

## 5.5 代理模式

# 6 面向对象编程实践

## 6.1 深度遍历搜索迷宫路径

## 6.2 广度遍历搜索迷宫路径找出最短路径

## 6.3 大数加减法

## 6.4 海量数据查重以及求 top k 问题

## 6.5 数字化男女匹配问题

# 7 校招 C++ 面经讲解

# 8 应聘 C++ 研发岗简历模板
