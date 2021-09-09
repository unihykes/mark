PROJECT(mkra)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)

#Ŀ������
SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME mkra)

#������
SET(NEED_MARKCORE TRUE)
include(${MK_PATH}/mkops/config.cmake)

INCLUDE_DIRECTORIES(../include; ./LIRS;)
ADD_SOURCE_DIRS(./; ./LIRS)

ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
