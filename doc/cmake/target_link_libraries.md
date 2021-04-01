target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <lib>...)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <lib>... [PRIVATE|PUBLIC|INTERFACE> <lib>...] ...])
作用：
PUBLIC，PRIVATE和INTERFACE关键字能够实现在一条命令中同时指定链接依赖和链接接口。
参数：
1.若使用PUBLIC，库文件和目标文件会被链接到接口并成为它的一部分。
2.若使用PRIVATE，库文件和目标文件只会被链接到接口但不会成为它的一部分。
3.若使用INTERFACE，被附加到接口后并不被链接目标文件所使用。

<br><br><br><br><br><br>

当创建动态库时，

如果源文件(例如CPP)中包含第三方头文件，但是头文件（例如hpp）中不包含该第三方文件头，采用PRIVATE。
如果源文件和头文件中都包含该第三方文件头，采用PUBLIC。
如果头文件中包含该第三方文件头，但是源文件(例如CPP)中不包含，采用 INTERFACE。
原文：CMake target_link_libraries Interface Dependencies
<br><br><br><br><br><br>


.so 依赖目录 cmake_cmake：target_** 中的 PUBLIC，PRIVATE，INTERFACE
https://blog.csdn.net/weixin_39997696/article/details/110604073?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-1&spm=1001.2101.3001.4242