VC获取特殊目录SHGetFolderPath SHGetSpecialFolderPath

WindowsAPI  SHGetFolderPath SHGetSpecialFolderPath  可以用于获取系统CSIDL路径。

BOOL SHGetSpecialFolderPath(     
    HWND hwndOwner,
    LPTSTR lpszPath,
    int nFolder,
    BOOL fCreate
);

HRESULT SHGetFolderPath(     
    HWND hwndOwner,
    int nFolder,
    HANDLE hToken,
    DWORD dwFlags,
    LPTSTR pszPath
);

以上为函数原型，其中nFolder指定要获取的目录（具体参考MSDN说明）

CSIDL_BITBUCKET   回收站 
CSIDL_CONTROLS   控制面板 
CSIDL_DESKTOP   Windows   桌面Desktop 
CSIDL_DESKTOPDIRECTORY   Desktop的目录 
CSIDL_DRIVES   我的电脑 
CSIDL_FONTS   字体目录 
CSIDL_NETHOOD   网上邻居 
CSIDL_NETWORK   网上邻居虚拟目录 
CSIDL_PERSONAL   我的文档 
CSIDL_PRINTERS   打印机 
CSIDL_PROGRAMS   程序组 
CSIDL_RECENT   最近打开的文档 
CSIDL_SENDTO   “发送到”菜单项 
CSIDL_STARTMENU   任务条启动菜单项 
CSIDL_STARTUP   启动目录 
CSIDL_TEMPLATES   文档模板





TCHAR szPath[MAX_PATH];

if(SUCCEEDED(SHGetFolderPath(NULL,
                             CSIDL_PERSONAL|CSIDL_FLAG_CREATE,
                             NULL,
,
                             szPath)))
{
    PathAppend(szPath, TEXT("New Doc.txt"));
    HANDLE hFile = CreateFile(szPath, );
}