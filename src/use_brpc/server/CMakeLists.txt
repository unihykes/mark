PROJECT(use_brpc_server)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
CMAKE_POLICY(VERSION 3.17)

#begin
INCLUDE($ENV{MK_MAKE}/begin.cmake)

#目标类型
SET(TARGET_NAME use_brpc_server)
SET(TARGET_TYPE RUNTIME)
SET(AUTO_RUN OFF)

#依赖库
SET(NEED_GTEST TRUE)
SET(NEED_GFLAGS TRUE)
SET(NEED_PROTOBUF TRUE)
SET(NEED_BRPC TRUE)
SET(NEED_MARKCORE TRUE)

#编译proto
INCLUDE(${MK_PATH}/3rd_Party/protobuf/compile_proto.cmake)
ADD_BUILD_PROTO_FILES( ../proto ../proto/use_brpc.proto)

#end
INCLUDE($ENV{MK_MAKE}/end.cmake)
