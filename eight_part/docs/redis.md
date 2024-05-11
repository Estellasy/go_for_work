# Redis

## 基础
### 1. 什么是Redis
Redis(**Re**mote **Di**ctionary **S**erver)是一个开源的使用ANSI C语言编写、支持网络、可基于内存亦可持久化的日志型、Key-Value数据库，并提供多种语言的API。

Redis的Value支持：
- string
- hash
- list
- set
- zset
- bitmaps
- hyperloglog
- geo

**Redis和MySQL的区别**
- Redis：数据存储在内存中的NoSQL数据库，读写性能好，使用最广泛的中间件；
- MySQL：数据存储在硬盘中的关系型数据库，读写性能差，适合事务支持和复杂查询的场景。

**Redis和Memcached的区别**
- Redis：支持数据的持久化，可以将内存中的数据保存在磁盘中，重启的时候可以再次加载进行使用；
- Memcached：支持数据的持久化，可以将内存中的数据保存在磁盘中，重启的时候可以再次加载进行使用；
- Redis：不仅仅支持简单的k/v类型的数据，同时还提供list，set，zset，hash等数据结构的存储；

### 2. 特性
- 支持数据持久化
- 支持事务
- 支持主从复制
- 支持过期键删除
- 支持发布订阅
- 支持Lua脚本
- 支持多种集群方案

### 3. 数据类型