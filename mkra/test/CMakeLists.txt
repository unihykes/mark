PROJECT(use_mkreplacement)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)

#Ŀ������
SET(TARGET_NAME use_mkreplacement)
SET(TARGET_TYPE RUNTIME)

#������
SET(NEED_GTEST TRUE)
SET(NEED_BENCHMARK TRUE)
SET(NEED_MARKCORE TRUE)

#������
include(${MK_PATH}/mkra/config.cmake)

#���� main.cpp
set(INCLUDE_SOURCE_FILES ${INCLUDE_SOURCE_FILES} ${MK_PATH}/markcore/ut/main.cpp)


#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
