Win7下挂载Linux远程服务器NFS文件系统实例
http://blog.chinaunix.net/uid-124509-id-4214151.html

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


Windows 7 挂载 NFS 共享目录
```

安装
控制面板 － 程序和功能 － 打开或关闭 Windows 功能 － NFS 服务 － NFS 客户端

查看远程服务器上的 NFS 共享目录
运行命令提示符
> showmount -e HOSTNAME
导出列表在 HOSTNAME:
/raid0/data/files

挂载 NFS 目录
> mount HOSTNAME:/raid0/data/files/ N:

卸载 NFS 目录
> umount -a

挂载匿名共享的 NFS 目录需要添加2个注册表项，然后重启。
[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\ClientForNFS\CurrentVersion\Default]
"AnonymousUid"=dword:00000000
"AnonymousGid"=dword:00000000
这里的 Uid 和 Gid 就是远程服务器上 NFS 共享目录属主的 uid 和 gid
# id
uid=0(root) gid=0(root)



Windows7 NFS客户端访问NFS无法写入文件问题。
http://jingyan.baidu.com/album/c910274bfd6800cd361d2df3.html



另一篇介绍win7挂载NFS的教程：
http://jingyan.baidu.com/article/6b1823095126c5ba58e15903.html


更复杂的方法：
http://blog.chinaunix.net/uid-13539494-id-3051194.html



```