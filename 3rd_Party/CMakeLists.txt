PROJECT(3rd_Party)

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

IF(NOT EXISTS $ENV{MK_DEPS_PKGS}/__build)
    file(MAKE_DIRECTORY $ENV{MK_DEPS_PKGS}/__build)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "file(MAKE_DIRECTORY $ENV{MK_DEPS_PKGS}/__build)")
ENDIF()

#benchmark
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/benchmark/build.sh)
ENDIF()

#boost
#ADD_SUBDIRECTORY(boost/boost_full_1_75_0)

#brpc 
#todo:由于与其他库有依赖(gflags,protobuf),brpc需要手动编译
#execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/brpc/build.sh)

#cpp-btree 
#模板库,无需编译

#crc32c
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/crc32c/build.sh)
ENDIF()

#gflags
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/gflags/build.sh)
ENDIF()

#gtest
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/gtest/build.sh)
ENDIF()

#jemalloc
#todo

#jsoncpp
#todo

#leveldb
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/leveldb/build.sh)
ENDIF()

#libexpat
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libexpat/build.sh)
ENDIF()

#libressl
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libressl/build.sh)
ENDIF()

#libunwind
#todo

#libuuid
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libuuid/build.sh)
ENDIF()

#protobuf
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/protobuf/build.sh)
ENDIF()

#redis
#todo

#snappy
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/snappy/build.sh)
ENDIF()

#thrift
#todo

#zlib
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/zlib/build.sh)
ENDIF()

#zstd
IF(UNIX)
    execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/zstd/build.sh)
ENDIF()

#ai:对其他库有依赖,需要手动编译
#ADD_SUBDIRECTORY(ai)