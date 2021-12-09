

## CAP
一个分布式系统最多只能同时满足一致性（Consistency）、可用性（Availability）和分区容错性（Partition tolerance）这三项中的两项。
https://baijiahao.baidu.com/s?id=1687697302388087668&wfr=spider&for=pc

## 一致性
最终一致性
线性一致性

## 数据偏斜
数据分区的目的是：将数据和查询负载均匀地分布在节点上。而如果数据分区不公平，则会出现某些分区的数据或查询比其他分区要多，我们称之为偏斜。
数据偏斜就使得分区效果变差，导致负载不均衡形成分区热点。


## 级联索引



## CRUSH算法介绍
CRUSH数据分布算法的全称是：Controlled, Scalable, Decentralized Placement of Replicated Data.


## 读后写的问题:
https://blog.csdn.net/u011832039/article/details/78924418?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link


## write-ahead logs
https://blog.csdn.net/chdhust/article/details/87545567