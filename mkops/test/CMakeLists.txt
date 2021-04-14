PROJECT(use_mkops)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)

#目标类型
SET(TARGET_NAME use_mkops)
SET(TARGET_TYPE RUNTIME)

#依赖库
SET(NEED_GTEST TRUE)
SET(NEED_BENCHMARK TRUE)
SET(NEED_MARKCORE TRUE)

#依赖 mkops
include(${MK_PATH}/mkops/config.cmake)

#借用 main.cpp
set(INCLUDE_SOURCE_FILES ${INCLUDE_SOURCE_FILES} ${MK_PATH}/markcore/ut/main.cpp)


#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
