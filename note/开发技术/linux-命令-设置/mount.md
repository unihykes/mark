

#mount:



mount [-t vfstype] [-o options] device dir

1. -t vfstype 指定文件系统的类型，通常不必指定。mount 会自动选择正确的类型。常用类型有：
>
	光盘或光盘镜像：iso9660
	DOS fat16文件系统：msdos
	Windows 9x fat32文件系统：vfat
	Windows NT ntfs文件系统：ntfs
	Mount Windows文件网络共享：smbfs
	UNIX(LINUX) 文件网络共享：nfs

2. -o options 主要用来描述设备或档案的挂接方式。常用的参数有：
>	loop：用来把一个文件当成硬盘分区挂接上系统
	ro：采用只读方式挂接设备
	rw：采用读写方式挂接设备
	iocharset：指定访问文件系统所用字符集

3. device 要挂接(mount)的设备。

4. dir设备在系统上的挂接点(mount point)。





## 挂接光盘镜像文件

* mount -o loop -t iso9660 /home/sunky/mydisk.iso /mnt/vcdrom
使用/mnt/vcdrom就可以访问盘镜像文件mydisk.iso里的所有文件了。


## 挂接移动硬盘/U盘
mount -t ntfs /dev/sdc1 /mnt/usbhd1
注：
对ntfs格式的磁盘分区应使用-t ntfs 参数，
对fat32格式的磁盘分区应使用-t vfat参数。
若汉字文件名显示为乱码或不显示，可以使用下面的命令格式。
mount -t ntfs -o iocharset=cp936 /dev/sdc1 /mnt/usbhd1

# 挂接Windows文件共享
todo


#挂接UNIX系统NFS文件共享
todo

#umount
“有些时候，可能某些设备(通常是 CD-ROM)正忙或无法响应。此时，大多数用户的解决办法是重新启动计算机。我们大可不必这么做。例如，如果 umount /dev/hdc 失败的话，您可以试试“lazy” umount。语法十分简单：

umount -l <挂载点|设备>
此命令将会断开设备并关闭打开该设备的全部句柄。通常，您可以使用 eject <挂载点|设备>命令弹出碟片。所以，如果 eject 命令失效而您又不想重新启动，请使用 lazy umount。”
