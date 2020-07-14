参考资料：

Windows平台下Oracle RAC的安装与配置实验参考手册
https://wenku.baidu.com/view/cae933d628ea81c758f57875.html###

一步一步搭建oracle 11gR2 rac+dg之环境准备(二)
http://blog.itpub.net/26736162/viewspace-1290416/

Windows2008搭建oracle11g rac
http://blog.itpub.net/26217983/viewspace-1478139/
http://blog.csdn.net/zhaoxiaofei0929/article/details/36865283

vsphere中搭建共享存储：
http://www.linuxidc.com/Linux/2017-05/143879.htm





windows2008配置：
1.在vsphereESXi上搭建2个相同的win2008虚拟机；

2.搭建共享存储：
参考：http://www.linuxidc.com/Linux/2017-05/143879.htm
创建4个共享磁盘，分别为30G,32G,35G,36G(大小不同，方便区分。。)

3.win2008虚拟机配置
参考：http://blog.csdn.net/zhaoxiaofei0929/article/details/36865283

4.分别修改2个节点主机名为node1，node2

5.关闭2个win2008中的防火墙，关闭远程访问限制，设置网络，以便可以远程连接；
192.168.92.99
192.168.92.100

6.分别配置node1和node2的DEP以及关闭UAC；
计算机-属性-高级-性能设置；


控制面板-用户账户-打开或关闭“用户帐户控制”


7.配置虚拟内存；
计算机-属性-高级-性能设置-高级-虚拟内存
自定义虚拟内存大小-通常内存2倍，或为oracle推荐进行设置；


8.禁用媒体感知功能；
修改注册表：
HKEY_LOCAL_MACHINE/SYSTEM/CurrentControlSet/Services/Tcpip/Parameters/
新建一个DWORD值，命名为DisableDHCPMediaSense 值为1，如下图所示，需要重启后生效。
该配置项是oracle安装的一个检查项。


9.配置网络：
修改网卡名称为public和private

node1设置网络：
192.168.92.99
10.10.10.10

node2设置网络：
192.168.92.100
10.10.10.11



10.修改网卡优先级顺序；
将public上移，分别取消public和private的ipv6协议；




11.配置hosts文件；
分别在node1,node2两个节点配置本地hosts文件:
hosts文件的路径为：
C:\WINDOWS\System32\drivers\etc\hosts，
192.168.92.99       node1
192.168.92.100     node2

192.168.92.97      node1-vip
192.168.92.98     node2-vip

10.10.10.10        node1-private
10.10.10.11       node2-private

192.168.92.57   scan-cluster



12.重启一下电脑，使上面步骤的修改生效；


13.初始化共享磁盘：
node1依次联机并初始化磁盘；
node2进行联机操作即可；



14.创建裸设备磁盘分区
node1服务器上操作，开始—运行—cmd。
输入 Diskpart，在diskpart命令下输入：
automount enable 
开机自动挂载磁盘，该操作两节点都要做。


15.在node1上创建分区：

在node1上继续输入：
list disk 显示磁盘数量与名称。

在node1上依次创建4个磁盘的分区
Select disk 1 #选择磁盘，该磁盘用于CRS
Create part ext #创建扩展分区
Create part log #以全部空间创建逻辑分区

Select disk 2
Create part ext
Create part log

Select disk 3
Create part ext
Create part log

Select disk 4
Create part ext
Create part log






16.在node2上输入automount enable即可，无需再分区和格式化；


安装Oracle Database Grid Infrastructure


1.下载地址：
http://www.oracle.com/technetwork/cn/database/enterprise-edition/downloads/database12c-win64-download-2297732-zhs.html
winx64_12102_grid_1of2.zip
winx64_12102_grid_2of2.zip

2.将安装包上传到node1的一个本地分区上；
本例中只有一个C盘，则上传到C:\software\grid目录中；

3.环境检查：
cd C:\software\grid
runcluvfy stage -pre crsinst -n node1,node2 -verbose




4.在node1节点上，安装grid infrastructure
grid infrastructure只需要在一个节点上安装；
运行C:\software\grid\setup.exe
详细步骤参考如下链接的3.13节：
注意：先看一下下面的注意事项，12C和连接中的11g有些许不同；
http://blog.csdn.net/zhaoxiaofei0929/article/details/36865283

以上链接中一些未注明的注意事项：
4.1该页面的集群名称需要与之前修改hosts文件时，写入hosts中的名称一致；



4.2，这里选择这个选项使用本地共享磁盘：


4.3.设置密码: 
l542621126TODO



4.4.使用windows内置账户



4.5.勾选全部忽略


4.6：最后一步安装过程非常慢，非常慢，慢慢等；




安装数据库ASM磁盘组创建方式

1,打开asm管理工具：


创建2个DATA磁盘，并组合为一个磁盘组；







安装oracle软件

1.安装只在node1机器上进行操作。
2.将安装包copy到虚拟机中，点击setup；
3.按照文档安装完毕；
http://blog.csdn.net/zhaoxiaofei0929/article/details/36865283
4.在node2上已管理员权限执行：
C:\app\Administrator\product\12.1.0\dbhome_1\BIN\selecthome.bat

5.创建oracle rac数据库：
使用dbca创建rac数据库;名称：orcl





