#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/brpc/incubator-brpc
BUILD_PATH=${MK_DEPS_PKGS}/__build/brpc
PREFIX_PATH=${MK_DEPS_PKGS}/brpc


mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   \
    -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}  \
    -DWITH_DEBUG_SYMBOLS=OFF \
    -DDOWNLOAD_GTEST=OFF \
    -DBUILD_SHARED_LIBS=ON \
    -DLINK_SO=ON \
    -DBUILD_UNIT_TESTS=OFF \
    -DCMAKE_INCLUDE_PATH="${MK_DEPS_PKGS}/gflags/include;${MK_DEPS_PKGS}/leveldb/include;${MK_DEPS_PKGS}/protobuf/include" \
    -DCMAKE_LIBRARY_PATH="${MK_DEPS_PKGS}/gflags/lib;${MK_DEPS_PKGS}/leveldb/lib64;${MK_DEPS_PKGS}/protobuf/lib64"  \
    -DProtobuf_INCLUDE_DIR=${MK_DEPS_PKGS}/protobuf/include \
    -DProtobuf_LIBRARY=${MK_DEPS_PKGS}/protobuf/lib64 \
    -DProtobuf_LIBRARIES=${MK_DEPS_PKGS}/protobuf/lib64/libprotobuf.so \
    -DProtobuf_PROTOC_EXECUTABLE=${MK_DEPS_PKGS}/protobuf/bin/protoc
    
make -j4
make install
cd  ${MK_PATH}/3rd_Party
