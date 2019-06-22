## Socket编程指南及示例程序
```
例子代码就在我的博客中，包括六个UDP和TCP发送接受的cpp文件，一个基于MFC的局域网聊天小工具工程，和此小工具的所有运行时库、资源和执行程序。代码的压缩包位置是http://www.blogjava.net/Files/wxb_nudt/socket_src.rar。1 前言
在一些常用的编程技术中，Socket网络编程可以说是最简单的一种。而且Socket编程需要的基础知识很少，适合初学者学习网络编程。目前支持网络传输的技术、语言和工具繁多，但是大部分都是基于Socket开发的，虽说这些“高级”的网络技术屏蔽了大部分底层实现，号称能极大程度的简化开发，而事实上如果你没有一点Socket基础，要理解和应用这些技术还是很困难的，而且会让你成为“半瓢水”。
深有感触的是当年我学习CORBA的时候，由于当时各方面的基础薄弱，整整啃了半年书，最终还是一头雾水。如果现在让我带一个人学CORBA，我一定会安排好顺序：首先弄清C++语法；然后是VC编译环境或者nmake的用法；接下来学习一些网络基础知识；然后是Socket编程；这些大概要花费3、4个月。有了这些基础学习CORBA一周即可弄懂，两个月就可以基于CORBA进行开发了。
好了，说了半天其实中心思想就一个，Socket很简单，很好学！如果你会C++或者JAVA，又懂一点点网络基础如TCP和UDP的机制，那么你看完本文就可以熟练进行Socket开发了。2 Socket简介（全文摘抄）
（本节内容全部抄自网络，不保证正确性，有兴趣的可以看看！）
80年代初，美国政府的高级研究工程机构（ARPA）给加利福尼亚大学Berkeley分校提供了资金，让他们在UNIX操作系统下实现TCP/IP协议。在这个项目中，研究人员为TCP/IP网络通信开发了一个API（应用程序接口）。这个API称为Socket接口（套接字）。今天，SOCKET接口是TCP/IP网络最为通用的API，也是在INTERNET上进行应用开发最为通用的API。
90年代初，由Microsoft联合了其他几家公司共同制定了一套WINDOWS下的网络编程接口，即WindowsSockets规范。它是BerkeleySockets的重要扩充，主要是增加了一些异步函数，并增加了符合Windows消息驱动特性的网络事件异步选择机制。WINDOWSSOCKETS规范是一套开放的、支持多种协议的Windows下的网络编程接口。从1991年的1.0版到1995年的2.0.8版，经过不断完善并在Intel、Microsoft、Sun、SGI、Informix、Novell等公司的全力支持下，已成为Windows网络编程的事实上的标准。目前，在实际应用中的WINDOWSSOKCETS规范主要有1.1版和2.0版。两者的最重要区别是1.1版只支持TCP/IP协议，而2.0版可以支持多协议。2.0版有良好的向后兼容性，任何使用1.1版的源代码，二进制文件，应用程序都可以不加修改地在2.0规范下使用。
SOCKET实际在计算机中提供了一个通信端口，可以通过这个端口与任何一个具有SOCKET接口的计算机通信。应用程序在网络上传输，接收的信息都通过这个SOCKET接口来实现。在应用开发中就像使用文件句柄一样，可以对SOCKET句柄进行读，写操作。3 再说两句
网上很多文章对于Socket的来龙去脉有如教科书一般的精准。但是涉及具体编程技术就往往被VC等集成开发环境所毒害了，把Windows SDK、MFC、Socket、多线程、DLL以及编译链接等等技术搅合在一起煮成一锅夹生饭。
既然要学习Socket，就应该用最简单直白的方式把Socket的几个使用要点讲出来。我认为程序员最关心的有以下几点，按照优先级排列如下：
1. Socket的机制是什么？
2. 用C/C++写Socket需要什么头文件、库文件、DLL，它们可以由谁提供，安装后一般处于系统的哪个文件夹内？
3. 编写Socket程序需要的编程基础是什么？
4. Socket库内最重要的几个函数和数据类型是什么？
5. 两个最简单的例子程序；
6. 一个贴近应用的稍微复杂的Socket应用程序。
我将一一讲述这些要点，并给出从简到繁，从朴素到花哨的所有源代码以及编译链接的命令。4 Socket的机制是什么？
我们可以简单的把Socket理解为一个可以连通网络上不同计算机程序之间的管道，把一堆数据从管道的A端扔进去，则会从管道的B端（也许同时还可以从C、D、E、F……端冒出来）。管道的端口由两个因素来唯一确认，即机器的IP地址和程序所使用的端口号。IP地址的含义所有人都知道，所谓端口号就是程序员指定的一个数字，许多著名的木马程序成天在网络上扫描不同的端口号就是为了获取一个可以连通的端口从而进行破坏。比较著名的端口号有http的80端口和ftp的21端口（我记错了么？）。当然，建议大家自己写程序不要使用太小的端口号，它们一般被系统占用了，也不要使用一些著名的端口，一般来说使用1000~5000之内的端口比较好。
Socket可以支持数据的发送和接收，它会定义一种称为套接字的变量，发送数据时首先创建套接字，然后使用该套接字的sendto等方法对准某个IP/端口进行数据发送；接收端也首先创建套接字，然后将该套接字绑定到一个IP/端口上，所有发向此端口的数据会被该套接字的recv等函数读出。如同读出文件中的数据一样。5 所需的头文件、库文件和DLL
对于目前使用最广泛的Windows Socket2.0版本，所需的一些文件如下（以安装了VC6为例说明其物理位置）：
l 头文件winsock2.h，通常处于C:"Program Files"Microsoft Visual Studio"VC98"INCLUDE；查看该头文件可知其中又包含了windows.h和pshpack4.h头文件，因此在windows中的一些常用API都可以使用；
l 库文件Ws2_32.lib，通常处于C:"Program Files"Microsoft Visual Studio"VC98"Lib；
l DLL文件Ws2_32.dll，通常处于C:"WINDOWS"system32，这个是可以猜到的。6 编写Socket程序需要的编程基础
在开始编写Socket程序之前，需要以下编程基础：
l C++语法；
l 一点点windows SDK的基础，了解一些SDK的数据类型与API的调用方式；
l 一点点编译、链接和执行的技术；知道cl和link的最常用用法即可。7 UDP
用最通俗的话讲，所谓UDP，就是发送出去就不管的一种网络协议。因此UDP编程的发送端只管发送就可以了，不用检查网络连接状态。下面用例子来说明怎样编写UDP，并会详细解释每个API和数据类型。7.1 UDP广播发送程序
下面是一个用UDP发送广播报文的例子。
#include <winsock2.h>
#include <iostream.h>
void main()
{
SOCKET sock; //socket套接字
char szMsg[] = "this is a UDP test package";//被发送的字段
//1.启动SOCKET库，版本为2.0
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 2, 0 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( 0 != err ) //检查Socket初始化是否成功
{
cout<<"Socket2.0初始化失败，Exit!";
return;
}
//检查Socket库的版本是否为2.0
if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
{
WSACleanup( );
return;
}
//2.创建socket，
sock = socket(
AF_INET, //internetwork: UDP, TCP, etc
SOCK_DGRAM, //SOCK_DGRAM说明是UDP类型
0 //protocol
);
if (INVALID_SOCKET == sock ) {
cout<<"Socket 创建失败，Exit!";
return;
}
//3.设置该套接字为广播类型，
bool opt = true;
setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char FAR *>(&opt), sizeof(opt));
//4.设置发往的地址
sockaddr_in addrto; //发往的地址
memset(&addrto,0,sizeof(addrto));
addrto.sin_family = AF_INET; //地址类型为internetwork
addrto.sin_addr.s_addr = INADDR_BROADCAST; //设置ip为广播地址
addrto.sin_port = htons(7861); //端口号为7861
int nlen=sizeof(addrto);
unsigned int uIndex = 1;
while(true)
{
Sleep(1000); //程序休眠一秒
//向广播地址发送消息
if( sendto(sock, szMsg, strlen(szMsg), 0, (sockaddr*)&addrto,nlen)
== SOCKET_ERROR )
cout<<WSAGetLastError()<<endl;
else
cout<<uIndex++<<":an UDP package is sended."<<endl;
}
if (!closesocket(sock)) //关闭套接字
{
WSAGetLastError();
return;
}
if (!WSACleanup()) //关闭Socket库
{
WSAGetLastError();
return;
}
}
编译命令：
CL /c UDP_Send_Broadcast.cpp
链接命令（注意如果找不到该库，则要在后面的/LIBPATH参数后加上库的路径）：
link UDP_Send_Broadcast.obj ws2_32.lib
执行命令：
D:"Code"成品代码"Socket"socket_src>UDP_Send_Broadcast.exe
1:an UDP package is sended.
2:an UDP package is sended.
3:an UDP package is sended.
4:an UDP package is sended.
^C
下面一一解释代码中出现的数据类型与API函数。有耐心的可以仔细看看，没耐心的依葫芦画瓢也可以写程序了。7.2 SOCKET类型
SOCKET是socket套接字类型，在WINSOCK2.H中有如下定义：
typedef unsigned int u_int;
typedef u_int SOCKET;
可知套接字实际上就是一个无符号整型，它将被Socket环境管理和使用。套接字将被创建、设置、用来发送和接收数据，最后会被关闭。7.3 WORD类型、MAKEWORD、LOBYTE和HIBYTE宏
WORD类型是一个16位的无符号整型，在WTYPES.H中被定义为：
typedef unsigned short WORD;
其目的是提供两个字节的存储，在Socket中这两个字节可以表示主版本号和副版本号。使用MAKEWORD宏可以给一个WORD类型赋值。例如要表示主版本号2，副版本号0，可以使用以下代码：
WORD wVersionRequested;
wVersionRequested = MAKEWORD( 2, 0 );
注意低位内存存储主版本号2，高位内存存储副版本号0，其值为0x0002。使用宏LOBYTE可以读取WORD的低位字节，HIBYTE可以读取高位字节。7.4 WSADATA类型和LPWSADATA类型
WSADATA类型是一个结构，描述了Socket库的一些相关信息，其结构定义如下：
typedef struct WSAData {
WORD wVersion;
WORD wHighVersion;
char szDescription[WSADESCRIPTION_LEN+1];
char szSystemStatus[WSASYS_STATUS_LEN+1];
unsigned short iMaxSockets;
unsigned short iMaxUdpDg;
char FAR * lpVendorInfo;
} WSADATA;
typedef WSADATA FAR *LPWSADATA;
值得注意的就是wVersion字段，存储了Socket的版本类型。LPWSADATA是WSADATA的指针类型。它们不用程序员手动填写，而是通过Socket的初始化函数WSAStartup读取出来。7.5 WSAStartup函数
WSAStartup函数被用来初始化Socket环境，它的定义如下：
int PASCAL FAR WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData);
其返回值为整型，调用方式为PASCAL（即标准类型，PASCAL等于__stdcall），参数有两个，第一个参数为WORD类型，指明了Socket的版本号，第二个参数为WSADATA类型的指针。
若返回值为0，则初始化成功，若不为0则失败。7.6 WSACleanup函数
这是Socket环境的退出函数。返回值为0表示成功，SOCKET_ERROR表示失败。7.7 socket函数
socket的创建函数，其定义为：
SOCKET PASCAL FAR socket (int af, int type, int protocol);
第一个参数为int af，代表网络地址族，目前只有一种取值是有效的，即AF_INET，代表internet地址族；
第二个参数为int type，代表网络协议类型，SOCK_DGRAM代表UDP协议，SOCK_STREAM代表TCP协议；
第三个参数为int protocol，指定网络地址族的特殊协议，目前无用，赋值0即可。
返回值为SOCKET，若返回INVALID_SOCKET则失败。7.8 setsockopt函数
这个函数用来设置Socket的属性，若不能正确设置socket属性，则数据的发送和接收会失败。定义如下：
int PASCAL FAR setsockopt (SOCKET s, int level, int optname,
const char FAR * optval, int optlen);
其返回值为int类型，0代表成功，SOCKET_ERROR代表有错误发生。
第一个参数SOCKET s，代表要设置的套接字；
第二个参数int level，代表要设置的属性所处的层次，层次包含以下取值：SOL_SOCKET代表套接字层次；IPPROTO_TCP代表TCP协议层次，IPPROTO_IP代表IP协议层次（后面两个我都没有用过）；
第三个参数int optname，代表设置参数的名称，SO_BROADCAST代表允许发送广播数据的属性，其它属性可参考MSDN；
第四个参数const char FAR * optval，代表指向存储参数数值的指针，注意这里可能要使用reinterpret_cast类型转换；
第五个参数int optlen，代表存储参数数值变量的长度。7.9 sockaddr_in、in_addr类型，inet_addr、inet_ntoa函数
sockaddr_in定义了socket发送和接收数据包的地址，定义：
struct sockaddr_in {
short sin_family;
u_short sin_port;
struct in_addr sin_addr;
char sin_zero[8];
};
其中in_addr的定义如下：
struct in_addr {
union {
struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
struct { u_short s_w1,s_w2; } S_un_w;
u_long S_addr;
} S_un;
首先阐述in_addr的含义，很显然它是一个存储ip地址的联合体（忘记union含义的请看c++书），有三种表达方式：
第一种用四个字节来表示IP地址的四个数字；
第二种用两个双字节来表示IP地址；
第三种用一个长整型来表示IP地址。
给in_addr赋值的一种最简单方法是使用inet_addr函数，它可以把一个代表IP地址的字符串赋值转换为in_addr类型，如
addrto.sin_addr.s_addr=inet_addr("192.168.0.2");
本例子中由于是广播地址，所以没有使用这个函数。其反函数是inet_ntoa，可以把一个in_addr类型转换为一个字符串。
sockaddr_in的含义比in_addr的含义要广泛，其各个字段的含义和取值如下：
第一个字段short sin_family，代表网络地址族，如前所述，只能取值AF_INET；
第二个字段u_short sin_port，代表IP地址端口，由程序员指定；
第三个字段struct in_addr sin_addr，代表IP地址；
第四个字段char sin_zero[8]，很搞笑，是为了保证sockaddr_in与SOCKADDR类型的长度相等而填充进来的字段。
以下代表指明了广播地址，端口号为7861的一个地址：
sockaddr_in addrto; //发往的地址
memset(&addrto,0,sizeof(addrto));
addrto.sin_family = AF_INET; //地址类型为internetwork
addrto.sin_addr.s_addr = INADDR_BROADCAST; //设置ip为广播地址
addrto.sin_port = htons(7861); //端口号为78617.10 sockaddr类型
sockaddr类型是用来表示Socket地址的类型，同上面的sockaddr_in类型相比，sockaddr的适用范围更广，因为sockaddr_in只适用于TCP/IP地址。Sockaddr的定义如下：
struct sockaddr {
u_short sa_family;
char sa_data[14];
};
可知sockaddr有16个字节，而sockaddr_in也有16个字节，所以sockaddr_in是可以强制类型转换为sockaddr的。事实上也往往使用这种方法。7.11 Sleep函数
线程挂起函数，表示线程挂起一段时间。Sleep(1000)表示挂起一秒。定义于WINBASE.H头文件中。WINBASE.H又被包含于WINDOWS.H中，然后WINDOWS.H被WINSOCK2.H包含。所以在本例中使用Sleep函数不需要包含其它头文件。7.12 sendto函数
在Socket中有两套发送和接收函数，一是sendto和recvfrom；二是send和recv。前一套在函数参数中要指明地址；而后一套需要先将套接字和一个地址绑定，然后直接发送和接收，不需绑定地址。sendto的定义如下：
int PASCAL FAR sendto (SOCKET s, const char FAR * buf, int len, int flags, const struct sockaddr FAR *to, int tolen);
第一个参数就是套接字；
第二个参数是要传送的数据指针；
第三个参数是要传送的数据长度（字节数）；
第四个参数是传送方式的标识，如果不需要特殊要求则可以设置为0，其它值请参考MSDN；
第五个参数是目标地址，注意这里使用的是sockaddr的指针；
第六个参数是地址的长度；
返回值为整型，如果成功，则返回发送的字节数，失败则返回SOCKET_ERROR。7.13 WSAGetLastError函数
该函数用来在Socket相关API失败后读取错误码，根据这些错误码可以对照查出错误原因。7.14 closesocket
关闭套接字，其参数为SOCKET类型。成功返回0，失败返回SOCKET_ERROR。7.15 小结
总结以上内容，写一个UDP发送程序的步骤如下：
1. 用WSAStartup函数初始化Socket环境；
2. 用socket函数创建一个套接字；
3. 用setsockopt函数设置套接字的属性，例如设置为广播类型；很多时候该步骤可以省略；
4. 创建一个sockaddr_in，并指定其IP地址和端口号；
5. 用sendto函数向指定地址发送数据，这里的目标地址就是广播地址；注意这里不需要绑定，即使绑定了，其地址也会被sendto中的参数覆盖；若使用send函数则会出错，因为send是面向连接的，而UDP是非连接的，只能使用sendto发送数据；
6. 用closesocket函数关闭套接字；
7. 用WSACleanup函数关闭Socket环境。
那么，与之类似，一个UDP接收程序的步骤如下，注意接收方一定要bind套接字：
1. 用WSAStartup函数初始化Socket环境；
2. 用socket函数创建一个套接字；
3. 用setsockopt函数设置套接字的属性，例如设置为广播类型；
4. 创建一个sockaddr_in，并指定其IP地址和端口号；
5. 用bind函数将套接字与接收的地址绑定起来，然后调用recvfrom函数或者recv接收数据； 注意这里一定要绑定，因为接收报文的套接字必须在网络上有一个绑定的名称才能保证正确接收数据；
6. 用closesocket函数关闭套接字；
7. 用WSACleanup函数关闭Socket环境。
广播接收程序见源程序代码UDP_Recv_Broadcast.cpp。编译、链接、执行与UDP_Send_Broadcast类似。7.16 UDP点对点发送接收程序
广播发送和接收使用并不广泛，一般来说指定发送和接收的IP比较常用。点对点方式的UDP发送和接收与上面的例子非常类似，不同的就是需要指定一个具体的IP地址。并且不需要调用setsockopt设置socket的广播属性。
其具体源代码见UDP_Send_P2P.cpp和UDP_Recv_P2P.cpp。
注意在使用这两个程序时要设为自己所需的IP。8 TCP
TCP与UDP最大的不同之处在于TCP是一个面向连接的协议，在进行数据收发之前TCP必须进行连接，并且在收发的时候必须保持该连接。
发送方的步骤如下（省略了Socket环境的初始化、关闭等内容）：
1. 用socket函数创建一个套接字sock；
2. 用bind将sock绑定到本地地址；
3. 用listen侦听sock套接字；
4. 用accept函数接收客户方的连接，返回客户方套接字clientSocket；
5. 在客户方套接字clientSocket上使用send发送数据；
6. 用closesocket函数关闭套接字sock和clientSocket；
而接收方的步骤如下：
1. 用socket函数创建一个套接字sock；
2. 创建一个指向服务方的远程地址；
3. 用connect将sock连接到服务方，使用远程地址；
4. 在套接字上使用recv接收数据；
5. 用closesocket函数关闭套接字sock；
值得注意的是，在服务方有两个地址，一个是本地地址myaddr，另一个是目标地址addrto。本地地址myaddr用来和本地套接字sock绑定，目标地址被sock用来accept客户方套接字clientSocket。这样sock和clientSocket连接成功，这两个地址也连接上了。在服务方使用clientSocket发送数据，则会从本地地址传送到目标地址。
在客户方只有一个地址，即来源地址addrfrom。这个地址被用来connect远程的服务方套接字，connect成功则本地套接字与远程的来源地址连接了，因此可以使用该套接字接收远程数据。其实这时客户方套接字已经被隐性的绑定了本地地址，所以不需要显式调用bind函数，即使调用也不会影像结果。
具体源代码见TCP_Send.cpp和TCP_Recv.cpp。注意将源代码中的IP地址修改为符合自己需要的IP。为了减少代码复杂性，没有使用读取本机IP的代码，后续例子程序中含有此功能代码。8.1 bind函数
bind函数用来将一个套接字绑定到一个IP地址。一般只在服务方（即数据发送方）调用，很多函数会隐式的调用bind函数。8.2 listen函数
从服务方监听客户方的连接。同一个套接字可以多次监听。8.3 connect和accept函数
connect是客户方连接服务方的函数，而accept是服务方同意客户方连接的函数。这两个配套函数分别在各自的程序中被成功调用后就可以收发数据了。8.4 send和recv函数
send和recv是用来发送和接收数据的两个重要函数。send只能在已经连接的状态下使用，而recv可以面向连接和非连接的状态下使用。
send的定义如下：
int WSAAPI send(
SOCKET s,
const char FAR * buf,
int len,
int flags
);
其参数的含义和sendto中的前四个参数一样。而recv的定义如下：
int WSAAPI recv(
SOCKET s,
char FAR * buf,
int len,
int flags
);
其参数含义与send中的参数含义一样。9 一个局域网聊天工具的编写
掌握了以上关于socket的基本用法，编写一个局域网聊天程序也就变得非常简单，如同设计一个普通的对话框程序一样。9.1 功能设计
功能设计如下：
1. 要能够指定聊天对象的IP和端口（端口可以内部确定）；
2. 要能够发送消息给指定聊天对象；
3. 要能够接收聊天对象的消息；
4. 接收消息时要播放声音；
5. 接收消息时如果当前对话框不是最前端，要闪动图标；
6. 要有托盘图标，可以将对话框收入托盘；9.2 功能实现
将内部端口设为3456，提供一个IP地址控件来设置聊天对象的IP。该控件必须能够读取IP地址并赋值给内部变量。将地址转换为in_addr类型。
发送消息需要使用一个套接字。
接收消息也需要使用一个套接字，由于发送消息也使用了一个套接字，为了在同一个进程中同时发送和接收消息，需要使用多线程技术，将发送消息的线程设为主线程；而接收消息的线程设为子线程，子线程只负责接收UDP消息，在收到消息后显示到主界面中。
接收消息时播放声音这个功能在子线程中完成，使用sndPlaySound函数，并提供一个wav文件即可。
闪动图标这个最白痴的功能需要使用一个Timer，在主对话框类中添加一个OnTimer函数，定时检查当前窗口状态变量是否为假，若为假就每次设置另一个图标。若当前窗口显示到最顶端，则设置为默认图标。
托盘图标功能用网上下载的CtrayIcon类轻松搞定。需要提供一个自定义消息，一个弹出菜单资源。9.3 所需资源
头文件：winsock2.h，Mmsystem.h
库文件：ws2_32.lib，winmm.lib
dll：Ws2_32.dll，winmm.dll
wav文件：recv.wav
图标：一个主程序图标IDI_MAIN、四个变化图标IDI_ICON1~4;
菜单：一个给托盘用的弹出菜单IDR_TRAYICON;
说明，Mmsystem.h和winmm.lib、winmm.dll是为了那个播放声音的功能。9.4 托盘功能
托盘属于界面功能，是变更很少的需求，因此首先完成。
1. 引入TRAYICON.H和TRAYICON.cpp两个类；
2. 在CLANTalkDlg类中加入一个CTrayIconm_trayIcon;属性；
3. 在CLANTalkDlg的构造函数中初始化m_trayIcon，m_trayIcon(IDR_TRAYICON)；
4. 添加一个自定义消息WM_MY_TRAY_NOTIFICATION，即在三个地方添加消息定义、消息响应函数、消息映射；
5. 在InitDialog方法中调用托盘初始化的两个函数 m_trayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION); m_trayIcon.SetIcon(IDI_MAIN);
6. 重写OnClose方法，添加弹出菜单的OnAppSuspend和OnAppOpen以及OnAppAbout方法；
7. 重写对话框的OnCancel方法。9.5 动态图标
动态图标也是界面相关功能，首先完成。
1. 添加四个HICON变量m_hIcon1,m_hIcon2,m_hIcon3,m_hIcon4；
2. 在构造函数中初始化这四个变量m_hIcon1 = AfxGetApp()->LoadIcon(IDI_ICON1);
3. 在InitDialog中设置调用SetTimer(1,300,NULL);设置一个timer，id为1，间隔为300微秒；
4. 添加一个布尔属性m_bDynamicIcon，指示目前是否需要动态图标，并给出一个设置函数SetDynamicIcon；
5. 添加一个OnTimer函数，让每次timer调用时根据m_bDynamicIcon的值修改图标；
两个地方是用来设置动态图标的，一个是当程序收到消息并且程序不在桌面顶端时，这时设置为动态图标，在后面的消息接收线程中处理；二是当程序显示到桌面顶端时，设置为非动态；
重载OnActivate方法可以完成第二个时刻的要求。当窗口状态为WA_ACTIVE或者WA_CLICKACTIVE时SetDynamicIcon(false)，否则设置SetDynamicIcon(true);9.6 发送UDP报文功能
发送UDP报文只需在主线程中完成，需要以下步骤：
1. 初始化Socket环境，这可以在CLANTalkApp的InitInstance中完成，同理关闭Socket环境在ExitInstance中完成；我们可以使用前面的方法，也可以直接调用MFC中的AfxSocketInit函数，这个函数可以确保在程序结束时自动关闭Socket环境；
2. 创建socket，考虑到报错信息需要弹出对话框，因此不在CLANTalkDlg的构造函数中创建，而是在InitDialog中构建；发送报文的socket为m_sendSock；
3. 设置目的地址功能，需要一个地址赋值函数setAddress(char* szAddr);可以将一个字符串地址赋值给sockaddr_in形式的地址；在CLANTalkDlg中增加一个sockaddr_in m_addrto;属性；
4. 读取文本框中的文字，用sendto发送到对象地址；
5. 清空文本框，在记录框中添加聊天记录。
这时可以使用前面的UDP简单接收程序来辅助测试，因为此时还未完成报文接收功能。9.7 接收UDP报文功能
接收UDP报文要考虑几个问题，第一个是要创建一个子线程，在子线程中接收报文；第二是接收报文和发送报文要有互斥机制，以免冲突；第三是接收到报文要播放声音；第四是接收报文且当前窗口不在桌面顶端要调用动态图标功能。
按照以上需求设计步骤如下：
1. 创建接收套接字m_recvSock，
2. 利用gethostname和gethostbyname等函数获取本机IP，并将套接字bind到该地址；
3. 添加一个CwinThread* m_pRecvThread属性，并在InitDialog中调用AfxBeginThread创建子线程；
4. 编写子线程运行函数void RecvProcess(LPVOID pParam)，这时一个全局函数，为了方便调用CLANTalkDlg类中的各种变量与方法，将CLANTalkDlg类的指针作为参数传入子线程函数，并将RecvProcess设置为CLANTalkDlg类的友元。
5. 子线程函数中完成以下功能：利用recv接收报文；保存聊天记录；判断当前窗口是否在前台，并修改动态图标属性；播放声音。
6. 用来记录聊天信息的ClistBox的Sort属性要去掉，否则记录会按内容排序，很不好看。在RC编辑器中去掉这个属性即可。
7. 最后要注意，在主线程退出时要保证子线程退出，但此时子线程还阻塞在recv方法上，因此主线程向自己发送一条消息消除阻塞，同时改变子线程退出标志保证子线程可以退出。9.8 设置聊天对象IP
点击“确认对象”按钮时，检测IP地址控件，如果IP地址有效，则将IP地址读入内部属性。这个IP地址作为发送信息的目标地址。
这个设置只能设置发送消息的对象，所有人都可以向本机发送信息，只要他的端口是正确的。9.9 编译链接和运行
下载压缩包后可以打开VC工程编译链接，若直接运行则可以点击LANTalkExeFile目录中的可执行文件，这个目标包含了运行所需要的所有dll和资源文件。
当然，如果需要可以用InstallShield做一个安装程序，不过看来是没有必要的。9.10 小结
这个聊天程序很简单，但是基本上具有了一个框架，可以有最简单的聊天功能。要在此基础上进行扩展几乎已经没有什么技术问题了。10 使用好的Socket包可以简化开发过程
本文中所有的技术尽量采用最原始的方式来使用。例如多线程使用的是AfxBeginThread，套接字使用了最原始的套接字，并在很多地方直接使用了SDK函数，而尽量避免了MFC等代码框架，这是为了方便他人掌握技术的最基本内涵。
其实在具体的编程中，当然是怎么方便怎么来，Socket和多线程以及界面等功能都有大量方便可用的代码库，复用这些代码库会比自己动手写方便很多。但是，掌握了基本原理再使用这些库，事半功倍！

```