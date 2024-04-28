# Notes-on-Learning-Linux-the-Right-Way
# 《Linux就该这样学》笔记

[English](README.md) | 中文

1. [installation](1.installation.md) 介绍了在安装系统时所遇到的问题
2. [RPM_and_YUM](2.RPM_and_YUM.md) 介绍了RPM和YUM的使用
3. [systemd](3.systemd.md) 介绍了systemd的使用
4. [bash_and_command](4.bash_and_command.md) 介绍了bash和命令的长短格式
5. [frequently_commands](5.frequently_command.md) 介绍了常用的命令
6. [basic_concept](6.basic_concept.md) 介绍了一些基本概念
   - 环境变量
   - 环境变量PATH
   - 网卡配置信息
   - 用户身份UID
   - 用户组GID
   - passwd密码
7. [vim](7.vim.md) 介绍了vim的使用
8. [Shell_Fundamentals_and_Script_Programming](8.Shell_Fundamentals_and_Script_Programming.md) 介绍了Shell的基础知识和脚本编程
   - Shell 中常用的转义字符
   - 5 种重定向技术
   - 管道命令符 `|`
   - 命令行的通配符
   - 写 Shell 脚本的基本步骤
   - Shell 脚本如何接收用户参数
   - `$?`
   - Shell 中的条件表达式
   - 流程控制语句 `if` `for` `while` `case`
9. [File_and_Permission_Management](9.File_and_Permission_Management.md) 介绍了文件和权限管理
   - 文件权限与归属
   - 文件的特殊权限
   - 文件的隐藏属性
   - 文件的访问控制列表（ACL）
10. [System_Services_and_Tasks](10.System_Services_and_Tasks.md) 介绍了系统服务与任务
   - 计划任务服务程序，**分为一次性计划任务与长期性计划任务**
   - `su` 命令与 `sudo` 服务
11. [Storage Structure and Disk Partition](11.Storage-structure-and-disk-partition.md) 介绍了存储结构与磁盘分区
   - 文件系统层次化标准（FHS）
   - /dev/
   - 主分区、扩展分区、逻辑分区
   - 文件系统：Ext3、Ext4、XFS、Btrfs、ReiserFS、JFS、F2FS、ZFS
   - inode 表格
   - 分区、格式化、挂载
   - 添加交换分区、磁盘容量配额
12. [Using RAID and LVM disk array technology](12.Using_RAID_and_LVM_disk_array_technology.md) 介绍了RAID与LVM磁盘阵列技术的使用
   - LVM技术是在硬盘分区和文件系统之间添加了一个逻辑层，它提供了一个抽象的卷组，可以把多块硬盘进行卷组合并。
   - **LVM 还具备有“快照卷”功能。**
   - LVM 的删除是有顺序的
13. [iptables firewalld ufw](13.iptables_firewalld_and_ufw.md) 介绍了iptables firewalld ufw的使用
   - 防火墙的规则是有顺序的，**先匹配的规则优先级高**
   - 五大规则分类
14. [ssh](14.ssh.md) 介绍了如何使用 ssh 服务管理远程主机
   - nmtui 是 NetworkManager 文本用户界面工具的缩写，它是一个在终端中配置网络连接的命令行工具。
   - 使用 `nmcli` 创建网络会话
   - 绑定多网卡
   - sshd 服务的配置
   - scp 命令
   - 不间断会话服务（`screen`）
15. [Deploy static websites using Apache Services](15.Deploy_static_websites_using_Apache_services.md) 介绍了如何使用 Apache 服务部署静态网站
   - IIS、Nginx 和 Apache
   - Apache 服务的安装与配置
   - SELinux安全子系统
   - 虚拟主机功能
16. [Transfer files using vsftpd services](16.Transfer_files_using_vsftpd_services.md) 介绍了如何使用 vsftpd 服务传输文件
   - FTP
   - vsftpd(very secure ftp daemon，非常安全的FTP守护进程)
   - PAM(可插拔认证模块)
   - 简单文件传输协议(Trivial File Transfer Protocol, TFTP)
17. [Use Samba or NFS to achieve file sharing](17.Use_Samba_or_NFS_to_achieve_file_sharing.md)
   - Samba 允许多系统之间共享文件和打印机
   - NFS 在 Linux 系统之间共享文件和目录
18. [Using BIND to provide domain name resolution service](18.Using_BIND_to_provide_domain_name_resolution_service.md) 介绍了如何使用 BIND 提供域名解析服务
19. [Use DHCP to dynamically manage host addresses](19.Use_DHCP_to_dynamically_manage_host_addresses.md)
20. [Deploy the mail system using Postify and Dovecot](20.Deploy_the_mail_system_using_Postifx_and_Dovecot.md)
21. [Deploy proxy caching service using Squid](21.Deploy_proxy_caching_service_using_Squid.md)
   - Squid 是 Linux 系统中最为流行的一款高性能代理服务软件。
   - **标准正向代理、透明正向代理、反向代理**
   - ACL
   - CDN