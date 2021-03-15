::@echo off

set VS2019_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools

::检查参数
@if "%1" == "64" goto 64
@if "%1" == "32" goto 32

:64
set CMAKE_BUILD_VERSION=x64
call "%VS2019_PATH%\VsDevCmd.bat"
goto env

:32
set CMAKE_BUILD_VERSION=i386
call "%VS2019_PATH%\VsDevCmd.bat"

:env
@echo on


::进入项目根目录,转换反斜杠为斜杠, E:\AA\BB\CC -->> E:/AA/BB/CC
cd ..\..\
set MK_PATH=%cd:\=/%

cd ..
set MK_PACKAGE=%cd:\=/%
cd %MK_PATH%

::设置环境变量
set CMAKE_PLATFORM_NAME=win
set CMAKE_PLATFORM_VERSION=all

set MK_PLATFORM=%CMAKE_PLATFORM_NAME%_%CMAKE_PLATFORM_VERSION%_%CMAKE_BUILD_VERSION%
set MK_MAKE=%MK_PATH%/make
set MK_TARGET=%MK_PACKAGE%/mark_%MK_PLATFORM%/target
set MK_BUILD=%MK_PACKAGE%/mark_%MK_PLATFORM%/build

@echo off
set PATH=%MK_MAKE%/script_win;%PATH%
@echo on