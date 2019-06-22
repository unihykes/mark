
# 相关连接:

CMake 手册详解
1. http://www.cnblogs.com/coderfenghc/archive/2012/06/16/CMake_ch_01.html
2. https://www.cnblogs.com/coderfenghc/archive/2012/06/17/2552899.html
3. https://www.cnblogs.com/coderfenghc/archive/2012/06/18/2553964.html
4. https://www.cnblogs.com/coderfenghc/archive/2012/06/19/2555388.html
5. https://www.cnblogs.com/coderfenghc/archive/2012/06/20/2556996.html
6. https://www.cnblogs.com/coderfenghc/archive/2012/06/23/2559603.html
7. https://www.cnblogs.com/coderfenghc/archive/2012/06/25/2562778.html
8. https://www.cnblogs.com/coderfenghc/archive/2012/07/04/2576862.html
9. https://www.cnblogs.com/coderfenghc/archive/2012/07/05/2578451.html
10. https://www.cnblogs.com/coderfenghc/archive/2012/07/08/2581734.html
11. https://www.cnblogs.com/coderfenghc/archive/2012/07/11/2585616.html
12. https://www.cnblogs.com/coderfenghc/archive/2012/07/14/2591135.html
13. https://www.cnblogs.com/coderfenghc/archive/2012/07/15/2592758.html
14. https://www.cnblogs.com/coderfenghc/archive/2012/07/19/2599988.html
15. https://www.cnblogs.com/coderfenghc/archive/2012/07/22/2604041.html
16. https://www.cnblogs.com/coderfenghc/archive/2012/07/28/2613567.html
17. https://www.cnblogs.com/coderfenghc/archive/2012/07/29/2614253.html
18. https://www.cnblogs.com/coderfenghc/archive/2012/08/05/2624266.html
19. https://www.cnblogs.com/coderfenghc/archive/2012/08/12/2627561.html
20. https://www.cnblogs.com/coderfenghc/archive/2012/09/03/2668008.html
21. https://www.cnblogs.com/coderfenghc/archive/2012/10/06/2677767.html
22. https://www.cnblogs.com/coderfenghc/archive/2012/10/20/2712806.html

CMAKE的使用 
https://www.cnblogs.com/lidabo/p/3974305.html

cmake 常用变量和常用环境变量查表手册---整理 .
http://www.cnblogs.com/xianghang123/p/3556425.html

在linux下使用CMake构建应用程序
http://blog.chinaunix.net/uid-28458801-id-3501768.html

cmake使用示例与整理总结
https://github.com/carl-wang-cn/demo/blob/master/cmake/README.md

## 安装说明:

官网:https://cmake.org/
下载链接：https://cmake.org/download/


安装cmake
输入rpm -qa CMake 查看是否安装 CMake

l  安装说明：以下是原码包的安装方法
下载源码包；

将源码包放到任意目录；

解压 tar xzvf cmake.tgz；进入到解压目录 依次执行 ./bootstrap
make
make install
安装成后后，输入cmake –help会出现有关cmake的使用命令       


## CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS
```
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
编译dll的时候,如果添加这个定义,则会将该dll中的所有符号全部导出;
用.def文件控制的导出符号将会失效(函数名会变成?fun@cpp@xxxxxxx);
因此,如果上层使用
LoadLibrary() 
GetProcAddress()
方式加载接口的话,会无效;

解决办法:
将dll内部待导出函数前,添加 extern "C" 强制保留原名称;


相关资料:
https://stackoverflow.com/questions/225432/export-all-symbols-when-creating-a-dll
```


## cmake -T vs140_xp失败
---
如果安装vs2015时候，没有选择“针对C++的windowsXP支持”的话，则用cmake编译时会报错；

报错信息:
>
	-- The C compiler identification is unknown
	-- The CXX compiler identification is unknown
	CMake Error at CMakeLists.txt:1 (PROJECT):
	  No CMAKE_C_COMPILER could be found.
	CMake Error at CMakeLists.txt:1 (PROJECT):
	  No CMAKE_CXX_COMPILER could be found.
	  
如果不想安装该功能，则需要修改为cmake -T vs140；


## SET(SUBSYSTEM "WINDOWS")
	IF(WIN32)
	SET(SUBSYSTEM "WINDOWS")
	ENDIF(WIN32)

	注释：
	todo:


## SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
```
一个小例子,用来判断平台差异： 
IF (WIN32) 
     MESSAGE(STATUS “This is windows.”)
 ELSE (WIN32) 
     MESSAGE(STATUS “This is not windows”)
 ENDIF (WIN32)
 上述代码用来控制在不同的平台进行不同的控制,但是,阅读起来却并不是那么舒服,ELSE(WIN32)之类的语句很容易引起歧义。 
可以SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON) 
这时候就可以写成: 
IF (WIN32) 
ELSE () 
ENDIF () 
配合ELSEIF使用,可能的写法是这样:
 IF (WIN32) 
     #do something related to WIN32
ELSEIF (UNIX) 
     #do something related to UNIX
ELSEIF(APPLE) 
     #do something related to APPLEENDIF (WIN32)
```



## SET(CMAKE_USE_RELATIVE_PATHS TRUE)
cmake采用相对路径