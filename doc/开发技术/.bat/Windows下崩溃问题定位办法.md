  最近在使用windows下的服务器，偶尔从日志中看到一天之中服务器上的几个进程切换了大概有5次左右，我的第一反应就是这些进程崩溃在一天之中崩溃了5次。因为守护进程十几秒就拉起来了，所以本来就数量不多的用户也感知不到。但是这个隐患不能留呀，一定要有一定的措施去处理呀。目前我使用了以下几种办法来做一些简单的处理：

      1、查看系统日志，看看是否系统日志有记录。基本操作就是右键“我的电脑”。管理——>系统工具——>事件查看器             ——>Windows日志——>应用程序，在里面查看错误这一项。基本就是如下这种的情况。
      
找到上面的这种基本就说明系统崩溃了，并且被记录了。但是说句实话，这些东西没啥用，你去百度0xc0000005根本就看不到什么玩意，就说明什么内存的问题。一个代码大了，什么都找不到。所以这个只能帮你说明你的程序确实有问题，不是人为重启的。我对照着这个信息和日志，确实发现有对应的进程号切换的情况。但是5次里面大概只有2次，所以还有3次有可能是其他原因。目前怀疑是被守护进程保活失败杀掉之后重启了导致的，这些在系统层面找不到原因的进程重启，就不能使用下面的办法了，至于到底是为什么，等我定位出来再说。我们着重说说那2次。

        2、想办法找到dump文件。其实目前定位崩溃问题使用windbg直接attach上到进程上面然后等问题复现是最好的办法，但是这会导致你时时刻刻都盯着服务器，而且一旦抓到了崩溃点你的服务器就不能用了。这个很容易被感知到的，不靠谱呀。所以就必须使用自动生成dump文件了。这个办法主要是修改注册表，让系统自己生成。其实想想这个也很正常，windows都能在日志里面捕捉到崩溃，一定能顺便把dump文件写下来。执行脚本如下：

@echo off
echo 设置Dump...
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps"
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpFolder /t REG_EXPAND_SZ /d "C:\MyDump" /f
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpType /t REG_DWORD /d 2 /f
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpCount /t REG_DWORD /d 10 /f
echo Dump已经设置
pause
@echo o

这样其实就是修改了注册表里面关于dump的一部分，保证在程序进行崩溃的时候，可以自动生成dump我自己实际测试过是有用的。写了如下的代码来实现崩溃：

int main()
{
    int i;
    cin>>i;
    return *(int*)0;
}

最后在C:\MyDump就可以看到(我使用的是win7的电脑)。

然后再使用windbg挂上pdb就可以执行了。此处不是讲的重点。后面有机会，就再将一下windbg深入一点的。

好了，今天就到这里吧。









windbg查看coredump文件

韩虎(Hugh) 12-22 16:29:55
.reload /i

韩虎(Hugh) 12-22 16:29:57
~*kn


