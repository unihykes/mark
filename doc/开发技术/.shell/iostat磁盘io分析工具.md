转:https://www.cnblogs.com/jiujuan/p/9027265.html

一：简介#
iostat（I/O statistics）输入输出缩写，用来动态监视系统的磁盘操作活动。它能监视磁盘的活动统计情况，同时也能监视CPU的活动情况。缺点是，iostat不能对某一个具体的进程进行深入的分析，仅仅是对系统整体情况进行分析。
iostat属于sysstat包。 centos下安装
yum install sysstat
二：iostat -help#

# iostat -help
Usage: iostat [ options ] [ <interval> [ <count> ] ]
Options are:
[ -c ] [ -d ] [ -h ] [ -k | -m ] [ -N ] [ -t ] [ -V ] [ -x ] [ -y ] [ -z ]
[ -j { ID | LABEL | PATH | UUID | ... } ]
[ [ -T ] -g <group_name> ] [ -p [ <device> [,...] | ALL ] ]
[ <device> [...] | ALL ]

用法
iostat [参数] [时间] [次数]
iostat -d 2 3 # 每2秒钟显示磁盘的使用情况，显示3次
三：命令参数#
-c 仅显示CPU使用情况
-d 仅显示磁盘使用情况
-k 以KB为单位显示
-m 以M为单位显示
-N 显示磁盘阵列(LVM)信息
-n 显示NFS使用情况
-p [磁盘]显示磁盘和分区的情况
-t 显示终端和CPU的信息
-x 显示详细信息
-V 显示版本信息
四：实例#
1：iostat -x#

# iostat -x
avg-cpu: %user %nice %system %iowait %steal %idle
0.45 0.00 0.33 0.39 0.00 98.83
Device: rrqm/s wrqm/s r/s w/s rkB/s wkB/s avgrq-sz avgqu-sz await r_await w_await svctm %util
vda 0.00 2.70 0.03 4.04 0.35 28.81 14.33 0.09 21.79 32.90 21.72 1.26 0.51

cpu属性值说明：
%user：CPU处在用户模式下的时间百分比。
%nice：CPU处在带NICE值的用户模式下的时间百分比。
%system：CPU处在系统模式下的时间百分比。
%iowait：CPU等待输入输出完成时间的百分比。
%steal：管理程序维护另一个虚拟处理器时，虚拟CPU的无意识等待时间百分比。
%idle：CPU空闲时间百分比。

注：如果%iowait的值过高，表示硬盘存在I/O瓶颈，%idle值高，表示CPU较空闲，如果%idle值高但系统响应慢时，有可能是CPU等待分配内存，此时应加大内存容量。%idle值如果持续低于10，那么系统的CPU处理能力相对较低，表明系统中最需要解决的资源是CPU。
 
disk属性值：
rrqm/s: 每秒进行 merge 的读操作数目。即 rmerge/s
wrqm/s: 每秒进行 merge 的写操作数目。即 wmerge/s
r/s: 每秒完成的读 I/O 设备次数。即 rio/s
w/s: 每秒完成的写 I/O 设备次数。即 wio/s
rkB/s: 每秒读K字节数。
wkB/s: 每秒写K字节数。
avgrq-sz: 平均每次设备I/O操作的数据大小 (扇区)。
avgqu-sz: 平均I/O队列长度。
await: 平均每次设备I/O操作的等待时间 (毫秒)。
svctm: 平均每次设备I/O操作的服务时间 (毫秒)。
%util: 一秒中有百分之多少的时间用于 I/O 操作，即被io消耗的cpu百分比

备注：如果 %util 接近 100%，说明产生的I/O请求太多，I/O系统已经满负荷，该磁盘可能存在瓶颈。如果 svctm 比较接近 await，说明 I/O 几乎没有等待时间；如果 await 远大于 svctm，说明I/O 队列太长，io响应太慢，则需要进行必要优化。
如果avgqu-sz比较大，也表示有当量io在等待。
2：定时显示所有信息#

# iostat 2 3 
avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.45    0.00    0.33    0.39    0.00   98.83

Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
vda               4.07         0.35        28.81    1967413  164198228

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.50    0.00    0.00    0.50    0.00   98.99

Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
vda              49.75         0.00       225.13          0        448

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.50    0.00    0.00    0.00    0.00   99.50

Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
vda               0.00         0.00         0.00          0          0

3：显示指定磁盘细信息#
# iostat -d vda
Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
vda               4.07         0.35        28.81    1967413  164201088
4：以m为单位显示信息#

# iostat -m
avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.45    0.00    0.33    0.39    0.00   98.83

Device:            tps    MB_read/s    MB_wrtn/s    MB_read    MB_wrtn
vda               4.07         0.00         0.03       1921     160354

5：查看tps和吞吐量#
# iostat -d -k 1 1
Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
vda               4.07         0.35        28.81    1967417  164204704
tps：该设备每秒的传输次数（Indicate the number of transfers per second that were issued to the device.）。“一次传输”意思是“一次I/O请求”。多个逻辑请求可能会被合并为“一次I/O请求”。“一次传输”请求的大小是未知的
kB_read/s：每秒从设备（drive expressed）读取的数据量
kB_wrtn/s：每秒向设备（drive expressed）写入的数据量
kB_read：读取的总数据量；kB_wrtn：写入的总数量数据量
6：查看cpu状态#

#  iostat -c 1 2
avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.45    0.00    0.33    0.39    0.00   98.83

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           2.00    0.00    2.00    3.00    0.00   93.00

7：查看设备使用情况%util和响应时间await#
#iostat -d -x -k 1 1

Device:  rrqm/s   wrqm/s    r/s     w/s    rkB/s  wkB/s  avgrq-sz avgqu-sz  await  svctm  %util
vda       0.02     7.25    0.04    1.90     0.74   35.47  37.15    0.04      19.13   5.58   1.09
rrqm/s： 每秒进行 merge 的读操作数目.即 delta(rmerge)/s
wrqm/s： 每秒进行 merge 的写操作数目.即 delta(wmerge)/s
r/s： 每秒完成的读 I/O 设备次数.即 delta(rio)/s
w/s： 每秒完成的写 I/O 设备次数.即 delta(wio)/s
rkB/s： 每秒读K字节数
wkB/s： 每秒写K字节数
avgrq-sz：平均每次设备I/O操作的数据大小 (扇区)
avgqu-sz：平均I/O队列长度.即 delta(aveq)/s/1000 (因为aveq的单位为毫秒)
await： 平均每次设备I/O操作的等待时间 (毫秒).即 delta(ruse+wuse)/delta(rio+wio)
svctm： 平均每次设备I/O操作的服务时间 (毫秒).即 delta(use)/delta(rio+wio)
%util： 一秒中有百分之多少的时间用于 I/O 操作,或者说一秒中有多少时间 I/O 队列是非空的，即 delta(use)/s/1000 (因为use的单位为毫秒)
 
如果 %util 接近 100%，说明产生的I/O请求太多，I/O系统已经满负荷，该磁盘可能存在瓶颈。 idle小于70% IO压力就较大了，一般读取速度有较多的wait。 同时可以结合vmstat 查看查看b参数(等待资源的进程数)和wa参数(IO等待所占用的CPU时间的百分比，高过30%时IO压力高)。
另外 await 的参数也要多和 svctm 来参考。差的过高就一定有 IO 的问题。
avgqu-sz 也是个做 IO 调优时需要注意的地方，这个就是直接每次操作的数据的大小，如果次数多，但数据拿的小的话，其实 IO 也会很小。如果数据拿的大，才IO 的数据会高。
svctm 一般要小于 await (因为同时等待的请求的等待时间被重复计算了)，svctm 的大小一般和磁盘性能有关，CPU/内存的负荷也会对其有影响，请求过多也会间接导致 svctm 的增加。await 的大小一般取决于服务时间(svctm) 以及 I/O 队列的长度和 I/O 请求的发出模式。如果 svctm 比较接近 await，说明 I/O 几乎没有等待时间；如果 await 远大于 svctm，说明 I/O 队列太长，应用得到的响应时间变慢，如果响应时间超过了用户可以容许的范围，这时可以考虑更换更快的磁盘，调整内核 elevator 算法，优化应用，或者升级 CPU。
队列长度(avgqu-sz)也可作为衡量系统 I/O 负荷的指标，但由于 avgqu-sz 是按照单位时间的平均值，所以不能反映瞬间的 I/O 洪水。
 
形象的比喻：
r/s+w/s 类似于交款人的总数
平均队列长度(avgqu-sz)类似于单位时间里平均排队人的个数
平均服务时间(svctm)类似于收银员的收款速度
平均等待时间(await)类似于平均每人的等待时间
平均I/O数据(avgrq-sz)类似于平均每人所买的东西多少
I/O 操作率 (%util)类似于收款台前有人排队的时间比例
设备IO操作:总IO(io)/s = r/s(读) +w/s(写)
平均等待时间=单个I/O服务器时间*(1+2+...+请求总数-1)/请求总数
每秒发出的I/0请求很多,但是平均队列就4,表示这些请求比较均匀,大部分处理还是比较及时。
作者：九卷
出处：https://www.cnblogs.com/jiujuan/p/9027265.html
本站使用「CC BY 4.0」创作共享协议，转载请在文章明显位置注明作者及出处。