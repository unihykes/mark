
下载:
https://www.wxwidgets.org/downloads/


wxTreeCtrl
http://blog.sina.com.cn/s/blog_4fcd1ea30100vec7.html

wxWidgets (跨平台的GUI库)参考资料
http://www.cnblogs.com/byeyear/category/542253.html
http://docs.wxwidgets.org/trunk/classwx_dialog.html
http://blog.csdn.net/t0ny/article/details/1783920
http://sourceforge.net/projects/wxwindows

wxwidgets教程
https://blog.csdn.net/zhaowende/article/details/6967209

Windows下VS（vs2015）命令行编译wxWidgets与Hello world 工程
https://blog.csdn.net/u012183487/article/details/79780689

wxWidgets类列表(2.6.4)
http://www.cnblogs.com/answer/archive/2008/12/17/975618.html

[ZETCODE]wxWidgets教程五：布局管理
https://www.cnblogs.com/pingge/p/3458387.html?utm_source=tuicool&utm_medium=referral


编译:
略

使用:
    1、包含目录
    右击项目，打开项目属性页，配置一项选择所有配置
    配置属性->C/C++->常规->附加包含目录中添加：
    %%%%%%%%\include
    %%%%%%%%\lib\vc_lib\mswu

    2、库目录
    配置属性->链接器->常规->附加库目录中添加：
    %%%%%%%%%\lib\vc_lib

    3、 MFC的使用
    配置属性->MFC的使用：使用标准 Windows 库

    4、依赖项
    配置属性->链接器->输入->附加依赖项按照如下规则添加编译出来的lib文件：
    debug选项：

    5、预处理器定义
    配置一项改为Debug
    配置属性->C/C++->预处理器->预处理器定义中添加：
    __WXMSW__
    __WXDEBUG__


## _HAS_ITERATOR_DEBUGGING 导致deubg程序运行时崩溃
    debug环境下:
    在编译wxwidgets时候,
    wxwidgets的默认编译选项中_HAS_ITERATOR_DEBUGGING = 1

    在编eisoo代码时候,例如basecore之类的,_HAS_ITERATOR_DEBUGGING = 0

    当用ut链接basecore和wxwidgets的lib文件时候,出现莫名其妙的错误,
    ut调用xpcom组件接口,传入接口的参数,地址发生错乱;

    解决办法:
    将eisoo代码线中_HAS_ITERATOR_DEBUGGING 统一设置为1