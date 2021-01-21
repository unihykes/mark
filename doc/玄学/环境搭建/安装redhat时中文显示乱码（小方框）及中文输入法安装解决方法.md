安装CentOS的时候选择了中文，结果在终端不能显示中文，都是乱码，

```
解决方法：修改/etc/sysconfig/i18n,内容为

LANG="zh_CN.GB18030"
LANGUAGE="zh_CN.GB18030:zh_CN.GB2312:zh_CN"
SUPPORTED="zh_CN.UTF-8:zh_CN:zh:en_US.UTF-8:en_US:en"
SYSFONT="lat0-sun16"
退出重新登录即可
测试方法：在终端输入 date 命令测试，如果显示为以下形式,则说明成功解决了


如果系统中没有中文字体,请安装中文字体:

#yum install fonts-chinese.noarch

如果字体文件找不到,也可以用rpm包安装

需要两个中文支持的包：
fonts-chinese-3.02-12.el5.noarch.rpm
ftp://ftp.muug.mb.ca/mirror/centos/5.4/os/x86_64/CentOS/fonts-chinese-3.02-12.el5.noarch.rpm

fonts-ISO8859-2-75dpi-1.0-17.1.noarch.rpm
ftp://ftp.muug.mb.ca/mirror/centos/5.4/os/x86_64/CentOS/fonts-ISO8859-2-75dpi-1.0-17.1.noarch.rpm
一 个是中文字体，一个是字体显示包。
下载后，在命令行安装:
#rpm -ivh XXXX （ XXXX 代表上面那两个包的全名， rpm 不会不知道怎么用吧？）

CentOS系统安装完成后，重新启动即可。


安装redhat时中文显示乱码（小方框）解决方法
在安装linux的时候，安装完了中文出现乱码或者是当时选错了选成了英文的，到时候中文显示乱码，下面说一下问题的解决：
在首次安装RHEL5时，如果选择的是英文，那么系统将不安装中文支持包，这样就导致了中文显示为乱码（小方框）.......
有很多人说vi /etc/sysconfig/i18n文件，其实根本就没有那个必要。
解决方法:
安装
1、fonts-chinese-3.02-9.6.el5.noarch.rpm.  如果无法安装，则加个--force
2、fonts-ISO8859-2-75dpi-1.0-17.1.noarch.rpm
多数人到了这里就没有做其它操作了,导致仍然无法正确显示中文。
3、cd /usr/share/fonts/
4、fc-cache -fv  #  
以上的两个步骤，才是成功完成的关键！所以这里要特别注意！重新启动系统即可
另附中文输入法安装方法
将下面几个包都安装好后就可以出现中文输入法了。

要在系统安装盘里找到以下文件（也就是在/server文件夹下）：
  scim-libs-1.4.4-41.el5.i386.rpm
   scim-1.4.4-41.el5.i386.rpm
   scim-chinese-standard-0.0.2-1.el5.i386.rpm
   scim-tables-0.5.6-7.i386.rpm
   scim-tables-chinese-0.5.6-7.i386.rpm
   scim-pinyin-0.5.91-16.el5.i386.rpm
   双击运行他们，记住按以上顺序依次运行，因为他们之间上下存在依赖关系。
   重新启动系统即可
另附 红帽5，桌面可以正常显示中文，但终端里中文却是乱码解决方法

vi /etc/sysconfig/i18n
将内容改为
LANG="zh_CN.GB18030"
LANGUAGE="zh_CN.GB18030:zh_CN.GB2312:zh_CN"
SUPPORTED="zh_CN.GB18030:zh_CN:zh:en_US.UTF-8:en_US:en"
SYSFONT="lat0-sun16"

  重新启动系统即可
```