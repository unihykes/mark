::@echo off

::检查参数
@if "%1" == "64" goto 64
@if "%1" == "32" goto 32

:64
set MK_SYSTEM_TYPE=x64
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x64
goto env

:32
set MK_SYSTEM_TYPE=i386
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x86

:env
@echo on

::设置环境变量
::进入项目根目录,转换反斜杠为斜杠, E:\AA\BB\CC -->> E:/AA/BB/CC
cd ..\..\
set MK_PATH=%cd:\=/%

cd ..
set MK_PACKAGE=%cd:\=/%/cache/mark_win_all_%MK_SYSTEM_TYPE%
cd %MK_PATH%


@echo off
set PATH=%MK_PATH%/make/script_win;%PATH%
@echo on