#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/crc32c/crc32c
BUILD_PATH=${MK_DEPS_PKGS}/__build/crc32c
PREFIX_PATH=${MK_DEPS_PKGS}/crc32c

mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH} \
                    -DBUILD_SHARED_LIBS=ON  \
                    -DCRC32C_BUILD_TESTS=OFF \
                    -DCRC32C_BUILD_BENCHMARKS=OFF \
                    -DCRC32C_USE_GLOG=OFF

make -j4
make install
cd  ${MK_PATH}/3rd_Party

