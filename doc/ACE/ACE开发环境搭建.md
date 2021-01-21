```
Windows平台
1) 下载ACE源码
ACE官方网址：http://www.cs.wustl.edu/~schmidt/ACE.html
ACE下载地址：http://download.dre.vanderbilt.edu/
2) 下载ActivePerl
ActivePerl官方下载网址：http://www.activestate.com/activeperl/downloads/
3) 设置系统环境变量
ACE_ROOT=安装目录
Path环境变量中增加：%ACE_ROOT%\lib
4) 增加config.h
在%ACE_ROOT%\ace目录下创建 config.h文件，文件内容如下
#include "ace/config-win32.h"
5) 用MPC生成工程文件
VS2003
%ACE_ROOT%\bin\mwc.pl -type vc71 -value_template "configurations='MFC Release' 'MFC Debug' Release Debug" -features "mfc=1" %ACE_ROOT%\ace\ace.mwc
VS2005
%ACE_ROOT%\bin\mwc.pl -type vc8 -value_template "configurations='MFC Release' 'MFC Debug' Release Debug" -features "mfc=1" %ACE_ROOT%\ace\ace.mwc
VS2008
%ACE_ROOT%\bin\mwc.pl -type vc9 -value_template "configurations='MFC Release' 'MFC Debug' Release Debug" -features "mfc=1" %ACE_ROOT%\ace\ace.mwc
将在%ACE_ROOT%\ace目录下生成ace.sln
6) 编译
打开%ACE_ROOT%\ace\ace.sln，并编译，库生成位置在%ACE_ROOT%\lib目录下，ACEd.dll和ACEd.lib（或者ACE.dll和ACE.lib）

Linux平台
1) 下载ACE源码
ACE官方网址：http://www.cs.wustl.edu/~schmidt/ACE.html
ACE下载地址：http://download.dre.vanderbilt.edu/
2) 设置环境变量
ACE_ROOT=/home/dushubo/ACE_wrappers
MPC_ROOT=$ACE_ROOT/MPC
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ACE_ROOT/lib
PATH=.:/bin:/sbin:/usr/bin:/usr/sbin:$PATH
3) 增加config.h
在%ACE_ROOT%/ace目录下创建config.h文件，文件内容如下
#include "ace/config-linux.h"
4) 增加platform-macros.GNU
在%ACE_ROOT%/include/makeinclude目录下创建platform-macros.GNU文件，文件内容如下
include $(ACE_ROOT)/include/makeinclude/platform_linux.GNU
5) 执行如下命令
cd $ACE_ROOT
mkdir build
cd build
../configure
make
进入su
make install




```