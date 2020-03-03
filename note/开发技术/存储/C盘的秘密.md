$RECYCLE.BIN：就是回收站用的文件夹，每个分区都有的
Boot：启动菜单BCD以及对应多国语言的位置
Recovery：包含系统恢复环境（众所周知的WinPE由这个镜像修改的），用于主系统（如C盘系统）被破坏的时候，启动来进行某些恢复操作。
System Volume Information：系统还原必用目录，如果关闭系统还原，这个目录依然存在，只不过保留大概20K的信息。
Bootmgr：启动管理器的主文件，没有它，一切都启动不了，会提示找不到bootmgr或者文件已损坏。而且此文件不能使用NTFS的压缩或者加密功能。
BOOTNXT：如果硬盘有非 Windows 8系统，那么该文件用于启动其他系统。

BOOSECT.BAK：活动扇区的备份，备份了前16个扇区。

hiberfil.sys是启用休眠功能时，在磁盘上暂存内存内容的文件，大小与内存一致。设置关闭休眠功能，命令powercfg -h off 删除该文件；
pagefile.sys是虚拟内存，与设置的虚拟内存最小值一致。
swapfile.sys似乎是win8 metro应用所使用的交换文件。



