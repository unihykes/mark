VC++下命名管道编程的原理及实现
http://developer.51cto.com/art/200708/53201.htm

```
概述
管道（Pipe）实际是用于进程间通信的一段共享内存，创建管道的进程称为管道服务器，连接到一个管道的进程为管道客户机。命名管道（Named Pipes）是在管道服务器和一台或多台管道客户机之间进行单向或双向通信的一种命名的管道。一个命名管道的所有实例共享同一个管道名，但是每一个实例均拥有独立的缓存与句柄，并且为客户——服务通信提供有一个分离的管道。实例的使用保证了多个管道客户能够在同一时间使用同一个命名管道。
Microsoft Windows NT、Windows 2000、Windows 95以及Windows 98均提供对命名管道的支持（不包括Windows CE），但只有Windows NT和Windows 2000才支持服务器端的命名管道技术。命名管道可以在同一台计算机的不同进程之间，或在跨越一个网络的不同计算机的不同进程之间进行有连接的可靠数据通信，如果连接中断，连接双方都能立即收到连接断开的信息。命令管道是围绕Windows文件系统而设计的一种机制，采用的是命名管道文件系统（Named Pipe File System, NPFS）接口。对数据的收发也采用文件读写函数ReadFile（）和WriteFile（）来完成。在设计上，由于命名管道也利用了微软网络提供者（MSNP）重定向器，因此无需涉及底层的通信协议细节。命名管道还充分利用了Windows NT及Windows 2000内建的安全特性，通信的安全性相对较好。
命名规范及通信模式
每一个命名管道都有一个唯一的名字以区分于存在于系统的命名对象列表中的其他命名管道。管道服务器在调用CreateNamedPipe（）函数创建命名管道的一个或多个实例时为其指定了名称。对于管道客户机，则是在调用CreateFile（）或CallNamedPipe（）函数以连接一个命名管道实例时对管道名进行指定。命名管道的命名规范与邮槽有些类似，对其标识也是采用的UNC格式：

\\Server\Pipe\[Path]Name

其中，第一部分\\Server指定了服务器的名字，命名管道服务即在此服务器创建，其字串部分可表示为一个小数点（表示本机）、星号（当前网络字段）、域名或是一个真正的服务；第二部分\Pipe与邮槽的\Mailslot一样是一个不可变化的硬编码字串，以指出该文件是从属于NPFS；第三部分\[Path]Name则使应用程序可以唯一定义及标识一个命名管道的名字，而且可以设置多级目录。
命名管道提供了两种基本的通信模式：字节模式和消息模式。可在CreateNamePipe（）创建命名管道时分别用PIPE_TYPE_BYTE和PIPE_TYPE_MESSAGE标志进行设定。在字节模式中，信息以连续字节流的形式在客户与服务器之间流动。这也就意味着，对于客户机应用和服务器应用，在任何一个特定的时间段内，都无法准确知道有多少字节从管道中读出或写入。在这种通信模式中，一方在向管道写入某个数量的字节后，并不能保证管道另一方能读出等量的字节。对于消息模式，客户机和服务器则是通过一系列不连续的数据包进行数据的收发。从管道发出的每一条消息都必须作为一条完整的消息读入。
使用命名管道
管道服务器首次调用CreateNamedPipe（）函数时，使用nMaxInstance参数指定了能同时存在的管道实例的最大数目。服务器可以重复调用CreateNamedPipe（）函数去创建管道新的实例，直至达到设定的最大实例数。下面给出CreateNamedPipe（）的函数原型：

HANDLE CreateNamedPipe(
　LPCTSTR lpName, // 指向管道名称的指针
　DWORD dwOpenMode, // 管道打开模式
　DWORD dwPipeMode, // 管道模式
　DWORD nMaxInstances, // 最大实例数
　DWORD nOutBufferSize, // 输出缓存大小
　DWORD nInBufferSize, // 输入缓存大小
　DWORD nDefaultTimeOut, // 超时设置
　LPSECURITY_ATTRIBUTES lpSecurityAttributes // 安全属性指针
);

如果在已定义超时值变为零以前，有一个实例管道可以使用，则创建成功并返回管道句柄，以此侦听来自客户机的连接请求。另一方面，客户机通过函数WaitNamedPipe（）使服务器进程等待来自客户的实例连接。如果在超时值变为零以前，有一个管道可供连接使用，则函数将成功返回，并通过调用CreateFile（）或CallNamedPipe（）来呼叫对服务器的连接。此时服务器将接受客户的连接请求，成功建立连接，服务器调用的等待客户机建立连接的ConnectNamedPipe（）函数也将成功返回。 
从调用时序上看，首先是客户机通过WaitNamedPipe（）使服务器的CreateFile（）在限时时间内创建实例成功，然后双方通过ConnectNamedPipe（）和CreateFile（）成功连接，在返回用以通信的文件句柄后，客户、服务双方即可进行通信。 
在建立了连接后，客户机与服务器即可通过ReadFile（）和WriteFile（）并利用得到的管道句柄，以文件读写的形式彼此间进行信息交换。 当客户与服务器的通信结束，或是由于某种原因一方需要断开时，由客户机调用CloseFile（）函数关闭打开的管道句柄，服务器随即调用DisconnectNamedPipe（）函数。当然，服务器也可以通过单方面调用DisconnectNamedPipe（）来终止连接。在终止连接后调用函数CloseHandle（）来关闭此管道。下面给出的程序清单即是按照上述方法实现的命名管道服务器和客户机进行通信的简单程序实现代码：
服务器端：

m_hPipe = CreateNamedPipe("\\\\.\\Pipe\\Test", PIPE_ACCESS_DUPLEX, 
  PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL); // 创建命名管道
if (m_hPipe == INVALID_HANDLE_VALUE)
　m_sMessage = "创建命名管道失败!";
else{
　m_sMessage = "成功创建命名管道!";
　AfxBeginThread(ReadProc, this); // 开启线程
}

由于ConnectNamedPipe（）函数在没有客户机连接到服务器时会无限等待下去，因此为避免由此引起主线程的阻塞，为其开辟了一个子线程ReadProc：

UINT ReadProc(LPVOID lpVoid)
{
　char buffer[1024]; // 数据缓存
　DWORD ReadNum;
　CServerView* pView = (CServerView*)lpVoid; // 获取视句柄
　if (ConnectNamedPipe(pView->m_hPipe, NULL) == FALSE) // 等待客户机的连接
　{
CloseHandle(pView->m_hPipe); // 关闭管道句柄
pView->m_sMessage = "与客户机建立连接失败!"; // 显示信息
pView->Invalidate();
return 0;
　}else{
pView->m_sMessage = "与客户机建立连接!"; // 显示信息
pView->Invalidate();
　}
　// 从管道读取数据
　if (ReadFile(pView->m_hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)
　{
CloseHandle(pView->m_hPipe); // 关闭管道句柄
pView->m_sMessage = "从管道读取数据失败!"; // 显示信息
pView->Invalidate();
　} else {
buffer[ReadNum] = '\0'; // 显示接收到的信息
pView->m_sMessage = CString(buffer);
pView->Invalidate();
　}
　return 1;
}

在客户同服务器建立连接后，ConnectNamedPipe（）才会返回，其下语句才得以执行。随后的ReadFile（）将负责把客户写入管道的数据读取出来。在全部操作完成后，服务器可以通过调用函数DisconnectNamedPipe（）而终止连接：

if (DisconnectNamedPipe(m_hPipe) == FALSE) // 终止连接
　m_sMessage = "终止连接失败!";
else
{
　CloseHandle(m_hPipe); // 关闭管道句柄
　m_sMessage = "成功终止连接!";
}

客户机端：

CString Message = "[测试数据,由客户机发出]"; // 要发送的数据
DWORD WriteNum; // 发送的是数据长度
// 等待与服务器的连接
if (WaitNamedPipe("\\\\.\\Pipe\\Test", NMPWAIT_WAIT_FOREVER) == FALSE)
{
　m_sMessage = "等待连接失败!"; // 显示信息
　Invalidate();
　return;
}
// 打开已创建的管道句柄
HANDLE hPipe = CreateFile("\\\\.\\Pipe\\Test", GENERIC_READ | GENERIC_WRITE, 
  0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
if (hPipe == INVALID_HANDLE_VALUE)
{
　m_sMessage = "管道打开失败!"; // 显示信息
　Invalidate();
　return;
} else {
　m_sMessage = "成功打开管道!"; // 显示信息
　Invalidate();
}
// 向管道写入数据
if (WriteFile(hPipe, Message, Message.GetLength(), 
  &WriteNum, NULL) == FALSE)
{
　m_sMessage = "数据写入管道失败!"; // 显示信息
　Invalidate();
} else {
　m_sMessage = "数据成功写入管道!"; // 显示信息
　Invalidate();
}
CloseHandle(hPipe); // 关闭管道句柄
```