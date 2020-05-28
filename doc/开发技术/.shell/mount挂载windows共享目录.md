

http://blog.chinaunix.net/uid-23835539-id-401938.html

```
挂载:
mount -t cifs //192.168.52.223/e -o username=xxxxx,password=xxxxxxx /home/aaaa
mount -t cifs //192.168.1.2/f    -o username=xxxxx,password=xxxx    /home/f

取消挂载：
umount //192.168.52.223/e



umount -f /home/f

开机自动挂载:
如果你需要每次系统启动都挂载这个目录，那就需要在fstab 文件里把需要挂载项添加进去 添加行：
cd /etc/fstab
//192.168.52.222/d      /home/d                cifs     default,username=xxx,password=xxx 0 2
//192.168.52.222/d      /home/d                cifs     auto,username=xxx,password=xxxxxx 0 0
修改fstab后，直接输入mount -a即可立即生效；


```





常见错误：
一、挂载时，用户/密码错误

mount error(13): Permission denied
Refer to the mount.cifs(8) manual page (e.g. man mount.cifs)
对应/var/log/message记录
Oct 12 16:20:01 localhost kernel: Status code returned 0xc000006d NT_STATUS_LOGON_FAILURE
Oct 12 16:20:01 localhost kernel: CIFS VFS: Send error in SessSetup = -13
Oct 12 16:20:01 localhost kernel: CIFS VFS: cifs_mount failed w/return code

二、没有分享目录

Retrying with upper case share name
mount error(6): No such device or address
Refer to the mount.cifs(8) manual page (e.g. man mount.cifs)
对应/var/log/message记录
Oct 12 16:20:06 localhost kernel: CIFS VFS: cifs_mount failed w/return code = -6
Oct 12 16:20:17 localhost kernel: CIFS VFS: cifs_mount failed w/return code = -6
Oct 12 16:20:17 localhost kernel: CIFS VFS: cifs_mount failed w/return code 



