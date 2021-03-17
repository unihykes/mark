#!/bin/sh

#开启回显
set -x

#参数检查
if [ "$1" = "32" ];
then
    CMAKE_BUILD_VERSION=i386
else
	CMAKE_BUILD_VERSION=x64
fi


# 进入根目录
cd ../../
export MK_PATH=`pwd`
cd ..
export MK_PACKAGE=`pwd`
cd $MK_PATH

#设置环境变量
CMAKE_PLATFORM_NAME="linux"
CMAKE_PLATFORM_VERSION="all"
MY_CXX_COMPILER=/usr/bin/g++
MY_C_COMPILER=/usr/bin/gcc

export CMAKE_PLATFORM_NAME
export CMAKE_PLATFORM_VERSION
export CMAKE_BUILD_VERSION
export MY_CXX_COMPILER
export MY_C_COMPILER

export MK_PLATFORM=${CMAKE_PLATFORM_NAME}_${CMAKE_PLATFORM_VERSION}_${CMAKE_BUILD_VERSION}
export MK_MAKE=$MK_PATH/make
export MK_TARGET=$MK_PACKAGE/mark_$MK_PLATFORM/target
export MK_BUILD=$MK_PACKAGE/mark_$MK_PLATFORM/build
export MK_DEPS_PKGS=/eisoo/depspkgs

export PATH=$PATH:$MK_MAKE/script_unix:$MK_MAKE/script_unix/bin
chmod -R +x $MK_MAKE/script_unix/*.sh
chmod -R +x $MK_MAKE/script_unix/bin/*

#关闭回显
set +x