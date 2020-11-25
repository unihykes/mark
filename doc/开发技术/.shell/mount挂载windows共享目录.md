

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



## 【linux】系统无法启动:fsck.ext4 unable to resolve 'UUID=e929833...
天做了DRBD 用的分区/data ，是/dev/sda5
今天重新启动报错：

fsck.ext4 unable to resolve 'UUID=a4a7a0f7-b54f-4774-9fb1'
解决办法：
启动进入系统：
cat /etc/fstab
UUID=a4a7a0f7-b54f-4774-9fb1 对应的是/data

系统现在是只读状态：
mount -o remount rw /
chmod a+rw /etc/fstab
vi /etc/fstab
删除UUID，reboot
输入命令 ls -l /dev/disk/by-uuid  可以查看磁盘和uuid的关系