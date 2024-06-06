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

## 1.6 move 语义 和 forward 类型完美转发




# 2 智能指针

# 3 绑定器和函数对象、`lambda` 表达式

# 4 C++11 内容汇总、多线程应用实践

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
