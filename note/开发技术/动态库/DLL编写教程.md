http://www.blogjava.net/wxb_nudt/archive/2007/09/11/144371.html

```

DLL编写教程
半年不能上网，最近网络终于通了，终于可以更新博客了，写点什么呢？决定最近写一个编程技术系列，其内容是一些通用的编程技术。例如DLL，COM，Socket，多线程等等。这些技术的特点就是使用广泛，但是误解很多；网上教程很多，但是几乎没有什么优质良品。我以近几个月来的编程经验发现，很有必要好好的总结一下这些编程技术了。一来对自己是总结提高，二来可以方便光顾我博客的朋友。
好了，废话少说，言归正传。第一篇就是《DLL编写教程》，为什么起这么土的名字呢？为什么不叫《轻轻松松写DLL》或者《DLL一日通》呢？或者更nb的《深入简出DLL》呢？呵呵，常常上网搜索资料的弟兄自然知道。
本文对通用的DLL技术做了一个总结，并提供了源代码打包下载，下载地址为：
http://www.blogjava.net/Files/wxb_nudt/DLL_SRC.rar
DLL的优点
简单的说，dll有以下几个优点：
1)      节省内存。同一个软件模块，若是以源代码的形式重用，则会被编译到不同的可执行程序中，同时运行这些exe时这些模块的二进制码会被重复加载到内存中。如果使用dll，则只在内存中加载一次，所有使用该dll的进程会共享此块内存（当然，像dll中的全局变量这种东西是会被每个进程复制一份的）。
2)      不需编译的软件系统升级，若一个软件系统使用了dll，则该dll被改变（函数名不变）时，系统升级只需要更换此dll即可，不需要重新编译整个系统。事实上，很多软件都是以这种方式升级的。例如我们经常玩的星际、魔兽等游戏也是这样进行版本升级的。
3)      Dll库可以供多种编程语言使用，例如用c编写的dll可以在vb中调用。这一点上DLL还做得很不够，因此在dll的基础上发明了COM技术，更好的解决了一系列问题。
最简单的dll
开始写dll之前，你需要一个c/c++编译器和链接器，并关闭你的IDE。是的，把你的VC和C++ BUILDER之类的东东都关掉，并打开你以往只用来记电话的记事本程序。不这样做的话，你可能一辈子也不明白dll的真谛。我使用了VC自带的cl编译器和link链接器，它们一般都在vc的bin目录下。（若你没有在安装vc的时候选择注册环境变量，那么就立刻将它们的路径加入path吧）如果你还是因为离开了IDE而害怕到哭泣的话，你可以关闭这个页面并继续去看《VC++技术内幕》之类无聊的书了。
最简单的dll并不比c的helloworld难，只要一个DllMain函数即可，包含objbase.h头文件（支持COM技术的一个头文件）。若你觉得这个头文件名字难记，那么用windows.H也可以。源代码如下：dll_nolib.cpp
#include <objbase.h>
#include <iostream.h>
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 
{
    HANDLE g_hModule;
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
       cout<<"Dll is attached!"<<endl;
       g_hModule = (HINSTANCE)hModule;
       break;
    case DLL_PROCESS_DETACH:
       cout<<"Dll is detached!"<<endl;
       g_hModule=NULL;
       break;
    }
    return true;
}
其中DllMain是每个dll的入口函数，如同c的main函数一样。DllMain带有三个参数，hModule表示本dll的实例句柄（听不懂就不理它，写过windows程序的自然懂），dwReason表示dll当前所处的状态，例如DLL_PROCESS_ATTACH表示dll刚刚被加载到一个进程中，DLL_PROCESS_DETACH表示dll刚刚从一个进程中卸载。当然还有表示加载到线程中和从线程中卸载的状态，这里省略。最后一个参数是一个保留参数（目前和dll的一些状态相关，但是很少使用）。
从上面的程序可以看出，当dll被加载到一个进程中时，dll打印"Dll is attached!"语句；当dll从进程中卸载时，打印"Dll is detached!"语句。
编译dll需要以下两条命令：
cl /c dll_nolib.cpp
这条命令会将cpp编译为obj文件，若不使用/c参数则cl还会试图继续将obj链接为exe，但是这里是一个dll，没有main函数，因此会报错。不要紧，继续使用链接命令。
Link /dll dll_nolib.obj
这条命令会生成dll_nolib.dll。
注意，因为编译命令比较简单，所以本文不讨论nmake，有兴趣的可以使用nmake，或者写个bat批处理来编译链接dll。
加载DLL（显式调用）
使用dll大体上有两种方式，显式调用和隐式调用。这里首先介绍显式调用。编写一个客户端程序：dll_nolib_client.cpp
#include <windows.h>
#include <iostream.h>
int main(void)
{
    //加载我们的dll
    HINSTANCE hinst=::LoadLibrary("dll_nolib.dll"); 
    if (NULL != hinst)
    {
       cout<<"dll loaded!"<<endl;
    }
    return 0;
}
注意，调用dll使用LoadLibrary函数，它的参数就是dll的路径和名称，返回值是dll的句柄。 使用如下命令编译链接客户端：
Cl dll_nolib_client.cpp
并执行dll_nolib_client.exe，得到如下结果：
Dll is attached!
dll loaded!
Dll is detached!
以上结果表明dll已经被客户端加载过。但是这样仅仅能够将dll加载到内存，不能找到dll中的函数。
使用dumpbin命令查看DLL中的函数
Dumpbin命令可以查看一个dll中的输出函数符号名，键入如下命令：
Dumpbin –exports dll_nolib.dll
通过查看，发现dll_nolib.dll并没有输出任何函数。
如何在dll中定义输出函数
总体来说有两种方法，一种是添加一个def定义文件，在此文件中定义dll中要输出的函数；第二种是在源代码中待输出的函数前加上__declspec(dllexport)关键字。
Def文件
首先写一个带有输出函数的dll，源代码如下：dll_def.cpp
#include <objbase.h>
#include <iostream.h>
void FuncInDll (void)
{
    cout<<"FuncInDll is called!"<<endl;
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 
{
    HANDLE g_hModule;
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
       g_hModule = (HINSTANCE)hModule;
       break;
    case DLL_PROCESS_DETACH:
        g_hModule=NULL;
        break;
    }
    return TRUE;
}
这个dll的def文件如下：dll_def.def
;
; dll_def module-definition file
;
LIBRARY         dll_def.dll
DESCRIPTION     '(c)2007-2009 Wang Xuebin'
EXPORTS
                FuncInDll @1 PRIVATE
你会发现def的语法很简单，首先是LIBRARY关键字，指定dll的名字；然后一个可选的关键字DESCRIPTION，后面写上版权等信息（不写也可以）；最后是EXPORTS关键字，后面写上dll中所有要输出的函数名或变量名，然后接上@以及依次编号的数字（从1到N），最后接上修饰符。
用如下命令编译链接带有def文件的dll：
Cl /c dll_def.cpp
Link /dll dll_def.obj /def:dll_def.def
再调用dumpbin查看生成的dll_def.dll：
Dumpbin –exports dll_def.dll
得到如下结果：
Dump of file dll_def.dll
File Type: DLL
 Section contains the following exports for dll_def.dll
           0 characteristics
    46E4EE98 time date stamp Mon Sep 10 15:13:28 2007
        0.00 version
           1 ordinal base
           1 number of functions
           1 number of names
    ordinal hint RVA      name
          1    0 00001000 FuncInDll
 Summary
        2000 .data
        1000 .rdata
        1000 .reloc
        6000 .text
观察这一行
          1    0 00001000 FuncInDll
会发现该dll输出了函数FuncInDll。
显式调用DLL中的函数
写一个dll_def.dll的客户端程序：dll_def_client.cpp
#include <windows.h>
#include <iostream.h>
int main(void)
{
    //定义一个函数指针
    typedef void (* DLLWITHLIB )(void); 
    //定义一个函数指针变量
    DLLWITHLIB pfFuncInDll = NULL; 
    //加载我们的dll
    HINSTANCE hinst=::LoadLibrary("dll_def.dll"); 
    if (NULL != hinst)
    {
       cout<<"dll loaded!"<<endl;
    }
    //找到dll的FuncInDll函数
    pfFuncInDll = (DLLWITHLIB)GetProcAddress(hinst, "FuncInDll"); 
    //调用dll里的函数
    if (NULL != pfFuncInDll)
    {
       (*pfFuncInDll)();   
    }
    return 0;
}
有两个地方值得注意，第一是函数指针的定义和使用，不懂的随便找本c++书看看；第二是GetProcAddress的使用，这个API是用来查找dll中的函数地址的，第一个参数是DLL的句柄，即LoadLibrary返回的句柄，第二个参数是dll中的函数名称，即dumpbin中输出的函数名（注意，这里的函数名称指的是编译后的函数名，不一定等于dll源代码中的函数名）。
编译链接这个客户端程序，并执行会得到：
dll loaded!
FuncInDll is called!
这表明客户端成功调用了dll中的函数FuncInDll。
__declspec(dllexport)
为每个dll写def显得很繁杂，目前def使用已经比较少了，更多的是使用__declspec(dllexport)在源代码中定义dll的输出函数。
Dll写法同上，去掉def文件，并在每个要输出的函数前面加上声明__declspec(dllexport)，例如：
__declspec(dllexport) void FuncInDll (void)
这里提供一个dll源程序dll_withlib.cpp，然后编译链接。链接时不需要指定/DEF:参数，直接加/DLL参数即可，
Cl /c dll_withlib.cpp
Link /dll dll_withlib.obj
然后使用dumpbin命令查看，得到：
1    0 00001000 ?FuncInDll@@YAXXZ
可知编译后的函数名为?FuncInDll@@YAXXZ，而并不是FuncInDll，这是因为c++编译器基于函数重载的考虑，会更改函数名，这样使用显式调用的时候，也必须使用这个更改后的函数名，这显然给客户带来麻烦。为了避免这种现象，可以使用extern “C”指令来命令c++编译器以c编译器的方式来命名该函数。修改后的函数声明为：
extern "C" __declspec(dllexport) void FuncInDll (void)
dumpbin命令结果：
1    0 00001000 FuncInDll
这样，显式调用时只需查找函数名为FuncInDll的函数即可成功。
extern “C”
使用extern “C”关键字实际上相当于一个编译器的开关，它可以将c++语言的函数编译为c语言的函数名称。即保持编译后的函数符号名等于源代码中的函数名称。
隐式调用DLL
显式调用显得非常复杂，每次都要LoadLibrary，并且每个函数都必须使用GetProcAddress来得到函数指针，这对于大量使用dll函数的客户是一种困扰。而隐式调用能够像使用c函数库一样使用dll中的函数，非常方便快捷。
下面是一个隐式调用的例子：dll包含两个文件dll_withlibAndH.cpp和dll_withlibAndH.h。
代码如下：dll_withlibAndH.h
extern "C" __declspec(dllexport) void FuncInDll (void);
dll_withlibAndH.cpp
#include <objbase.h>
#include <iostream.h>
#include "dll_withLibAndH.h"//看到没有，这就是我们增加的头文件
extern "C" __declspec(dllexport) void FuncInDll (void)
{
    cout<<"FuncInDll is called!"<<endl;
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 
{
    HANDLE g_hModule;
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
       g_hModule = (HINSTANCE)hModule;
       break;
    case DLL_PROCESS_DETACH:
        g_hModule=NULL;
        break;
    }
    return TRUE;
}
编译链接命令：
Cl /c dll_withlibAndH.cpp
Link /dll dll_withlibAndH.obj
在进行隐式调用的时候需要在客户端引入头文件，并在链接时指明dll对应的lib文件（dll只要有函数输出，则链接的时候会产生一个与dll同名的lib文件）位置和名称。然后如同调用api函数库中的函数一样调用dll中的函数，不需要显式的LoadLibrary和GetProcAddress。使用最为方便。客户端代码如下：dll_withlibAndH_client.cpp
#include "dll_withLibAndH.h"
//注意路径，加载 dll的另一种方法是 Project | setting | link 设置里
#pragma comment(lib,"dll_withLibAndH.lib")
int main(void)
{
    FuncInDll();//只要这样我们就可以调用dll里的函数了
    return 0;
}
__declspec(dllexport)和__declspec(dllimport)配对使用
上面一种隐式调用的方法很不错，但是在调用DLL中的对象和重载函数时会出现问题。因为使用extern “C”修饰了输出函数，因此重载函数肯定是会出问题的，因为它们都将被编译为同一个输出符号串（c语言是不支持重载的）。
事实上不使用extern “C”是可行的，这时函数会被编译为c++符号串，例如（?FuncInDll@@YAXH@Z、 ?FuncInDll@@YAXXZ），当客户端也是c++时，也能正确的隐式调用。
这时要考虑一个情况：若DLL1.CPP是源，DLL2.CPP使用了DLL1中的函数，但同时DLL2也是一个DLL，也要输出一些函数供Client.CPP使用。那么在DLL2中如何声明所有的函数，其中包含了从DLL1中引入的函数，还包括自己要输出的函数。这个时候就需要同时使用__declspec(dllexport)和__declspec(dllimport)了。前者用来修饰本dll中的输出函数，后者用来修饰从其它dll中引入的函数。
所有的源代码包括DLL1.H，DLL1.CPP，DLL2.H，DLL2.CPP，Client.cpp。源代码可以在下载的包中找到。你可以编译链接并运行试试。
值得关注的是DLL1和DLL2中都使用的一个编码方法，见DLL2.H
#ifdef DLL_DLL2_EXPORTS
#define DLL_DLL2_API __declspec(dllexport)
#else
#define DLL_DLL2_API __declspec(dllimport)
#endif
DLL_DLL2_API void FuncInDll2(void);
DLL_DLL2_API void FuncInDll2(int);
在头文件中以这种方式定义宏DLL_DLL2_EXPORTS和DLL_DLL2_API，可以确保DLL端的函数用__declspec(dllexport)修饰，而客户端的函数用__declspec(dllimport)修饰。当然，记得在编译dll时加上参数/D “DLL_DLL2_EXPORTS”，或者干脆就在dll的cpp文件第一行加上#define DLL_DLL2_EXPORTS。
VC生成的代码也是这样的！事实证明，我是抄袭它的，hoho！
DLL中的全局变量和对象
解决了重载函数的问题，那么dll中的全局变量和对象都不是问题了，只是有一点语法需要注意。如源代码所示：dll_object.h
#ifdef DLL_OBJECT_EXPORTS
#define DLL_OBJECT_API __declspec(dllexport)
#else
#define DLL_OBJECT_API __declspec(dllimport)
#endif
DLL_OBJECT_API void FuncInDll(void);
extern DLL_OBJECT_API int g_nDll;
class DLL_OBJECT_API CDll_Object {
public:
    CDll_Object(void);
    show(void);
    // TODO: add your methods here.
};
Cpp文件dll_object.cpp如下：
#define DLL_OBJECT_EXPORTS 
#include <objbase.h>
#include <iostream.h>
#include "dll_object.h"
DLL_OBJECT_API void FuncInDll(void)
{
    cout<<"FuncInDll is called!"<<endl;
}
DLL_OBJECT_API int g_nDll = 9;
CDll_Object::CDll_Object()
{
    cout<<"ctor of CDll_Object"<<endl;
}
CDll_Object::show()
{
    cout<<"function show in class CDll_Object"<<endl;
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) 
{
    HANDLE g_hModule;
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
       g_hModule = (HINSTANCE)hModule;
       break;
    case DLL_PROCESS_DETACH:
        g_hModule=NULL;
        break;
    }
    return TRUE;
}
编译链接完后Dumpbin一下，可以看到输出了5个符号：
1    0 00001040 ??0CDll_Object@@QAE@XZ
 2    1 00001000 ??4CDll_Object@@QAEAAV0@ABV0@@Z
 3    2 00001020 ?FuncInDll@@YAXXZ
 4    3 00008040 ?g_nDll@@3HA
 5    4 00001069 ?show@CDll_Object@@QAEHXZ
它们分别代表类CDll_Object，类的构造函数，FuncInDll函数，全局变量g_nDll和类的成员函数show。下面是客户端代码：dll_object_client.cpp
#include "dll_object.h"
#include <iostream.h>
//注意路径，加载 dll的另一种方法是 Project | setting | link 设置里
#pragma comment(lib,"dll_object.lib")
int main(void)
{
    cout<<"call dll"<<endl;
    cout<<"call function in dll"<<endl;
    FuncInDll();//只要这样我们就可以调用dll里的函数了
    cout<<"global var in dll g_nDll ="<<g_nDll<<endl;
    cout<<"call member function of class CDll_Object in dll"<<endl;
    CDll_Object obj;
    obj.show();
    return 0;
}
运行这个客户端可以看到：
call dll
call function in dll
FuncInDll is called!
global var in dll g_nDll =9
call member function of class CDll_Object in dll
ctor of CDll_Object
function show in class CDll_Object
可知，在客户端成功的访问了dll中的全局变量，并创建了dll中定义的C++对象，还调用了该对象的成员函数。
中间的小结
牢记一点，说到底，DLL是对应C语言的动态链接技术，在输出C函数和变量时显得方便快捷；而在输出C++类、函数时需要通过各种手段，而且也并没有完美的解决方案，除非客户端也是c++。
记住，只有COM是对应C++语言的技术。
下面开始对各各问题一一小结。
显式调用和隐式调用
何时使用显式调用？何时使用隐式调用？我认为，只有一个时候使用显式调用是合理的，就是当客户端不是C/C++的时候。这时是无法隐式调用的。例如用VB调用C++写的dll。（VB我不会，所以没有例子）
Def和__declspec(dllexport)
其实def的功能相当于extern “C” __declspec(dllexport)，所以它也仅能处理C函数，而不能处理重载函数。而__declspec(dllexport)和__declspec(dllimport)配合使用能够适应任何情况，因此__declspec(dllexport)是更为先进的方法。所以，目前普遍的看法是不使用def文件，我也同意这个看法。
从其它语言调用DLL
从其它编程语言中调用DLL，有两个最大的问题，第一个就是函数符号的问题，前面已经多次提过了。这里有个两难选择，若使用extern “C”，则函数名称保持不变，调用较方便，但是不支持函数重载等一系列c++功能；若不使用extern “C”，则调用前要查看编译后的符号，非常不方便。
第二个问题就是函数调用压栈顺序的问题，即__cdecl和__stdcall的问题。__cdecl是常规的C/C++调用约定，这种调用约定下，函数调用后栈的清理工作是由调用者完成的。__stdcall是标准的调用约定，即这些函数将在返回到调用者之前将参数从栈中删除。
这两个问题DLL都不能很好的解决，只能说凑合着用。但是在COM中，都得到了完美的解决。所以，要在Windows平台实现语言无关性，还是只有使用COM中间件。
总而言之，除非客户端也使用C++，否则dll是不便于支持函数重载、类等c++特性的。DLL对c函数的支持很好，我想这也是为什么windows的函数库使用C加dll实现的理由之一。
在VC中编写DLL
在VC中创建、编译、链接dll是非常方便的，点击fileàNewàProjectàWin32 Dynamic-Link Library，输入dll名称dll_InVC然后点击确定。然后选择A DLL that export some symbols，点击Finish。即可得到一个完整的DLL。
仔细观察其源代码，是不是有很多地方似曾相识啊，哈哈！
最后
贴上女儿近照一张，小家伙长得太快了!
```