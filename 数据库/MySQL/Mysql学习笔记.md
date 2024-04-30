# MySQL学习笔记

- [MySQL学习笔记](#mysql学习笔记)
  - [1 MySQL 数据库的基本使用](#1-mysql-数据库的基本使用)
    - [1.1 SQL 的介绍](#11-sql-的介绍)
    - [1.2 安装 MySQL 数据库](#12-安装-mysql-数据库)
      - [1.2.1 服务端安装](#121-服务端安装)
      - [1.2.2 配置文件详解](#122-配置文件详解)
      - [1.2.3 客户端安装](#123-客户端安装)
    - [1.3 数据类型和约束](#13-数据类型和约束)
      - [1.3.1 数据类型](#131-数据类型)
      - [1.3.2 数据约束](#132-数据约束)
      - [1.3.3 数据类型附录表](#133-数据类型附录表)
    - [1.4 图形化客户端 Navicat](#14-图形化客户端-navicat)
    - [1.5 命令行客户端 MySQL 的使用](#15-命令行客户端-mysql-的使用)
      - [1.5.1 数据库操作 SQL 语句](#151-数据库操作-sql-语句)
      - [1.5.2 表结构操作 SQL 语句](#152-表结构操作-sql-语句)
      - [1.5.3 表数据操作 SQL 语句](#153-表数据操作-sql-语句)
      - [1.5.4 客户端 SQL 语句小结](#154-客户端-sql-语句小结)
    - [1.6 as 和 distinct 关键字](#16-as-和-distinct-关键字)

## 1 MySQL 数据库的基本使用

### 1.1 SQL 的介绍

*SQL(Structured Query Language)* 是结构化查询语言，是一种用来操作 *RDBMS(Relational Database Management System)* 的数据库的语言。也就是说通过 SQL 可以操作 *oracle, sql server, mysql, sqlite* 等关系型的数据库。

SQL的作用是实现数据库客户端和数据库服务端之间的通信，SQL就是通信的桥梁。

**SQL** 语言主要分为：

- **DQL**：数据查询语言，用于对数据进行查询，如`select`
- **DML**：数据操作语言，对数据进行增加、修改、删除，如`insert, update, delete`
- **TPL**：事务处理语言，对事务进行处理，包括`begin transaction, commit, rollback`
- **DCL**：数据控制语言，进行授权与权限回收，如`grant, revoke`
- **DDL**：数据定义语言，进行数据库、表的管理等，如`create, drop`

SQL语言不区分大小写

### 1.2 安装 MySQL 数据库

#### 1.2.1 服务端安装

***mysql.yml***
```yml
services:
  mysql:
    image: mysql:latest
    container_name: mysql
    ports:
      - "23306:3306"
    environment:
      MYSQL_ROOT_PASSWORD: 1
    volumes:
      - ~/mysql/data:/var/lib/mysql
      - ~/mysql/conf:/etc/mysql/conf.d
      - ~/mysql/logs:/var/log/mysql
```

执行 `docker-compose -f mysql.yml up -d` 启动 MySQL 服务。

#### 1.2.2 配置文件详解

配置文件路径：`/etc/mysql/mysql.conf.d/mysqld.cnf`

```shell
#
# MySQL数据库服务器配置文件。
#
# 您可以将此文件复制到以下位置之一：
# - "/etc/mysql/my.cnf" 以设置全局选项，
# - "~/.my.cnf" 以设置用户特定选项。
# 
# 您可以使用程序支持的所有长选项。
# 使用 --help 运行程序以获取可用选项列表，并使用 --print-defaults 查看它实际上会理解和使用哪些选项。
#
# 有关说明，请参阅：
# http://dev.mysql.com/doc/mysql/en/server-system-variables.html
 
# 这将传递给所有mysql客户端
# 据报道，密码应该用引号或单引号括起来，特别是如果它们包含 "#" 字符...
# 在更改socket位置时，请记得编辑 /etc/mysql/debian.cnf。
 
# 这里是一些特定程序的条目
# 以下值假定您至少有 32M RAM

# mysqld_safe配置
[mysqld_safe]
socket          = /var/run/mysqld/mysqld.sock  # MySQL安全启动器的通信socket路径
nice            = 0  # 优先级设置

# mysqld基本设置
[mysqld]
user            = mysql  # MySQL服务运行的用户
pid-file        = /var/run/mysqld/mysqld.pid  # MySQL进程标识文件位置
socket          = /var/run/mysqld/mysqld.sock  # MySQL通信socket路径
port            = 3306  # MySQL监听的端口号
basedir         = /usr  # MySQL的安装基础目录
datadir         = /var/lib/mysql  # MySQL的数据存储目录
tmpdir          = /tmp  # MySQL的临时文件存储目录
lc-messages-dir = /usr/share/mysql  # MySQL的语言文件目录
skip-external-locking  # 跳过外部锁定，改善性能
log_bin        =  mylnx12_bin  # MySQL二进制日志文件的名称
server_id      = 0  # MySQL服务器的ID
character-set-server=utf8mb4  # 设置字符集
collation-server=utf8mb4_general_ci  # 设置排序规则
 
#
# 默认情况下，不再使用skip-networking，而是仅在localhost上监听，这更兼容且不会降低安全性。
bind-address            = 127.0.0.1
#
# * Fine Tuning
#
key_buffer_size         = 16M
max_allowed_packet      = 100M
thread_stack            = 192K
thread_cache_size       = 8
# This replaces the startup script and checks MyISAM tables if needed
# the first time they are touched
myisam-recover-options  = BACKUP
#max_connections        = 100
#table_cache            = 64
#thread_concurrency     = 10
#
# * Query Cache Configuration
#
query_cache_limit       = 1M
query_cache_size        = 16M
#
# * 日志和复制
#
# 这两个位置由cronjob定期轮换。
# 请注意，这种日志类型对性能有很大影响。
# 从5.1版本开始，您可以在运行时启用日志！
#general_log_file        = /var/log/mysql/mysql.log
#general_log             = 1
#
# 错误日志 - 应该只有很少的条目。
#
log_error = /var/log/mysql/error.log
#
# 这里可以查看执行时间特别长的查询
#log_slow_queries       = /var/log/mysql/mysql-slow.log
#long_query_time = 2
#log-queries-not-using-indexes
#
# 以下内容可用于轻松重播备份日志或用于复制。
# 注意：如果您正在设置复制从服务器，请查看README.Debian以了解其他可能需要更改的设置。
#server-id              = 1
#log_bin                        = /var/log/mysql/mysql-bin.log
expire_logs_days        = 10
max_binlog_size   = 100M
#binlog_do_db           = include_database_name
#binlog_ignore_db       = include_database_name
#
# * InnoDB
#
# 默认情况下，InnoDB已启用，在/var/lib/mysql/中具有10MB的数据文件。
# 阅读手册了解更多InnoDB相关选项。有很多！
#
# * 安全功能
#
# 如果要使用chroot，请阅读手册！
# chroot = /var/lib/mysql/
#
# 生成SSL证书时，建议使用OpenSSL GUI "tinyca"。
#
# ssl-ca=/etc/mysql/cacert.pem
# ssl-cert=/etc/mysql/server-cert.pem
#: ssl-key=/etc/mysql/server-key.pem
```

#### 1.2.3 客户端安装

- 图形化工具（Navicat）

- 命令行工具：`sudo apt install mysql-client`

### 1.3 数据类型和约束

数据类型和约束保证了表中数据的准确性和完整性

#### 1.3.1 数据类型

**常用数据类型:**

- 整数：`int, bit`
- 小数：`decimal`
- 字符串：`varchar, char`
- 日期时间: `date, time, datetime`
- 枚举类型(enum)

**数据类型说明:**

- `decimal` 表示浮点数，如 `decimal(5, 2)` 表示共存 5 位数，小数占 2 位.
- `char` 表示固定长度的字符串，如`char(3)`，如果填充`'ab'`时会补一个空格为`'ab '`，3 表示字符数
- `varchar` 表示可变长度的字符串，如`varchar(3)`，填充`'ab'`时就会存储`'ab'`，3 表示字符数
- 对于图片、音频、视频等文件，不存储在数据库中，而是上传到某个服务器上，然后在表中存储这个文件的保存路径.
- 字符串 `text` 表示存储大文本，当字符大于 4000 时推荐使用, 比如技术博客.

#### 1.3.2 数据约束

约束是指数据在数据类型限定的基础上额外增加的要求

**常见的约束：**

- 主键 `primary key`: 物理上存储的顺序. MySQL 建议所有表的主键字段都叫 `id`, 类型为 `int unsigned`
- 非空 `not null`: 此字段不允许填写空值
- 唯一 `unique`: 此字段的值不允许重复
- 默认 `default`: 当不填写字段对应的值会使用默认值
- 外键 `foreign key`: 对关系字段进行约束, 当为关系字段填写值时, 会到关联的表中查询此值是否存在, 如果存在则填写成功, 如果不存在则填写失败并抛出异常

#### 1.3.3 数据类型附录表

1. 整数类型

| 类型 | 字节大小 | 有符号范围(Signed) | 无符号范围(Unsigned) |
| :---- | :-------- | :------------------- | :--------------------- |
| TINYINT | 1 | -128 ~ 127 | 0 ~ 255 |
| SMALLINT | 2 | -32768 ~ 32767 | 0 ~ 65535 |
| MEDIUMINT | 3 | -8388608 ~ 8388607 | 0 ~ 16777215 |
| INT/INTEGER | 4 | -2147483648 ~2147483647 | 0 ~ 4294967295 |
| BIGINT | 8 | -9223372036854775808 ~ 9223372036854775807 | 0 ~ 18446744073709551615 |

2. 字符串

| 类型 | 说明 | 使用场景 |
| :---- | :---- | :------- |
| CHAR | 固定长度，小型数据 | 身份证号、手机号、电话、密码 |
| VARCHAR | 可变长度，小型数据 | 姓名、地址、品牌、型号 |
| TEXT | 可变长度，字符个数大于 4000 | 存储小型文章或者新闻 |
| LONGTEXT | 可变长度， 极大型文本数据 | 存储极大型文本数据 |

3. 时间类型

| 类型 | 字节大小 | 示例 |
| :---- | :-------- | :--- |
| DATE | 4 | '2020-01-01' |
| TIME | 3 | '12:29:59' |
| DATETIME | 8 | '2020-01-01 12:29:59' |
| YEAR | 1 | '2017' |
| TIMESTAMP | 4 | '1970-01-01 00:00:01' UTC ~ '2038-01-01 00:00:01' UTC |


### 1.4 图形化客户端 Navicat

1. 创建数据库

![20240430144319](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240430144319.png)

- 字符集：就是编码格式，一般选择 `utf8mb4`，支持中文、表情等
- 排序规则：一般选择 `utf8mb4_general_ci`，不区分大小写，区分大小写的话选择 `utf8mb4_bin`

2. 创建数据表

![20240430145415](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240430145415.png)

3. 编辑数据表

![20240430145606](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240430145606.png)

### 1.5 命令行客户端 MySQL 的使用

1. 登录数据库

```shell
mysql -uroot -p1

# -u: 用户名
# -p: 密码, 如果不填写，回车之后会提示输入密码
```

2. 查看登录效果

```shell
select now(); # 查看当前时间
```

#### 1.5.1 数据库操作 SQL 语句

1. 查看所有数据库

```shell
show databases;
```

2. 创建数据库

```shell
create database <database_name> charset=utf8mb4;
```

3. 使用数据库

```shell
use <database_name>;
```

4. 查看当前使用的数据库

```shell
select database();
```

5. 删除数据库

```shell
drop database <database_name>;
```

#### 1.5.2 表结构操作 SQL 语句

1. 查看当前数据库中所有表

```shell
show tables;
```

2. 创建表

```shell
create table students (
    id int unsigned primary key auto_increment not null,
    name varchar(20) not null,
    age tinyint unsigned default 0,
    height decimal(5, 2),
    gender enum('男', '女', '人妖', '保密')
);
```

**说明：**

```shell
create table <table_name> (
    字段名称 数据类型 可选的约束条件,
    colum1 datatype contrai,
    ...
);
```

3. 修改表-添加字段

```shell
alter table 表名 add 列名 类型 约束;
# 例：
alter table students add birthday datetime;
```

4. 修改表-修改字段类型

```shell
alter table 表名 modify 列名 类型 约束;
# 例：
alter table students modify birthday date not null;
```

- `modify`: 只能修改字段类型或者约束，不能修改字段名

5. 修改表-修改字段名和字段类型

```shell
alter table 表明 change 原名 新名 类型 约束;
# 例：
alter table students change birthday birth datetime not null;
```

- `change`: 既能对字段重命名又能修改字段类型还能修改约束

6. 修改表-删除字段

```shell
alter table 表名 drop 列名;
# 例：
alter table students drop birth;
```

7. 查看创表SQL语句

```shell
show create table 表名;
# 例：
show create table students;
```

8. 查看创库SQL语句

```shell
show create database 数据库名;
# 例：
show create database test;
```

9. 删除表

```shell
drop table 表名;
# 例：
drop table students;
```

#### 1.5.3 表数据操作 SQL 语句

1. 查询数据

```shell
# 1. 查询所有列
select * from 表名;
例：
select * from students;
# 2. 查询指定列
select 列1, 列2, ... from 表名;
例：
select id,name from students;
```

2. 添加数据

```shell
# 1. 全列插入：值的顺序与表结构字段的顺序完全一一对应
insert into 表名 values (...)
例:
insert into students values(0, 'xx', default, default, '男');

# 2. 部分列插入：值的顺序与给出的列顺序对应
insert into 表名 (列1,...) values(值1,...)
例:
insert into students(name, age) values('王二小', 15);

# 3. 全列多行插入
insert into 表名 values(...),(...)...;
例:
insert into students values(0, '张飞', 55, 1.75, '男'),(0, '关羽', 58, 1.85, '男');

# 4. 部分列多行插入
insert into 表名(列1,...) values(值1,...),(值1,...)...;
例：
insert into students(name, height) values('刘备', 1.75),('曹操', 1.6);
```

说明：
- 主键列是自动增长，但是在全列插入时需要占位，通常使用空值(`0` 或者 `null` 或者 `default`)
- 在全列插入时，如果字段列有默认值可以使用 `default` 来占位，插入后的数据就是之前设置的默认值

3. 修改数据

```shell
update 表名 set 列1=值1, 列2=值2 ... where 条件
例：
update students set age = 18, gender = '女' where id = 6;
```

4. 删除数据

```shell
delete from 表名 where 条件
例：
delete from students where id=5;
```

问题：

上面的操作称之为物理删除，一旦删除就不容易恢复，我们可以使用逻辑删除的方式来解决这个问题。

```shell
# 添加删除表示字段，0 表示未删除 1 表示删除
alter table students add isdelete bit default 0;
# 逻辑删除数据
update students set isdelete = 1 where id = 8;
```

> 逻辑删除，本质就是修改操作

#### 1.5.4 客户端 SQL 语句小结

- 登录数据库: `mysql -uroot -p`

- 退出数据库: `quit` 或者 `exit` 或者 `ctr + d`

- 创建数据库: `create database 数据库名 charset=utf8;`;

- 使用数据库: `use 数据库名;`

- 删除数据库: `drop database 数据库名;`

- 创建表: `create table 表名(字段名 字段类型 约束, ...);`

- 修改表-添加字段: `alter table 表名 add 字段名 字段类型 约束`

- 修改表-修改字段类型: `alter table 表名 modify 字段名 字段类型 约束`

- 修改表-修改字段名和字段类型: `alter table 表名 change 原字段名 新字段名 字段类型 约束`

- 修改表-删除字段: `alter table 表名 drop 字段名;`

- 删除表: `drop table 表名;`

- 查询数据: `select * from 表名;` 或者 `select 列1, 列2, ... from 表名;`

- 插入数据: `insert into 表名 values (...)` 或者 `insert into 表名 (列1,...) values(值1,...)`

- 修改数据: `update 表名 set 列1=值1,列2=值2... where 条件`

- 删除数据: `delete from 表名 where 条件`

### 1.6 as 和 distinct 关键字
