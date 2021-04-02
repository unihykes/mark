#!/bin/bash

#在编译之前,需要执行 libexpat/expat 目录下 ./buildconf.sh 下载依赖库,可在windows下的git-bash执行

SRC_PATH=${MK_PATH}/3rd_Party/libexpat/libexpat/expat
BUILD_PATH=${MK_DEPS_PKGS}/__build/libexpat
PREFIX_PATH=${MK_DEPS_PKGS}/libexpat



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
                    -DBUILD_SHARED_LIBS=ON \
                    -DEXPAT_BUILD_DOCS=OFF \
                    -DEXPAT_BUILD_EXAMPLES=OFF \
                    -DEXPAT_BUILD_TESTS=OFF \
                    -DEXPAT_BUILD_TOOLS=OFF
                    
                    
                    

make -j4
make install
cd  ${MK_PATH}/3rd_Party
