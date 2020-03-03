```
查看已安装软件的信息
rpm -ql xxxx


1.如何安装rpm软件包
rpm软件包的安装可以使用程序rpm来完成。执行下面的命令
 rpm -i your-package.rpm
 其中your-package.rpm是你要安装的rpm包的文件名，一般置于当前目录下。
 安装过程中可能出现下面的警告或者提示：
 ... conflict with ... 可能是要安装的包里有一些文件可能会覆盖现有
 的文件，缺省时这样的情况下是无法正确安装的可以用

 rpm --force -i 强制安装即可
 ... is needed by ...
... is not installed ... 此包需要的一些软件你没有安装可以用
rpm --nodeps -i 来忽略此信息
也就是说，rpm -i --force --nodeps 可以忽略所有依赖关系和文件问题，什么包
都能安装上，但这种强制安装的软件包不能保证完全发挥功能

2.如何安装.src.rpm软件包
有些软件包是以.src.rpm结尾的，这类软件包是包含了源代码的rpm包，在安装时
需要进行编译。这类软件包有两种安装方法，
方法一：
1.执行rpm -i your-package.src.rpm
2. cd /usr/src/redhat/SPECS
3. rpmbuild -bp your-package.specs 一个和你的软件包同名的specs文件
4. cd /usr/src/redhat/BUILD/your-package/ 一个和你的软件包同名的目录
5. ./configure 这一步和编译普通的源码软件一样，可以加上参数
6. make
7. make install

方法二:
1.执行rpm -i you-package.src.rpm
2. cd /usr/src/redhat/SPECS
前两步和方法一相同
3. rpmbuild -bb your-package.specs 一个和你的软件包同名的specs文件
这时，在/usr/src/redhat/RPM/i386/ （根据具体包的不同，也可能是i686,noarch等等)
在这个目录下，有一个新的rpm包，这个是编译好的二进制文件。
执行rpm -i new-package.rpm即可安装完成。

3.如何卸载rpm软件包
使用命令 rpm -e 包名，包名可以包含版本号等信息，但是不可以有后缀.rpm
比如卸载软件包proftpd-1.2.8-1，可以使用下列格式：
rpm -e proftpd-1.2.8-1
rpm -e proftpd-1.2.8
rpm -e proftpd-
rpm -e proftpd
不可以是下列格式：
rpm -e proftpd-1.2.8-1.i386.rpm
rpm -e proftpd-1.2.8-1.i386
rpm -e proftpd-1.2
rpm -e proftpd-1
有时会出现一些错误或者警告：
... is needed by ... 这说明这个软件被其他软件需要，不能随便卸载
可以用rpm -e --nodeps强制卸载

4.如何不安装但是获取rpm包中的文件
使用工具rpm2cpio和cpio
rpm2cpio xxx.rpm | cpio -vi
rpm2cpio xxx.rpm | cpio -idmv
rpm2cpio xxx.rpm | cpio --extract --make-directories
参数i和extract相同，表示提取文件。v表示指示执行进程
d和make-directory相同，表示根据包中文件原来的路径建立目录
m表示保持文件的更新时间。

5.如何查看与rpm包相关的文件和其他信息
下面所有的例子都假设使用软件包mysql-3.23.54a-11
1.我的系统中安装了那些rpm软件包
rpm -qa 讲列出所有安装过的包
如果要查找所有安装过的包含某个字符串sql的软件包
rpm -qa |grep sql

2.如何获得某个软件包的文件全名
rpm -q mysql 可以获得系统中安装的mysql软件包全名，从中可以获得
当前软件包的版本等信息。这个例子中可以得到信息mysql-3.23.54a-11

3.一个rpm包中的文件安装到那里去了？
rpm -ql 包名
注意这里的是不包括.rpm后缀的软件包的名称
也就是说只能用mysql或者mysql-3.23.54a-11而不是mysql-3.23.54a-11.rpm。
如果只是想知道可执行程序放到那里去了，也可以用which，比如
which mysql

4.一个rpm包中包含那些文件
一个没有安装过的软件包，使用rpm -qlp ****.rpm
一个已经安装过的软件包，还可以使用rpm -ql ****.rpm

5.如何获取关于一个软件包的版本，用途等相关信息？
一个没有安装过的软件包，使用rpm -qip ****.rpm
一个已经安装过的软件包，还可以使用rpm -qi ****.rpm

6.某个程序是哪个软件包安装的，或者哪个软件包包含这个程序
rpm -qf `which 程序名` 返回软件包的全名
rpm -qif `which 程序名` 返回软件包的有关信息
rpm -qlf `which 程序名` 返回软件包的文件列表
注意，这里不是引号，而是`，就是键盘左上角的那个键。
也可以使用rpm -qilf，同时输出软件包信息和文件列表

7.某个文件是哪个软件包安装的，或者哪个软件包包含这个文件
注意，前一个问题中的方法，只适用与可执行的程序，而下面的方法，不仅可以
用于可执行程序，也可以用于普通的任何文件。前提是知道这个文件名。
首先获得这个程序的完整路径，可以用whereis或者which，然后使用rpm -qf例如：
# whereis ftptop
ftptop: /usr/bin/ftptop /usr/share/man/man1/ftptop.1.gz
# rpm -qf /usr/bin/ftptop
proftpd-1.2.8-1
# rpm -qf /usr/share/doc/proftpd-1.2.8/rfc/rfc0959.txt
proftpd-1.2.8-1
```