#!/bin/bash

#在编译之前,需要执行libressl目录下 ./autogen.sh 下载依赖库

SRC_PATH=${MK_PATH}/3rd_Party/snappy/snappy
BUILD_PATH=${MK_DEPS_PKGS}/__build/snappy
PREFIX_PATH=${MK_DEPS_PKGS}/snappy



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
                    -DBUILD_SHARED_LIBS=ON \
                    -DSNAPPY_BUILD_TESTS=OFF \
                    -DSNAPPY_BUILD_BENCHMARKS=OFF
                    
                    
                    

make -j4
make install
cd  ${MK_PATH}/3rd_Party
