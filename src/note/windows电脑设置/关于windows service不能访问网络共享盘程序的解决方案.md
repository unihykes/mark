http://www.cnblogs.com/foohack/p/5644145.html

我映射一个网络驱动器到本机的时候，发现本机的程序直接能访问读取网络驱动器，但是把本机的程序作为本机的windows服务运行的时候就不能访问了。

Qt中的QDir::exist(folder)访问失败。这样导致的原因是映射网络驱动器，需要服务程序运行的权限账户和远程共享文件的机器要运行在同一个域（Domain）

下面，用PStool这个工具就可以了，它直接使用SYSTEM账户权限，来映射网络驱动器。这样，远程驱动器和本机的service就处于同一个域下了。



注意：这个是比较hack的做法，并不推荐这么做。微软是不支持的。



1.用psexec创建网络驱动器:

admin 权限运行CMD，然后运行psexec -i -s cmd.exe 

然后在新打开的CMD窗口中运行以下命令映射网络驱动器Z盘， net use z: \\192.168.52.223\e  /persistent:yes

 以上的net命令可能会让你输入远程的系统用户名和密码，我的远程是XP，所以用户名密码是：Administrator/无密码

注： 所有微软的Windows 系统默认管理员用户都是Administator 而密码是你自己设定的，系统没有默认密码

2.运行本机windows服务，成功访问网络驱动器Z



references:

http://stackoverflow.com/questions/18632193/directory-exists-returns-false-for-mapped-drive-in-c-sharp-coding

http://stackoverflow.com/questions/3622089/windows-service-cant-access-network-share

http://serverfault.com/questions/177139/windows-service-cant-access-network-share

http://stackoverflow.com/questions/182750/map-a-network-drive-to-be-used-by-a-service

https://technet.microsoft.com/en-us/sysinternals/psexec   （PStool工具下载）



下载地址
http://www.xdowns.com/soft/softdown.asp?softid=125362

