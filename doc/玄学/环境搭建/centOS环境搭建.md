```
头文件找不到
如果发现stropts.h文件找不到的错误，
用yum provides */stropts.h搜索文件被包含在哪个包里面，
搜到后，按照系统是32位还是64位选择安装包，然后用yum install 命令安装

各类.命令：
nl：与cat -n 相似，查看文件同时显示行号；
centOS下安装gc：yum -y install gcc*
centOS下安装g++：yum install gcc-c++
centOS下安装gdb：yum -y install gdb
centOS下安装glib：yum -y install glib*

centOS下安装e2fsprogs：yum -y install e2fsprogs*
常见安装包大杂烩：yum -y install ntp make openssl openssl-devel pcre pcre-devel libpng libpng-devel libjpeg-6b libjpeg-devel-6b freetype freetype-devel gd gd-devel zlib zlib-devel gcc gcc-c++ libXpm libXpm-devel ncurses ncurses-devel libmcrypt libmcrypt-devel libxml2 libxml2-devel imake autoconf automake screen sysstat compat-libstdc++-33 curl curl-devel

安装svn：参考 http://blog.chinaunix.net/uid-7198617-id-2676894.html
使用yum 安装SVN包
搭建svn服务器：svnadmin create /home/svn/code


如果yum失败：This system is not registered with RHN
红帽中出现This system is not registered with RHN这个的原因是因为红帽中没有注册RHN。
解决办法：（假定你已安装yum，且网络畅通）更改yum的源，即更换/etc/yum.repos.d /rhel-debuginfo.repo 这个文件。
进入/etc/yum.repos.d/目录，
终端中输入wget http://docs.linuxtone.org/soft/lemp/CentOS-Base.repo即可在此目录下得到CentOS- Base.repo文件，这是centos的源文件，只需将其重命名为rhel-debuginfo.repo即可，以前的文件做个备份。

网络问题:

无法ping通www.baidu.com：
无法进行socket：关闭linux防火墙：
chkconfig --level 2345 iptables off
 /etc/init.d/iptables stop

svn 网络不可达
修复网卡配置，直接抄100.204

connect: network is unreachable:

# ifconfig eth0 192.168.179.131 netmask 255.255.255.0 
# route add default gw 192.168.179.131

Destination Host Unreachable:
修改网卡配置：
cd /etc/sysconfig/network-scripts

无法启动Mysql服务：

/usr/local/mysql/support-files/mysql.server start


Redhat中文无法显示：
vi /etc/sysconfig/i18n
将内容改为
LANG="zh_CN.GB18030"
LANGUAGE="zh_CN.GB18030:zh_CN.GB2312:zh_CN"
SUPPORTED="zh_CN.GB18030:zh_CN:zh:en_US.UTF-8:en_US:en"
SYSFONT="lat0-sun16"
重新启动系统即可。

编译问题：
uuid.h找不到：安装e2fsprogs：
    RetHat直接用yum下载：yum -y install e2fsprogs*
    centOS如果yum失败在按照下面步骤：

    到网站：http://download.chinaunix.net/download/0003000/2490.shtml中下载 e2fsprogs-1.41.14.tar.gz 
        tar zxvf e2fsprogs-1.41.14.tar.gz 
        cd e2fsprogs-1.41.14
        ./configure –enable-elf-shlibs
        make
        make install
        cp -r lib/uuid/ /usr/include/
        cp -rf lib/libuuid.so* /usr/lib

error: ext/hash_fun.h: No such file or directory
修改abprec.h 160行：
#include <ext/hash_fun.h> 改成：#include <backward/hash_fun.h>

error: ‘::memset’ has not been declared
修改defs.h:在第一行加入#include <cstring>

error: ‘auto_ptr’ is not a member of ‘std’
修改文件：src\sharecmn\asautil\ncASAConnectManager.cpp
添加：#include<memory>  using namespace std；

文件权限不足：
提示权限不足时，修改相应的文件的权限值
chmod 777 *

提示libncutil.so needed：
找到相应文件（\src\console\sysutil\modifyclusterstatus\makefile.gcc）
makefile中添加NEED_NCUTIL

error: ldap.h: No such file or directory
yum -y install  cyrus-sasl*
yum -y install openldap*


注册组件问题:

Can not initialize XPCOM Glue
Can not aquire component registrar
尚未解决









```