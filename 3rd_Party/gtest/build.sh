#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/gtest/googletest
BUILD_PATH=${MK_DEPS_PKGS}/__build/gtest
PREFIX_PATH=${MK_DEPS_PKGS}/gtest

mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH} \
                    -DBUILD_SHARED_LIBS=ON 

make -j4
make install
cd  ${MK_PATH}/3rd_Party

