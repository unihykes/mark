::@echo off

@if "%1" == "64" goto 64
@if "%1" == "32" goto 32

:64
set MK_SYSTEM_TYPE=x64
set CMAKE_GENERATOR="Visual Studio 16 2019" -A x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
goto env

:32
set MK_SYSTEM_TYPE=x86
set CMAKE_GENERATOR="Visual Studio 16 2019" -A Win32
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"

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