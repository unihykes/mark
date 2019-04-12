RHEL 7.2 下是没有ifconfig 命令 , 如果需要查询IP及网卡设置，可以使用以下命令：
[root@localhost network-scripts]# ip addr
[root@localhost network-scripts]# pifconfig

网络配置：
[root@localhost network-scripts]# cd /etc/sysconfig/network-scripts/
[root@localhost network-scripts]# vi ifcfg-ens32

修改 以下内容
BOOTPROTO=static
ONBOOT=yes
IPADDR=192.168.xx.xx
GATEWAY=192.168.xx.xx
NETMASK=255.255.255.0

修改完成后 使用 重启网络服务
[root@localhost network-scripts]# systemctl  restart network


关闭防火墙：
http://jingyan.baidu.com/article/e52e3615a9009440c70c5162.html

RHEL7 单独安装图形 X11
RHEL7 默认是最小化安装（Minimal Install），没有图形界面，
yum -y groupinstall "Server with GUI"
安装好以后输入:startx查看是否成功
