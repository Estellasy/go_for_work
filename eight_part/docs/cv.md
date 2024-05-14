- 编程语言：熟悉 Golang，了解 GMP 调度模型、GC 原理、channel 与内存管理相关知识。
- 脚本语言：具有 Python 机器学习、深度学习、爬虫相关经验，熟悉 Python 脚本编写。
- 数据库：熟悉 MySQL 的基本原理和使用，了解索引、事务、锁机制。了解 Redis，了解内部数据结构、事务、内存淘汰策略等。
- 计算机网络和操作系统：了解 OSI 七层模型，熟悉 TCP/IP、HTTP 等常用网络协议。熟悉操作系统进程间通信、内存管理、文件管理相关知识。
- 工作流：熟悉 Linux 常用命令，了解 Git 常用命令。
- 自我评价：
  - 乐观开朗，待人平和真诚，在校期间多次参加数学建模竞赛，解决实际问题和快速学习新技术的能力较强，具有良好的沟通能力和团队合作精神。
  - 经常阅读英文论文和文档，英语六级成绩 521，其中阅读 200+。

**填坑**
- Redis 数据类型 持久化 事务 内存淘汰策略（0514）
- MySQL复习
- 项目相关（0515）
- Golang复习
- Linux复习（0515）
- Kafka八股文

bitcask是一种基于预写日志的高性能持久化存储引擎，用于存储key-value数据。本项目使用go语言实现了bitcask存储模型，实现了快速的写入、读取和删除操作，最多只需一次磁盘 i/o。
- 持久化：实现了数据持久化功能，确保数据的可靠性和可恢复性。实现了 bitcask模型的 merge方法，对旧 wal数据进行合并去重，清理无效数据，减少磁盘空间占用。
- 索引：基于 google/btree实现索引，实现高效、快速的数据访问，支持范围查找。
- 并发控制：使用读写锁，确保数据的一致性和并发访问的正确性。
- 性能优化：实现了 bitcask模型的 hint文件，采用 wal方式记录 key和索引，避免重启时全量加载所有数据构建内存索引，提高启动速度。


采用go语言实现的云存储系统，整合了腾讯云cos和minio集群，提供了文件上传和下载服务。
- 用户鉴权：整合了 gomail发送验证码和第三方 qq身份验证功能，支持验证码登录、密码登录和扫码登录。利用jwt进行会话管理，确保安全性和用户体验。
- 文件传输：实现了文件分块上传、断点续传和文件秒传功能。利用 goroutine和 channel处理文件分块和合并问题，使用 redis记录传输状态。
- 性能优化：基于批量消息处理思想，采用 kafka、batcher和 goroutine实现文件元信息的高并发处理。在生产端使用 batcher进行消息聚合，提高吞吐性能；在消费端使用多个 goroutine进行并发消费。