bcp官网介绍：
http://www.boost.org/doc/libs/1_49_0/tools/bcp/doc/html/index.html


一、bcp使用方式简介：

1、准备环境
安装好的vs2015
将boost压缩包(boost_1_64_0.zip)解压：
打开cmd窗口，从apollo项目的cmake目录中设置好环境变量
abenv.bat x64


2、编译b2和bjam工具
cd   "解压路径"\boost_1_64_0  //"解压路径"填写你解压的真实路径
bootstrap.bat
脚本运行完成后，会生成b2.exe和bjam.exe;


3、编译bcp工具
cd "解压路径"\boost_1_64_0
bjam.exe  tools/bcp
编译好以后，在"解压路径"\boost_1_64_0\dist\bin目录下，生成了bcp.exe


4、查询待剪裁的模块：
b2 --show-libraries
输出：
    The following libraries require building:
        - atomic
        - chrono
        - container
        - context
        - coroutine
        - coroutine2
        - date_time
        - exception
        - fiber
        - filesystem
        - graph
        - graph_parallel
        - iostreams
        - locale
        - log
        - math
        - metaparse
        - mpi
        - program_options
        - python
        - random
        - regex
        - serialization
        - signals
        - system
        - test
        - thread
        - timer
        - type_erasure
        - wave

5、选择待剪裁的模块：
排除掉:python,test,locale,mpi(需要依赖第三方库) 等模块;
其他模块有实际项目需要，则按需剪裁；

6、查看模块依赖命令示例（可选）：
dist\bin\bcp  --list filesystem
dist\bin\bcp  --list ystem

7、清理目标目录：
将准备保留剪裁文件的目标目录清空（每次进行剪裁都需要删除上一次剪裁生成的文件，以免目录混乱）。

8、开始剪裁
仍然在booost根目录中，输入：
cd  "解压路径"\boost_1_64_0
本例中我们假设保存剪裁文件的目标目录为： C:\boost\boostbcp //实际情况请自行选择
则输入以下命令:
    dist\bin\bcp.exe        ^
         atomic.hpp  ^
         chrono.hpp  ^
         container.hpp  ^
         context.hpp  ^
         coroutine.hpp  ^
         coroutine2.hpp  ^
         date_time.hpp  ^
         exception.hpp  ^
         fiber.hpp  ^
         filesystem.hpp  ^
         graph.hpp  ^
         graph_parallel.hpp  ^
         iostreams.hpp  ^
         log.hpp  ^
         math.hpp  ^
         metaparse.hpp  ^
         program_options.hpp  ^
         random.hpp  ^
         regex.hpp  ^
         serialization.hpp  ^
         signals.hpp  ^
         system.hpp  ^
         thread.hpp  ^
         timer.hpp  ^
         type_erasure.hpp  ^
         wave.hpp           C:\boost\boostbcp

备注:
在cmd下，^符号是换行符
必须确保目标目录已存在，上例中  C:\boost\boostbcp 需要预先创建 
这一步操作会讲所选的模块及其依赖的源文件全部copy到目标目录中；

9、编写CMakeLists文件
```cmake
-DBOOST_ALL_NO_LIB
boost在vc中,如果使用了某些头文件的话,默认行为会自动链接到对应的lib文件，
如果不想自动连接,则可以使用BOOST_ALL_NO_LIB宏来取消自动连接；
 
-DBOOST_ALL_DYN_LINK
外界调用该库（boostbcp）时使用动态链接，引用的头文件不会进行自动链接cpp；
    
-DBOOST_THREAD_BUILD_DLL=1
备注：todo
 
-DBOOST_ATOMIC_DYN_LINK=1
备注：todo

一系列:BOOST_XXXX_SOURCE
-DBOOST_ATOMIC_SOURCE
-DBOOST_SYSTEM_SOURCE
-DBOOST_CHRONO_SOURCE
-DBOOST_DATE_TIME_SOURCE
-DBOOST_FILESYSTEM_SOURCE
-DBOOST_REGEX_SOURCE
-DBOOST_RANDOM_SOURCE
备注1：
    一系列BOOST_XXXX_SOURCE 宏的作用,拿atomic做示例：
    查看:\boost\atomic\detail\link.hpp
    #if defined(BOOST_ATOMIC_SOURCE)
        #define BOOST_ATOMIC_DECL BOOST_SYMBOL_EXPORT
        #define BOOST_ATOMIC_BUILD_DLL
    #else
        #define BOOST_ATOMIC_DECL BOOST_SYMBOL_IMPORT
    #endif
    查看:\boost\config\platform\win32.hpp
        #define BOOST_SYMBOL_EXPORT __declspec(dllexport)
        #define BOOST_SYMBOL_IMPORT __declspec(dllimport)
    可以发现，如果没有定义 BOOST_ATOMIC_SOURCE 的话，cpp中函数定义使用的是__declspec(dllimport)
    编译该动态库时，函数定义处应该使用__declspec(dllexport)导出，使用__declspec(dllimport)的话会编译错误！
    编译错误示例:
    atomic\src\lockpool.cpp(102): error C2491: “boost::atomics::detail::lockpool::scoped_lock::scoped_lock”: 不允许 dllimport 函数 的定义
    综上所述，在编译boostbcp的时候，应该先定义宏 DBOOST_ATOMIC_SOURCE
    其他模块同理
备注2：
    1.__declspec(dllimport)是外界程序调用该动态库时，导入动态库接口时使用；
    2.thread模块没有使用宏BOOST_THREAD_SOURCE，thread模块应该使用宏BOOST_THREAD_BUILD_DLL
    3.exception模块没有使用宏BOOST_EXCEPTION_SOURCE，该模块编译时无需添加预编译宏；
 
 
-DBOOST_SYSTEM_NO_DEPRECATED
备注：todo


CMakeLists:添加待编译目录：
windows和linux下的thread/src下源码不同，需区别处理；
BUILD_SOURCE_DIRS(
            thread/src/win32
            thread/src
            system/src
            smart_ptr/src
            regex/src
            filesystem/src
            exception/src
            date_time/src/gregorian
            date_time/src/posix_time
            chrono/src
            atomic/src
            random/src
            todo...)
            
```

10、编译 boostbcp
cd   C:\boost\boostbcp
makec cleanall
makec
编译成功后，会在目标位置生成动态库；

11、bcp命令简介：
bcp的使用是简单的，假设我们允许程序员用A、B、C、D这样四个模块，那么我们可以这样：
dist\bin\bcp --boost:=E:\git\boostlib\boost_1_64_0   A B C D  output-Dir
这里A、B、C、D可以是：
Boost的头文件名。如: boost/shared_ptr.hpp
Boost的库名。如：regex
Boost的头文件标题：boost/shared_ptr 或者 shared_ptr
如果是在boost根目录下，那指定boost目录的参数也可以省去（--boost:=E:\git\boostlib\boost_1_64_0 ）。
output-Dir即是目标目录路径，该例中为：
bcp --boost:=E:\git\boostlib\boost_1_64_0   A B C D   C:\boost\boostbcp


12.使用boostbcp
```cmake
    1、添加头文件引用路径：
    xxx/boost)
     
    2、添加预编译宏：
    -DBOOST_ALL_NO_LIB
    取消boost自动链接；
     
    -DBOOST_LIB_DIAGNOSTIC
    让编译时的output窗口中输出程序具体链接了哪些boost库以及链接顺序。
     
    3、链接 boostbcp 库
    将 boostbcp.dll 复制到程序运行目录中，设置cmake链接命令；
    SET(LINK_BOOST_LIBS  boostbcp)
```