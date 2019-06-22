```
让linux开机使用纯文本环境（run level 3）来登录，只需要修改/etc/inittab这个文件的内容；


查看内存             
top    
free -m

查看ip                
ifconfig

查看空间命令：   
df - h

下载文件：          
wget

磁盘格式化：             
mkfs.xfs -f /dev/sdf
mkfs.ext3  /dev/sdf


挂载：                
mount /dev/sdf    /usrvol/volume0（挂载前最好先格式化）
取消挂载：         
umount -l /dev/sdf
umount的时候如果提示程序正在使用该分区（device is bysy），可使用命令 fuser- km /home终止占用的进程

软链接：            
ln /etc/init.d  testDir （后面是连接，前面是真实路径）

链接目录：       
 ln -s /etc/init.d  testDir
取消软链接         
rm -fr xxx (没有/)


查看数据库：     
ps ax|grep mysql

查看内核版本          
uname -r  

查看linux版本：
cat /etc/issue

查看系统版本          
cat /etc/redhat-release

看目前谁在线：         
 who

查看网络联机状态
netstat -a

修改语言:
LANG=en_US

查询上一次登录执行过的命令
cat ~/.bash_history

查看命令的别名
alias

查询某命令的执行文件位置           
type -a ls (查看ls命令文件的位置)

获取随机数（0-32767）                   
echo $RANDOM

获取随机数（0-9）                       
declare -i number=$RANDOM*10/32768; echo $number

查询本shell的PID                       
echo $$


查询上一个命令的回传码                 
echo $?

定义环境变量                               
declare -x XXXXX

登录bash后设置platform环境变量              
vim /etc/profile

查找字符串                                 
| grep -n --color=auto 'xxx'

查看系统所有的进程数据                 
ps aux
ps -lA

查看系统所有进程数据连同进程树状态     
ps axjf

显示进程树                                  
pstree -Ap

查看系统启动时间与工作负载             
uptime

跟踪网络                               
netstat

分析内核产生的信息                     
dmesg

查找被进程打开的文件名                 
lsof

设置自己的系统服务                         
chkconfig --add xxx

创建raid5                                  
mdadm --create --auto=yes /dev/md0 --level=5 --raid-devices=4 --spare-devices=1 /dev/sdb /dev/sdc /dev/sdd /dev/sde /dev/sdf

查询已启动的网络监听服务：                  
netstat -tulnp

查询主机路由表
route -n
     Destination：就是Network的意思
     Gateway：就是该接口的gateway的IP,若为0.0.0.0则表示不需要额外的IP
     Genmask：就是Netmask，与Destination组合成为一台主机或网络
     Flags：多个标志可以表示该网络或者主机表还是的意思
               U表示路由可用
               G表示该网络需要经由Gateway来帮忙转递
               H表示该行路由为一台主机，而非一整个网络
     Iface：就是Interface的意思，表示要去到Destination要使用哪一个网络接口

查询系统服务端口：
linux环境下，各网络服务于port的对于默认写在/etc/services文件内

通过内核查询网卡信息
dmesg |grep -in eth

查询内核是否已经加载了网卡
lsmod |grep e1000 （e1000是用dmesg查询出的网卡模块）

查询网卡模块信息
modinfo e1000
得到的结果中，filename即为驱动程序放置的目录

网络配置文件
/etc/sysconfig/network-scripts/ifcfg-eth0
     DEVICE=网卡的名称
     BOOTPROTO=是否使用dhcp
     HWADDR=是否加入网卡MAC地址
     IPADDR=IP地址
     NETMASK=子网掩码
     ONBOOT=要不要默认启动此接口
     GATEWAY=网关地址
     NM_CONTROLED=额外的网管软件

主机名配置文件
/etc/sysconfig/network
     NETWORKING=要不要使用网络
     NETWORKING_IPV6=是否支持IPv6
     HOSTNAME=主机名

DNS IP配置文件
/etc/resolv.conf
     Name Server DNS的IP地址    

私有IP对应的主机名
     /etc/hosts
          私有IP   主机名   别名

重启整个网络
/etc/init.d/network restart

启动/关闭某个网络接口
ifup eth0
ifdown eth0

手动配置网络（IP等）
首先修改/etc/sysconfig/network-scripts/ifcfg-eth0
然后调用/etc/init.d/network restart
然后检查IP参数：ifconfg eth0
然后检查路由定义：route -n
然后检查能否连接路由：ping -c 3 192.168.xx.xx (Geteway)

修改主机名：
vi /etc/sysconfig/network
vi /etc/hosts

添加虚拟IP
ifconfig etho:0 192.168.xx.xx
关闭虚拟ip
ifconfig eth0:0 down

显示所有IP的参数
ip address show

文字浏览器：
links
links http://192.168.179.xx

文字接口下载器：
wget
wget http://192.168.179.xx

sshd服务器配置
配置文件在/etc/ssh/sshd_config配置文件内








```