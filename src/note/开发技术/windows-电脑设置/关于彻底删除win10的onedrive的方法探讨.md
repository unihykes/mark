前言：首先没有任何贬低onedrive的意思，很多人支持onedrive，喜欢这个功能，方便。也有很多人讨厌onedrive，访问麻烦加上国内被墙。无论哪一种观点都是合理的，都没有必要来质疑或者反对。从skydrive到onedrive，微软统一化平台的愿望果断明显，技术的存在必然是有其优越性，但是也应允许不被所有人喜欢的可能。

这里仅仅是提供一种解决思路给那些不喜欢使用onedrive的朋友们，他们不喜欢onedrive的开机启动，不喜欢onedrive的导航栏显示，不喜欢onedrive在国内访问的困难等等之类的。

如果你是onedrive的绝对拥护者，那么就可以直接跳过。

Onedrive在win10的时候清除方面显得比win8的时候要顽固些。特别是导航栏的链接。最起码是9926开始（因为我从9926才长时间的使用，早起的TP版本基本上没怎么用，所以只能从9926开始说起）

以下的方法来大多源于论坛搜集（此处有默默的感谢），我只是摸索出了第4点的解决办法。


1） 关于禁止onedrive自启动简单的就是在任务管理器的启动中禁用onedrive的启动项目就可以。


2）关于组策略管理
运行gpedit.msc，进入【计算机配置】-【管理模板】-【windows组件】-【onedrive】，右侧的三个选项：
•默认情况下，将文档保存到 OneDrive，选择禁用；
•禁止使用 OneDrive 进行文件存储，选择启用
•禁止OneDrive 文件通过按流量的连接同步，选择启用。

如果是准备彻底删除onedrive，组策略的这三项其实是不用理会的，因为onedrive都没有了，这个策略设置就毫无意义。这个策略可能适用于同步行为的设置。


3）关于删除onedrive的程序卸载
卸载方法一：
运行输入 %localappdata%\Microsoft\OneDrive\ ,查看版本号，一般是一串数值的形式。运行CMD命令，输入%localappdata%\Microsoft\OneDrive\XXXXXXXXXXXXXXX(刚才查看到的那个版本号)\OneDriveSetup /uninstall，这个命令可以卸载掉大多的onedrive程序，剩余的可以自行删除（可能须要权限设置或者以管理员模式运行cmd）

卸载方法二：
强制删除。直接通过取得权限的方式来删除%localappdata%\Microsoft \onedrive文件夹（取得权限以后，可能需要先在进程中关闭掉相应的onedrive进程，才能把文件夹删除干净）

其实要是操作到卸载这一步的话，第1）点和第2）点的操作就属于重复操作。


4）关于删除导航栏中的onedrive。
卸载onedrive是不能清除导航栏里面的onedrive，进入注册表：
HKEY_CLASSES_ROOT\CLSID\{018D5C66-4533-4307-9B53-224DE2ED1FE6}\ShellFolder
把右侧的Attributes属性的值 f080004d修改为f090004d。
任务管理器中重启资源管理器后就生效了。