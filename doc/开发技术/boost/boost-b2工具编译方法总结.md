# 下载：
boost release包：
从官网可以下载到各个版本的release包，推荐使用当前最新版本；
http://www.boost.org

boost 开发代码线：
开发线代码也可以直接从github上clone下来；
https://github.com/boostorg/boost
注意：代码线clone完成后，还需要手动更新libs目录下的子模块，这个项目libs目录下源码都在子模块中，不更新的话没有源码；


windows环境下：
# 1、准备环境
安装好的vs2015
将boost压缩包(boost_1_64_0.zip)解压：
打开cmd窗口，从apollo项目的cmake目录中设置好环境变量
abenv.bat x64

# 2、编译b2和bjam工具
cd   "解压路径"\boost_1_64_0
"解压路径"请根据实际情况自行填写；
bootstrap.bat
脚本运行完成后，会生成b2.exe和bjam.exe;

#3、查询待编译的模块：
b2 --show-libraries
会列出所有要编译的库。
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

# 4、b2 --help查看使用说明；
b2 --help
b2 [options] [properties] [install|stage]
b2命令参数简介见另一篇笔记：《boost-b2工具参数总结》



# 5、用b2.exe编译需要编译的库：
备注: 在cmd下，^符号是换行符

install选项编译64位 debug
b2.exe ^
     --build-dir=E:\git\boostlib\deps_boost\build-dir\debug_x64 ^
   --includedir=E:\git\boostlib\deps_boost\include ^
         --prefix=E:\git\boostlib\deps_boost\prefix\debug_x64 ^
 --exec-prefix=E:\git\boostlib\deps_boost\exec-prefix\debug_x64 ^
           --libdir=E:\git\boostlib\deps_boost\libdir\debug_x64 ^
 --without-python ^
 variant=debug ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=64 ^
 install

install选项在mk环境下编译64位 debug
b2.exe ^
     --build-dir=%MK_PATH%\3rd_Party\deps_boost\build-dir\debug_x64 ^
   --includedir=%MK_PATH%\3rd_Party\deps_boost\include ^
         --prefix=%MK_PATH%\3rd_Party\deps_boost\prefix\debug_x64 ^
 --exec-prefix=%MK_PATH%\3rd_Party\deps_boost\exec-prefix\debug_x64 ^
           --libdir=%MK_PATH%\3rd_Party\deps_boost\libdir\debug_x64 ^
 --without-python ^
 variant=debug ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=64 ^
 install

stage选项编译64位 debug
b2.exe ^
 --build-dir=E:\git\boostlib\deps_boost\build-dir\debug_x64 ^
 --stagedir=E:\git\boostlib\deps_boost\stagedir\debug_x64 ^
 --without-python ^
 variant=debug ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=64 ^
 stage

备注：
b2.exe  --stagedir=E:\git\boostlib\deps_boost\lib\debug\x64  --without-python  variant=debug  link=shared  threading=multi  runtime-link=shared  address-model=64  stage


stage选项编译64位 release
b2.exe ^
 --build-dir=E:\git\boostlib\deps_boost\build-dir\release_x64 ^
 --stagedir=E:\git\boostlib\deps_boost\stagedir\release_x64 ^
 --without-python ^
 variant=release ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=64 ^
 stage

stage选项编译32位 debug
b2.exe ^
 --build-dir=E:\git\boostlib\deps_boost\build-dir\debug_x86 ^
 --stagedir=E:\git\boostlib\deps_boost\stagedir\debug_x86 ^
 --without-python ^
 variant=debug ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=32 ^
 stage

stage选项编译32位 release
b2.exe ^
 --build-dir=E:\git\boostlib\deps_boost\build-dir\release_x86 ^
 --stagedir=E:\git\boostlib\deps_boost\stagedir\release_x86 ^
 --without-python ^
 variant=release ^
 link=shared ^
 threading=multi ^
 runtime-link=shared ^
 address-model=32 ^
 stage

```
/*以前的笔记
 编译win_debug_x64
    动态库：b2.exe --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=debug address-model=64 --stagedir=win_debug_x64
    静态库：b2.exe --with-system --with-thread --with-date_time --with-regex --with-serialization link=static   threading=multi variant=debug address-model=64 --stagedir=win_debug_x64
 编译win_release_x64
    b2.exe --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=release address-model=64 --stagedir=win_release_x64
编译win_debug_i386
    b2.exe --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=debug address-model=32 --stagedir=win_debug_i386
编译win_release_i386
    b2.exe --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=release address-model=32 --stagedir=win_release_i386
*/
```

# 6、windows使用boost动态库：
需要在程序中定义boost宏，否则链接时会提示找不到libboostxxxxxxxx
#define BOOST_ALL_DYN_LINK
使用静态库的时候，不需要该宏；


# 7、使用动态库示例：
```cpp
//#define BOOST_DATE_TIME_SOURCE
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
int main()
{
    return 0;
}

注意开头的宏 “#define BOOST_DATE_TIME_SOURCE” 注掉了。
若启用这个宏定义，则默认由编译器重新编译嵌入的头文件；
若不启用这个宏定义，则表示使用系统已编译好的date_time库。

7.1 禁用#define BOOST_DATE_TIME_SOURCE 宏，然后将 libboost_date_time-vc120-mt-gd-1_56.lib 从 ..\boost_1_56_0\bin\vc12\lib 中移除，
     编译debug版的程序时，提示连接错误，缺少libboost_date_time-vc120-mt-gd-1_56.lib。

7.2 启用#define BOOST_DATE_TIME_SOURCE 宏，
     编译debug版的程序时，可发现即使在缺少 libboost_date_time-vc120-mt-gd-1_56.lib的情况下，也能成功编译。

```



# Linux环境下：
1.解压
tar zxvf boost_1_54_0.tar.gz
2. cd boost_1_54_0
3. ./bootstrap.sh
    生成b2工具
4. 编译linux__debug_x64
    ./b2 --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=debug address-model=64 --stagedir=linux_debug_x64
5. 编译linux_release_x64
    ./b2 --with-system --with-thread --with-date_time --with-regex --with-serialization link=shared threading=multi variant=release address-model=64 --stagedir=linux_release_x64
6、好像与windows没有什么大区别；




