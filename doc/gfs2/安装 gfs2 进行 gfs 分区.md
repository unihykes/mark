安装 gfs2 进行 gfs 分区

安装 gfs2 进行 gfs 分区
[root@Aries ~]# for i in 1 2 3 ; do ssh node${i}.lansgg.com 'yum -y install gfs2-utils' ;done

使用gfs2命令工具在之前创建好的/dev/sdb1上创建集群文件系统gfs2，可以使用如下命令
[root@node1 ~]# mkfs.gfs2 -j 3 -p lock_dlm -t testCluster:sdb1 /dev/sdb1

mkfs.gfs2为gfs2文件系统创建工具，其一般常用的选项有：

-b BlockSize：指定文件系统块大小，最小为512，默认为4096；

-J MegaBytes：指定gfs2日志区域大小，默认为128MB，最小值为8MB；

-j Number：指定创建gfs2文件系统时所创建的日志区域个数，一般需要为每个挂载的客户端指定一个日志区域；有几个node节点就要指定几个


-p LockProtoName：所使用的锁协议名称，通常为lock_dlm或lock_nolock之一；

-t LockTableName：锁表名称，一般来说一个集群文件系统需一个锁表名以便让集群节点在施加文件锁时得悉其所关联到的集群文件系统，锁表名称为 clustername:fsname，其中的clustername必须跟集群配置文件中的集群名称保持一致，因此，也仅有此集群内的节点可访问此集群 文件系统；此外，同一个集群内，每个文件系统的名称必须惟一。



新建目录进行文件系统挂载
[root@Aries ~]# for i in 1 2 3 ; do ssh node${i}.lansgg.com 'mkdir /test ' ;done
[root@node1 ~]# mount /dev/sdb1 /test/
[root@node1 ~]# echo "test" > /test/test.tt

如果分区无法识别，可以重启系统尝试

挂载gfs分区，查看是否存在node1上创建的text.tt
[root@Aries ~]# for i in  2 3 ; do ssh node${i}.lansgg.com 'mount /dev/sdb1 /test/ ; cat /test/test.tt ' ;done
test
test
