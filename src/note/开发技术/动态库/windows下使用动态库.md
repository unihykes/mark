注册动态库:
regsvr32 disk.dll

解注册动态库:
regsvr32 /u disk.dll


查看dll接口命令：Dumpbin -exports xxx.dll
(Dumpbin需要在cmd的编译环境下,vs环境)

编译成obj：cl /c xxx.cpp
将obj链接为dll：link /dll xxx.obj
