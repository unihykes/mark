PROJECT(mkops)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)


ADD_DEFINITIONS("-D__MAKE_MK_DLL__")
SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME mkops)

SET(NEED_MARKCORE TRUE)
SET(NEED_BRPC TRUE)

INCLUDE_DIRECTORIES(../include;)

INCLUDE(${MK_PATH}/3rd_Party/protobuf/compile_proto.cmake)
ADD_BUILD_PROTO_FILES(../proto  ../proto/mkIOpsRpc.proto)

#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
