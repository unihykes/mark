

```cpp


http://blog.csdn.net/hurtmanzc/article/details/8553830

Linux下显示加载动态库注意事项


    最近将Windows上的若干个工程移植到Linux平台，exe工程通过显示加载的方

式调用一个插件dll中的功能，在Windows平台上运行都很正常，但是在Linux平台

上遇到一个很诡异的现象，在Linux平台显示调用插件dll(已经编译成so，为了描

述方便，这里统一用动态库、DLL等window平台上的术语)中的函数时，发现一层

层跟进去后，有函数调用的不是编译dll时cpp中的函数，而是调用到另外一个dll

中的同名函数，开始以为是调试环境的问题（用到一个调试插件，在vs2010上远

程调试Linux服务器上的程序），但是经过修改文件名重新编译后，发现问题仍在

，通过逐行调试发现并非是调试器选错cpp源文件的问题，调试过程的每一行都能

够和非期望cpp中的源码对应上，说明并不是调试器的问题，而是在Linux端确实

在执行该非期望cpp编译出来的机器码。

    这就太奇怪了，按Windows编程经验，程序一旦编译后，在Link的时候各个符

号就都有了明确地址，怎么会在运行期间发生变化呢？顶着满头的雾水折腾了一

天，临近下班的时候，搜到一篇讲解dlopen函数文章，似乎说的这个问题有关系

，一下有种如获至宝的感觉。原来Linux平台上用dlopen打开共享库时，可以指定

对共享库中符号的处理方式，修改成“动态库中定义的符号不能被其后打开的其

它库重定位”模式后，在调试程序，发现可以正确调用期望cpp中的函数了。

修改之前：
 dlopen(strLibName, RTLD_LAZY);
修改之后：
 dlopen(strLibName, RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND);

谜底揭开以后，才发现是一个如此简单的问题。

附：dlopen 说明
 功能：打开一个动态链接库
 包含头文件：
#include <dlfcn.h>
函数定义：
void * dlopen( const char * pathname, int mode);
函数描述：
 在dlopen（）函数以指定模式打开指定的动态连接库文件，并返回一个句柄给调

用进程。使用dlclose（）来卸载打开的库。
mode是打开方式，其值有多个，不同操作系统上实现的功能有所不同，在linux下

，按功能可分为三类：
1、解析方式
RTLD_LAZY：在dlopen返回前，对于动态库中的未定义的符号不执行解析（只对函

数引用有效，对于变量引用总是立即解析）。
RTLD_NOW： 需要在dlopen返回前，解析出所有未定义符号，如果解析不出来，在

dlopen会返回NULL，错误为：: undefined symbol: xxxx.......
 2、作用范围，可与解析方式通过“|”组合使用。
RTLD_GLOBAL：动态库中定义的符号可被其后打开的其它库重定位。
RTLD_LOCAL： 与RTLD_GLOBAL作用相反，动态库中定义的符号不能被其后打开的

其它库重定位。如果没有指明是RTLD_GLOBAL还是RTLD_LOCAL，则缺省为

RTLD_LOCAL。
3、作用方式
RTLD_NODELETE： 在dlclose()期间不卸载库，并且在以后使用dlopen()重新加载

库时不初始化库中的静态变量。这个flag不是POSIX-2001标准。
RTLD_NOLOAD： 不加载库。可用于测试库是否已加载(dlopen()返回NULL说明未加

载，否则说明已加载），也可用于改变已加载库的flag，如：先前加载库的flag

为RTLD_LOCAL，用dlopen(RTLD_NOLOAD|RTLD_GLOBAL)后flag将变成RTLD_GLOBAL

。这个flag不是POSIX-2001标准。
RTLD_DEEPBIND：在搜索全局符号前先搜索库内的符号，避免同名符号的冲突。这

个flag不是POSIX-2001标准。


```