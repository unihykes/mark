#!/bin/bash

#开启回显
set -x

#设置环境变量
CMAKE_BUILD_CURDIR=`pwd`
CMAKE_BUILD_VERBOSE=0
CMAKE_BUILD_CPU_COUNT=
CMAKE_CUSTOM_DEFINES=
CMAKE_BUILD_DIR=${MK_BUILD}/${CMAKE_BUILD_TYPE}/${CMAKE_BUILD_CURDIR#*mk/}/Build

function compile ()
{
    #build目录不存在
    if [ ! -d $CMAKE_BUILD_DIR ];
    then
        echo "Create build direcory..."
        mkdir -p $CMAKE_BUILD_DIR
    fi
    
    cd $CMAKE_BUILD_DIR

    DIR=`pwd`
    
    #makefile文件不存在
    if [[ ! -f Makefile ]]
    then
        echo "...generate makefile in $DIR..."
        cmake -DCMAKE_PLATFORM_NAME=${CMAKE_PLATFORM_NAME}          \
              -DCMAKE_PLATFORM_VERSION=${CMAKE_PLATFORM_VERSION}    \
              -DCMAKE_CXX_COMPILER=${MY_CXX_COMPILER}               \
              -DCMAKE_C_COMPILER=${MY_C_COMPILER}                   \
              -DCMAKE_BUILD_VERSION=${CMAKE_BUILD_VERSION}          \
              -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}                \
              -DAUTO_RUN=0                                          \
              $CMAKE_CUSTOM_DEFINES                                 \
              $CMAKE_BUILD_CURDIR 
    fi
	
    echo "run compile() in $PWD ..."
    make ${CMAKE_BUILD_CPU_COUNT}
}

function clean ()
{
    echo "run clean() in $CMAKE_BUILD_DIR...."
    if [[ ! -d $CMAKE_BUILD_DIR ]]
    then
        mkdir -p $CMAKE_BUILD_DIR
        cd $CMAKE_BUILD_DIR
    fi

    if [ -d $CMAKE_BUILD_DIR ]
    then 
        cd $CMAKE_BUILD_DIR
        DIR=`pwd`
        echo "Start clean in $DIR ..."
        if [ -f Makefile ];
        then
            make clean
        fi
        cd ..
    fi
}

function cleanall ()
{
    echo "run cleanall() in $CMAKE_BUILD_DIR...."
    if [[ ! -d $CMAKE_BUILD_DIR ]]
    then
        mkdir -p $CMAKE_BUILD_DIR
        cd $CMAKE_BUILD_DIR
    fi

    if [ -d $CMAKE_BUILD_DIR ]
    then 
        cd $CMAKE_BUILD_DIR
        DIR=`pwd`
        echo "Start cleanall in $DIR ..."
        if [ -f Makefile ];
        then
            make clean
        fi
        cd -
        rm -rf $CMAKE_BUILD_DIR
    fi
}

#关闭回显
set +x