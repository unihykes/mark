::@echo off

@if "%1" == "64" goto 64
@if "%1" == "32" goto 32

:64
set MK_SYSTEM_TYPE=x64
set CMAKE_GENERATOR="Visual Studio 14 2015 Win64"
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x64
goto env

:32
set MK_SYSTEM_TYPE=x86
set CMAKE_GENERATOR="Visual Studio 14 2015"
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x86

:env
@echo on
cd ..\..\

::设置环境变量
set MK_PATH=%cd:\=/%
cd ..
set MK_PACKAGE=%cd:\=/%/cache/mark_win_all_%MK_SYSTEM_TYPE%
set MK_DEPS_PKGS=%MK_PACKAGE%/depspkgs

set PATH=%MK_PATH%/make/script_win;%PATH%

cd %MK_PATH%