#!/bin/bash
set -x

SRC_PATH=${MK_PATH}/3rd_Party/highwayhash/highwayhash
BUILD_PATH=${MK_DEPS_PKGS}/__build/highwayhash
PREFIX_PATH=${MK_DEPS_PKGS}/highwayhash

rm -rf ${BUILD_PATH}
rm -rf ${PREFIX_PATH}

mkdir ${BUILD_PATH}
cd ${BUILD_PATH}
cmake ${SRC_PATH}   -DCMAKE_INSTALL_PREFIX=${PREFIX_PATH}

make -j4
#make install
mkdir -p ${PREFIX_PATH}/include
mkdir -p ${PREFIX_PATH}/lib64
cp -r ${SRC_PATH}/highwayhash  ${PREFIX_PATH}/include/highwayhash
cp -r ${BUILD_PATH}/libhighwayhash.a  ${PREFIX_PATH}/lib64/

cd  ${MK_PATH}/3rd_Party
