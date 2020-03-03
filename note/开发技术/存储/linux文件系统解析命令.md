注：以/dev/sdd1磁盘为例
1、格式化一个卷
mkfs.ext3   /dev/sdd1

2、查看卷的超级块和卷组描述符的信息
dumpe2fs  -h /dev/sda1 | less  （-h） 表示的是只查看超级块
dumpe2fs /dev/sdd1 | grep "journal"  查出跟journal相关的数据行，数据怎么处理自行定义


3、将卷的某几个数据块拿出来用winhex进行分析的方法
dd if=/dev/sdd1 bs=xxx skip=xxx count=xxx > /sdd1xxx.txt
bs 是设备卷的块大小。 skip 表示跳过多个块，注意块是从0编号开始的。
count 表示要读取多少个块 ，并将这些块从定向到sdd1xxx.txt的文件中，这样就可以把这个文件下载到windows 客户端进行winhex分析了。

4、查看journal日志块的数据信息，查看某个inode的数据信息
echo "stat <8>" | debugfs /dev/sdd1


5、用二进制显示卷的数据
hexdump -C -s 0x12344  -n 1024  /dev/sdd1 | less

6、灵活获取命令输出信息
dumpe2fs %s | grep -i superblock |awk {'print $4'}

7、mount 命令，如何设置默认的挂载文件系统类型
[root@yufei ~]# mount /dev/sdb1 /mnt
这里我没有指定文件系统的类型，为什么不指定也能被正确识别呢？主要是因为我们的系统中已经有了这些默认的类型驱动，那么我是怎么知道系统中到底有多少是默认的呢？你可以通过查看下面两个文件来得知。
/etc/filesystems：系统指定的默认挂载文件系统类型
/proc/filesystems：Linux系统已经加载的文件系统类型
这里面虽然是有了，但我怎么知道我的Linux系统有没有相关文件系统类型的驱动呢？我们可能通过 /lib/modules/$(uname -r)/kernel/fs/这个目录里面的信息来查看支持的文件系统驱动程序。
如果是在这之外的文件系统，就必需加上-t和相应的文件系统类型了。

8、查看文件所在的inode位置
在 Linux 系统中查看 inode 号可使用命令 stat 或 ls -i（若是 AIX 系统，则使用命令 istat）



