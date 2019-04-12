Windows Namespace Extension中自制系统新建菜单的实现方法

1 确定系统菜单中要有哪些新建项：
打开注册表项
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Discardable\PostSetup\ShellNew\Classes
该项为多字符串类型，每个字符串对应了一个新建项。

如
.bmp ->位图
.contact ->联系人
.doc ->word文档
.txt ->文本文档
等等....

2 了解了需要添加哪些新建项后，我们需要知道每个项所有的具体信息：

（1），新建项的描述（在新建菜单中显示）：
在HEKY_CLASSES_ROOT下找到对应新建项名字的注册表项
如：.bmp -> HEKY_CLASSES_ROOT\.bmp
.txt -> HEKY_CLASSES_ROOT\.txt
读取该注册表项下的默认子项值，该值对应了文件关联程序的注册表项
如：HEKY_CLASSES_ROOT\.bmp 下一般为Paint.Picture

定位关联程序的注册表项
如：HEKY_CLASSES_ROOT\Paint.Picture
读取该注册表项下的默认子项值，该值便是关联程序的描述，用于显示在新建菜单中

（2），新建项的图标（在新建菜单中显示）
参考（1）中，定位关联程序的注册表项
读取该注册表项下的DefaultIcon相关内容

或，

使用SHGetFileInfo API直接得到Icon句柄
如：
.bmp ->
SHGetFileInfo (_T("x.bmp"),
          FILE_ATTRIBUTE_NORMAL,
          &info,
          sizeof(info),
          SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON);

.txt->
SHGetFileInfo (_T("x.txt"),
          FILE_ATTRIBUTE_NORMAL,
          &info,
          sizeof(info),
          SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_SMALLICON);
以此类推

（3），新建项所新建的文件内容（点击新建后的操作）
参考（1）中找到对应新建项名字的注册表项
遍历其找到ShellNew子项
若其中包含FileName子项，则拷贝FileName所指定的文件内容，作为新建文件
若其中包含NullFile子项，则直接创建空文件，作为新建的文件



如果shellNew中找不到，则可以尝试去C:\Windows\ShellNew中看看；