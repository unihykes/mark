linux 从一台机器复制文件到另一台linux机器上去

1、功能说明
scp就是security copy，用于将文件或者目录从一个Linux系统拷贝到另一个Linux系统下。scp传输数据用的是SSH协议，保证了数据传输的安全，其格式如下：
scp 远程用户名@IP地址:文件的绝对路径 本地Linux系统路径
scp 本地Linux系统文件路径 远程用户名@IP地址：远程系统文件绝对路径名
scp使用第一种格式是将远程Linux系统上的某个文件或者目录拷贝到本地Linux系统上来，使用第二种是将本地的某个文件或者目录拷贝到远程Linux系统的某个路径下。
2、举例
（1）目前我们处在IP为“192.168.60.133”的Linux系统下，计划将系统下的/home/ixdba/etc.tar.gz文件拷贝到IP为“192.168.60
168”的远程Linux系统中root用户下的/tmp目录下：
scp /home/ixdba/etc.tar.gz root@192.168.60.168:/tmp
命令输入完毕，会要求输入“192.168.60.168”服务器root的密码，然后开始远程拷贝数据。
如果我们处在“192.168.60.168”服务器上，也可以使用下面的命令传输数据：
scp root@192.168.60.133:/home/ixdba/etc.tar.gz /tmp
命令输入完毕，此时会要求输入“192.168.60.133”服务器root的密码，然后开始远程拷贝数据。
例如：scp ./id_rsa.pub jing.wei@10.28.8.20:/home/jing.wei
进入一个服务器将当前目录下id_rsa.pub拷贝到另一个服务器。

（2）将本地/etc目录中所有的文件和子目录拷贝到IP为“192.168.60.135”的远程Linux系统的root用户下的/opt目录中：
scp -r /etc root@192.168.60.135:/opt
这里的选项“r”与cp命令的“r”选项含义相同。



加端口号:
scp -P 5557    /six-th/a.out    eisoo_ssh@192.168.92.57:/six-th



