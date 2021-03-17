#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/protobuf/protobuf/cmake
BUILD_PATH=${MK_DEPS_PKGS}/__build/protobuf
PREFIX_PATH=${MK_DEPS_PKGS}/protobuf



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
                    -DBUILD_SHARED_LIBS=ON \
                    -Dprotobuf_BUILD_TESTS=OFF

make -j4
make install
cd ../../
