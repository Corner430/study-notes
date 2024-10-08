- [Linux 就该这么学.pdf](https://github.com/Corner430/study-notes/blob/main/book.md#linux-就该这么学)


- [第 1 章 部署虚拟环境安装 Linux 系统](#第-1-章-部署虚拟环境安装-linux-系统)
  - [1.1 - 1.4 安装 RHEL 7](#11---14-安装-rhel-7)
  - [1.5 RPM（红帽软件包管理器）](#15-rpm红帽软件包管理器)
  - [1.6 Yum 软件仓库](#16-yum-软件仓库)
  - [1.7 systemd 初始化进程](#17-systemd-初始化进程)
    - [1.7.1 SysV init 和 systemd](#171-sysv-init-和-systemd)
    - [1.7.2 systemd 的基本用法](#172-systemd-的基本用法)
    - [1.7.3 自定义 systemd 服务](#173-自定义-systemd-服务)
    - [1.7.4 systemd 配置文件目录](#174-systemd-配置文件目录)
- [第 2 章 新手必须掌握的 Linux 命令](#第-2-章-新手必须掌握的-linux-命令)
  - [2.1 系统信息与状态](#21-系统信息与状态)
  - [2.2 文件与目录操作](#22-文件与目录操作)
  - [2.3 磁盘管理](#23-磁盘管理)
  - [2.4 用户与权限管理](#24-用户与权限管理)
  - [2.5 网络与通信](#25-网络与通信)
  - [2.6 进程与任务管理](#26-进程与任务管理)
  - [2.7 数据处理与编程](#27-数据处理与编程)
  - [2.8 用户切换与权限提升](#28-用户切换与权限提升)
  - [2.9 环境变量与 shell 操作](#29-环境变量与-shell-操作)
  - [2.10 其他](#210-其他)
- [第 3 章 管道符、重定向与环境变量](#第-3-章-管道符重定向与环境变量)
  - [3.1 5 种重定向技术](#31-5-种重定向技术)
  - [3.2 管道符与通配符](#32-管道符与通配符)
  - [3.3 环境变量](#33-环境变量)
    - [3.3.1 系统环境变量和用户环境变量](#331-系统环境变量和用户环境变量)
    - [3.3.2 环境变量的设置和使用](#332-环境变量的设置和使用)
- [第 4 章 Vim 编辑器与 Shell 命令脚本](#第-4-章-vim-编辑器与-shell-命令脚本)
  - [4.1 Vim 编辑器](#41-vim-编辑器)
  - [4.2 Shell 脚本](#42-shell-脚本)
    - [4.2.1 shell 脚本的编写步骤](#421-shell-脚本的编写步骤)
    - [4.2.2 shell 脚本接收用户参数](#422-shell-脚本接收用户参数)
    - [4.2.3 shell 中的条件表达式](#423-shell-中的条件表达式)
    - [4.2.4 流程控制语句之 if 语句](#424-流程控制语句之-if-语句)
    - [4.2.5 流程控制语句之 for 语句](#425-流程控制语句之-for-语句)
    - [4.2.6 流程控制语句之 while 语句](#426-流程控制语句之-while-语句)
    - [4.2.7 流程控制语句之 case 语句](#427-流程控制语句之-case-语句)
  - [4.3 计划任务服务程序](#43-计划任务服务程序)
  - [4.4 nologin 帐户](#44-nologin-帐户)
    - [4.4.1 nologin 帐户介绍](#441-nologin-帐户介绍)
    - [4.4.2 设置 nologin 帐户](#442-设置-nologin-帐户)
- [第 5 章 用户身份与文件权限](#第-5-章-用户身份与文件权限)
  - [5.1 用户身份 UID](#51-用户身份-uid)
  - [5.2 用户组 GID](#52-用户组-gid)
  - [5.3 文件权限与归属](#53-文件权限与归属)
    - [5.3.1 chmod 的细节](#531-chmod-的细节)
  - [5.4 文件的特殊权限](#54-文件的特殊权限)
  - [5.5 文件的隐藏属性](#55-文件的隐藏属性)
  - [5.6 su 和 sudo 命令](#56-su-和-sudo-命令)
    - [5.6.1 visudo](#561-visudo)
    - [5.6.2 修改用户](#562-修改用户)
- [第 6 章 存储结构与磁盘划分](#第-6-章-存储结构与磁盘划分)
  - [6.1 文件系统层次化标准（FHS, Filesystem Hierarchy Standard）](#61-文件系统层次化标准fhs-filesystem-hierarchy-standard)
  - [6.2 硬件设备文件名称](#62-硬件设备文件名称)
  - [6.3 磁盘分区](#63-磁盘分区)
    - [6.3.1 主分区、扩展分区和逻辑分区](#631-主分区扩展分区和逻辑分区)
      - [6.3.1.1 主分区](#6311-主分区)
      - [6.3.1.2 扩展分区](#6312-扩展分区)
      - [6.3.1.3 逻辑分区](#6313-逻辑分区)
    - [6.3.2 挂载、分区、格式化](#632-挂载分区格式化)
      - [6.3.2.1 挂载](#6321-挂载)
      - [6.3.2.2 分区](#6322-分区)
      - [6.3.2.3 格式化](#6323-格式化)
      - [6.3.2.4 交换分区](#6324-交换分区)
  - [6.4 磁盘配额](#64-磁盘配额)
  - [6.5 软硬方法链接](#65-软硬方法链接)
- [第 7 章 使用 RAID 与 LVM 磁盘阵列技术](#第-7-章-使用-raid-与-lvm-磁盘阵列技术)
  - [7.1 RAID](#71-raid)
    - [7.1.1 RAID 的概念与作用](#711-raid-的概念与作用)
    - [7.1.2 RAID 级别](#712-raid-级别)
    - [7.1.3 部署 RAID](#713-部署-raid)
    - [7.1.4 磁盘阵列 + 备份盘](#714-磁盘阵列--备份盘)
  - [7.2 LVM](#72-lvm)
    - [7.2.1 LVM 的概念与作用](#721-lvm-的概念与作用)
    - [7.2.2 常用的 LVM 命令](#722-常用的-lvm-命令)
- [第 8 章 iptables 与 firewalld 防火墙](#第-8-章-iptables-与-firewalld-防火墙)
  - [8.1 防火墙执行方式](#81-防火墙执行方式)
    - [8.1.1 iptables](#811-iptables)
      - [8.1.1.1 数据包处理位置](#8111-数据包处理位置)
      - [8.1.1.2 数据包处理方式](#8112-数据包处理方式)
      - [8.1.1.3 iptables 常用命令](#8113-iptables-常用命令)
    - [8.1.2 firewalld](#812-firewalld)
      - [8.1.2.1 firewalld](#8121-firewalld)
      - [8.1.2.2 firewalld-cmd](#8122-firewalld-cmd)
      - [8.1.2.3 使用Firewalld](#8123-使用firewalld)
- [第 9 章 使用 ssh 服务管理远程主机](#第-9-章-使用-ssh-服务管理远程主机)
  - [9.1 绑定两块网卡](#91-绑定两块网卡)
  - [9.2 配置 sshd 服务](#92-配置-sshd-服务)
  - [9.3 远程传输命令](#93-远程传输命令)
  - [9.4 不间断会话服务](#94-不间断会话服务)
- [第 10 章 使用 Apache 服务部署静态网站](#第-10-章-使用-apache-服务部署静态网站)
- [第 11 章 使用 vsftpd 服务传输文件](#第-11-章-使用-vsftpd-服务传输文件)
  - [11.1 FTP 服务](#111-ftp-服务)
  - [11.2 vsftpd（very secure ftp daemon，非常安全的FTP守护进程）](#112-vsftpdvery-secure-ftp-daemon非常安全的ftp守护进程)
- [第 12 章 使用 Samba 或 NFS 实现文件共享](#第-12-章-使用-samba-或-nfs-实现文件共享)
  - [12.1 Samba 介绍](#121-samba-介绍)
  - [12.2 安装与使用 Samba](#122-安装与使用-samba)
  - [12.3 NFS 介绍](#123-nfs-介绍)
  - [12.4 autofs 自动挂载服务](#124-autofs-自动挂载服务)
- [第 13 章 使用 BIND 提供域名解析服务](#第-13-章-使用-bind-提供域名解析服务)
  - [13.1 DNS 服务基本常识](#131-dns-服务基本常识)
  - [13.2 三种 DNS 服务器](#132-三种-dns-服务器)
  - [13.3 BIND 服务程序](#133-bind-服务程序)
    - [13.3.1 部署 BIND 服务程序](#1331-部署-bind-服务程序)
- [第 14 章 使用 DHCP 动态管理主机地址](#第-14-章-使用-dhcp-动态管理主机地址)
- [第 15 章 使用 Postifx 与 Dovecot 部署邮件系统](#第-15-章-使用-postifx-与-dovecot-部署邮件系统)
- [第 16 章 使用 Squid 部署代理缓存服务](#第-16-章-使用-squid-部署代理缓存服务)
  - [16.1 Squid 服务程序](#161-squid-服务程序)
  - [16.2 ACL （访问控制列表）](#162-acl-访问控制列表)
- [第 17 章 使用 ISCSI 服务部署网络存储](#第-17-章-使用-iscsi-服务部署网络存储)
- [第 18 章 使用 MariaDB 数据库管理系统](#第-18-章-使用-mariadb-数据库管理系统)
- [第 19 章 使用 PXE + Kickstart 无人值守安装服务](#第-19-章-使用-pxe--kickstart-无人值守安装服务)
- [第 20 章 使用 LNMP 架构部署动态网站环境](#第-20-章-使用-lnmp-架构部署动态网站环境)

# 第 1 章 部署虚拟环境安装 Linux 系统

## 1.1 - 1.4 安装 RHEL 7
设备主机名存储在 `/etc/hostname` 中

## 1.5 RPM（红帽软件包管理器）

RPM (Red Hat Package Manager)常用命令：

- 安装软件包：`rpm -i package.rpm`
- 升级软件包：`rpm -U package.rpm`
- 列出已安装的软件包：`rpm -q package-name`
- 查看软件包信息：`rpm -qi package-name`
- 卸载软件包：`rpm -e package-name`

## 1.6 Yum 软件仓库

Yum (Yellowdog Updater, Modified)能够管理 RPM 软件包及其依赖关系

- 搜索可用软件包：`yum search package-name`
- 安装软件包：`yum install package-name`
- 升级软件包：`yum update`
- 列出已安装的软件包：`yum list installed`
- 查看软件包信息：`yum info package-name`
- 卸载软件包：`yum remove package-name`
- 清理缓存：`yum clean all`

## 1.7 systemd 初始化进程

### 1.7.1 SysV init 和 systemd

System V init(SysV init) 和 systemd都是用于初始化Linux操作系统的系统初始化系统

- 初始化脚本和启动过程：
    - SysV init：在SysV init系统中，启动和停止系统服务需要使用各种以"rc"开头的脚本（例如r`c.d/rc0.d、rc1.d、rc2.d`等）。每个**运行级别（runlevel）**都有对应的目录
    - systemd：引入了**单元（unit）**的概念，每个服务都由一个单元文件（`.service`）来定义，这些单元文件存储在`/usr/lib/systemd/system/`和`/etc/systemd/system/`
- 启动速度：
  - SysV init：顺序启动，等待
  - systemd：根据有无依赖关系并行启动
- 基础功能：
  - SysV init：功能有限
  - systemd：不仅可以管理系统服务，还可以处理设备挂载、用户登录会话等
- 日志管理：
  - SysV init：依赖于Syslog守护进程，而Syslog本身可能需要额外的配置和管理。
  - systemd：采用日志管理工具"journalctl"，可以直接查看和管理系统日志

### 1.7.2 systemd 的基本用法

- 重新加载 systemd 配置：`systemctl daemon-reload`
- 启动一个系统单元（服务）：`systemctl start <unit>`
- 停止一个系统单元（服务）：`systemctl stop <unit>`
- 重启一个系统单元（服务）：`systemctl restart <unit>`
- 显示一个系统单元（服务）的状态：`systemctl status <unit>`
- 设置一个系统单元（服务）开机自启：`systemctl enable <unit>`
- 禁止一个系统单元（服务）开机自启：`systemctl disable <unit>`
- 屏蔽一个系统单元（服务）以防止其启动：`systemctl mask <unit>`
- 取消屏蔽一个系统单元（服务）：`systemctl unmask <unit>`
- 列出当前加载的所有系统单元（服务）：`systemctl list-units --type=service`
- 查看系统日志：`journalctl -u apache2`
- 设置一个定时器单元开机自启：`systemctl enable backup.timer`
- 启动一个定时器单元：`systemctl start backup.timer`
- 配置系统时间和日期：`timedatectl set-time "2023-08-12 10:00:00"`
- 配置主机名和相关设置：`hostnamectl set-hostname myserver`

### 1.7.3 自定义 systemd 服务

1. 编写服务配置文件：`vim /etc/systemd/system/my-service.service`

   ```ini
   [Unit]
   Description=My Custom Service
   After=network.target

   [Service]
   ExecStart=/path/to/your/script_or_program
   Restart=always

   [Install]
   WantedBy=default.target
   ```

2. 使用 [1.7.2 systemd 的基本用法](#172-systemd-的基本用法) 来正常管理即可

### 1.7.4 systemd 配置文件目录

- `/usr/lib/systemd/system/` 包含由软件包提供的预定义服务配置文件。
- `/etc/systemd/system/` 包含本地管理员或用户自定义的服务配置文件，并覆盖`/usr/lib/systemd/system/`中的同名文件。

# 第 2 章 新手必须掌握的 Linux 命令

## 2.1 系统信息与状态

- [echo: 输出指定的字符串或者变量](https://wangchujiang.com/linux-command/c/echo.html)
- [date: 显示或设置系统时间与日期](https://wangchujiang.com/linux-command/c/date.html)
- [uptime: 查看Linux系统负载信息](https://wangchujiang.com/linux-command/c/uptime.html)
- [uname: 打印系统信息](https://wangchujiang.com/linux-command/c/uname.html)
- [free -h: 显示内存的使用情况](https://wangchujiang.com/linux-command/c/free.html)
- [who: 显示当前所有登陆用户的信息](https://wangchujiang.com/linux-command/c/who.html)
- [last: 列出目前与过去登入系统的用户相关信息](https://wangchujiang.com/linux-command/c/last.html)
- [env: 显示系统中已存在的环境变量](https://wangchujiang.com/linux-command/c/env.html)
- [history: 显示或操作历史列表](https://wangchujiang.com/linux-command/c/history.html)，例如`!数字`
- [getent: 获取指定的数据库信息](https://wangchujiang.com/linux-command/c/getent.html)

## 2.2 文件与目录操作

- [pwd: 显示当前工作目录的绝对路径](https://wangchujiang.com/linux-command/c/pwd.html)
- [cd: 切换用户当前工作目录](https://wangchujiang.com/linux-command/c/cd.html)
- [ls: 显示目录内容列表](https://wangchujiang.com/linux-command/c/ls.html)
- [cat: 连接多个文件并打印到标准输出（适用于内容较少的）](https://wangchujiang.com/linux-command/c/cat.html)，例如`cat -n`
- [more: 显示文件内容，每次显示一屏（适用于内容较多的）](https://wangchujiang.com/linux-command/c/more.html)
- [head: 显示文件的开头部分](https://wangchujiang.com/linux-command/c/head.html)
- [tail: 在屏幕上显示指定文件的末尾若干行](https://wangchujiang.com/linux-command/c/head.html)，例如`tail -f`实时显示最新追加的内容
- [tr: 将字符进行替换压缩和删除](https://wangchujiang.com/linux-command/c/tr.html)
- [wc: 统计文件的字节数、字数、行数](https://wangchujiang.com/linux-command/c/wc.html)
- [diff: 比较给定的两个文件的不同](https://wangchujiang.com/linux-command/c/diff.html)
- [touch: 创建新的空文件](https://wangchujiang.com/linux-command/c/touch.html)，可以用来更新文件的时间标签
- [mkdir: 用来创建目录，可以递归的建立层级目录](https://wangchujiang.com/linux-command/c/mkdir.html)
- [cp: 将源文件或目录复制到目标文件或目录中](https://wangchujiang.com/linux-command/c/cp.html)
- [mv: 用来对文件或目录重新命名](https://wangchujiang.com/linux-command/c/mv.html)
- [rm: 用于删除给定的文件或目录](https://wangchujiang.com/linux-command/c/rm.html)
- [file: 用来探测给定文件的类型](https://wangchujiang.com/linux-command/c/file.html)
- [tar: 将许多文件一起保存至一个单独的磁带或磁盘归档，并能从归档中单独还原所需文件](https://wangchujiang.com/linux-command/c/tar.html)
- [grep: 强大的文本搜索工具](https://wangchujiang.com/linux-command/c/grep.html)，例如`-v`
- [find: 在指定目录下查找文件](https://wangchujiang.com/linux-command/c/find.html)
- [stat: 用于显示文件的状态信息](https://wangchujiang.com/linux-command/c/stat.html)
- [cut: 连接文件并打印到标准输出设备上](https://wangchujiang.com/linux-command/c/cut.html)
- [dd: 复制文件并对源文件的内容进行转换或格式化处理](https://wangchujiang.com/linux-command/c/dd.html)

## 2.3 磁盘管理

- [mount: 用于挂载Linux系统外的文件](https://wangchujiang.com/linux-command/c/mount.html)
- [umount: 用于卸载已经加载的文件系统](https://wangchujiang.com/linux-command/c/umount.html)
- [fdisk: 查看磁盘使用情况和磁盘分区](https://wangchujiang.com/linux-command/c/fdisk.html)
- [file: 用来探测给定文件的类型](https://wangchujiang.com/linux-command/c/file.html)
- [partprobe: 不重启的情况下重读分区](https://wangchujiang.com/linux-command/c/partprobe.html)
- [mkfs: 用于在设备上创建Linux文件系统](https://wangchujiang.com/linux-command/c/mkfs.html)
- [df: 显示磁盘的相关信息，常用 `-h` 参数](https://wangchujiang.com/linux-command/c/df.html)
- [du: 显示每个文件和目录的磁盘使用空间，常用 `-sh` 参数](https://wangchujiang.com/linux-command/c/du.html)
- [mkswap: 建立和设置SWAP交换分区](https://wangchujiang.com/linux-command/c/mkswap.html)
- [quota: 显示磁盘已使用的空间与限制](https://wangchujiang.com/linux-command/c/quota.html)
- [edquota: 用于编辑指定用户或工作组磁盘配额](https://wangchujiang.com/linux-command/c/edquota.html)
- [ln: 用来为文件创建链接](https://wangchujiang.com/linux-command/c/ln.html)

## 2.4 用户与权限管理

- [useradd: 创建新的用户](https://wangchujiang.com/linux-command/c/useradd.html)
- [usermod: 修改用户的基本信息](https://wangchujiang.com/linux-command/c/usermod.html)
- [userdel: 删除用户以及与用户相关的文件](https://wangchujiang.com/linux-command/c/userdel.html)
- [groupadd: 创建新的用户组](https://wangchujiang.com/linux-command/c/groupadd.html)
- [groups: 显示用户所属的用户组](https://wangchujiang.com/linux-command/c/groups.html)
- [passwd: 修改用户的密码](https://wangchujiang.com/linux-command/c/passwd.html)
- [chmod: 修改文件或目录的权限](https://wangchujiang.com/linux-command/c/chmod.html)
- [chown: 修改文件或目录的所有者](https://wangchujiang.com/linux-command/c/chown.html)，`-R` 递归修改
- [chattr: 修改文件或目录的属性](https://wangchujiang.com/linux-command/c/chattr.html)
- [lsattr: 显示文件或目录的属性](https://wangchujiang.com/linux-command/c/lsattr.html)
- [setfacl: 设置文件或目录的访问控制列表](https://wangchujiang.com/linux-command/c/setfacl.html)
- [getfacl: 显示文件或目录的访问控制列表](https://wangchujiang.com/linux-command/c/getfacl.html)

## 2.5 网络与通信

- [telnet: 登录远程主机和管理(测试ip端口是否连通)](https://wangchujiang.com/linux-command/c/telnet.html)
- [netstat: 查看Linux中网络系统状态信息](https://wangchujiang.com/linux-command/c/netstat.html)
- [ifconfig: 配置和显示Linux系统网卡的网络参数](https://wangchujiang.com/linux-command/c/ifconfig.html)
- [ping: 测试主机之间网络的连通性(ipv4)](https://wangchujiang.com/linux-command/c/ping.html)
- [wget: Linux系统下载文件工具](https://wangchujiang.com/linux-command/c/wget.html)
- [nmcli: 地址配置工具](https://wangchujiang.com/linux-command/c/nmcli.html)
- [ssh-copy-id: 把本地的ssh公钥文件安装到远程主机对应的账户下](https://wangchujiang.com/linux-command/c/ssh-copy-id.html)
- [ssh-keygen: 为ssh生成、管理和转换认证密钥](https://wangchujiang.com/linux-command/c/ssh-keygen.html)
- [scp: 加密的方式在本地主机和远程主机之间复制文件](https://wangchujiang.com/linux-command/c/scp.html)
- [screen: 用于命令行终端切换](https://wangchujiang.com/linux-command/c/screen.html)

## 2.6 进程与任务管理

- [ps: 报告当前系统的进程状态](https://wangchujiang.com/linux-command/c/ps.html)
- [top: 显示或管理执行中的程序](https://wangchujiang.com/linux-command/c/top.html)
- [pidof: 查找指定名称的进程的进程号ID号](https://wangchujiang.com/linux-command/c/pidof.html)
- [at: 在指定的时间执行指定的任务](https://wangchujiang.com/linux-command/c/at.html)
- [atrm: 删除待执行的任务](https://wangchujiang.com/linux-command/c/atrm.html)
- [crontab: 定时执行任务](https://wangchujiang.com/linux-command/c/crontab.html)
- [kill: 用于终止某个指定PID的服务进程](https://wangchujiang.com/linux-command/c/kill.html)
- [killall: 使用进程的名称来杀死一组进程](https://wangchujiang.com/linux-command/c/killall.html)

## 2.7 数据处理与编程

- [awk: 文本和数据进行处理的编程语言](https://wangchujiang.com/linux-command/c/awk.html)
- [expr: 计算表达式的值](https://wangchujiang.com/linux-command/c/expr.html)
- [let: 计算表达式并将结果保存到变量中](https://wangchujiang.com/linux-command/c/let.html)

## 2.8 用户切换与权限提升

- [su: 切换到其他用户的身份上](https://wangchujiang.com/linux-command/c/su.html)
- [sudo: 以其他用户的身份执行命令](https://wangchujiang.com/linux-command/c/sudo.html)

## 2.9 环境变量与 shell 操作
- [export: 为shell变量或函数设置导出属性](https://wangchujiang.com/linux-command/c/export.html)

## 2.10 其他

- [exit: 退出当前的shell](https://wangchujiang.com/linux-command/c/exit.html)
- [whereis: 查找二进制程序、源代码、man手册页等相关文件的路径](https://wangchujiang.com/linux-command/c/whereis.html)
- [which: 查找并显示给定命令的绝对路径](https://wangchujiang.com/linux-command/c/which.html)
- [read: 从键盘读取变量值](https://wangchujiang.com/linux-command/c/read.html)
- [semanage: 默认目录的安全上下文查询与修改](https://wangchujiang.com/linux-command/c/semanage.html)
- [restorecon: 恢复文件的安全上下文](https://wangchujiang.com/linux-command/c/restorecon.html)
- [getenforce: 显示当前SELinux的应用模式，是强制、执行还是停用](https://wangchujiang.com/linux-command/c/getenforce.html)
- [htpasswd: apache服务器创建密码认证文件](https://wangchujiang.com/linux-command/c/htpasswd.html)
- [watch: 可以将命令的输出结果输出到标准输出设备，多用于周期性执行命令/定时执行命令](https://wangchujiang.com/linux-command/c/watch.html)

# 第 3 章 管道符、重定向与环境变量

## 3.1 5 种重定向技术
- 标准覆盖输出重定向
- 标准追加输出重定向
- 错误覆盖输出重定向
- 错误追加输出重定向
- 输入重定向

输入重定向是指把文件导入到命令中，而输出重定向则是指把原本要输出到屏幕的数据信息写入到指定文件中

- `0`：标准输入重定向（STDIN），默认从键盘输入
- `1`：标准输出重定向（STDOUT），默认输出到屏幕
- `2`：错误输出重定向（STDERR），默认输出到屏幕

- 将文件作为命令的标准输入：`command < file`
- 从标准输入中读入，直到遇见分界符才停止：`command << delimiter`
- 将文件1作为命令的标准输入并将标准输出到文件2：`command < file1 > file2`
- 将标准输出重定向到文件中（清空原有文件的数据）：`command > file`
- 将错误输出重定向到文件中（清空原有文件的数据）：`command 2> file`
- 将标准输出重定向到文件中（追加到原有内容的后面）：`command >> file`
- 将错误输出重定向到文件中（追加到原有内容的后面）：`command 2>> file`
- 将标准输出与错误输出共同写入到文件中（追加到原有内容的后面）：`command >> file 2>&1` 或者 `command &>> file`

`dev/null` 是一个特殊的文件，可以被用于丢弃不需要的输出流

## 3.2 管道符与通配符

- `|`：管道命令符，用于将一个命令的输出连接到另一个命令的输入，这种机制称为"管道"
- `*`：匹配任意长度的字符序列（包括空）
- `?`：匹配任意单个字符
- `[ ]`：匹配方括号中的任意一个字符
- `{ }`：展开为所有可能的组合
- `\`：取消通配符的特殊含义，将其视为普通字符。**转义字符**

## 3.3 环境变量

### 3.3.1 系统环境变量和用户环境变量

- 系统环境变量：由Linux操作系统设置的全局变量，对所有用户和进程都可见
    - `PATH`: 用于定义可执行文件的查找路径。
    - `LANG`: 用于指定默认的系统语言设置。
    - `HOME`: 用于指定用户的家目录路径。
    - `TMPDIR` 或 `TEMP`: 用于指定临时文件的目录路径。

- 用户环境变量：每个用户在登录时设置的变量，对每个用户的会话都有效，可以覆盖系统环境变量
    - `~/.bashrc`: 用于bash shell的配置文件。
    - `~/.profile`: 用于登录时的配置文件。
    - `~/.bash_profile`: 用于bash shell登录时的配置文件。

### 3.3.2 环境变量的设置和使用

- 设置环境变量：`export MY_VARIABLE=value`
- 查看环境变量：`echo $MY_VARIABLE`
- 永久性环境变量：编辑用户的配置文件（如`~/.bashrc`或`~/.bash_profile`）并添加`export MY_VARIABLE=value`
- 临时追加到 `PATH`：`export PATH=$PATH:/path/to/new_directory`
- （当前用户）永久追加到 `PATH`：编辑用户的配置文件（如`~/.bashrc`或`~/.bash_profile`）并添加`export PATH=$PATH:/path/to/new_directory`
- （所有用户）永久追加到 `PATH`：编辑系统级别的配置文件（如`/etc/environment`）并添加`PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/path/to/new_directory"`

# 第 4 章 Vim 编辑器与 Shell 命令脚本

## 4.1 Vim 编辑器

- [Vim 笔记](https://github.com/Corner430/study-notes/blob/main/Linux运维/vim笔记.md)

## 4.2 Shell 脚本

### 4.2.1 shell 脚本的编写步骤

1. 创建脚本文件：`touch myscript.sh`
2. 添加 Shebang 行：`#!/bin/bash`
3. 编写脚本内容
4. 赋予执行权限：`chmod +x myscript.sh`
5. 运行脚本：`./myscript.sh` 或 `bash myscript.sh` 或 `source myscript.sh`

### 4.2.2 shell 脚本接收用户参数

- 位置参数：`$1`、`$2`、`$3`、`$0`、`$*`、`$#`
- `$?`：获取上一个命令的退出状态，`0` 表示成功，非零值表示失败

```bash
#!/bin/bash

# $0 表示脚本本身的名称，例如：./myscript.sh
echo "脚本名称：$0"

# $1 表示第一个参数，例如：./myscript.sh argument1
echo "第一个参数：$1"

# $2 表示第二个参数，例如：./myscript.sh argument1 argument2
echo "第二个参数：$2"

# $3 表示第三个参数，例如：./myscript.sh argument1 argument2 argument3
echo "第三个参数：$3"

# $* 表示所有参数的列表，以单个字符串表示
echo "所有参数：$*"

# $# 表示参数的数量
echo "参数的数量：$#"
```

### 4.2.3 shell 中的条件表达式

- `[ expression ]`：用于测试表达式是否成立，**两边的方括号与表达式之间必须有空格**

- 文件测试表达式
    - `-e file`：检查文件是否存在
    - `-f file`：检查文件是否为普通文件
    - `-d file`：检查文件是否为目录
    - `-s file`：检查文件是否非空
    - `-r file`：检查文件是否可读
    - `-w file`：检查文件是否可写
    - `-x file`：检查文件是否可执行
    - `file1 -nt file2`：检查文件1是否比文件2新
    - `file1 -ot file2`：检查文件1是否比文件2旧
    - `-O file`：检查文件是否属于当前用户
    - `-G file`：检查文件是否属于当前用户所属的组
    - `file1 -ef file2`：检查文件1是否和文件2为同一个硬链接

- 逻辑测试表达式
    - `expression1 -a expression2`：逻辑与，检查同时满足表达式1和表达式2的条件是否成立
    - `expression1 -o expression2`：逻辑或，检查满足表达式1或表达式2中任意一个条件是否成立
    - `! expression`：逻辑非，取反，检查表达式的条件是否不成立

- 整数值比较表达式
    - `int1 -eq int2`：检查整数1是否等于整数2
    - `int1 -ne int2`：检查整数1是否不等于整数2
    - `int1 -gt int2`：检查整数1是否大于整数2
    - `int1 -lt int2`：检查整数1是否小于整数2
    - `int1 -ge int2`：检查整数1是否大于等于整数2
    - `int1 -le int2`：检查整数1是否小于等于整数2

- 字符串比较表达式
    - `str1 = str2`：检查字符串1是否等于字符串2
    - `str1 != str2`：检查字符串1是否不等于字符串2
    - `-z str`：检查字符串是否为空（长度为0）
    - `-n str`：检查字符串是否非空（长度大于0）
    - `str`：检查字符串是否非空（与`-n`运算符类似，但不需要`-n`修饰符，直接写字符串即可）

- `&&` 和 `||` 运算符
    - `command1 && command2`：与
    - `command1 || command2`：或

> `&&` 和 `||` 并不是条件测试运算符，是根据前一个命令的退出状态码决定是否执行后一个命令

### 4.2.4 流程控制语句之 if 语句

多分支的 if 语句：
```bash
if [ 条件1 ]
then
    command1
elif [ 条件2 ]
then
    command2
else
    command3
fi
```

### 4.2.5 流程控制语句之 for 语句
```bash
for 变量 in 取值列表
do
    command
done
```

### 4.2.6 流程控制语句之 while 语句
```bash
while [ 条件 ]
do
    command
done
```

### 4.2.7 流程控制语句之 case 语句
```bash
case $变量名 in
    取值1)
        command1
        ;;
    取值2)
        command2
        ;;
    *)
        command3
        ;;
esac
```

## 4.3 计划任务服务程序

- 一次性计划任务：执行完毕后就会自动删除
  - [at: 在指定的时间执行指定的任务](https://wangchujiang.com/linux-command/c/at.html)
  - [atrm: 删除待执行的任务](https://wangchujiang.com/linux-command/c/atrm.html)

- 长期性计划任务：周期性执行的计划任务，执行完毕后不会自动删除
  - [crontab: 定时执行任务](https://wangchujiang.com/linux-command/c/crontab.html)

## 4.4 nologin 帐户
### 4.4.1 nologin 帐户介绍

- `nologin`：一个特殊的系统用户帐户或Shell。阻止特定用户登录到系统，并且通常用于防止一些帐户（如系统服务帐户）登录并交互式地执行命令。

### 4.4.2 设置 nologin 帐户

设置用户的登录 shell 为 `nologin`
- 修改 `/etc/passwd` 文件：`/usr/sbin/nologin` 或 `/sbin/nologin`

> `nologin`帐户仅影响交互式登录，而不会影响通过SSH密钥进行的非交互式操作或系统服务的正常运行。

# 第 5 章 用户身份与文件权限

## 5.1 用户身份 UID

UID(User ID, UID) 用来唯一的标识用户

- UID 为 `0`：超级用户，也称为 root 用户
- UID 为 `1` 到 `999`：系统用户和服务账户
- UID 为 `1000` 到 `65,535`：普通用户
- `id username`：查看用户的 UID 和所属的组信息

## 5.2 用户组 GID

GID(Group ID, GID) 用来唯一的标识用户组

- GID 为 `0`：root 用户组
- GID 为 `1` 到 `999`：系统用户组和服务组
- GID 为 `1000` 到 `65,535`：普通用户组

每个用户在创建时会伴随着一个与其同名的**基本用户组**，仅其一人。

一个用户只有一个基本用户组，但可以有多个**扩展用户组**。

## 5.3 文件权限与归属

**一切皆文件**

- `-`：普通文件
- `d`：目录
- `l`：符号链接（软链接）
- `c`：字符设备文件（键鼠）
- `b`：块设备文件（硬盘，USB）
- `p`：命名管道（FIFO），用于进程间通信
- `s`：套接字（Socket），用于网络通信
- `r`：读权限 `4`
- `w`：写权限 `2`
- `x`：执行权限 `1`
- `-`：无权限 `0`
- `ls -l`
    - `-rwxr-xr-x 1 username groupname size date filename`
        - `-`：普通文件
        - `rwx`：文件所有者的权限
        - `r-x`：文件所属组的权限
        - `r-x`：其他用户的权限
        - `1`：链接计数，指向该文件或目录的硬链接数量
        - `username`：文件的所有者
        - `groupname`：文件的所属组
        - `size`：文件的大小，以字节为单位
        - `date`：文件的最后修改日期和时间
        - `filename`：文件的名称

### 5.3.1 chmod 的细节

- `chmod u+x example.sh`：给文件的拥有者添加执行权限
- `chmod g+x example.sh`：给文件的所属组添加执行权限
- `chmod o+x example.sh`：给文件的其他用户添加执行权限
- `chmod a+x example.sh`：给文件的所有用户添加执行权限
- `chmod +x example.sh`：给文件的所有用户添加执行权限

## 5.4 文件的特殊权限

- SUID（Set User ID）
   - 对于文件：当SUID标志设置在一个可执行文件上时，**表示在执行该文件时，进程将以文件所有者的权限运行，而不是执行该文件的用户的权限**。
   - 对于目录：在目录上设置SUID标志没有实际作用。

   表示SUID标志的符号是一个小写的 `s`，当没有执行权限时则为大写的 `S`。

- SGID（Set Group ID）
   - 对于文件：当SGID标志设置在一个可执行文件上时，**表示在执行该文件时，进程将以文件所属组的权限运行，而不是执行该文件的用户的权限。**
   - 对于目录：当SGID标志设置在一个目录上时，**表示在该目录下新创建的文件和目录将继承该目录的所属组，而不是创建者的默认组**。

   表示SGID标志的符号是一个小写的 `s`，当没有执行权限时则为大写的 `S`。

3. SBIT（Sticky Bit）
   - 对于目录：当SBIT标志设置在一个目录上时，**表示只有文件的所有者、目录的所有者或超级用户才能删除在此目录下其他用户创建的文件，即保护目录中的文件不被其他非所有者用户删除**。

   表示SBIT标志的符号是一个小写的 `t`，当没有执行权限时则为大写的 `T`。

> 其实，文件能否被删除并不取决于自身的权限，而是取决于其所在的目录的权限

## 5.5 文件的隐藏属性

## 5.6 su 和 sudo 命令

### 5.6.1 visudo

`visudo`是一个用于编辑`/etc/sudoers`文件的工具

```
# 允许用户A执行所有命令，不需要密码
userA ALL=(ALL) NOPASSWD: ALL

# 允许用户B以root权限执行特定命令，需要密码
userB ALL=(ALL) PASSWD: /usr/bin/command1, /usr/bin/command2

# 允许用户组C以root权限执行所有命令，需要密码
%groupC ALL=(ALL) PASSWD: ALL
```

### 5.6.2 修改用户

- 用户信息：`/etc/passwd`
  - 直接用文本编辑器来修改其中的用户参数项目
  - 使用`usermod`命令修改已经创建的用户信息。

`usermod` 的 `-d -m` 选项可重新指定用户的家目录**并自动把旧的数据转移过去**。

# 第 6 章 存储结构与磁盘划分

## 6.1 [文件系统层次化标准（FHS, Filesystem Hierarchy Standard）](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)

- `/`：根目录
- `/boot`：启动文件
- `/dev`：设备文件
- `/etc`：系统配置文件
- `/home`：用户主目录
- `/bin`：存放单用户下还可以使用的指令
- `/sbin`：系统命令文件
- `/lib`：系统**库**文件
- `/root`：root 用户的主目录
- `/tep`：任何人都可以使用的“共享”临时目录
- `/media`：可移动设备的挂载点
- `/mnt`：用于暂时挂载其他文件系统或设备
- `/opt`：第三方软件安装目录
- `/usr`：用户自行安装的软件
- `/var`：存放经常变化的文件，如日志文件、邮件、数据库等
- `/lost+found`：系统异常关机后，文件系统自动检查时将一些丢失的文件片段存放在这里
- `/proc`：虚拟文件系统，包含系统内核、进程、外部设备及网络状态等
- `/run`：运行时文件，存储系统启动后产生的临时运行时数据，如PID文件和套接字文件
- `/sys`：Sysfs虚拟文件系统，提供了关于内核、设备和其他系统信息的信息
- `/var/run`：存储运行中的进程的PID文件
- `/var/log`：存储系统日志文件，包括系统事件和各种应用程序的日志
- `/var/cache`：存储缓存文件，可以包括已安装软件包的缓存等
- `/var/lib`：用于存储应用程序的可变数据，如数据库文件

## 6.2 硬件设备文件名称

系统内核中的 **udev 设备管理器** 会自动把硬件名称规范起来

- IDE 硬盘：`/dev/hd[a-d]`
- SCSI/SATA/USB 硬盘：`/dev/sd[a-p]`
- 光驱：`/dev/cdrom`
- 软盘：`/dev/fd[0-1]`
- 打印机：`/dev/lp[0-2]`
- 鼠标：`/dev/mouse`
- 调制解调器：`/dev/modem`
- 串行端口：`/dev/ttyS[0-3]`
- 并行端口：`/dev/lp[0-2]`
- 声卡：`/dev/dsp`
- 随机存储器：`/dev/ram[0-15]`
- 网络接口：`/dev/eth[0-15]`

## 6.3 磁盘分区

可以采用 `a~p` 来代表 16 块不同的硬盘（默认从 a 开始分配），这个次序并不是由插槽决定的，而是由系统内核的识别顺序来决定的。只是恰巧很多主板的插槽顺序和系统内核的识别顺序一致

- 主分区或扩展分区的编号从 1 开始，最多可以有 4 个
- 逻辑分区的编号从 5 开始，最多可以有 11 个

**分区的数字编码可以手工指定**

### 6.3.1 主分区、扩展分区和逻辑分区

#### 6.3.1.1 主分区

硬件设备是由大量的扇区组成的，每个扇区的容量为 512 字节。其中第一个扇区最重要，保存着主引导记录与分区表信息。

在第一个扇区中，主引导记录需要占用 446 字节，**分区表**为 64 字节，结束符占用 2 字节

其中分区表中每记录一个分区信息就需要 16 字节，这样一来最多只有 4 个分区信息可以写到第一个扇区中，**这 4 个分区就是 4 个主分区**

#### 6.3.1.2 扩展分区

第一个扇区最多只能创建出4个分区。于是为了解决分区个数不够的问题，可以将第一个扇区的分区表中 16 字节（原本要写入主分区信息）的空间（称之为扩展分区）拿出来指向另外一个分区。

扩展分区其实并不是一个真正的分区，而更像是一个占用 16 字节分区表空间的指针，一个指向另外一个分区的指针。

#### 6.3.1.3 逻辑分区

用户一般会选择使用 3 个主分区加 1 个扩展分区的方法，然后在扩展分区中创建出数个逻辑分区，从而来满足多分区（大于 4 个）的需求。

### 6.3.2 挂载、分区、格式化

#### 6.3.2.1 挂载

- [mount: 用于挂载Linux系统外的文件](https://wangchujiang.com/linux-command/c/mount.html)
- [umount: 用于卸载已经加载的文件系统](https://wangchujiang.com/linux-command/c/umount.html)

- 永久挂载
    - 配置文件：`/etc/fstab`
    - 格式：`设备文件 挂载目录 格式类型 权限选项 自检 优先级`
    - 示例：`/dev/sdb2 /backup ext4 defaults 0 0`

- 格式类型：`ext4`、`ntfs`、`vfat` 等
- 权限选项：`rw`（读写）、`ro`（只读）、`auto`（自动挂载）、`noauto`（不自动挂载）、`exec`（允许执行）、`noexec`（不允许执行）、`sync`（同步写入）、`async`（异步写入）、`user`（允许普通用户挂载）、`nouser`（不允许普通用户挂载）、`dev`（允许创建设备文件）、`nodev`（不允许创建设备文件）、`suid`（允许 SUID）、`nosuid`（不允许 SUID）、`defaults`（默认权限）
- 自检：`0`（不检查）、`1`（检查）
- 优先级：`0`（不检查）、`1`（第一个检查）、`2`（第二个检查）

#### 6.3.2.2 分区

- [fdisk: 查看磁盘使用情况和磁盘分区](https://wangchujiang.com/linux-command/c/fdisk.html)
- [file: 用来探测给定文件的类型](https://wangchujiang.com/linux-command/c/file.html)
- [partprobe: 不重启的情况下重读分区](https://wangchujiang.com/linux-command/c/partprobe.html)

#### 6.3.2.3 格式化

- [mkfs: 用于在设备上创建Linux文件系统](https://wangchujiang.com/linux-command/c/mkfs.html)
- [df: 显示磁盘的相关信息，常用 `-h` 参数](https://wangchujiang.com/linux-command/c/df.html)
- [du: 显示每个文件和目录的磁盘使用空间，常用 `-sh` 参数](https://wangchujiang.com/linux-command/c/du.html)

#### 6.3.2.4 交换分区

SWAP 分区：硬盘划分出来的一块空间，用于暂时存放内存中暂时不常用的数据
- 在生产环境中，SWAP分区的大小一般是物理内存的两倍
- 在虚拟机中，SWAP分区的大小一般是物理内存的两倍到四倍

- [mkswap: 建立和设置SWAP交换分区](https://wangchujiang.com/linux-command/c/mkswap.html)

`/dev/sdb2 swap swap defaults 0 0`

## 6.4 磁盘配额

- [quota: 显示磁盘已使用的空间与限制](https://wangchujiang.com/linux-command/c/quota.html)
- [edquota: 用于编辑指定用户或工作组磁盘配额](https://wangchujiang.com/linux-command/c/edquota.html)


## 6.5 软硬方法链接

- 硬链接（hard link）：硬链接文件与原始文件其实是同一个文件，只是名字不同
- 软链接（symbolic link）：软链接文件只是一个指向原始文件的指针，**快捷方式**

[ln: 用来为文件创建链接](https://wangchujiang.com/linux-command/c/ln.html)

# 第 7 章 使用 RAID 与 LVM 磁盘阵列技术

## 7.1 RAID

### 7.1.1 RAID 的概念与作用

RAID 通过把多个硬盘设备组合成一个容量更大、安全性更好的磁盘阵列，并把数据切割成多个区段后分别存放在各个不同的物理硬盘设备上。

RAID 不仅降低了硬盘设备损坏后丢失数据的几率，还提升了硬盘设备的读写速度。

### 7.1.2 RAID 级别

- RAID 0 ：通过硬件或软件将多个物理设备串联在一起，一次写入数据到各个物理硬盘中，提升硬盘数据的吞吐速度，但**不具有数据备份和错误修复能力**

- RAID 1 ：将数据同时写入到多块硬盘设备上（可以将其视为数据的镜像或备份）。当其中某一块硬盘发生故障后，一般会立即自动以**热交换**的方式来恢复数据的正常使用。

- RAID 5 ：把硬盘设备的数据奇偶校验信息保存到其他硬盘设备中。RAID 5 磁盘阵列组中数据的奇偶校验信息并不是单独保存到某一块硬盘设备中，而是存储到除自身以外的其他每一块硬盘设备上

- RAID 10 ：RAID 1 + RAID 0。需要至少 4 块硬盘来组建，其中先分别两两制作成 RAID 1 磁盘阵列，以保证数据的安全性；然后再对两个RAID 1 磁盘阵列实施 RAID 0 技术，进一步提高设备的读写速度。

### 7.1.3 部署 RAID

使用 `mdadm`（多设备管理器） 来部署 RAID

### 7.1.4 磁盘阵列 + 备份盘

RAID 10 磁盘阵列中最多允许 50% 的硬盘设备发生故障，但是存在这样一种极端情况，即同一 RAID 1 磁盘阵列中的硬盘设备若全部损坏，也会导致数据丢失。


可以使用RAID 备份盘技术来预防这类事故。该技术的核心理念就是**准备一块足够大的硬盘，这块硬盘平时处于闲置状态，一旦 RAID 磁盘阵列中的硬盘出现故障后则会马上自动顶替上去。**


## 7.2 LVM

### 7.2.1 LVM 的概念与作用

RAID 痛点：部署之后难以修改硬盘分区大小

**LVM（逻辑卷管理器）的直观理解参考原文，非常形象**。LVM技术是在硬盘分区和文件系统之间添加了一个逻辑层，它提供了一个抽象的卷组，可以把多块硬盘进行卷组合并。

### 7.2.2 常用的 LVM 命令

| 功能/命令 | 物理卷管理 | 卷组管理 | 逻辑卷管理 |
| :---: | :---: | :---: | :---: |
| 扫描 | `pvscan` | `vgscan` | `lvscan` |
| 建立 | `pvcreate` | `vgcreate` | `lvcreate` |
| 显示 | `pvdisplay` | `vgdisplay` | `lvdisplay` |
| 删除 | `pvremove` | `vgremove` | `lvremove` |
| 扩展 | | `vgextend` | `lvextend` |
| 缩小 | | `vgreduce` | `lvreduce` |

- [e2fsck: 用于检查第二扩展文件系统的完整性](https://wangchujiang.com/linux-command/c/e2fsck.html)

- `resize2fs`: 一个用于调整 ext2、ext3 和 ext4 文件系统大小的命令行工具。它用于扩展或缩小现有文件系统的大小，以适应不同的存储需求。

LVM 具有快照卷功能

> LVM 删除时，需要先备份信息，**之后依次删除逻辑卷、卷组、物理卷设备，这个顺序不可颠倒。**

# 第 8 章 iptables 与 firewalld 防火墙

## 8.1 防火墙执行方式

- 匹配顺序：自上而下，先匹配到的规则生效，如果没有匹配到规则，则执行默认策略
- `iptables`：下一次重启生效，`service iptables save` 保存

### 8.1.1 iptables

#### 8.1.1.1 数据包处理位置

- 在进行路由选择前处理数据包（PREROUTING）
- 处理**流入**的数据包（INPUT）
- 处理流出的数据包（OUTPUT）
- 处理转发的数据包（FORWARD）
- 在进行路由选择后处理数据包（POSTROUTING）

#### 8.1.1.2 数据包处理方式

- `ACCEPT`：允许数据包通过
- `DROP`：丢弃数据包，不给任何回应。**连接超时**
- `REJECT`：丢弃数据包，并给发送端一个错误回应。**端口不可达**
- `LOG`：记录数据包的信息，但不影响数据包的传输

> 连接超时也可能是因为目标主机不在线

#### 8.1.1.3 iptables 常用命令

- 允许 ICMP 流量进入，即允许 ping 命令：`iptables -A INPUT -p icmp -j ACCEPT`
- 查看 iptables 规则：`iptables -L`
- 清除 iptables 规则：`iptables -F`
- 允许或拒绝数据包：`iptables -A INPUT -p tcp --dport 22 -j ACCEPT`
- 端口转发：`iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8080`
- 设置网络地址转换（NAT）：`iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE`
- 允许相关和已建立的连接：`iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT`

### 8.1.2 firewalld

#### 8.1.2.1 firewalld
`firewalld` 是一个在 Linux 上用于管理防火墙规则的工具，使用区域（zone）来定义不同网络环境的策略规则。

| 区域名称 | 描述 | 默认策略规则 |
|-----------------|--------------|---------------|
| trusted | 最宽松的区域，允许所有数据包通过，通常用于本地网络或受信任的网络。 | 允许所有数据包。 |
| public | 通常用于公共网络，如互联网连接，拒绝入站连接，允许外发连接。 | 拒绝入站连接，允许外发连接。 |
| external | 用于外部网络连接，设置更为严格的策略规则以增加安全性，类似于 public 区域。 | 拒绝入站连接，允许外发连接。 |
| home | 用于家庭网络环境，允许某些传入连接，如文件共享或打印机共享。 | 允许一些传入连接，例如文件共享或打印机共享。 |
| work | 用于工作场所或办公室网络环境，通常允许更多传入连接，以支持业务需求。 | 允许更多传入连接，以满足业务需求。 |
| internal | 用于内部网络环境，通常允许所有传入连接。 | 允许所有传入连接。 |
| dmz | 用于半受信任的网络环境，允许某些传入连接，但通常限制了对内部网络的访问。 | 限制对内部网络的访问，允许某些传入连接。 |
| block | 非常严格的区域，拒绝所有传入和传出的连接。 | 拒绝所有传入和传出的连接。 |
| custom | 可创建自定义区域，定义自己的策略规则以满足特定的网络需求。 | 自定义策略规则以满足特定需求。 |

#### 8.1.2.2 firewalld-cmd

`firewalld-cmd` 是 `firewalld` 防火墙配置管理工具的CLI（命令行界面）版本

| 参数 | 作用 |
|-------------|-------|
| `--get-default-zone` | 查询默认的区域名称 |
| `--set-default-zone=<zone>` | 设置默认的区域名称 |
| `--get-zones` | 显示可用的区域 |
| `--get-services` | 查询指定服务所属的区域和接口 |
| `--get-active-zones` | 列出所有活跃接口及它们所属的区域 |
| `--add-source=<source> [--zone=<zone>]` | 向指定区域添加源地址规则 |
| `--remove-source=<source> [--zone=<zone>]` | 从指定区域移除源地址规则 |
| `--add-interface=<网卡名称>` | 将源自该网卡的所有流量导向某个指定区域 |
| `--change-interface=<网卡名称>` | 将某个网卡与区域进行关联 |
| `--list-all` | 列出当前区域的网卡配置参数、资源、端口以及服务等信息 |
| `--list-all-zones` | 列出所有区域的网卡配置参数、资源、端口以及服务等信息 |
| `--add-service=<service> [--zone=<zone>]` | 向指定区域添加服务 |
| `--add-port=<port>/<protocol> [--zone=<zone>]` | 向指定区域添加端口规则 |
| `--remove-service=<service> [--zone=<zone>]` | 从指定区域移除服务 |
| `--remove-port=<port>/<protocol> [--zone=<zone>]` | 从指定区域移除端口规则 |
| `--reload` | 重新加载 `firewalld` 防火墙配置，应用新的规则 |
| `--panic-on` | 激活紧急模式，拒绝所有传入和传出连接，通常在安全问题发生时使用 |
| `--panic-off` | 关闭紧急模式，允许正常流量传入和传出，用于解决安全问题后恢复正常 |

#### 8.1.2.3 使用Firewalld

- 启动 `firewalld` 服务：`systemctl start firewalld`
- 停止 `firewalld` 服务：`systemctl stop firewalld`
- 启用 `firewalld` 服务在系统启动时自动运行：`systemctl enable firewalld`
- 禁用 `firewalld` 服务在系统启动时自动运行：`systemctl disable firewalld`
- 查看 `firewalld` 状态：`systemctl status firewalld`
- 列出所有可用的区域：`firewall-cmd --get-zones`
- 查看当前活动区域：`firewall-cmd --get-active-zones`
- 切换接口到不同的区域：`firewall-cmd --zone=public --change-interface=eth0`，将 `eth0` 接口切换到 `public` 区域
- 添加一个服务到防火墙规则（例如，允许SSH访问）：`firewall-cmd --zone=public --add-service=ssh`
- 永久保存防火墙规则的更改：`firewall-cmd --runtime-to-permanent`
- 查看指定区域的规则：`firewall-cmd --zone=public --list-all`
- 移除一个服务从防火墙规则（例如，移除SSH服务）：`firewall-cmd --zone=public --remove-service=ssh`

# 第 9 章 使用 ssh 服务管理远程主机

## 9.1 绑定两块网卡

网卡绑定，也称为网络接口绑定、网卡聚合或链路聚合 

- 共同传输数据
- 自动备援
- 网卡绑定驱动模式
  - mode0：平衡负载模式，（需要在与服务器本地网卡相连的交换机设备上进行端口聚合来做支撑）
  - mode1：自动备援模式
  - mode6：平衡负载模式

## 9.2 配置 sshd 服务

SSH、FTP、Telnet 都可用来进行远程登陆，但ssh最安全

- 基于口令的验证
- 基于密钥的验证
- 设置完成后需要 `systemctl restart sshd`
- 配置文件：`/etc/ssh/sshd_config`

| 参数 | 作用 |
|:---:|:---:|
| `Port 22` | 默认的 sshd 服务端口 |
| `ListenAddress 0.0.0.0` | 设定 sshd 服务监听的 IP 地址 |
| `PermitRootLogin yes` | 设定是否允许 root 管理员直接登录 |
| `StrictModes yes` | 当远程用户的私钥改变时直接拒绝连接 |
| `MaxAuthTries 6` | 最大密码尝试次数 |
| `MaxSessions 10` | 最大终端数 |
| `PasswordAuthentication yes` | 是否允许密码验证 |
| `PermitEmptyPasswords no` | 是否允许空密码登录（很不安全） |

- [ssh-copy-id: 把本地的ssh公钥文件安装到远程主机对应的账户下](https://wangchujiang.com/linux-command/c/ssh-copy-id.html)
- [ssh-keygen: 为ssh生成、管理和转换认证密钥](https://wangchujiang.com/linux-command/c/ssh-keygen.html)

## 9.3 远程传输命令

- [scp: 加密的方式在本地主机和远程主机之间复制文件](https://wangchujiang.com/linux-command/c/scp.html)

## 9.4 不间断会话服务

- [screen: 用于命令行终端切换](https://wangchujiang.com/linux-command/c/screen.html)

# 第 10 章 使用 Apache 服务部署静态网站

# 第 11 章 使用 vsftpd 服务传输文件

## 11.1 FTP 服务

- FTP 基于客户端/服务端模式，默认使用20、21号端口
  - 端口20（数据端口）用于进行数据传输
  - 端口21（命令端口）用于接受客户端发出的相关FTP命令与参数

- FTP 工作模式
  - 主动模式：FTP 服务器主动向客户端发起连接请求
  - 被动模式：FTP 服务器等待客户端发起连接请求（FTP的默认工作模式）

## 11.2 vsftpd（very secure ftp daemon，非常安全的FTP守护进程）


#  第 12 章 使用 Samba 或 NFS 实现文件共享

## 12.1 Samba 介绍

Samba 是一个开源的网络文件共享协议，允许不同操作系统之间共享文件和打印机

## 12.2 安装与使用 Samba

- 配置文件 `/etc/samba/smb.conf`
- 配置文件可以定义共享资源，设置身份验证、访问控制等

   ```plaintext
   [share_name]
   path = /path/to/shared/folder
   writable = yes
   valid users = your_username
   ```

   - `share_name` 是共享的名称。
   - `path` 是共享资源的路径。
   - `writable` 指定共享是否可写入。
   - `valid users` 指定可以访问共享的用户。

- 检查配置文件的语法错误：`testparm`
- 添加 Samba 用户：`smbpasswd -a your_username`
- 重启 Samba 服务：`systemctl restart smbd`
- 使用 Samba
  - Windows 映射网络驱动器
  - Linux 使用 `smbclient` 或 `smbmount` 命令

## 12.3 NFS 介绍

- NFS（Network File System）是一种分布式文件系统协议，用于在网络上共享文件和目录

- NFS工作基于客户端-服务器模型

- 需要同时配置服务端和客户端

## 12.4 autofs 自动挂载服务

# 第 13 章 使用 BIND 提供域名解析服务

## 13.1 DNS 服务基本常识

- DNS(Domain Name System，域名系统)是一项用于管理和解析域名与 IP 地址对应关系的技术
  - 正向解析：将域名解析为 IP 地址
  - 反向解析：将 IP 地址解析为域名
- DNS 采用目录树的层级结构来存储域名与 IP 地址的对应关系，形成一个分布式的数据库系统
- 常见的域名后缀
  - .com（商业组织），通用顶级域名
  - .org（非营利组织），通用顶级域名
  - .gov（政府部门）
  - .edu（教育机构）
  - .net（网络服务商），通用顶级域名
  - .puba（公共大众）
  - .mil（军事机构）
  - .cn（中国），国家顶级域名
  - .jp（日本），国家顶级域名
  - .uk（英国），国家顶级域名
  - .us（美国），国家顶级域名

最高级、最权威的根 DNS 服务器总共有 13 台，分别位于美国、英国、瑞典、日本等国家，其中 10 台位于美国，1 台位于英国，1 台位于瑞典，1 台位于日本。这些根 DNS 服务器的 IP 地址分别为：

| 名称 | 管理单位 | 地理位置 | IP 地址 |
| :--- | :--- | :--- | :--- |
| A | INTERNIC.NET | 美国弗吉尼亚州 | 198.41.0.4 |
| B | 美国信息科学研究所 | 美国加利福尼亚州 | 128.9.0.107 |
| C | PSINet 公司 | 美国弗吉尼亚州 | 192.33.4.12 |
| D | 马里兰大学 | 美国马里兰州 | 128.8.10.90 |
| E | 美国航空航天管理局 | 美国加利弗吉亚州 | 192.203.230.10 |
| F | 因特网软件联盟 | 美国加利福尼亚州 | 192.5.5.241 |
| G | 美国国防部网络信息中心 | 美国弗尼亚州 | 192.112.36.4 |
| H | 美国陆军研究所 | 美国马里兰州 | 128.63.2.53 |
| I | Autonomica 公司 | 瑞典斯德哥尔摩 | 192.36.148.17 |
| J | VeriSign 公司 | 美国弗吉尼亚州 | 192.58.128.30 |
| K | RIPE NCC | 英国伦敦 | 193.0.14.129 |
| L | IANA | 美国弗吉尼亚州 | 199.7.83.42 |
| M | WIDE Project | 日本东京 | 202.12.27.33 |

## 13.2 三种 DNS 服务器

- **主服务器**：在特定区域内具有唯一性，负责维护该区域内的域名与 IP 地址之间的对应关系。
- **从服务器**：从主服务器中获得域名与 IP 地址的对应关系并进行维护，以防主服务器宕机等情况。
- **缓存服务器**：通过向其他域名解析服务器查询获得域名与 IP 地址的对应关系，并将经常查询的域名信息保存到服务器本地，以此来提高重复查询的效率。

## 13.3 BIND 服务程序

BIND（Berkeley Internet Name Domain，伯克利因特网名称域）服务是全球范围内使用最广泛、最安全可靠且高效的域名解析服务程序。

### 13.3.1 部署 BIND 服务程序

# 第 14 章 使用 DHCP 动态管理主机地址

- 动态主机配置协议（DHCP，Dynamic Host Configuration Protocol）协议用于自动管理局域网内主机的 IP 地址、子网掩码、网关地址及 DNS 地址等参数

- Windows 中的 MAC 地址用的是 `-`，而 Linux 中的 MAC 地址用的是 `:`。

# 第 15 章 使用 Postifx 与 Dovecot 部署邮件系统

# 第 16 章 使用 Squid 部署代理缓存服务

## 16.1 Squid 服务程序

- Squid 是 Linux 系统中最为流行的一款高性能代理服务软件，通常用作 Web 网站的前置缓存服务，能够代替用户向网站服务器请求页面数据并进行缓存。（代理缓存服务器）

- 代理模式
  - 正向代理模式：用户通过代理服务器访问互联网资源
  - 反向代理模式：多台节点主机反向缓存网站数据，加快用户访问速度
- 为安全计，许多网站都默认禁止了反向代理功能，开启了 **CDN （内容分发网络）服务**

## 16.2 ACL （访问控制列表）

- 结合 ACL（访问控制列表）功能，可以根据指定的策略条件来缓存数据或限制用户的访问

# 第 17 章 使用 ISCSI 服务部署网络存储

# 第 18 章 使用 MariaDB 数据库管理系统

# 第 19 章 使用 PXE + Kickstart 无人值守安装服务

# 第 20 章 使用 LNMP 架构部署动态网站环境
