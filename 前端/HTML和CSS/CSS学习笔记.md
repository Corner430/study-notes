# CSS 学习笔记

## 1 CSS 的介绍

1. css 的定义

> css(Cascading Style Sheet)层叠样式表，它是用来美化页面的一种语言。

没有使用css的效果图

![css1](imgs/css1.png)

使用css的效果图

![css2](imgs/css2.png)

2. css 的作用
    1. 美化界面, 比如: 设置标签文字大小、颜色、字体加粗等样式。
    2. 控制页面布局, 比如: 设置浮动、定位等样式。

3. css 的基本语法

选择器{

样式规则

}

样式规则：

属性名1：属性值1;

属性名2：属性值2;

属性名3：属性值3;

...

选择器: **是用来选择标签的，选出来以后给标签加样式。**

代码示例:

```css
div{ 
    width:100px; 
    height:100px; 
    background:gold; 
}
```

说明

css 是由两个主要的部分构成：**选择器和一条或多条样式规则**，注意: **样式规则需要放到大括号里面。**

## 2 css 的引入方式

**css的三种引入方式**

- 行内式
- 内嵌式（内部样式）
- 外链式

1. 行内式

直接在标签的 `style` 属性中添加 `css` 样式

示例代码:

```css
<div style="width:100px; height:100px; background:red ">hello</div>
```

- 优点：方便、直观。
- 缺点：缺乏可重用性。

2. 内嵌式（内部样式）

在 `<head>` 标签内加入 `<style>` 标签，在 `<style>` 标签中编写 css 代码。

示例代码:

```css
<head>
   <style type="text/css">
      h3{
         color:red;
      }
   </style>
</head>
```

- 优点：在同一个页面内部便于复用和维护。
- 缺点：在多个页面之间的可重用性不够高。

3. 外链式

将`css`代码写在一个单独的`.css`文件中，在`<head>`标签中使用`<link>`标签直接引入该文件到页面中。

示例代码:

```css
<link rel="stylesheet" type="text/css" href="css/main.css">
```

- 优点：使得css样式与html页面分离，便于整个页面系统的规划和维护，可重用性高。
- 缺点：css代码由于分离到单独的css文件，容易出现css代码过于集中，若维护不当则极容易造成混乱。

4. css引入方式选择

- 行内式几乎不用
- 内嵌式在学习css样式的阶段使用
- 外链式在公司开发的阶段使用，可以对 css 样式和 html 页面分别进行开发。

## 3 css 选择器

1. css 选择器的定义

css 选择器是用来选择标签的，选出来以后给标签加样式。

2. css 选择器的种类

- 标签选择器
- 类选择器
- 层级选择器(后代选择器)
- id选择器
- 组选择器
- 伪类选择器

3. 标签选择器

根据标签来选择标签，以标签开头，此种选择器影响范围大，一般用来做一些通用设置。

示例代码

```css
<style type="text/css">
    p{
        color: red;
    }
</style>

<div>hello</div>
<p>hello</p>
```

4. 类选择器

根据类名来选择标签，以 `.` 开头, 一个类选择器可应用于多个标签上，一个标签上也可以使用多个类选择器，多个类选择器需要使用空格分割，应用灵活，可复用，是css中应用最多的一种选择器。

示例代码

```css
<style type="text/css">
    .blue{color:blue}
    .big{font-size:20px}
    .box{width:100px;height:100px;background:gold} 
</style>

<div class="blue">这是一个div</div>
<h3 class="blue big box">这是一个标题</h3>
<p class="blue box">这是一个段落</p>
```

5. 层级选择器(后代选择器)

根据层级关系选择后代标签，以**选择器1 选择器2**开头，主要应用在标签嵌套的结构中，减少命名。

示例代码

```css
<style type="text/css">
    div p{
        color: red;
    }
    .con{width:300px;height:80px;background:green}
    .con span{color:red}
    .con .pink{color:pink}
    .con .gold{color:gold}    
</style>

<div>
    <p>hello</p>
</div>

<div class="con">
    <span>哈哈</span>
    <a href="#" class="pink">百度</a>
    <a href="#" class="gold">谷歌</a>
</div>
<span>你好</span>
<a href="#" class="pink">新浪</a>
```

> 注意: 这个层级关系不一定是父子关系，也有可能是祖孙关系，只要有后代关系都适用于这个层级选择器

6. id选择器

根据id选择标签，以#开头, 元素的id名称不能重复，所以id选择器只能对应于页面上一个元素，不能复用，id名一般给程序使用，所以不推荐使用id作为选择器。

示例代码

```css
<style type="text/css">
    #box{color:red} 
</style>

<p id="box">这是一个段落标签</p>   <!-- 对应以上一条样式，其它元素不允许应用此样式 -->
<p>这是第二个段落标签</p> <!-- 无法应用以上样式，每个标签只能有唯一的id名 -->
<p>这是第三个段落标签</p> <!-- 无法应用以上样式，每个标签只能有唯一的id名  -->
```

> 注意: 虽然给其它标签设置id=“box”也可以设置样式，但是不推荐这样做，因为id是唯一的，以后js通过id只能获取一个唯一的标签对象。

7. 组选择器

根据组合的选择器选择不同的标签，以 `,` 分割开, 如果有公共的样式设置，可以使用组选择器。

示例代码

```css
<style type="text/css">
    .box1,.box2,.box3{width:100px;height:100px}
    .box1{background:red}
    .box2{background:pink}
    .box2{background:gold}
</style>

<div class="box1">这是第一个div</div>
<div class="box2">这是第二个div</div>
<div class="box3">这是第三个div</div>
```

8. 伪类选择器

用于向选择器添加特殊的效果, 以 `:` 分割开, 当用户和网站交互的时候改变显示效果可以使用伪类选择器

示例代码

```css
<style type="text/css">
    .box1{width:100px;height:100px;background:gold;}
    .box1:hover{width:300px;}
</style>

<div class="box1">这是第一个div</div>
```

## 4 css 属性

### 4.1 布局常用样式属性

- `width` 设置元素(标签)的宽度，如：`width:100px`;
- `height` 设置元素(标签)的高度，如：`height:200px`;
- `background` 设置元素背景色或者背景图片，如：`background:gold`; 设置元素的背景色, `background: url(images/logo.png)`; 设置元素的背景图片。
- `border` 设置元素四周的边框，如：`border:1px solid black`; 设置元素四周边框是1像素宽的黑色实线
- 以上也可以拆分成四个边的写法，分别设置四个边的：
- `border-top` 设置顶边边框，如：`border-top:10px solid red`;
- `border-left` 设置左边边框，如：`border-left:10px solid blue`;
- `border-right` 设置右边边框，如：`border-right:10px solid green`;
- `border-bottom` 设置底边边框，如：`border-bottom:10px solid pink`;
- `padding` 设置元素包含的内容和元素边框的距离，也叫内边距，如`padding:20px`;`padding`是同时设置4个边的，也可以像`border`一样拆分成分别设置四个边:`padding-top`、`padding-left`、`padding-right`、`padding-bottom`。
- `margin` 设置元素和外界的距离，也叫外边距，如`margin:20px`;`margin`是同时设置4个边的，也可以像`border`一样拆分成分别设置四个边:`margin-top`、`margin-left`、`margin-right`、`margin-bottom`。
- `float` 设置元素浮动，浮动可以让块元素排列在一行，浮动分为左浮动：`float:left`; 右浮动：`float:right`;

### 4.2 文本常用样式属性

- color 设置文字的颜色，如： color:red;
- font-size 设置文字的大小，如：font-size:12px;
- font-family 设置文字的字体，如：font-family:'微软雅黑';为了避免中文字不兼容，一般写成：font-family:'Microsoft Yahei';
- font-weight 设置文字是否加粗，如：font-weight:bold; 设置加粗 font-weight:normal 设置不加粗
- line-height 设置文字的行高，如：line-height:24px; 表示文字高度加上文字上下的间距是24px，也就是每一行占有的高度是24px
- text-decoration 设置文字的下划线，如：text-decoration:none; 将文字下划线去掉
- text-align 设置文字水平对齐方式，如text-align:center 设置文字水平居中
- text-indent 设置文字首行缩进，如：text-indent:24px; 设置文字首行缩进24px