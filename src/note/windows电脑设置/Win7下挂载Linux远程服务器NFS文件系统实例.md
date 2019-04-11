
```
Win7与远程Linux服务器在同一网段。1．在Linux（RHEL5.5）服务器端设置nfs文件系统共享：
将远程Linux服务器（dellzq，IP:10.52.19.253）新加的盘disk4（2TB）共享出去（以下均在root用户下terminal窗口中操作）：
开启nfs服务： ntsysv 回车，选中nfs服务，确定--退出，接着执行，
service nfs restart
chkconfig nfs on
vi /etc/exports，添加以下的行保存退出：
/disk4  *(rw,no_root_squash,sync)
接着执行： exportfs  -av 回车

出现： exporting  *:/disk4 说明磁盘disk4已共享成功。

2．启用Win7的nfs功能：

点开：计算机-控制面板（查看方式：类别，点选大或小图标方式）-程序和功能-打开或关闭Windows功能-勾选NFS服务和Telnet客户端（可用作登录和操作Linux服务器）-确定。

3．在Win7中执行挂载操作：
徽标键+R弹出运行窗口，输入cmd 确定-弹出msdos窗口，输入：
mount \\10.52.19.253\disk4 z: 回车，稍候，将出现以下连接成功的信息：
z：现已成功连接到  \\10.52.19.253\disk4
命令已成功完成。

点开计算机，可以看到 disk4（\\10.52.19.253）(Z:)的驱动器盘符了。

4．修改Win7对nfs盘的read-only属性：
打开注册表定位到：HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\ClientForNFS\CurrentVersion\Default，鼠标右键点，新建-QWORD(64位)值(Q)，增加两项：AnonymousUid，AnonymousGid
重启计算机，重新mount即可。这时，在msdos窗口敲，mount回车后，显示信息为；
 本地    远程                                 属性
-------------------------------------------------------------------------------
z:       \\10.52.19.253\disk4                   UID=0, GID=0
                                                rsize=32768, wsize=32768
                                                mount=soft, timeout=3.2
                                                retry=1, locking=yes
                                                fileaccess=755, lang=GB2312-80
                                                casesensitive=no
                                                sec=sys
发现这时的UID=0, GID=0，即Win7下已有对/disk4的全部控制权限。
如要去除nfs共享，用 umount -a（卸载全部挂接点）即可。
  
```