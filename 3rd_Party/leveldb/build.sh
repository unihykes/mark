#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/leveldb/leveldb
BUILD_PATH=${MK_DEPS_PKGS}/__build/leveldb
PREFIX_PATH=${MK_DEPS_PKGS}/leveldb


mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
                    -DBUILD_SHARED_LIBS=ON \
                    -DLEVELDB_BUILD_TESTS=OFF  \
                    -DLEVELDB_BUILD_BENCHMARKS=OFF

make -j4
make install
cd  ${MK_PATH}/3rd_Party