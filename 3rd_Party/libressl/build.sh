#!/bin/bash

#在编译之前,需要执行libressl目录下 ./autogen.sh 下载依赖库

SRC_PATH=${MK_PATH}/3rd_Party/libressl/libressl
BUILD_PATH=${MK_DEPS_PKGS}/__build/libressl
PREFIX_PATH=${MK_DEPS_PKGS}/libressl



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
                    -DBUILD_SHARED_LIBS=ON \
                    -DLIBRESSL_APPS=OFF \
                    -DLIBRESSL_TESTS=OFF \
                    -DENABLE_ASM=OFF
                    
                    

make -j4
make install
cd ../../
