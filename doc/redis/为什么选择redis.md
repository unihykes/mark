[toc]

# cached


## 可选开源框架

#### memcached
https://memcached.org/
单个value只能保存1MB的数据

#### redis
https://www.redis.net.cn/
Remote Dictionary Server
单个value的最大限制是1GB


#### 备注:
##### 区别:
redis单个value的最大限制是1GB，不像memcached只能保存1MB的数据
memcached所有的值均是简单的字符串，redis作为其替代者，支持更为丰富数据类型
Redis的速度比memcached快很多
redis可以持久化其数据

##### 分布式缓存技术PK：选择Redis还是Memcached？
https://www.jianshu.com/p/7c44168ce922

##### 在选择缓存时，什么时候选择redis，什么时候选择memcached
选择redis的情况：

复杂数据结构，value的数据是哈希，列表，集合，有序集合等这种情况下，会选择redis，因为memcache无法满足这些数据结构，最典型的的使用场景是，用户订单列表，用户消息，帖子评论等。

需要进行数据的持久化功能，但是注意，不要把redis当成数据库使用，如果redis挂了，内存能够快速恢复热数据，不会将压力瞬间压在数据库上，没有cache预热的过程。对于只读和数据一致性要求不高的场景可以采用持久化存储

高可用，redis支持集群，可以实现主动复制，读写分离，而对于memcache如果想要实现高可用，需要进行二次开发。

存储的内容比较大，memcache存储的value最大为1M。

选择memcache的场景：

纯KV，数据量非常大的业务，使用memcache更合适，原因是：

memcache的内存分配采用的是预分配内存池的管理方式，能够省去内存分配的时间，redis是临时申请空间，可能导致碎片化。

虚拟内存使用，memcache将所有的数据存储在物理内存里，redis有自己的vm机制，理论上能够存储比物理内存更多的数据，当数据超量时，引发swap，把冷数据刷新到磁盘上，从这点上，数据量大时，memcache更快

网络模型，memcache使用非阻塞的10复用模型，redis也是使用非阻塞的I。复用模型，但是redis还提供了一些非KV存储之外的排序，聚合功能，复杂的CPU计算，会阻塞整个I0调度，从这点上由于redis提供的功能较多，memcache更快些

线程模型，memcache使用多线程，主线程监听，worker子线程接受请求，执行读写，这个过程可能存在锁冲突。redis使用的单线程，虽然无锁冲突，但是难以利用多核的特性提升吞吐量。

## 缓存淘汰算法
LFU、LRU、ARC、FIFO、MRU

#### Redis有哪几种数据淘汰策略？
noeviction：返回错误当内存限制达到并且客户端尝试执行会让更多内存被使用的命令(大部分的写入指令，但DEL和几个例外)

allkeys-lru：尝试回收最少使用的键(LRU)，使得新添加的数据有空间存放。

volatile-lru：尝试回收最少使用的键(LRU)，但仅限于在过期集合的键，使得新添加的数据有空间存放。

allkeys-random：回收随机的键使得新添加的数据有空间存放。

volatile-random：回收随机的键使得新添加的数据有空间存放，但仅限于在过期集合的键。

volatile-ttl：回收在过期集合的键，并且优先回收存活时间(TTL)较短的键，使得新添加的数据有空间存放。



#### 如何保障数据库和redis缓存的一致性
[如何保障数据库和redis缓存的一致性](https://blog.csdn.net/ln152315/article/details/105169458?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromBaidu-1.control&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromBaidu-1.control)