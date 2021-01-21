#执行df -h命令无返回数据
<1>
发现是之前挂载的windows目录失去连接(windows电脑重启关机等原因)
//10.1.23.75/123 on /mnt type cifs (rw,relatime,vers=1.0,cache=strict,username=Everyone,.......）

[root@localhost ~]# umount -f //10.1.23.75/123 #卸载这个网络挂载
查了百度一下。fuser 命令也是解决办法。并且fuser可以查询是哪个网络连接导致的df -h卡死。但是此处并未用到

<2>df -h command卡死无响应
使用starce查看df -h 执行状态

[root@localhost ~]# strace df -h
[root@localhost python]# systemctl restart proc-sys-fs-binfmt_misc.automount