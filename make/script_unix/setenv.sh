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
export MONK_PATH=`pwd`


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

export MONK_PLATFORM=${CMAKE_PLATFORM_NAME}_${CMAKE_PLATFORM_VERSION}_${CMAKE_BUILD_VERSION}
export MONK_TARGET=$MONK_PATH/$MONK_PLATFORM/target
export MONK_BUILD=$MONK_PATH/$MONK_PLATFORM/build
export MONK_MAKE=$MONK_PATH/make
export MONK_DEPS=$MONK_PATH/deps/deps_monk
export MONK_SRC=$MONK_PATH/src

export PATH=$PATH:$MONK_MAKE/script_unix:$MONK_MAKE/script_unix/bin
chmod -R +x $MONK_MAKE/script_unix/*.sh
chmod -R +x $MONK_MAKE/script_unix/bin/*

#关闭回显
set +x