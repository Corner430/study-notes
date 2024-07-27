# MongoDB 学习笔记

1. [NoSQL 简介](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md)
   1. [关系型数据库遵循 ACID 规则](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#11-关系型数据库遵循-acid-规则)
   2. [RDBMS vs NoSQL](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#12-rdbms-vs-nosql)
   3. [CAP 定理（CAP Theorem）](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#13-cap-定理cap-theorem)
   4. [BASE 理论](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#14-base-理论)
   5. [ACID vs BASE](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#15-acid-vs-base)
   6. [NoSQL 数据库分类](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/01.NoSQL简介.md#16-nosql-数据库分类)
2. [MongoDB 简介](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/02.MongoDB简介.md)
   1. [特点](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/02.MongoDB简介.md#21-特点)
3. [MongoDB 概念解析](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/03.MongoDB概念解析.md)
   1. [完整术语列表](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/03.MongoDB概念解析.md#31-完整术语列表)
4. [MongoDB 的安装](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md)
   1. [在主机安装和启动 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#41-在主机安装和启动-mongodb)
      1. [安装 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#411-安装-mongodb)
      2. [启动 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#412-启动-mongodb)
      3. [连接 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#413-连接-mongodb)
      4. [允许外网访问 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#414-允许外网访问-mongodb)
      5. [查看 mongodb 连接数](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#415-查看-mongodb-连接数)
   2. [在 docker 安装 mongodb](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#42-在-docker-安装-mongodb) 
      1. [默认配置启动](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#421-默认配置启动) 
      2. [自定义配置文件启动](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#422-自定义配置文件启动)
      3. [docker-compose 命令启动，同时启动 mongodb 管理界面服务](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/04.MongoDB的安装.md#423-docker-compose-命令启动同时启动-mongodb-管理界面服务)
5. [MongoDB 账号管理](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/05.MongoDB账号管理.md)
   1. [创建管理员](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/05.MongoDB账号管理.md#51-创建管理员)
   2. [创建自定义用户](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/05.MongoDB账号管理.md#52-创建自定义用户)
   3. [查看已经创建的用户](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/05.MongoDB账号管理.md#53-查看已经创建的用户)
   4. [删除用户](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/05.MongoDB账号管理.md#54-删除用户)
6. [MongoDB 增删查改](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md)
   1. [数据类型](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#61-数据类型)
      1. [BSON](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#611-bson)
      2. [ObjectId](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#612-objectid)
   2. [新增数据](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#62-新增数据)
   3. [查询数据](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#63-查询数据)
      1. [基本 API](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#631-基本-api)
      2. [等值查询](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#632-等值查询)
      3. [范围查询](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#633-范围查询)
      4. [逻辑查询](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#634-逻辑查询)
      5. [集合查询](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#635-集合查询)
      6. [额外操作](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#636-额外操作)
   4. [修改数据](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#64-修改数据)
      1. [基本 API](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#641-基本-api)
      2. [常规修改器](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#642-常规修改器)
      3. [数组修改器](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#643-数组修改器)
   5. [删除数据](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/06.MongoDB增删查改.md#65-删除数据)
7. [MongoDB 索引](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/07.MongoDB索引.md)
   1. [索引简介](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/07.MongoDB索引.md#71-索引简介)
      1. [创建索引](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/07.MongoDB索引.md#711-创建索引)
      2. [查看索引](https://github.com/Corner430/study-notes/blob/main/数据库/MongoDB/07.MongoDB索引.md#712-查看索引)
   2. 索引的类型
      1. 单字段索引
      2. 复合索引
      3. 多键索引
      4. 哈希索引
      5. 地理空间索引
      6. 文本索引
   3. 索引的性质
      1. 唯一索引
      2. 稀疏性
      3. 部分索引
      4. TTL 索引
   4. 删除索引
   5. EXPLAIN
      1. 输出参数
      2. 覆盖索引
8. MongoDB 聚合
   1. 聚合简述
   2. 聚合管道
      1. `$match`
      2. `$project`
      3. `$group`
      4. `$unwind`
      5. `$sort`
      6. `$limit`
      7. `$skip`
      8. `$lookup`
         1. 关联查询
         2. 非相关查询
      9. `$out`
      10. 自动优化
   3. MapReduce
   4. 单用途聚合方法
      1. `count`
      2. `estimatedDocumentCount`
      3. `distinct`
9. MongoDB 复制
   1. 副本集
      1. 复制功能
      2. 仲裁者
   2. 故障发现与恢复
      1. 故障发现
      2. 优先选举
      3. 投票成员
   3. 搭建副本集
      1. 下载并解压
      2. 配置环境变量
      3. 修改配置
      4. 启动服务
      5. 配置副本集
      6. 查看副本集情况
10. MongoDB 分片
    1. 分片机制
       1. 核心组件
       2. 分片键
       3. 分片策略
       4. 块拆分
       5. 数据查询
       6. 非分片集合
    2. 集群搭建
       1. 分片副本集配置
       2. 配置副本集配置
       3. 路由服务配置
       4. 配置分发
       5. 启动分片和配置服务
       6. 初始化所有副本集
       7. 启动路由服务
       8. 测试分片
11. 数据备份与恢复
    1. mongoexport 导出 json/csv 结构化数据
    2. mongoimport 导入 json/csv 结构化数据
    3. mongodump 导出二进制数据
    4. mongorestore 导入二进制数据
12. MongoDB 的其它
    1. 获取 mongodb 状态信息
    2. 非正常关闭 mongodb 导致无法启动的解决方法

# 参考资料

- [官方文档](https://www.mongodb.com/zh-cn/docs/)
- [官方配置说明](https://docs.mongodb.com/manual/reference/configuration-options/)
