
### LSM-tree
![](https://img-blog.csdnimg.cn/20190521200208933.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3UwMTA0NTQwMzA=,size_16,color_FFFFFF,t_70)
![](https://www.2cto.com/uploadfile/Collfiles/20141110/20141110091559148.jpg)

* 基于SSTable的存储引擎：
>1.当一条数据写入时，我们将其插入到基于内存的平衡树中（Red-black tree）。 内存中的树我们称之为Memtable。
2.当Memtable的大小超过一定阈值时，我们将Memtable Flush到磁盘，转为SSTable。
3.当我们查询时，需要同时查询内存中的Memtable和磁盘中的SSTable。
4.周期性的在后台进行异步的Merge和Compaction操作。
5.为了防止Memtable在Flush到磁盘前机器故障导致数据丢失，我们可以在磁盘上维护一个只追加写的log文件，称之为Write-Ahead-Log,当集群故障后可以从log中恢复出Memtable。 所以我们在每次写入Memtable，需要先写入WAL。当Memtable flush到磁盘后，对应的WAL文件就可以删除。
https://blog.bcmeng.com/post/lsm-tree-vs-b-tree.html
https://blog.csdn.net/u014774781/article/details/52105708
