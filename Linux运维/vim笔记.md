- [1 教程](#1-教程)
- [2 模式](#2-模式)
  - [2.1 普通模式](#21-普通模式)
  - [2.2 插入模式](#22-插入模式)
  - [2.3 可视模式](#23-可视模式)
  - [2.4 命令行模式](#24-命令行模式)
- [3 文件](#3-文件)
  - [3.1 管理多个文件](#31-管理多个文件)
    - [3.1.1 用缓冲区列表管理打开的文件](#311-用缓冲区列表管理打开的文件)
    - [3.1.2 用参数列表将缓冲区分组](#312-用参数列表将缓冲区分组)
    - [3.1.3 管理隐藏缓冲区](#313-管理隐藏缓冲区)
    - [3.1.4 将工作区切分成窗口](#314-将工作区切分成窗口)
    - [3.1.5 用标签页将窗口分组](#315-用标签页将窗口分组)
  - [3.2 打开及保存文件](#32-打开及保存文件)
    - [3.2.1 用 :edit 命令打开文件](#321-用-edit-命令打开文件)
    - [3.2.2 用 :find 打开文件](#322-用-find-打开文件)
    - [3.2.3 使用 netrw 管理文件系统](#323-使用-netrw-管理文件系统)
    - [3.2.4 把文件保存到不存在的目录中](#324-把文件保存到不存在的目录中)
    - [3.2.5 以超级用户权限保存文件](#325-以超级用户权限保存文件)
- [4 更快地移动及跳转](#4-更快地移动及跳转)
- [5 寄存器](#5-寄存器)
- [6 模式](#6-模式)
- [7 工具](#7-工具)
- [8 折叠](#8-折叠)
- [9 自动补全](#9-自动补全)
- [10 插件](#10-插件)
- [9 vscode 常用](#9-vscode-常用)
- [10 Vim 重编译](#10-vim-重编译)
- [11 vimrc](#11-vimrc)


# 1 教程

- [Vimtutor_1.5](http://www2.geog.ucl.ac.uk/~plewis/teaching/unix/vimtutor)
- [vimtutor](https://vimhelp.org/usr_01.txt.html#vimtutor)：有一些书籍进行推荐，还有电子版
- [VIM无废话极简入门](https://www.bilibili.com/video/BV1qg4y13766/?spm_id_from=333.880.my_history.page.click&vd_source=2dd00fcea46a9c5a26706a99eb12ea3f)
- [Vim 实用技巧.pdf](https://github.com/Corner430/study-notes/blob/main/book.md#Vim-实用技巧)
- 《精通vim》
- [lazyvim](https://github.com/LazyVim/LazyVim)
- [Vimium](https://github.com/philc/vimium)
- [Vimium-c](https://github.com/gdh1995/vimium-c)

下载最新中文版本的vimtutor：`vim --clean -c 'e $VIMRUNTIME/tutor/tutor.zh_cn.utf-8' -c 'w! TUTORCOPY' -c 'q'`

# 2 模式

## 2.1 普通模式
- `.` 重复上一次修改
- `u` 撤销
- `<C-r>` 重做
| `>` | 增加缩进 |
| `<` | 减少缩进 |
| `=` | 自动缩进 |
- `>G` 增加从当前行到文档末尾处的缩进层级
- `C` 删除当前光标到行尾的字符，并进入插入模式
- `s` 删除当前光标所在字符，并进入插入模式
- `S` 删除当前行，并进入插入模式
- `cc` 清除整行，然后进入插入模式。保持原来的缩进。
- `I` 在行首插入
- `o` 在下一行插入
- `O` 在上一行插入
- `t`或`f` 在行内查找下一指定字符
- `T`或`F` 在行内查找上一指定字符
- `;` 快速跳转到下一个与当前光标位置处的字符匹配的位置的命令。
- `,` 快速跳转到上一个与当前光标位置处的字符匹配的位置的命令。
- `w`或`e`或`b` 逐个广义单词移动
- `{` 或 `}` 逐个段落移动
- `Shift + (` 和 `Shift + )` 分别将光标移动到上一句和下一句的开头。
- `H` 将光标移动到屏幕的顶部。
- `L` 将光标移动到屏幕的底部。
- `0` 或者 `^` 行首
- `dd` 删除一行
- `di` 删除范围内的字符
- `da` 删除范围内的字符(包括范围字符)
- `dw` 删除一个单词
- `db` 回删一个单词
- `d3w` 删除三个单词
- `daw` 删除一个单词
- `dap` 删除一个段落
- `yj` 复制下一行
- `yi` 范围复制
- `ya` 范围复制(包括范围字符)
- `g~` 反转大小写
- `gu` 转换为小写
- `gU` 转换为大写
- `*` 向下查找当前光标所在的单词
- `#` 向上查找当前光标所在的单词
- `&` 重复上一次使用 `:s` 命令执行的替换操作
- `/` 向下查找
- `?` 向上查找
- `<C-a>` += 操作
- `<C-x>` -= 操作
- `zz` 将当前行显示在窗口正中
- `P` 前粘贴
- `<C-g>` 显示当前行号、列号及文件信息
- `<C-w>s` 水平切分当前窗口，新窗口仍显示当前缓冲区
- `<C-w>v` 垂直切分当前窗口，新窗口仍显示当前缓冲区
- `qx{changes}q` 录制宏
- `ga` 查看光标下字符的十进制和十六进制编码


> `<Esc>` 和插入模式中的 `<Up>`、`<Down>`、`<Left>`、`<Right>` 会**产生一个新的撤销块**。

## 2.2 插入模式
- `<C-[>` 退出插入模式
- `<C-o>` 进入到插入-普通模式, eg: `<C-o>zz`
- `<C-h>` 删除前一个字符（同退格键）
- `<C-w>` 删除前一个单词
- `<C-u>` 删至行首
- `<C-r>0` 将刚才复制到的文本粘贴到当前光标位置
- `<C-r>{register}` 其中{register}是想要插入的寄存器
- `<C-r>=` 调用表达式寄存器，例如：`<C-r>=6*8`

## 2.3 可视模式

- `v` 普通可视化
- `V` 行可视化
- `<C-v>` 块可视化，windows 下为 `<C-q>`
- `gv` 重选上次的高亮选区
- `o` 切换高亮选取的活动端
- `vit` 选择标签里的内容。`it` 命令是一种被称为文本对象（text object）的特殊动作命令。
- `~` 反转大小写
- `U` 将所选中的字符转换为大写
- `r` 对选中的区域进行统一修改
- `I` 和 `A` 仍然有效，但 `i` 和 `a` 却有新的约定

## 2.4 命令行模式

- `q/` 打开查找命令历史的命令行窗口
- `q:` 打开命令历史的命令行窗口
- `<C-f>` 从命令行模式切换到命令行窗口
- `:term[inal]` 打开终端
- `:e[dit] {file}` 打开文件
- `:w[rite]` 保存文件
- `:q[uit]` 退出
- `:num` 等同于 `num G`
- `:+num` 向下移动 num 行
- `:-num` 向上移动 num 行
- `:{start},{end}` 可以用行号、位置标记或是查找模式来指定范围的开始位置及结束位置
  - `1` 表示文件的第一行
  - `$` 表示文件的最后一行
  - `0` 表示虚拟行，位于文件第一行上方
  - `.` 表示光标所在行
  - `'m` 表示包含位置标记 m 的行
  - `'<` 表示高亮选取的起始行
  - `'>` 表示高亮选取的结束行
  - `%` 表示整个文件（`:1,$` 的简写形式）
- `<C-d>` 自动弹出命令提示
- `:[range]s[ubstitute]/{pattern}/{string}/[flags]` 对指定范围内出现 `{pattern}` 的地方替换为 `{string}`
- `:[range]d[elete] [x]` 删除指定范围的行
- `:[range]y[ank] [x]` 复制指定范围的行
- `:[range]pu[t] [x]` 粘贴寄存器 x 中的内容
- `:[range]co[py] {address}` 把指定范围内的行拷贝到 {address} 指定的行之下
- `:t {address}` copy to ，把当前行拷贝到 {address} 指定的行之下
- `:[range]m[ove] {address}` 把指定范围内的行移动到 {address} 指定的行之下
- `:m {address}` move to ，把当前行移动到 {address} 指定的行之下
- `:[range]norm[al] {commands}` 对指定范围内的每一行执行普通模式命令 `{commands}`
- `:[range]norm[al] .` **对指定范围内的每一行重复上一次修改**
- `:[range]norm[al] A;` 对指定范围内的每一行在行尾添加分号
- `:[range]j[oin]` 连接指定范围内的行
- `:[range]g[lobal]/{pattern}/[cmd]` 对指定范围内匹配 `{pattern}` 的所有行执行 Ex 命令 `{cmd}`
- `@:` 重复上一次执行的 Ex 命令
- `:!{cmd}` 执行外部命令
- `:!shell` 执行外部 shell
  - 如果是在shell中打开的vim，那么可以使用`<C-z>`挂起vim，之后可以通过 `jobs` 来进行查看，并使用 `fg` 唤醒
- `:read !{cmd}` 把命令的标准输出重定向到缓冲区
- `:write !{cmd}` 把缓冲区的内容重定向到命令的标准输入
  - `:write !sh` 把缓冲区的内容传给 sh 命令作为标准输入
  - `:write ! sh` 同上
  - `:write! sh` 把缓冲区内容写到一个名为 sh 的文件中
- `:ls` 列出缓冲区
- `:bn` 下一个缓冲区
- `:bp` 上一个缓冲区
- `:bf` 第一个缓冲区
- `:bl` 最后一个缓冲区
- `:bd` 删除缓冲区
- `:sp[lit] {file}` 水平切分当前窗口，并在新窗口中载入 {file}
- `:vsp[lit] {file}` 垂直切分当前窗口，并在新窗口中载入 {file}

# 3 文件

## 3.1 管理多个文件

### 3.1.1 用缓冲区列表管理打开的文件

**目录下文件：a.md b.md**

- `vim *.md` 打开 a.md 和 b.md，其中 b.md 在**后台缓冲区**中
  - `:ls` 查看缓冲区
  - `:bnext` 和 `:bprev` 切换缓冲区

### 3.1.2 用参数列表将缓冲区分组

- `:args` 查看参数列表 => [a.md] b.md
- `:args index.html` 将 index.html 添加到参数列表中
- `:args *.*` 将当前目录下的所有符合条件的文件添加到参数列表中，但**不会递归子目录**
- `:agrs **/*.*` 将当前目录下的所有符合条件的文件添加到参数列表中，**会递归子目录**
- `:args \`cat filelist.txt\`` 从文件中读取文件名，添加到参数列表中
- `:argdo %s/foo/bar/g` 对参数列表中的每个文件执行替换操作

### 3.1.3 管理隐藏缓冲区

文件夹下： a.md b.md

通过 `vim *.md` 打开，此时 a.md 是活动文件，对其进行修改，但不保存直接强制性使用 `:bn!` 切换到 b.md，此时通过 `:ls` 查看缓冲区，输入如下：

```shell
1 #h + "a.md"
2 %a   "b.md"
```
- `%` 表示当前活动文件
- `#` 表示轮换文件
- `h` 表示隐藏缓冲区（hidden）
- `+` 表示修改过
- `a` 表示活动缓冲区（active）

> - 此时使用 `:q` 退出时候，vim 会自动把第一个有改动的隐藏缓冲区载入到当前窗口等待处理。
> - `:w[rite]` 把缓冲区内容写入到磁盘
> - `:e[dit]!` 把磁盘文件内容读入缓冲区（即回滚所做修改）
> - `:qa[ll]!` 关闭所有窗口，摒弃修改而无需警告
> - `:wa[ll]!` 把所有改变的缓冲区写入磁盘

### 3.1.4 将工作区切分成窗口

> **窗口是缓冲区的显示区域!**
>   - 可以在多个窗口中显示同一个缓冲区
>   - 也可以在每个窗口里载入不同的缓冲区


- 创建分割窗口
  - `<C-w>s` 水平切分当前窗口，新窗口仍显示当前缓冲区
  - `<C-w>v` 垂直切分当前窗口，新窗口仍显示当前缓冲区
  - `:sp[lit] {file}` 水平切分当前窗口，并在新窗口中载入 `{file}`
  - `:vsp[lit] {file}` 垂直切分当前窗口，并在新窗口中载入 `{file}`
- 在窗口间切换
  - `<C-w>w` 在窗口间循环切换，等价 `<C-w><C-w>`，即按住 Ctrl 不放手，连续按两次 w
  - `<C-w>h` 切换到左边的窗口
  - `<C-w>j` 切换到下边的窗口
  - `<C-w>k` 切换到上边的窗口
  - `<C-w>l` 切换到右边的窗口
- 关闭窗口
  - `<C-w>c` 和 `:clo[se]` 关闭活动窗口
  - `<C-w>o` 和 `:on[ly]` 只保留活动窗口，关闭其他窗口
- 改表窗口大小及重新排列窗口
  - `<C-w>=` 使所有窗口等宽等高
  - `<C-w>_` 最大化活动窗口的高度
  - `<C-w>|` 最大化活动窗口的宽度
  - `[N]<C-w>_` 把活动窗口的高度设为 [N] 行
  - `[N]<C-w>|` 把活动窗口的宽度设为 [N] 列

### 3.1.5 用标签页将窗口分组

> **标签页是可以容纳一系列窗口的容器**

![把窗口组织到标签页里](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240524214512.png)

- 打开及关闭标签页
  - `:tabe[dit] {filename}` 在新标签页打开 {filename}
  - `<C-w>T` 把当前窗口移到一个新标签页
  - `:tabc[lose]` 关闭当前标签页及其中的所有窗口
  - `:tabo[nly]` 只保留活动标签页，关闭所有其他标签页
- 在标签页间切换
  - `:tabn[ext] {N}` 或 `{N}gt` 切换到编号为 {N} 的标签页
  - `:tabn[ext]` 或 `gt` 切换到下一标签页
  - `:tabp[revious]` 或 `gT` 切换到上一标签页
- 重排标签页
  - `:tabm[ove] {N}` 把当前标签页移动到编号为 {N} 的标签页之后

## 3.2 打开及保存文件

- `:pwd` 打印当前工作目录

### 3.2.1 用 :edit 命令打开文件

- `:edit {file}` 可以接受相对于工作目录的文件路径
- `:edit %<Tab>` `%` 代表活动缓冲区的完整文件路径
- `:edit %:h<Tab>` `:h` 修饰符会去除文件名，但保留路径中的其他部分

### 3.2.2 用 :find 打开文件

> `:find` 命令**允许通过文件名打开一个文件，但无需输入该文件的完整路径**。要想利用此功能，首先要配置 `path` 选项。

- `:set path?` 查看当前的 `path` 选项
- `:set path+=**` 添加当前目录到 `path` 选项，递归子目录
- `:set path+=/usr/include` 添加 `/usr/include` 目录到 `path` 选项
- `:find {file}` 通过文件名打开文件
  > 如果**文件名不唯一**，可以使用 `<Tab>` 键来补全


### 3.2.3 使用 netrw 管理文件系统

netrw（Vim 原生的文件管理器） 是 Vim 发行版的标配插件，在 vimrc 中添加如下配置：

```vimrc
set nocompatible
filetype plugin on
```

- 打开文件管理器
  - `:E[xplore]` 打开当前目录
  - `:e[dit] .` 打开当前目录
  - `vim .` 打开当前目录
  - `:e[dit] {path}` 打开指定目录
- 与分割窗口协同工作

### 3.2.4 把文件保存到不存在的目录中

> 如果使用 `:e[dit] {path}` 打开一个不存在的目录，然后保存文件，Vim 会报错 `E212: Can't open file for writing`

**解决方案：**

```shell
:!mkdir -p %:h  # 创建不存在的目录
:w[rite]  # 保存文件
```

### 3.2.5 以超级用户权限保存文件

可以通过 `<C-g>` 查看文件状态为[readonly]只读

**解决方案**

```shell
:w !sudo tee % > /dev/null
[sudo] password for leo: 

W12: Warning: File "/etc/hosts" has changed and the buffer was changed in Vim as well
See ":help W12" for more info.
[O]K, (L)oad File: 
```

- `:w[rite] !{cmd}` 会把缓冲区的内容作为标准输入传给外部命令 `{cmd}`
- `%` 会展开成当前文件的完整路径


# 4 更快地移动及跳转

# 5 寄存器

# 6 模式

# 7 工具


# 8 折叠
- `zo` 打开当前行折叠
- `zc` 关闭当前折叠块
- `za` 打开或关闭当前折叠块
- `zR` 打开所有折叠块
- `zM` 关闭所有折叠块

# 9 自动补全

| 命令 | 补全类型 |
| :--- | :--- |
| `<C-n` | 正向选择补全普通关键字 |
| `<C-p` | 反向选择补全普通关键字 |
| `<C-x><C-n>` | 当前缓冲区关键字 |
| `<C-x><C-i>` | 包含文件关键字 |
| `<C-x><C-]>` | 标签文件关键字 |
| `<C-x><C-k>` | 字典查找 |
| `<C-x><C-l>` | 整行补全 |
| `<C-x><C-f>` | 文件名补全 |
| `<C-x><C-o>` | 全能（Omini）补全 |

# 10 插件
```bash
mkdir -p ~/.vim ~/.vim/autoload ~/.vim/backup ~/.vim/colors ~/.vim/plugged

curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

- [vim-plug](https://github.com/junegunn/vim-plug)
- [als 语法检查](https://github.com/dense-analysis/ale)
- [nerdtree 文件树](https://gihtub.com/preservim/nerdtree)
- [lightline 状态栏](https://github.com/itchyny/lightline.vim)
- [nerdcommenter 代码注释](https://github.com/preservim/nerdcommenter)
- [auto-pairs 自动补全括号](https://github.com/jiangmiao/auto-pairs)
- [seoul256 颜色主题](https://github.com/junegunn/seoul256.vim)
- [indentLine 代码对齐线](https://github.com/Yggdroot/indentLine)
- [surround](https://github.com/tpope/vim-surround)
- [copilot](https://github.com/github/copilot.vim)
- [codeium](https://github.com/Exafunction/codeium.vim)
- [cpp syntax highlight](https://github.com/octol/vim-cpp-enhanced-highlight)
- [clang-format](https://github.com/rhysd/vim-clang-format)
- [LeaderF 模糊搜索](https://github.com/Yggdroot/LeaderF)
- [leetcode](https://github.com/ianding1/leetcode.vim)


# 9 vscode 常用
- `gd` 跳转到定义
- `gq` 格式化代码
- `gb` 在找到的下一个单词上添加另一个光标，该单词与光标下的单词相同。
- `af` visual 模式下选择当前块
- `gh` 相当于将鼠标悬停在光标所在的位置。无需使用鼠标即可轻松查看类型和错误消息！

# 10 Vim 重编译

> 如果 anaconda 的 python 在系统的 PATH 中，那么在编译 vim 时，无法支持 python3

```bash
git clone https://github.com/vim/vim.git

cd vim/src
make distclean

sudo apt install python3-dev libncurses5-dev
./configure --with-features=huge --enable-python3interp --enable-rubyinterp --enable-luainterp --enable-perlinterp --enable-multibyte --enable-cscope

make
sudo make install

// conda
alias conda="~/miniconda3/bin/conda"
alias condapip="~/miniconda3/envs/pytorch/bin/pip"
alias condapip3="~/miniconda3/envs/pytorch/bin/pip3"
alias condapython="~/miniconda3/envs/pytorch/bin/python"
```

# 11 vimrc
[rfc](https://www.freecodecamp.org/news/vimrc-configuration-guide-customize-your-vim-editor/)

```vim

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""               
"               
"               ██╗   ██╗██╗███╗   ███╗██████╗  ██████╗
"               ██║   ██║██║████╗ ████║██╔══██╗██╔════╝
"               ██║   ██║██║██╔████╔██║██████╔╝██║     
"               ╚██╗ ██╔╝██║██║╚██╔╝██║██╔══██╗██║     
"                ╚████╔╝ ██║██║ ╚═╝ ██║██║  ██║╚██████╗
"                 ╚═══╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝
"               
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""               

" Disable compatibility with vi which can cause unexpected issues.
set nocompatible

" Enable the use of backspace key.
set backspace=2

" Set the command line history to 200.
set history=200

" Enable type file detection. Vim will be able to try to detect the type of file in use.
filetype on

" Enable plugins and load plugin for the detected file type.
filetype plugin on

" Load an indent file for the detected file type.
filetype indent on

" Turn syntax highlighting on.
syntax on

" Add numbers to each line on the left-hand side.
set number

" Relative line numbers
set relativenumber

" Highlight cursor line underneath the cursor horizontally.
set cursorline

" Set the horizontal cursor color to light red
highlight CursorLine cterm=NONE ctermbg=lightred ctermfg=black guibg=lightred guifg=black


" Highlight cursor line underneath the cursor vertically.
" set cursorcolumn

" Set the vertical cursor column to light yellow
" highlight CursorColumn cterm=NONE ctermbg=lightyellow ctermfg=black guibg=lightyellow guifg=black


" Switch background color to dark or light.
" set background=dark
" set background=light

" --------------------------------------------------


" Set shift width to 2 spaces.
set shiftwidth=2

" Set tab width to 2 columns.
set tabstop=2

" Use space characters instead of tabs.
set expandtab

" Do not save backup files.
set nobackup

" Do not let cursor scroll below or above N number of lines when scrolling.
set scrolloff=10

" Do not wrap lines. Allow long lines to extend as far as the line goes.
set nowrap

" While searching though a file incrementally highlight matching characters as you type.
set incsearch

" Ignore capital letters during search.
set ignorecase

" Override the ignorecase option if searching for capital letters.
" This will allow you to search specifically for capital letters.
set smartcase

" Show partial command you type in the last line of the screen.
set showcmd

" Show the mode you are on the last line.
set showmode

" Show matching words during a search.
set showmatch

" Use highlighting when doing a search.
set hlsearch

" Set the commands to save in history default number is 20.
set history=1000


" -------------------------------------



" Enable auto completion menu after pressing TAB.
set wildmenu

" Make wildmenu behave like similar to Bash completion.
set wildmode=list:longest

" There are certain files that we would never want to edit with Vim.
" Wildmenu will ignore files with these extensions.
set wildignore=*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xlsx






" PLUGINS ---------------------------------------------------------------- {{{

call plug#begin('~/.vim/plugged')

  " 语法检查
  Plug 'dense-analysis/ale'
  
  " Navigation
  Plug 'preservim/nerdtree'

  " 状态栏
  " Plug 'itchyny/lightline.vim'

  " 代码注释
  Plug 'preservim/nerdcommenter'

  " 自动补全括号
  Plug 'jiangmiao/auto-pairs'

  " 颜色主题
  " Plug 'junegunn/seoul256.vim'

  " 代码对齐线 
  Plug 'Yggdroot/indentLine'

  " sorround
  Plug 'tpope/vim-surround'

  " copilot
  "Plug 'github/copilot.vim'

  " codeium
  Plug 'Exafunction/codeium.vim', { 'branch': 'main' }
  
  " cpp syntax highlight
  Plug 'octol/vim-cpp-enhanced-highlight'

  " clang-format
  Plug 'rhysd/vim-clang-format'

  " 模糊搜索
  Plug 'Yggdroot/LeaderF'

  " leetcode
  "Plug 'ianding1/leetcode.vim'


call plug#end()

" }}}


" MAPPINGS --------------------------------------------------------------- {{{

" Set the "," as the leader key.
let mapleader = "\\"

" Press \\ to jump back to the last cursor position.
nnoremap <leader>\ ``

" Press \p to print the current file to the default printer from a Linux operating system.
" View available printers:   lpstat -v
" Set default printer:       lpoptions -d <printer_name>
" <silent> means do not display output.
"nnoremap <silent> <leader>p :%w !lp<CR>

" Type jj to exit insert mode quickly.
inoremap jj <Esc>

" open terminal on the right side
nnoremap <leader>st :rightbelow vertical terminal<CR>

" write to clipboard
vnoremap <leader>w :w !clip.exe<CR>

" Press the space bar to type the : character in command mode.
nnoremap <space> :

" Press the space bar to type the : character in visual mode.
vnoremap <space> :

" Pressing the letter o will open a new line below the current one.
" Exit insert mode after creating a new line above or below the current line.
"nnoremap o o<esc>
"nnoremap O O<esc>

" Center the cursor vertically when moving to the next word during a search.
nnoremap n nzz
nnoremap N Nzz

" Yank from cursor to the end of line.
nnoremap Y y$

" Map the F5 key to run a Python or C++ script inside Vim.
" I map F5 to a chain of commands here.
" :w saves the file.
" <CR> (carriage return) is like pressing the enter key.
" !clear runs the external clear screen command.
" !python3 % executes the current file with Python.
" nnoremap <f5> :w <CR>:!clear <CR>:!python3 % <CR>
function! ExecuteFile()
    w
    silent !clear

    if &filetype ==# 'cpp'
        execute '!g++ -std=c++11 -g % -o %<'
        execute '!./%<'
    elseif &filetype ==# 'python'
        execute '!python3 %'
    elseif &filetype ==# 'c'
        execute '!gcc -std=c11 -g % -o %<'
        execute '!./%<'
    else
        echo "Unknown file type"
    endif
endfunction
nnoremap <f5> :call ExecuteFile()<CR>


" You can split the window in Vim by typing :split or :vsplit.
" Navigate the split view easier by pressing CTRL+j, CTRL+k, CTRL+h, or CTRL+l.
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-h> <c-w>h
nnoremap <c-l> <c-w>l

" Resize split windows using arrow keys by pressing:
" CTRL+UP, CTRL+DOWN, CTRL+LEFT, or CTRL+RIGHT.
noremap <c-up> <c-w>+
noremap <c-down> <c-w>-
noremap <c-left> <c-w>>
noremap <c-right> <c-w><

" NERDTree specific mappings.
" Map the F3 key to toggle NERDTree open and close.
nnoremap <F3> :NERDTreeToggle<cr>

" Have nerdtree ignore certain files and directories.
let NERDTreeIgnore=['\.git$', '\.jpg$', '\.mp4$', '\.ogg$', '\.iso$', '\.pdf$', '\.pyc$', '\.odt$', '\.png$', '\.gif$', '\.db$']

" }}}


" VIMSCRIPT -------------------------------------------------------------- {{{

" This will enable code folding.
" Use the marker method of folding.
augroup filetype_vim
    autocmd!
    autocmd FileType vim setlocal foldmethod=marker
augroup END

" More Vimscripts code goes here.

" }}}


" STATUS LINE ------------------------------------------------------------ {{{

" Clear status line when vimrc is reloaded.
set statusline=

" Status line left side.
set statusline+=\ %F\ %M\ %Y\ %R\ %{&ff}\ \ %{&fileencoding}

" Use a divider to separate the left side from the right side.
set statusline+=%=

" Status line right side.
set statusline+=\ ascii:\ %b\ hex:\ 0x%B\ row:\ %l\ col:\ %c\ percent:\ %p%%

" Show the status on the second to last line.
set laststatus=2

function! InsertStatuslineColor(mode)
  if a:mode == 'i'
    hi statusline guibg=Cyan ctermfg=6 guifg=Black ctermbg=0
  elseif a:mode == 'r'
    hi statusline guibg=Purple ctermfg=5 guifg=Black ctermbg=0
  else
    hi statusline guibg=DarkRed ctermfg=1 guifg=Black ctermbg=0
  endif
endfunction


au InsertEnter * call InsertStatuslineColor(v:insertmode)
au InsertLeave * hi statusline guibg=DarkGrey ctermfg=8 guifg=White ctermbg=15

" default the statusline to green when entering Vim
hi statusline guibg=DarkGrey ctermfg=8 guifg=White ctermbg=15

" }}}




" -----------nerdcommenter--------------

" Create default mappings
let g:NERDCreateDefaultMappings = 1

" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1

" Use compact syntax for prettified multi-line comments
let g:NERDCompactSexyComs = 1

" Align line-wise comment delimiters flush left instead of following code indentation
let g:NERDDefaultAlign = 'left'

" Set a language to use its alternate delimiters by default
let g:NERDAltDelims_java = 1

" Add your own custom formats or override the defaults
let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }

" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1

" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1

" Enable NERDCommenterToggle to check all selected lines is commented or not
let g:NERDToggleCheckAllLines = 1


" -----------seoul256.vim--------------------------
" Unified color scheme (default: dark)
" colo seoul256

" Light color scheme
" colo seoul256-light


" ----------------LeaderF----------------------------
" Don't display LeaderF help in normal mode
let g:Lf_HideHelp = 1

" Disable caching, regenerate results each time
let g:Lf_UseCache = 0

" Turn off version control tool, disregard version-controlled files
let g:Lf_UseVersionControlTool = 0

" Ignore current buffer's file name, exclude it from search scope
let g:Lf_IgnoreCurrentBufferName = 1

" Set LeaderF window position to popup
let g:Lf_WindowPosition = 'popup'

" Define LeaderF window separators and font
let g:Lf_StlSeparator = { 'left': "\ue0b0", 'right': "\ue0b2", 'font': "DejaVu Sans Mono for Powerline" }

" Disable preview feature, search results won't display preview info
let g:Lf_PreviewResult = {'Function': 0, 'BufTag': 0 }

" Mappings: Define actions for pressing specific keys in LeaderF
" Search for files
let g:Lf_ShortcutF = "<leader>ff"

" Search for buffers
noremap <leader>fb :<C-U><C-R>=printf("Leaderf buffer %s", "")<CR><CR>

" Search for most recently used files
noremap <leader>fm :<C-U><C-R>=printf("Leaderf mru %s", "")<CR><CR>

" Search for tags
noremap <leader>ft :<C-U><C-R>=printf("Leaderf bufTag %s", "")<CR><CR>

" Search for current word in current buffer
noremap <C-B> :<C-U><C-R>=printf("Leaderf! rg --current-buffer -e %s ", expand("<cword>"))<CR>

" Search for current word globally
noremap <C-F> :<C-U><C-R>=printf("Leaderf! rg -e %s ", expand("<cword>"))<CR>

" Search for visually selected text
xnoremap gf :<C-U><C-R>=printf("Leaderf! rg -F -e %s ", leaderf#Rg#visual())<CR>

" Use LeaderF to search recall history
noremap go :<C-U>Leaderf! rg --recall<CR>

" Operations related to gtags
" Must execute `Leaderf gtags --update` first
let g:Lf_GtagsAutoGenerate = 0
let g:Lf_Gtagslabel = 'native-pygments'

" Search for references
noremap <leader>fr :<C-U><C-R>=printf("Leaderf! gtags -r %s --auto-jump", expand("<cword>"))<CR><CR>

" Search for definitions
noremap <leader>fd :<C-U><C-R>=printf("Leaderf! gtags -d %s --auto-jump", expand("<cword>"))<CR><CR>

" Search recall history
noremap <leader>fo :<C-U><C-R>=printf("Leaderf! gtags --recall %s", "")<CR><CR>

" Show next gtags search result
noremap <leader>fn :<C-U><C-R>=printf("Leaderf gtags --next %s", "")<CR><CR>

" Show previous gtags search result
noremap <leader>fp :<C-U><C-R>=printf("Leaderf gtags --previous %s", "")<CR><CR>

" ----------------------clang-format-------------------------------------

let g:clang_format#style_options = {
            \ "AccessModifierOffset" : -4,
            \ "AllowShortIfStatementsOnASingleLine" : "true",
            \ "AlwaysBreakTemplateDeclarations" : "true",
            \ "Standard" : "C++11"}

" map to <Leader>cf in C++ code
autocmd FileType c,cpp,objc nnoremap <buffer><Leader>cf :<C-u>ClangFormat<CR>
autocmd FileType c,cpp,objc vnoremap <buffer><Leader>cf :ClangFormat<CR>
" if you install vim-operator-user
autocmd FileType c,cpp,objc map <buffer><Leader>x <Plug>(operator-clang-format)
" Toggle auto formatting:
nmap <Leader>C :ClangFormatAutoToggle<CR>

" ------------------------ale--------------------------------------------
" Disable ALE highlights
let g:ale_set_highlights = 0

" Define error and warning signs
let g:ale_sign_error = '✗'
let g:ale_sign_warning = '⚡'

" Define the sign column width
" let g:ale_statusline_format = ['✗ %d', '⚡ %d', '✔ OK']
let g:ale_statusline_format = '✗ %d ⚡ %d ✔ OK'

" Show ALE status in the status line
set statusline+=\ %{g:ale_statusline_format}

" Display Linter name, error or warning, etc.
let g:ale_echo_msg_error_str = 'E'
let g:ale_echo_msg_warning_str = 'W'
let g:ale_echo_msg_format = '[%linter%] %s [%severity%]'

" Disable linting on file open
let g:ale_lint_on_enter = 0

" Normal mode mappings, \[s to go to the previous error or warning, \]s to go to the next error or warning
" Consistent with vim's default spell checker
nmap <Leader>[s <Plug>(ale_previous_wrap)
nmap <Leader>]s <Plug>(ale_next_wrap)

" \s to toggle ALE
nmap <Leader>s :ALEToggle<CR>

" \d to view the detailed information of the error or warning
nmap <Leader>d :ALEDetail<CR>

" Set the linters for each file type.
let g:ale_linters = {
\   'c++': ['clang'],
\   'c': ['clang'],
\   'python': ['pylint'],
\}

" Set the fixers for each file type, including more comprehensive options:
let g:ale_fixers = {
  \ 'c++': ['clang-format', 'clangtidy', 'uncrustify'],
  \ 'c': ['clang-format', 'uncrustify'],              
  \ 'python': ['autopep8', 'yapf'],                  
  \ '*': ['remove_trailing_lines', 'trim_whitespace'],       
  \}

" -----------------------lightline-----------------------------
" delete the status line
"set noshowmode

" let g:lightline = {
"       \ 'colorscheme': 'one',
"       \ }

" -----------------------codeium-----------------------------
" Enable Codeium
let g:codeium_enabled = v:true

" Disable default key bindings
let g:codeium_disable_bindings = 1

" Show it in status line
set statusline+=\ \ %3{codeium#GetStatusString()}

" Manually trigger suggestion
imap <C-]>   <Cmd>call codeium#Complete()<CR>

" Insert suggestion
imap <script><silent><nowait><expr> <C-g> codeium#Accept()

" Next suggestion (Consistent with vim default autocomplete)
imap <leader><C-n>   <Cmd>call codeium#CycleCompletions(1)<CR>

" Previous suggestion (Consistent with vim default autocomplete)
imap <leader><C-p>   <Cmd>call codeium#CycleCompletions(-1)<CR>

" Clear current suggestion
imap <C-x>   <Cmd>call codeium#Clear()<CR>

" let g:codeium_filetypes = {
"     \ "C++": v:false,
"     \ }

" Enable search and indexing in the current project
let g:codeium_workspace_root_hints = ['.bzr','.git','.hg','.svn','_FOSSIL_','package.json']

" Launch Codeium Chat in a new browser window
" imap <C-c>   <Cmd>call codeium#Chat()<CR>
```
