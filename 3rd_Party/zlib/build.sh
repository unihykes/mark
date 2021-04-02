#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/zlib/zlib
BUILD_PATH=${MK_DEPS_PKGS}/__build/zlib
PREFIX_PATH=${MK_DEPS_PKGS}/zlib



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}

                    
                    
                    

make -j4
make install
cd  ${MK_PATH}/3rd_Party
