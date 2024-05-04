# JavaScript 笔记

- [JavaScript 笔记](#javascript-笔记)
  - [1 JavaScript 的定义](#1-javascript-的定义)
  - [2 JavaScript 的使用方式](#2-javascript-的使用方式)
  - [3 变量和数据类型](#3-变量和数据类型)
    - [3.1 定义变量](#31-定义变量)
    - [3.2 JavaScript 注释](#32-javascript-注释)
    - [3.3 数据类型](#33-数据类型)
    - [3.4 变量命名规范](#34-变量命名规范)
    - [3.5 匈牙利命名风格](#35-匈牙利命名风格)
  - [4 函数定义和调用](#4-函数定义和调用)
  - [5 变量作用域](#5-变量作用域)
  - [6 条件语句](#6-条件语句)
  - [7 获取标签元素](#7-获取标签元素)
  - [8 操作标签元素属性](#8-操作标签元素属性)
    - [8.1 属性的操作](#81-属性的操作)
    - [8.2 innerHTML](#82-innerhtml)
  - [9 数组及操作方法](#9-数组及操作方法)
  - [10 循环语句](#10-循环语句)
  - [11 字符串拼接](#11-字符串拼接)
  - [12 定时器](#12-定时器)
    - [12.1 定时器的创建](#121-定时器的创建)
    - [12.1 定时器的清除](#121-定时器的清除)
    - [12.3 代码示例](#123-代码示例)

## 1 JavaScript 的定义

JavaScript是运行在浏览器端的脚本语言, 是**由浏览器解释执行的**, 简称 `js`, 它能够让网页和用户有交互功能, 增加良好的用户体验效果。

**前端开发三大块**

1. HTML：负责网页结构
2. CSS：负责网页样式
3. JavaScript：负责网页行为，比如: 网页与用户的交互效果

## 2 JavaScript 的使用方式

```js
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <!-- 内嵌式 -->
  <script>
    alert("我是内嵌式的 js 代码");
  </script>
  <!-- 外链式 -->
  <script src="js/main.js"></script>
  <body>
    <!-- 行内式 -->
    <input type="button" value="按钮" onclick="alert('你点我了！')" />
  </body>
</html>
```

***main.js代码:***

```js
alert("我是外链式的 js 代码");
```

![20240503143222](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240503143222.png)

> 注意代码执行是自上而下的

## 3 变量和数据类型

### 3.1 定义变量

JavaScript 是一种弱类型语言，也就是说不需要指定变量的类型，JavaScript 的变量类型由它的值来决定，定义变量需要用关键字 `var`, 一条 JavaScript 语句应该以 `;` 结尾

**定义变量的语法格式:**

var 变量名 = 值;

```js
var iNum = 123;
var sTr = 'asd';

// 同时定义多个变量可以用","隔开，公用一个‘var’关键字

var iNum = 45, sTr='qwe', sCount='68';
```

### 3.2 JavaScript 注释

JavaScript 的注释分为单行注释(`//注释内容`)和多行注释(`/*多行注释*/`)

```js
<script type="text/javascript">    

// 单行注释
var iNum = 123;
/*  
    多行注释
    1、...
    2、...
*/
var sTr = 'abc123';
</script>
```

### 3.3 数据类型

js中有六种数据类型，包括五种基本数据类型和一种复杂数据类型(`object`)。

5 种基本数据类型：

1. `number` 数字类型
2. `string` 字符串类型
3. `boolean` 布尔类型 `true` 或 `false`
4. `undefined` `undefined`类型，变量声明未初始化，它的值就是 `undefined`
5. `null` `null`类型，表示空对象，如果定义的变量将来准备保存对象，可以将变量初始化为 `null`, 在页面上获取不到对象，返回的值就是 `null`

1 种复合类型：

1. `object` 后面学习的数组、函数和JavaScript对象都属于复合类型

```js
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      // 定义数字类型的变量
      var iNum = 1;
      var fNum1 = 2.5;

      // 定义字符串
      var sName = "张三";

      // 定义 boolean 类型
      var bIsOk = true;

      // 定义 undefined 类型
      var unData;

      // 定义空对象
      var oData = null;

      // 定义 JavaScript 对象
      var oPerson = {
        name: "李四",
        age: 18,
      };

      // alert(iNum);
      // alert(fNum1);
      // alert(sName);
      alert(oPerson.name);

      // 输出到 console
      console.log(oPerson.name);

      // 查看数据类型用 typeof
      alert(typeof iNum);
      alert(typeof fNum1);
      alert(typeof sName);
      alert(typeof bIsOk);
      alert(typeof unData);
      // 由于 js 历史原因，设计之前没有 null 类型，所以 null 类型的数据类型是 object
      alert(typeof oData);
      alert(typeof oPerson);
    </script>
  </head>
  <body></body>
</html>
```

### 3.4 变量命名规范

1. 区分大小写
2. 第一个字符必须是字母、下划线（`_`）或者美元符号（`$`）
3. 其他字符可以是字母、下划线、美元符或数字

### 3.5 匈牙利命名风格

- 对象`o` `Object` 比如：`oDiv`
- 数组`a` `Array` 比如：`aItems`
- 字符串`s` `String` 比如：`sUserName`
- 整数`i` `Integer` 比如：`iItemCount`
- 布尔值`b` `Boolean` 比如：`bIsComplete`
- 浮点数`f` `Float` 比如：`fPrice`
- 函数`fn`` Function` 比如：`fnHandler`

## 4 函数定义和调用

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script type="text/javascript">
      // 函数定义
      function sayHello() {
        alert("Hello World");
      }

      // 定义有参函数
      function Add(a, b) {
        alert(a + b);
      }

      // 函数调用
      sayHello();

      // 有参函数调用
      var res = Add(1, 2);
      alert(res);
    </script>
  </head>
  <body></body>
</html>
```

## 5 变量作用域

```js
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script type="text/javascript">
      // 定义一个全局变量
      var a = 12;

      function myalert() {
        // 定义一个局部变量
        var b = 23;
        alert(b);

        // 函数内部可以访问函数外部的全局变量
        alert(a);
      }

      myalert(); // 弹出23
      // alert(b);  // 函数外部无法访问函数内部的变量, 会在 console 中报错
    </script>
  </head>
  <body></body>
</html>
```

## 6 条件语句

1. 条件语句语法
    1. `if` 语句 - 只有当指定条件为 `true` 时，使用该语句来执行代码
    1. `if...else` 语句 - 当条件为 `true` 时执行代码，当条件为 `false` 时执行其他代码
    1. `if...else if....else` 语句 - 使用该语句来判断多条件，执行条件成立的语句

2. 比较运算符

假如 x = 5, 查看比较后的结果:

| 比较运算符 | 描述 | 例子 |
| :--- | :--- | :--- |
| == | 等于 | x == 8 为 false |
| === | 全等(值和类型) | x === 5 为 true; x === "5" 为 false |
| != | 不等于 | x != 8 为 true |
| > | 大于 | x > 8 为 false |
| < | 小于 | x < 8 为 true |
| >= | 大于或等于 | x >= 8 为 false |
| <= | 小于或等于 | x <= 8 为 true |

比较运算符示例代码:

```js
<script type="text/javascript">
    var iNum01 = 12;
    var sNum01 = "12";

    if (iNum01 == 12) {
    alert("相等！");
    } else {
    alert("不相等！");
    }

    // "==" 符号默认会将符号两边的变量转换成数字再进行对比，这个叫做隐式转换
    if (sNum01 == 12) {
    alert("相等！");
    } else {
    alert("不相等！");
    }

    // "===" 符号不会转换符号两边的数据类型
    if (sNum01 === 12) {
    alert("相等！");
    } else {
    alert("不相等！");
    }

    // 多条件判断
    var sFruit = "苹果";
    if (sFruit == "苹果") {
    alert("您选择的水果是苹果");
    } else if (sFruit == "鸭梨") {
    alert("您选择的水果是鸭梨");
    } else {
    alert("对不起，您选择的水果不存在!");
    }
</script>
```

3. 逻辑运算符

假如 x=6, y=3, 查看比较后的结果:

| 逻辑运算符 | 描述 | 例子 |
| :--- | :--- | :--- |
| && | and | (x < 10 && y > 1) 为 true |
| \|\| | or | (x==5 \|\| y==5) 为 false |
| ! | not | !(x==y) 为 true |

逻辑运算符示例代码:

```js
<script type="text/javascript">
    var x = 6;
    var y = 3;

    if (x < 10 && y > 1) {
    alert("都大于");
    } else {
    alert("至少有一个不大于");
    }

    if (x > 5 || y > 7) {
    alert("至少有一个大于");
    } else {
    alert("都不大于");
    }

    if (!(x == y)) {
    alert("等于");
    } else {
    alert("不等于");
    }
</script>
```

## 7 获取标签元素

可以使用内置对象 `document` 上的 `getElementById` 方法来获取页面上设置了 `id` 属性的标签元素，获取到的是一个`html`对象，然后将它赋值给一个变量，比如：

```js
<script type="text/javascript">
    // document 是 js 内置对象，getElementById 是 document 对象上的方法
    var oDiv = document.getElementById('div1');
    alert(oDiv);
</script>
<div id="div1">这是一个div元素</div>
```

**说明:**

上面的代码，如果把 javascript 写在元素的上面，就会出错，因为页面上从上往下加载执行的，javascript去页面上获取元素 `div1` 的时候，元素 `div1` 还没有加载。

**解决方法有两种:**

第一种方法：将 javascript 放到页面最下边（不推荐使用）

```js
<div id="div1">Hello World</div>

<script type="text/javascript">
    var oDiv = document.getElementById("div1");
    alert(oDiv);
</script>
```

第二种方法：设置页面加载完成执行的函数，在执行函数里面获取标签元素。

```js
<script type="text/javascript">
    // 匿名函数，页面加载完成后执行
    // window.onload = function () {
    // var oDiv = document.getElementById("div1");
    // alert(oDiv);
    // };

    // 非匿名函数，页面加载完成后执行
    function getDiv() {
        var oDiv = document.getElementById("div1");
        alert(oDiv);
    }
    window.onload = getDiv;
</script>
```

**说明:**

`onload` 是页面所有元素加载完成的事件，给 `onload` 设置函数时，当事件触发就会执行设置的函数。

## 8 操作标签元素属性

### 8.1 属性的操作

首先获取的页面标签元素，然后就可以对页面标签元素的属性进行操作，属性的操作包括:

- 属性的读取
- 属性的设置

属性名在 `js` 中的写法

1. `html` 的属性和 `js` 里面属性大多数写法一样，但是`class` 属性写成 `className`
2. `style` 属性里面的属性，有横杠的改成驼峰式，比如：`font-size`，改成`style.fontSize`

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .btnstyle {
        background: yellow;
        font-size: 30px;
      }
    </style>
    <script>
      window.onload = function () {
        // 根据 id 获取标签对象
        var oBtn = document.getElementById("btn1");
        // 获取标签的属性
        alert(oBtn.type);
        alert(oBtn.value);
        // 设置标签的属性
        oBtn.name = "username";
        // 设置标签的样式
        // oBtn.style.background = 'red';

        // 设置标签的类名
        oBtn.className = "btnstyle";

        // oBtn.style.fontSize = "50px";
      };
    </script>
  </head>
  <body>
    <input type="button" value="按钮" id="btn1" />
  </body>
</html>
```

### 8.2 innerHTML

`innerHTML` 可以读取或者设置标签包裹的内容

```js
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      window.onload = function () {
        // 根据 id 获取标签对象
        var oDiv = document.getElementById("div1");
        // 获取标签内容
        alert(oDiv.innerHTML);
        // 设置标签内容
        oDiv.innerHTML = "<a href='http://www.baidu.com'>百度</a>";
      };
    </script>
  </head>
  <body>
    <div id="div1">我是 div !!!</div>
  </body>
</html>
```

## 9 数组及操作方法

1. 数组的介绍

数组就是一组数据的集合, javascript 中, **数组里面的数据可以是不同类型的数据**, 好比 python 里面的列表.

2. 数组的定义

```js
// 实例化对象方式创建
var aList = new Array(1, 2, 3);

// 字面量方式创建，推荐使用
var aList2 = [1, 2, 3, 'asd'];
```

3. 多维数组

多维数组指的是数组的成员也是数组，把这样的数组叫做多维数组。

```js
var aList = [[1, 2, 3], ['a', 'b', 'c']];
```

4. 数组的操作
    1. 获取数组的长度
    ```js
    var aList = [1, 2, 3, 4];
    alert(aList.length); // 弹出4
    ```
    2. 根据下标取值
    ```js
    var aList = [1, 2, 3, 4];
    alert(aList[0]); // 弹出1
    ```
    3. 从数组最后添加和删除数据
    ```js
    var aList = [1, 2, 3, 4];
    aList.push(5);
    alert(aList); //弹出1, 2, 3, 4, 5
    aList.pop();
    alert(aList); // 弹出1, 2, 3, 4
    ```
    4. 根据下标添加和删除元素
    ```js
    arr.splice(start, num, element1, ....., elementN)
    ```

    参数解析：
    1. `start`：必需，开始删除的索引。
    2. `num`：可选，删除数组元素的个数。
    3. `elementN`：可选，在`start`索引位置要插入的新元素。

此方法会删除从`start`索引开始的`num`个元素，并将`elementN`参数插入到`start`索引位置。

**示例代码**

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      // 定义数组
      var aArray1 = new Array(1, 2, 3);
      console.log(aArray1);

      var aArray2 = [3, 6, 9];
      console.log(aArray2);

      // 多维数组
      var aArray3 = [
        [1, 2, 3],
        [4, 5, 6],
      ];
      console.log(aArray3);

      // 根据索引访问数组元素
      alert(aArray3[0][1]);

      // 演示数组的相关操作
      var aArray4 = [1, 2, 3, 4, 5];
      // 获取数组长度
      alert(aArray4.length);

      // 根据索引访问数组元素
      alert(aArray4[2]);

      // 根据索引修改数组元素
      aArray4[2] = 100;
      console.log(aArray4);

      // 追加元素
      aArray4.push("hello");
      console.log(aArray4);

      // 删除最后一个元素, 不支持传参
      var oValue = aArray4.pop();
      console.log(oValue);

      // 插入一个或多个元素
      aArray4.splice(2, 0, "world");
      aArray4.splice(2, 0, "hello", "world");
      console.log(aArray4);

      // 从 index 2 删除 2 个元素
      aArray4.splice(2, 2);
      console.log(aArray4);
    </script>
  </head>
  <body></body>
</html>
```

## 10 循环语句

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      var array = [1, 4, 5, 6, 7, 8, 9, 10];

      // for loop
      for (var i = 0; i < array.length; i++) {
        console.log(array[i]);
      }

      // while loop
      var index = 0;
      while (index < array.length) {
        console.log(array[index]);
        index++;
      }

      // do while loop
      index = 0;
      do {
        console.log(array[index]);
        index++;
      } while (index < array.length);
    </script>
  </head>
  <body></body>
</html>
```

## 11 字符串拼接

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      var iNum1 = 10;
      var fNum2 = 11.1;
      var sStr = "abc";

      result = iNum1 + fNum2;
      alert(result); // 21.1

      // 数字和字符串相加，会将数字转换为字符串
      result = iNum1 + sStr;
      alert(result); // 10abc
    </script>
  </head>
  <body></body>
</html>
```

## 12 定时器

定时器就是在一段特定的时间后执行某段程序代码。

### 12.1 定时器的创建

1. `setTimeout(func[, delay, param1, param2, ...])` ：以指定的**时间间隔**（以毫秒计）调用**一次**函数的定时器
2. `setInterval(func[, delay, param1, param2, ...])` ：以指定的**时间间隔**（以毫秒计）**重复**调用一个函数的定时器

**参数说明:**

- 第一个参数 `func` , 表示定时器要执行的函数名
- 第二个参数 `delay`, 表示时间间隔，默认是 `0`，单位是毫秒
- 第三个参数 `param1`, 表示定时器执行函数的第一个参数，一次类推传入多个执行函数对应的参数。

### 12.1 定时器的清除

1. `clearTimeout(timeoutID)` 清除只执行一次的定时器(`setTimeout`函数)
2. `clearInterval(timeoutID)` 清除反复执行的定时器(`setInterval`函数)

**参数说明:**

- `timeoutID` 为调用 `setTimeout` 函数时所获得的返回值，使用该返回标识符作为参数，可以取消该 `setTimeout` 所设定的定时执行操作。

### 12.3 代码示例

**单次执行函数的定时器**

```html
<script>
  function fuShow(name) {
    alert(name + ", " + "Hello World!");
    alert(tid);
    // 销毁定时器
    clearTimeout(tid);
  }

  // 根据时间间隔，调用一次函数的定时器
  // 返回值是一个定时器的ID
  var tid = setTimeout(fuShow, 3000, "corner");
</script>
```

**重复执行函数的定时器**

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script>
      function fuShow(name) {
        alert(name + ", " + "Hello World!");
      }

      function fnStop() {
        // alert(tid);
        // 清除定时器
        clearInterval(tid);
      }

      // 根据时间间隔，重复调用函数的定时器
      var tid = setInterval(fuShow, 2000, "Tom");
    </script>
  </head>
  <body>
    <input type="button" value="停止" onclick="fnStop()" />
  </body>
</html>
```