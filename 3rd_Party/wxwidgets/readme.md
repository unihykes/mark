编译步骤:
1.git clone代码线,更新wxwidgets的子模块;
2.复制文件"wxWidgets/include/wx/msw/setup0.h"到 "wxWidgets/include/wx/msw/setup.h"
3.运行脚本:make_wxWidgets.bat

使用步骤:
1.修改文件:build_target/lib/vc_x64_dll/mswud/wx/setup.h
    添加:
    #define wxMONOLITHIC 1
    #define  wxNO_GL_LIB
    或者在CmakeLists中定义
    
2.参考 usewxwidget.cmake 创建自己模块的CmakeLists
