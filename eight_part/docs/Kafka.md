# Kafka 消息队列
## Kafka介绍
### 1. Kafka是什么
```
kafka使用scala开发，支持多语言客户端（c++、java、python、go等）
Kafka最先由LinkedIn公司开发，之后成为Apache的顶级项目。
Kafka是一个分布式的、分区化、可复制提交的日志服务
LinkedIn使用Kafka实现了公司不同应用程序之间的松耦和，那么作为一个可扩展、高可靠的消息系统
支持高Throughput的应用
scale out：无需停机即可扩展机器
持久化：通过将数据持久化到硬盘以及replication防止数据丢失
支持online和offline的场景
```

### 2. Kafka特性
kafka是分布式的，其所有的构件，如broker（服务端集群）、producer（消息生产）、consumer（消费者）都可以是分布式的。

在消息生产时可以使用一个标识topic区分，并且进行分区。**每一个分区都是顺序的、不可改变的消息队列**，并且可以持续添加。

kafka同时为发布和订阅提供高吞吐量，kafka每秒可以生产约25w消息（50MB），每秒处理55w消息（110MB）。

消息被处理的状态在consumer中维护，而不是由server维护，当失败时能自动平衡。

**kafka的关键功能**
- 发布（写入）和订阅（读取）事件流，包括从其他系统持续导入/导出数据。
- 根据需要持久可靠地存储事件流。
- 在事件发生时或回顾性地处理事件流。

### 3. 常用场景
- 监控：主机通过kafka发送与系统和应用程序健康相关的指标，然后这些信息会被收集和处理，从而创建监控仪表盘并发送警告。
- 消息队列：应用程序使用kafka作为传统的消息系统实现标准的队列和消息的发布-订阅，例如搜索和内容提要。比起大多数消息系统来说，kafka拥有**更高的吞吐量，内置的分区、冗余和容错性**，使得kakfa成为一个很好的大规模消息处理应用的解决方案。消息系统一般吞吐量相对较低，但是需要更小的端到端延迟，并且常依赖于kafka提高的强大的持久性保障。在这一领域，kafka足以媲美传统消息系统，如rabbitmq和activeMR。
- 站点的用户活动追踪: 为了更好地理解用户行为，改善用户体验，将用户查看了哪个页面、点击了哪些内容等信息发送到每个数据中心的Kafka集群上，并通过Hadoop进行分析、生成日常报告。

> **常见消息队列的对比**

## Kafka深层介绍

## Kafka安装

## 操作Kafka

## 消息队列面试题

# Kafka速成教程
1. 什么是Kafka

Kafka最初由Linkedin开发，是一个开源**分布式处理流平台**，由scala和java编写。

2. 生产者和消费者机制

kafka通过zookeeper管理集群元数据。

在Kafka中，生产者producer负责将消息发送给broker，broker将生产者发送的消息存储到磁盘中。生产者推送消息采用push。

消费者consumer负责从broker中订阅并读取消息，消费者拉取消息采用pull。

![](./Pasted%20image%2020240516203329.png)

3. Kafka的producer生产者发送broker分区策略

发布订阅的对象主题是Topic，生产者将消息发送到指定的Topic，消费者负责对订阅的Topic进行消费。

kafka中，将Topic划分为多个partition，每个partition又有多个副本。

在同一Topic下，不同partion中的消息是不一样的。生产者生产出来的每一条消息只能发送到一个partition中，kafka的分区编号从0开始，如果生产者向具有两个partition的Topic发送消息，生产者会随机选择一个partition进行发送。

**如何将消息发送到指定分区**

在生产者的发送逻辑中，可以指定分区。

有一个数据结构叫做ProducerRecord，即发送给Broker的key/value键值对，封装基础数据信息，简称PR。

PR的内部结构如下
```
Topic 
PartitionID （可选）
Key （可选）
Value
```

**生产者发送逻辑**
- 如果指定了PartitionID，PR就会被发送到指定的Partition中；
- 如果没有指定PartitionID，但是指定了Key，PR会按照hash(key)发送到对应partition中；
- 如果都没有指定，会按照默认的round-robin轮询发送到每一个partition中；
- 如果同时指定partition id和key，会优先partitionid。

Partition有多个副本，但是只有一个replication leader负责partitoin和生产者消费者交互。

**生产者到Broker的发送流程**

kafka的客户端发送数据到服务器中，会经过内存缓冲区。通过KafkaProducer发送出去的消息先进入到客户端的本地缓存中，然后将消息收集到Batch中，当Batch中消息达到一定数量或者消息的等待时间达到一定阈值，就会将Batch中的消息发送到服务器中。

**生产者常见配置**
- bootstrap.servers  // broker地址
- acks      // 生产者发送消息后，服务端需要给生产者一个响应，生产者根据响应来决定是否发送下一条消息，默认是0，表示生产者不需要等待服务端的响应，只管发送消息，服务端不保证不丢失消息，消息丢失后，生产者会重新发送消息，默认是1，表示生产者需要等待服务端的响应，只有当服务端响应成功，生产者才会发送下一条消息，默认是all，表示生产者需要等待服务端的响应，只有当服务端所有副本都成功写入消息，生产者才会发送下一条消息。
- batch.size     // 每个分区未发送消息总字节大小，超过设置的值就会提供给服务端，默认值是16KB
- linger.ms     // 默认值是0，如果batch被填满或者linger.ms达到上限，满足其中一个就会被发送
- buffer.memory  // 内存缓冲区大小
- key.serializer // key序列化
- value.serializer // value序列化

4. Kafka Comsumer消费者机制和分区策略

**消费者根据什么模式从broker中获取数据**

消费者采用pull拉取方式从broker的partition中获取数据。

为什么是pull而不是push，是因为pull的话，消费者可以根据自己的消费能力灵活进行调整。
如果是push，则优点为可以快速处理，但是可能会造成消息堆积和延迟。

**消费者该从哪个分区进行消费**

# 八股文

**Kafka 都有哪些特点？**

高吞吐量、低延迟：kafka每秒可以处理几十万条消息，它的延迟最低只有几毫秒，每个topic可以分多个partition, consumer group 对partition进行consume操作。

可扩展性：kafka集群支持热扩展

持久性、可靠性：消息被持久化到本地磁盘，并且支持数据备份防止数据丢失

容错性：允许集群中节点失败（若副本数量为n,则允许n-1个节点失败）

高并发：支持数千个客户端同时读写

**那些场景会选择kafka**
- 日志收集
- 消息系统：解耦生产者和消费者，缓存消息等
- 用户活动跟踪
- 流式处理

**Kafka 的设计架构你知道吗？**
Kafka 架构分为以下几个部分：

Producer ：消息生产者，就是向 kafka broker 发消息的客户端。
Consumer ：消息消费者，向 kafka broker 取消息的客户端。
Topic ：可以理解为一个队列，一个 Topic 又分为一个或多个分区，
Consumer Group：这是 kafka 用来实现一个 topic 消息的广播（发给所有的 consumer）和单播（发给任意一个 consumer）的手段。一个 topic 可以有多个 Consumer Group。
Broker ：一台 kafka 服务器就是一个 broker。一个集群由多个 broker 组成。一个 broker 可以容纳多个 topic。
Partition：为了实现扩展性，一个非常大的 topic 可以分布到多个 broker上，每个 partition 是一个有序的队列。partition 中的每条消息都会被分配一个有序的id（offset）。将消息发给 consumer，kafka 只保证按一个 partition 中的消息的顺序，不保证一个 topic 的整体（多个 partition 间）的顺序。
Offset：kafka 的存储文件都是按照 offset.kafka 来命名，用 offset 做名字的好处是方便查找。例如你想找位于 2049 的位置，只要找到 2048.kafka 的文件即可。当然 the first offset 就是 00000000000.kafka。

**Kafka 分区的目的**

对于kafka集群的好处，实现负载均衡；对于消费者来说，提高并发度，提高效率。

**kafka如何做到消息的有序性**

每个partition都是有序的，每个partition只能由一个消费者消费。

**kafka producer的执行过程**

1. Producer生产消息
2. 从zookeeper中找到partition的leader
3. push消息
4. 通知follower
5. follower同步leader，并发送ack
6. leader收到所有副本的ack，更新offset，并向producer发送ack，表示消息写入成功

**kafka consumer消费消息时的线程模型**

https://www.nowcoder.com/discuss/484653437561450496