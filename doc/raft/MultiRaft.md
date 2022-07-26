什么是 MultiRaft ？
https://blog.csdn.net/qq_38289815/article/details/107682089

MultiRaft 需要解决的问题
单个 Raft-Group 在 KV 的场景下存在一些弊端:

(1) 系统的存储容量受制于单机的存储容量（使用分布式存储除外）。

(2) 系统的性能受制于单机的性能（读写请求都由Leader节点处理）。

 

MultiRaft 需要解决的一些核心问题：

(1) 数据何如分片。

(2) 分片中的数据越来越大，需要分裂产生更多的分片，组成更多 Raft-Group。

(3) 分片的调度，让负载在系统中更平均（分片副本的迁移，补全，Leader 切换等等）。

(4) 一个节点上，所有的 Raft-Group 复用链接（否则 Raft 副本之间两两建链，链接爆炸了）。

(5) 如何处理 stale 的请求（例如 Proposal 和 Apply 的时候，当前的副本不是 Leader、分裂了、被销毁了等等）。

(6) Snapshot 如何管理（限制Snapshot，避免带宽、CPU、IO资源被过度占用）。

要实现一个 Multi-Raft 还是很复杂和很有挑战的一件事情。