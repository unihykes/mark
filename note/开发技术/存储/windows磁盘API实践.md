```cpp
API的列表如下，网上找的，我觉得还是蛮详细的：

磁盘和驱动器管理API
GetLogicalDrivers       获取主机中所有的逻辑驱动器,以BitMap的形式返回.
GetLogicalDriverString    获取主机中所有的逻辑驱动器,以驱动器根路径字符串返回.
FindFirstVolume     查找主机中的第一个驱动器，返回查找句柄.
FindNextVolume      根据FindFirstVolume返回句柄,查找主机中后继的逻辑驱动器
FindVolumeClose     关闭驱动器查找句柄
GetDriveType      获取驱动器类型
GetVolumeInformation    获取逻辑驱动器信息
FindFirstVolumeMountPoint查找指定卷的第一个挂载点,返回查找句柄
FindNextVolumeMountPoint 根据FindFirstVolumeMountPoint返回的句柄,查找卷的后继挂载点.
FindVolumeMountPointClose 关闭挂载点查找句柄
GetVolumeNameForVolumeMountPoint 根据指定挂载点获取相应的卷设备名
SetVolumeMountPoint         将指定卷挂载到指定挂载点处
GetDiskFreeSpace            获取磁盘空间信息,包括每簇的扇区数,每扇区的字节数,簇数量,空闲的簇数量
GetDiskFreeSpaceEx          获取用户可用的空闲空间的字节数,磁盘总容量的字节数

文件和目录管理API
DeleteFile                  删除参数所指定文件
CopyFile                    复制指定文件为一个新文件
MoveFile                    将指定文件或目录移动到指定位置
CreateFile                  新建或打开一个文件,获取文件句柄
ReadFile                    读取由文件句柄指定文件的内容
WriteFile                   向由文件句柄指定的文件中写入内容
GetFileSize                 获取文件大小,返回DWORD中;大小超出DWORD最大值时可指定高32位的DWORD联合存储
GetFileSizeEx               获取文件大小,存储到一个64位的大整数联合体中.
CreateDirectory             创建一个目录
GetCurrentDirectory         获取当前程序所在目录
SetCurrentDirectory         设置当前程序所在目录
GetModuleFileName           获取当前模块全路径
FindFirstFile               查找指定目录下第一个文件句柄或目录,获得查找句柄
FindNextFile                根据FindFirstFile获得的句柄,循环查找文件或目录
GetFileAttributes           获取指定文件目录属性,返回一个DWORD值
GetFileAttributesEx         获取文件或目录属性,存储在WIN32_FILE_ATTRIBUTE_DATA结构体中
SetFileAttributes           将文件属性设定为指定值
FileTimeToLocalFileTime     将文件时间转换为本地时间
FileTimeToSystemTime        将文件转换为系统时间,SYSTEMTIME格式便于显示

高级文件操作
CreateFileMapping           创建文件的映射对象
MapViewOfFile               创建视图,将创建的文件映射对象映射到当前进程的地址空间中
FlushViewOfFile             将视图中的数据都写入磁盘,对视图的操作都会反映到磁盘上的文件中
OpenFileMapping             打开已经存在的命名的文件映射对象
UnmapViewOfFile             取消文件映射
GetMappedFileName           从映射对象获取被映射文件的文件设备名
QueryDosDevice              获取MS-DOS设备名
GetLocalDrivers
       最近真的是发现做文档也是一种习惯啊。慢慢来吧。
       第一个函数GetLocalDrivers这个函数的返回值是一个DWORD，也就是以Bitmap形式返回相关的信息，从0位开始为A盘，从以往后递归就是BCD……
       这个函数无参数，函数原型如下：
DWORD GetLogicalDrives(VOID);
代码运行结果：

可以对应一下，确实是正确的。不过H位为0应该是因为这光驱中无光盘。/*此处错误，0对应的是I盘，时间久远，估计是因为但是U盘被拔掉了。H盘位置对应的确实是1*/
 
GetLogicalDriveStrings
       这个函数还挺有意思的，可以用于获取目前系统上所有的盘符，有趣就在于其字符串的排列方式。函数原型如下：
 
DWORD GetLogicalDriveStrings(  DWORD nBufferLength,  // size of buffer
                                                      LPTSTR lpBuffer       // drive strings buffer);
       然后看下函数调用后其在缓冲区参数的结果：
 
       很有趣吧，哈哈，反正我是第一次见到。
       然后下面展示下这个字符串是如何结束的：
 
       最后面连续的两个0值表明字符串都已结束。好玩的很。
 
FindFirstVolume
       这个函数能获取计算机上的第一个卷，并且返回一个句柄，用于FindNextVolume函数的使用。函数原型如下：
HANDLE FindFirstVolume(  LPTSTR lpszVolumeName,   // output buffer
DWORD cchBufferLength    // size of output buffer);
演示结果：
      
这个函数我在使用的时候还遇到了一点小小的麻烦，就是最初我设置缓冲区大小为32，结果，返回了一个无效句柄……后来改的256，才正常工作了。
 
FindNextVolume
       这个函数时要配合着上面函数返回的句柄使用的函数，函数原型如下：
       BOOL FindNextVolume(  HANDLE hFindVolume,      // volume search handle
            LPTSTR lpszVolumeName,   // output buffer
            DWORD cchBufferLength    // size of output buffer);
贴下运行截图：
 
在这里你可能要问，上面这一串数据都是什么，我的回答：我也不知道。
FindVolumeClose
这个函数的作用就是单纯的关闭上面那个查找句柄的。不多说了。
GetDriveType
这个函数的作用是根据盘符来确定驱动器的类型。且看函数原型如下：
UINT GetDriveType(  LPCTSTR lpRootPathName   // root directory);
       这里参数是就是路径名，当然了，只有一个盘符，如CDEF，这个参数可以通过上面的一个函数GetLogicalDriveString的结果来使用。返回值就是驱动器类型了。类型表如下：
 
我写了个专用函数，如下：

1 //仅?限T单Ì£¤线?程¨¬使º1用®? 2
3 LPCTSTR GetTypeString(LPCTSTR lpDriverRoot)
4
5 {
6
7 static LPCTSTR Buf[7] = \
8
9 {
10
11 _T("UNKNOWN"),
12
13 _T("NO_ROOT_DIR"),
14
15 _T("REMOVABLE"),
16
17 _T("FIXED"),
18
19 _T("REMOTE"),
20
21 _T("CDROM"),
22
23 _T("RAMDISK"),
24
25 };
26
27 int nAddr = -1;
28
29 switch(GetDriveType(lpDriverRoot))
30
31 {
32
33 case DRIVE_UNKNOWN:
34
35 nAddr = 0;
36
37 break;
38
39 case DRIVE_NO_ROOT_DIR:
40
41 nAddr = 1;
42
43 break;
44
45 case DRIVE_REMOVABLE:
46
47 nAddr = 2;
48
49 break;
50
51 case DRIVE_FIXED:
52
53 nAddr = 3;
54
55 break;
56
57 case DRIVE_REMOTE:
58
59 nAddr = 4;
60
61 break;
62
63 case DRIVE_CDROM:
64
65 nAddr = 5;
66
67 break;
68
69 case DRIVE_RAMDISK:
70
71 nAddr = 6;
72
73 break;
74
75 default:
76
77 return NULL;
78
79 }
80
81 return Buf[nAddr];
82
83 }

 
运行结果：
 
这里截图只有一部分，显示了磁盘和光盘的区别。
GetVolumeInformation
       这个函数还是比较复杂的，无他，参数太多了，且看函数原型：
BOOL GetVolumeInformation(  LPCTSTR lpRootPathName,           // root directory
  LPTSTR lpVolumeNameBuffer,        // volume name buffer
  DWORD nVolumeNameSize,            // length of name buffer
  LPDWORD lpVolumeSerialNumber,     // volume serial number
  LPDWORD lpMaximumComponentLength, // maximum file name length
  LPDWORD lpFileSystemFlags,        // file system options
  LPTSTR lpFileSystemNameBuffer,    // file system name buffer
  DWORD nFileSystemNameSize         // length of file system name buffer);
一共8个参数，真要命。
这个函数的作用是用来获取指定路径的文件系统以及卷信息q其中有五个参数都是输出型参数。下面看下两个NameBuffer都返回的是什么。
 
　　这里看到lpVolumeNameBuffer参数返回的是驱动器的名字，这里系统盘是win7，而其他盘因为未命名所以什么也没有。
       lpFileSystemNameBuffer参数则是用于返回文件系统类型。这里能看到，硬盘的文件系统是NTFS。后面因为我的笔记本中插着U盘，所以其 显示结果是FAT32.
       而lpVolumeSerialNumber参数返回的是序列号，这个参数具体的用处我也不是很清楚。
       lpMaximumComponentLength参数返回的是文件系统支持的文件名最大长度。255还是很大的。
       lpFileSystemFlags文件系统选项的标志位，还是所谓的文图返回吧。这个参数有个专门的列表：
 
这种表就属于那种一看就头大的表，还是写个函数看一下比较靠谱。
 
函数实现：

1 void CheckFileSystemFlag(DWORD FSF)
2 {
3 //我是不是应该用个结构体做？ 4 static LPCTSTR lpList[12] =
5 {
6 _T("The file system preserves the case of file names when it places a name on disk."),
7 _T("The file system supports case-sensitive file names."),
8 _T("The file system supports Unicode in file names as they appear on disk."),
9 _T("The file system preserves and enforces ACLs. For example, NTFS preserves and enforces ACLs, and FAT does not."),
10 _T("The file system supports file-based compression."),
11 _T("The specified volume is a compressed volume; for example, a DoubleSpace volume."),
12 _T("The file system supports named streams."),
13 _T("The file system supports the Encrypted File System (EFS)."),
14 _T("The file system supports object identifiers."),
15 _T("The file system supports reparse points."),
16 _T("The file system supports sparse files."),
17 _T("The file system supports disk quotas.")
18 };
19 static const DWORD FlagList[12] =
20 {
21 FS_CASE_IS_PRESERVED,
22 FS_CASE_SENSITIVE,
23 FS_UNICODE_STORED_ON_DISK,
24 FS_PERSISTENT_ACLS,
25 FS_FILE_COMPRESSION,
26 FS_VOL_IS_COMPRESSED,
27 FILE_NAMED_STREAMS,
28 FILE_SUPPORTS_ENCRYPTION,
29 FILE_SUPPORTS_OBJECT_IDS,
30 FILE_SUPPORTS_REPARSE_POINTS,
31 FILE_SUPPORTS_SPARSE_FILES,
32 FILE_VOLUME_QUOTAS
33 };
34 for(int i = 0;i < 12;++ i)
35 {
36 if(FSF & FlagList[i])
37 wcout << lpList[i] << endl;
38 }
39 }

可以对照一下结果，能发现，NTFS仅仅没有压缩卷这一项。而FAT32则只有两个结果。文件系统的差别还是挺大的。
FindFirstVolumeMountPoint
       这个函数的原型如下：
HANDLE FindFirstVolumeMountPoint(  LPTSTR lpszRootPathName,     // volume name
  LPTSTR lpszVolumeMountPoint, // output buffer
  DWORD cchBufferLength        // size of output buffer);
这里第一个参数是使用FindFirstVolume的的volume字符串，也就是很长的那一串。但是在我的计算机上，这个函数的返回值始终都是失败，而且现在也没理解所谓的挂载是什么意思。这几个函数暂且搁置。
GetDiskFreeSpace
这个函数是用来获取磁盘信息的。函数原型如下：
BOOL GetDiskFreeSpace(  LPCTSTR lpRootPathName,          // root path
  LPDWORD lpSectorsPerCluster,     // sectors per cluster
  LPDWORD lpBytesPerSector,        // bytes per sector
  LPDWORD lpNumberOfFreeClusters,  // free clusters
  LPDWORD lpTotalNumberOfClusters  // total clusters);
       第一个参数就是路径名，比如C:\。演示下运行结果：
 

这个函数没大多好说的，看了就会用。
```