#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/zstd/zstd/build/cmake
BUILD_PATH=${MK_DEPS_PKGS}/__build/zstd
PREFIX_PATH=${MK_DEPS_PKGS}/zstd



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH} \
                    -DZSTD_BUILD_PROGRAMS=OFF \
                    -DZSTD_BUILD_TESTS=OFF
                    


make -j4
make install
cd  ${MK_PATH}/3rd_Party
