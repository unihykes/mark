PROJECT(3rd_Party)

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

IF(NOT EXISTS $ENV{MK_DEPS_PKGS}/__build)
    file(MAKE_DIRECTORY $ENV{MK_DEPS_PKGS}/__build)
ENDIF()

IF(UNIX)

#benchmark
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/benchmark/build.sh)

#boost
#ADD_SUBDIRECTORY(boost/boost_full_1_75_0)

#brpc:与其他库有依赖(gflags,protobuf),需要手动编译
#execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/brpc/build.sh)

#crc32c
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/crc32c/build.sh)

#fmt
#execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/fmt/build.sh)

#gflags
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/gflags/build.sh)

#gtest
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/gtest/build.sh)

#jemalloc
#todo

#jsoncpp
#todo

#leveldb
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/leveldb/build.sh)

#libexpat
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libexpat/build.sh)

#libressl
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libressl/build.sh)

#libunwind
#todo

#libuuid
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/libuuid/build.sh)

#linenoise
#header-only

#protobuf
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/protobuf/build.sh)

#redis
#todo

#snappy
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/snappy/build.sh)

#spdlog
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/snappy/build.sh)

#thrift
#todo

#zlib
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/zlib/build.sh)

#zstd
execute_process(COMMAND sh $ENV{MK_PATH}/3rd_Party/zstd/build.sh)


ENDIF()
