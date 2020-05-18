配置客户端机器的yum源

1、将系统盘加载到光驱中（这种是临时方案重启后需要重新加载光驱ISO，如果想一劳永逸的话，直接把iso上传到linux机器里，然后将iso挂载到指定目录，这样重启后也可以用）
mkdir /media/cdrom
挂载光盘:     mount /dev/cdrom  /media/cdrom
挂载iso文件: mount /home/software/rhel-server-6.6-x86_64-dvd.iso  -o loop /media/cdrom
写入配置文件
	xx.iso /media iso9660 defaults,ro,loop 0 0 

2、确认是否安装以下软件包：
rpm -qa |grep yum
rpm -qa |grep createrepo


3、手动安装yum（可选，如果已安装则不需要）：
rpm -ivh yum-3.2.29-60.el6.noarch.rpm //版本号需要用cdrom中存在的
rpm -ivh yum-metadata-parser-1.1.2-16.el6.x86_64.rpm
rpm -ivh yum-rhn-plugin-0.9.1-50.el6.noarch.rpm

4、手动安装createrepo（可选，如果已经安装则不需要）：
rpm -ivh createrepo-0.9.9-22.el6.noarch.rpm   //版本号需要用cdrom中存在的
如果有错误，则按照提示先安装依赖包； 


5、添加文件cdrom.repo,内容如下：
vi /etc/yum.repos.d/cdrom.repo
(实际上，不新建/etc/yum.repos.d/cdrom.repo也是可以的。直接编辑系统自带的/etc/yum.repos.d/ rhel-source.repo.repo文件也可以。将内容添加到文件后面)
待添加内容如下:

    [CDROM]
    name=RHEL6.6 cdrom
    baseurl=file:///media/cdrom/
    enable=1
    gpgcheck=0
    gpgkey=file:///media/cdrom/RPM-GPG-KEY-redhat-release


5.1、补充：redhat6.6有些安装包是在光盘的HighAvailability和ResilientStorage目录下的，需要额外配置：
[CDROM-HA]
name=linux My yum HA
baseurl=file:///media/cdrom/HighAvailability
enabled=1
gpgcheck=0

[CDROM-ResilientStorage]
name=CDROM ResilientStorage
baseurl=file:///media/cdrom/ResilientStorage
enabled=1
gpgcheck=0





6、【可选】刷新yum缓存：
yum clean
yum makecache

7、测试yum是否可用，查看cdrom的软件包列表 
yum list |grep gcc

8、 补充，如果是redhat5.2，做完如上操作后，yum list可能会报错(yum仍然不可用)

则参考如下处理：
http://www.cnblogs.com/kerrycode/archive/2015/09/24/4835571.html


9、【可选】：关闭其他源，打开指定yum源（其实就是把除了指定源之外，其他的源配置文件里的enabled选项置为0）
yum --disablerepo=* --enablerepo=CDROM list



10、好了。之后可以用命令 yum -y install xxxxxx   直接安装软件了；




