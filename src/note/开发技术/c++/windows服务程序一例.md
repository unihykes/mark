


# Windows服务程序一例


1. Windows提供了一大堆API用于服务程序的编写，如下所示：

ChangeServiceConfig
CloseServiceHandle
ControlService
CreateService
DeleteService
EnumDependentServices
EnumServicesStatus
GetServiceDisplayName
GetServiceKeyName
Handler
LockServiceDatabase
NotifyBootConfigStatus
OpenSCManager
OpenService
QueryServiceConfig
QueryServiceLockStatus
QueryServiceObjectSecurity
QueryServiceStatus
RegisterServiceCtrlHandler
ServiceMain
SetServiceBits
SetServiceObjectSecurity
SetServiceStatus
StartService
StartServiceCtrlDispatcher
UnlockServiceDatabase


2. 发送端实现发送端的实现在ipnotify_cli.c文件中。抛开Windows服务程序编写的相关规范来看，程序本身是很简单的，就是一个只发不收的UDP程序而已。简单得让人不忍赘述。另外，作者是用DEV-CPP编译该程序的，需要链接libws2_32.a，这个库文件中包含了Windows的套接口函数的实现。编译得到的程序是不能直接运行的，必须要注册为服务之后从Windows服务管理器中启动才行。有关服务注册和启动，请google之。附件中的SRVINSTW.exe是用来安装服务的，使用非常简单，请大胆实践。


3. 接收端实现作者所用的B主机为一台运行Linux的机器，因此，接收端的程序是采用Linux的套接口函数来编写的。当然，无论是Linux还是Windows，套接口都是相似的，但是差别总还是有那么一些。附件中一并附上接收端的源代码实现ipnotify_svr.c。


4. 结论 个人感觉，在Windows下弄一个守护进程始终要比Unix类系统下麻烦一些。不过也可能是我不习惯罢了。


5. 参考
ipnotify_cli.c的实现：

```cpp
/*
Name: ipnotify_cli.c
Copyright: ultimate free
Author: rockins
Date: 18-01-07 04:46
Description: a windows service, which will notify local IP address
to a remote supervisor
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define REM_HOST "202.115.26.*" /*my linux box, as supervisor host*/
#define REM_PORT 8277 /*8277, someone's birthday, as port*/
#define BUFF_SIZE 8192 /*packet data maximum length*/
#define FINGERPRINT "this is packet is from rockins\n" /*identification*/

signed int ipnotify_status = 1; /*service status:
0 inactive
1 active
*/

SERVICE_STATUS_HANDLE ipnotify_status_handle;
SERVICE_STATUS ipnotify_service_status;

/*
* prototype:
* VOID WINAPI Handler(
* DWORD fdwControl // requested control code
* );
*/
VOID WINAPI
ipnotify_handler(DWORD fdwControl)
{
if (fdwControl == SERVICE_CONTROL_STOP)
ipnotify_status = 0;
if (fdwControl == SERVICE_CONTROL_PAUSE)
ipnotify_status = 0;
if (fdwControl == SERVICE_CONTROL_CONTINUE)
ipnotify_status = 1;
if (fdwControl == SERVICE_CONTROL_INTERROGATE)
; // I donot know how to deal with this
if (fdwControl == SERVICE_CONTROL_SHUTDOWN)
ipnotify_status = 0;
}

/*
* prototype:
* VOID WINAPI ServiceMain(
* DWORD dwArgc, // number of arguments
* LPTSTR *lpszArgv // address of array of argument string pointers
* );
*/
VOID WINAPI
ipnotify_main(DWORD dwArgc, LPTSTR *lpszArgv)
{
WSADATA wsData; /*Windows Socket Application*/
SOCKET sock; /*socket object*/
struct sockaddr_in svr_addr; /*server socket address*/
int svr_addr_len; /*length of server addr*/
int err; /*save error code*/
int err_time = 0; /*error times*/
int len; /*length of packet data*/
char buff[BUFF_SIZE]; /*packet data*/

/*register service*/
ipnotify_status_handle = RegisterServiceCtrlHandler("ipnotify",
&ipnotify_handler);

/*update service status*/
ipnotify_service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
ipnotify_service_status.dwCurrentState = SERVICE_RUNNING;
ipnotify_service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
ipnotify_service_status.dwWin32ExitCode = NO_ERROR;
ipnotify_service_status.dwServiceSpecificExitCode = 0;
ipnotify_service_status.dwCheckPoint = 0;
ipnotify_service_status.dwWaitHint = 0;
if (!SetServiceStatus(ipnotify_status_handle, &ipnotify_service_status)) {
printf("SetServiceStatus()\n");
exit(-1);
}

/*init sending buffer*/
memset(buff, 0, BUFF_SIZE);
strncpy(buff, FINGERPRINT, BUFF_SIZE);

/*init network subsystem of win32*/
err = WSAStartup(MAKEWORD(2, 2), &wsData);
if (err) {
printf("cannot init winsock lib...\n");
exit(-1);
}

/*create socket object*/
sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
if (sock == INVALID_SOCKET) {
printf("cannot create socket...\n");
exit(-1);
}

/*stuff the server socket address*/
memset(&svr_addr, 0, sizeof(svr_addr));
svr_addr.sin_family = AF_INET;
svr_addr.sin_port = htons(REM_PORT);
svr_addr.sin_addr.s_addr = inet_addr(REM_HOST);

/*main loop*/
while (TRUE) {
if (ipnotify_status == 0)
break;

len = sendto(sock, buff, strlen(buff), 0,
(struct sockaddr *)&svr_addr, svr_addr_len);
if (len == SOCKET_ERROR) {
err = WSAGetLastError();
printf("error(%d) occured in recvfrom()...\n", err);
exit(-1);
}

printf("send fingerprint to the supervisor\n");
Sleep(2000);
}
}


int
main(int argc, char *argv[])
{
SERVICE_TABLE_ENTRY ipnotify_entry[] = {
{"ipnotify", ipnotify_main},
{NULL, NULL}
};

if (!StartServiceCtrlDispatcher(ipnotify_entry)) {
printf("StartServiceCtrlDispatcher()\n");
exit(-1);
}

system("pause");
return (0);
}

```


ipnotify_svr.c的实现：

```cpp
/*
Name: ipnotify_svr.c
Copyright: completely free
Author: rockins
Date: 18-01-07 05:11
Description: receive IP notify from another Windows box
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LISTEN_PORT 8277 /*someone's birthday, as port*/
#define FINGERPRINT "this is packet is from rockins\n" /*identification*/
#define BUFF_SIZE 8192 /*buffer size for incoming data*/

int
main(int argc, char *argv[])
{
int sock;
struct sockaddr_in listen_addr;
struct sockaddr_in peer_addr;
int listen_addr_len;
int peer_addr_len;
char buff[BUFF_SIZE];
char rcv_len;

/*create socket descriptor*/
sock = socket(AF_INET, SOCK_DGRAM, 0);
if (sock < 0) {
perror("socket()");
exit(-1);
}

/*stuff socket address structure*/
memset(&listen_addr, 0, sizeof(listen_addr));
listen_addr.sin_family = AF_INET;
listen_addr.sin_port = htons(LISTEN_PORT);
listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

/*bind to local listening UDP port*/
if (bind(sock, (struct sockaddr *)&listen_addr,
sizeof(listen_addr)) < 0) {
perror("bind()");
exit(-1);
}

/*main loop, exit when get what wanted*/
while (1) {
rcv_len = recvfrom(sock, buff, BUFF_SIZE, 0,
(struct sockaddr *)&peer_addr, &peer_addr_len);
if (rcv_len < 0) {
perror("recvfrom()");
exit(-1);
}

if (!strncmp(buff, FINGERPRINT, BUFF_SIZE)) {
printf("rockins's box: %s\n",
inet_ntoa(peer_addr.sin_addr));
exit(0);
}
}

return (0);
}
```