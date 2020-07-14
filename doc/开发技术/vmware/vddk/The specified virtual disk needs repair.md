转自http://tscsh.blog.163.com/blog/static/200320103201393095248828/
电脑突然断电后，或者非正常关机，ubuntu打不开了，出现错误提示
打开ubuntu时，出现如下错误：
Cannot open the disk 'G:\Ubuntu\Ubuntu (2).vmdk' or one of the snapshot disks it depends on.
Reason: The specified virtual disk needs repair.

解决方法：
在cmd里面执行如下命令进行修复：vmware-vdiskmanager.exe -R "G:\Ubuntu\Ubuntu (2).vmdk"

vmware-vdiskmanager.exe 下载链接：http://pan.baidu.com/s/125cVT