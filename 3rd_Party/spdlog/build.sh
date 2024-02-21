#!/bin/bash
set -x

SRC_PATH=${MK_PATH}/3rd_Party/spdlog/spdlog
BUILD_PATH=${MK_DEPS_PKGS}/__build/spdlog
PREFIX_PATH=${MK_DEPS_PKGS}/spdlog


rm -rf ${BUILD_PATH}
mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH} \
                    -DSPDLOG_BUILD_SHARED=ON \
                    -DSPDLOG_BUILD_EXAMPLE=OFF

make -j4
make install
cd  ${MK_PATH}/3rd_Party
