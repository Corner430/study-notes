- [1 教程](#1-教程)
- [2 常用命令](#2-常用命令)
  - [2.1 插入模式](#21-插入模式)
  - [2.2 可视模式](#22-可视模式)
  - [2.3 命令行模式](#23-命令行模式)
- [3 一箭双雕](#3-一箭双雕)
- [4 操作符 + 动作命令 = 操作](#4-操作符--动作命令--操作)
- [5 Vim 的一些使用技巧](#5-vim-的一些使用技巧)
- [6 折叠](#6-折叠)
- [7 自动补全](#7-自动补全)
- [8 插件](#8-插件)
- [9 搜索](#9-搜索)
- [10 寄存器](#10-寄存器)
  - [10.1 从外部复制文本到vim中](#101-从外部复制文本到vim中)
- [11 非常用技巧](#11-非常用技巧)
- [12 vscode 常用](#12-vscode-常用)
- [13 Vim 重编译](#13-vim-重编译)
- [14 vimrc](#14-vimrc)


## 1 教程

- [Vimtutor_1.5](http://www2.geog.ucl.ac.uk/~plewis/teaching/unix/vimtutor)
- [vimtutor](https://vimhelp.org/usr_01.txt.html#vimtutor)：有一些书籍进行推荐，还有电子版
- [VIM无废话极简入门](https://www.bilibili.com/video/BV1qg4y13766/?spm_id_from=333.880.my_history.page.click&vd_source=2dd00fcea46a9c5a26706a99eb12ea3f)
- [Vim 实用技巧.pdf](https://github.com/Corner430/study-notes/blob/main/book.md#Vim-实用技巧)
- 《精通vim》
- [lazyvim](https://github.com/LazyVim/LazyVim)
- [Vimium](https://github.com/philc/vimium)
- [Vimium-c](https://github.com/gdh1995/vimium-c)

下载最新中文版本的vimtutor：`vim --clean -c 'e $VIMRUNTIME/tutor/tutor.zh_cn.utf-8' -c 'w! TUTORCOPY' -c 'q'`

## 2 常用命令

- `W`或`E`或`B` 逐个广义单词移动
- `{` 或 `}` 逐个段落移动
- `b` 回退
- `0` 或者 `^` 行首
- `t`或`f` 在行内查找下一指定字符
- `T`或`F` 在行内查找上一指定字符
- `di` 删除范围内的字符
- `da` 删除范围内的字符(包括范围字符)
- `daw` 删除一个单词
- `dap` 删除一个段落
- `zz` 将当前行显示在窗口正中
- `:num` 等同于 `num G`
- `:+num` 向下移动 num 行
- `:-num` 向上移动 num 行
- `#` 在当前光标所在单词上按`#`，进入查找该单词状态
- `:%s/old/new` 全局替换
- `:34s/old/new` 替换第34行的字符
- `:34,40s/old/new` 替换第34到40行的字符
- `:10,20/your_search_term` 在第10到20行搜索
- `/hel.\{1,3\}` 正则表达式搜索
    - `hel`：匹配字母 "hel" 作为开头。
    - `.`：匹配除换行符外的任意字符。
    - `\{1,3\}`：表示前一个字符或子表达式的重复次数范围。这里指定了 1 到 3 次重复，表示匹配一个到三个任意字符。
- `yj` 复制下一行
- `yi` 范围复制
- `ya` 范围复制(包括范围字符)
- `P` 前粘贴
- `v` 普通可视化
- `V` 行可视化
- `Ctrl + v` (矩形)块可视化
- `Ctrl + G` 显示当前行号、列号及文件信息
- `Ctrl + a` 增加数字，例如：`10<C-a>` 将数字增加 10。**如果当前光标所在位置不是数字，那么会在当前行正向查找一个数字，然后增加。**
- `Ctrl + x` 减少数字，同上。**Vim 把以 0 开头的数字当作八进制处理。可以通过 `set nrformats=` 来进行设置。**
- `;` 快速跳转到下一个与当前光标位置处的字符匹配的位置的命令。
- `,` 快速跳转到上一个与当前光标位置处的字符匹配的位置的命令。
- `^` 越过缩进至第一个非空白字符
- `/` 向下查找
- `?` 向上查找
- `&` 重复上一次使用 `:s` 命令执行的替换操作
- `qx{changes}q` 录制宏
- `*` 在当前光标所在单词上按`*`，进入查找该单词状态。**并且会高亮显示所有匹配的单词，如果没有高亮，可以使用`:set hls`命令开启高亮显示。**
- `cc` 清除整行，然后进入插入模式。保持原来的缩进。
- `Shift + (` 和 `Shift + )` 分别将光标移动到上一句和下一句的开头。
- `H` 将光标移动到屏幕的顶部。
- `L` 将光标移动到屏幕的底部。
- `:term[inal]` 打开终端
- `ga` 查看光标下字符的十进制和十六进制编码

### 2.1 插入模式
- `<C-h>` 删除前一个字符（同退格键）
- `<C-w>` 删除前一个单词
- `<C-u>` 删至行首
- `<C-r>0` 将刚才复制到的文本粘贴到当前光标位置
- `<C-r>{register}` 其中{register}是想要插入的寄存器
- `<C-r>=` 调用表达式寄存器，例如：`<C-r>=6*8`


> 这些命令并非插入模式独有，在Vim的命令行模式中，以及在 bash shell 中，也可以使用它们。

- `<Esc>` 切换到普通模式
- `<C-[>` 切换到普通模式
- `<C-o>` 切换到 **插入 - 普通** 模式，可以执行一条普通模式命令，之后自动进入到插入模式
高频 `<C-o>zz`


### 2.2 可视模式

- 可以在不同风格的可视模式间切换
- `I` 和 `A` 仍然有效，但 `i` 和 `a` 却有新的约定
- `.` 在面向行可视时可以正常工作，但面向字符时却可能不尽如意
- `gv` 重选上次的高亮选区
- `o` 切换高亮选取的活动端
- `vit` 选择标签里的内容。`it` 命令是一种被称为文本对象（text object）的特殊动作命令。
- `U` 将所选中的字符转换为大写
- `r` 对选中的区域进行统一修改
- `<C-q>` windows下的 `<C-v>` 被占用，列选

### 2.3 命令行模式

- `<C-d>` 自动弹出命令提示

| 命令 | 用途 |
| :--- | :--- |
| `:[range]delete [x]` | 删除指定范围的行[到寄存器 x 中] |
| `:[range]yank [x]` | 复制指定范围的行[到寄存器 x 中] |
| `:[line]put [x]` | 在指定行后粘贴寄存器 x 中的内容 |
| `:[range]copy {address}` | 把指定范围内的行拷贝到 {address} 指定的行之下|
| `:[range]move {address}` | 把指定范围内的行移动到 {address} 指定的行之下|
| `:[range]join` | 连接指定范围内的行 |
| `:[range]normal {commands}` | 对指定范围内的每一行执行普通模式命令 {commands} |
| `:[range]substitute/{pattern}/{string}/[flags]` | 对指定范围内出现 {pattern} 的地方替换为 {string} |
| `:[range]global/{pattern}/[cmd]` | 对指定范围内匹配 {pattern} 的所有行执行 Ex 命令 {cmd} |

- `:{start},{end}` 可以用行号、位置标记或是查找模式来指定范围的开始位置及结束位置

| 符号 | 地址 |
| `1` | 文件的第一行 |
| `$` | 文件的最后一行 |
| `0` | 虚拟行，位于文件第一行上方 |
| `.` | 光标所在行 |
| `'m` | 包含位置标记 m 的行 |
| `'<` | 高亮选取的起始行 |
| `'>` | 高亮选取的结束行 |
| `%` | 整个文件（`:1,$` 的简写形式） |

## 3 一箭双雕

- `>G` 增加从当前行到文档末尾处的缩进层级
- `.` 重复上一次修改

一箭双雕
| 复合命令 | 等效的长命令 |
| :--- | :---: |
| C | c$ |
| s | cl |
| S | ^C |
| I | ^i |
| o | A<CR> |
| O | ko |
> 这些命令的共同点：都会从普通模式切换到插入模式，这将会对`.`命令产生影响。

## 4 操作符 + 动作命令 = 操作

此处相当精彩，参见 技巧 12 双剑合璧，天下无敌

例如知道 `daw` 删除一个单词，那么 `gUaw` 就可以把当前单词转换成大写形式，这就是所谓 `d{motion}`

| 命令 | 用途 |
| :--- | :---: |
| `c` | 修改 |
| `d` | 删除 |
| `y` | 复制 |
| `g~` | 反转大小写 |
| `gu` | 转换为小写 |
| `gU` | 转换为大写 |
| `>` | 增加缩进 |
| `<` | 减少缩进 |
| `=` | 自动缩进 |
| `!` | 运行外部过滤器过滤{motion}所跨越的行 |

## 5 Vim 的一些使用技巧

- `.` 命令是一个微型的宏，Vim可以录制任意数目的按键操作，然后在以后重复执行它们。这让我们可以把最常重复的工作流程录制下来，并用一个按键重放它们。

- 控制好对 `<Esc>` 键的使用，就可以 `u` 控制撤销的粒度。**如果再插入模式中使用了 `<Up>`、`<Down>`、`<Left>`、`<Right>` 这些光标键，将会产生一个新的撤销块。等同于先切换到了普通模式，然后用 `h`、`j`、`k`、`l` 移动光标。**

- 如果必要，应使用次数，例如：`c3w`、`b3w`。

- 当一个操作符命令被连续调用两次时，它会作用于当前行，例如：`dd`，`>>`

## 6 折叠
- `zo` 打开当前行折叠
- `zc` 关闭当前折叠块
- `za` 打开或关闭当前折叠块
- `zR` 打开所有折叠块
- `zM` 关闭所有折叠块

## 7 自动补全

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

## 8 插件
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

## 9 搜索
- `:grep` 和 `:vimgrep`
- `ack`

## 10 寄存器
- 默认寄存器：`""`，存储最近的复制和剪切操作的文本，使用 `y` 复制和 `d` 剪切，然后使用 `p` 粘贴。
- 命名寄存器：由大写字母和数字标识，如 `"a` 或 `"1`，用于存储和检索特定文本。例如，`"ayw` 复制单词到 `"a` 寄存器，然后使用 `"ap` 粘贴。
- 黑洞寄存器：`"_`，用于丢弃文本，特别适用于删除文本但不保存在其他寄存器中。
- 操作寄存器：使用 `"` 后跟寄存器标识符来选择要使用的寄存器，例如 `"a` 表示使用 `"a` 寄存器。
- 查看寄存器内容：使用 `:reg` 命令，如 `:reg a` 查看 `"a` 寄存器的内容。

### 10.1 从外部复制文本到vim中
```vim
set clipboard=unamed                " 复制到系统寄存器(*)
set clipboard=unnamedplus           " 复制到系统寄存器(+)
set clipboard=unnamed,unnamedplus   " 复制到系统寄存器(*, +)
```

## 11 非常用技巧
- `<C-v>{code}` 在**插入**模式下根据字符编码插入字符，例如：`<C-v>065`
- `<C-v>u{code}` 插入 Unicode，例如：`<C-v>u20bf`

| 按键操作 | 用途 |
| :-- | :-- |
| `<C-v>{123}` | 以十进制字符编码插入字符 |
| `<C-v>u{1234}` | 以十六进制字符编码插入字符 |
| `<C-v>{nodigit}` | 按原义插入非数字字符 |
| `<C-k>{char1}{char2}` | 插入以二合字母 {char1}{char2}表示的字符 |

针对 tabstop 的值，Vim 还有另外一种替换模式，称为虚拟替换模式：`gR`, `gr`

- `<C-g>` 在可视模式和选择模式之间切换

## 12 vscode 常用
- `gd` 跳转到定义
- `gq` 格式化代码
- `gb` 在找到的下一个单词上添加另一个光标，该单词与光标下的单词相同。
- `af` visual 模式下选择当前块
- `gh` 相当于将鼠标悬停在光标所在的位置。无需使用鼠标即可轻松查看类型和错误消息！

## 13 Vim 重编译

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

## 14 vimrc
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
