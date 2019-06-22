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
参考apollo\deps\boost下的CMakeLists;
本文档下方第二章节有简单介绍；

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






