#!/bin/bash

SRC_PATH=${MK_PATH}/3rd_Party/libuuid/libuuid-1.0.3
BUILD_PATH=${MK_DEPS_PKGS}/__build/libuuid
PREFIX_PATH=${MK_DEPS_PKGS}/libuuid



mkdir ${BUILD_PATH}
cd ${BUILD_PATH}

${SRC_PATH}/configure --prefix=${PREFIX_PATH}
make -j4
make install
cd ../../
