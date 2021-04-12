PROJECT(mkreplacement)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)

#目标类型
SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME mkreplacement)

#依赖库
SET(NEED_MARKCORE TRUE)

INCLUDE_DIRECTORIES(../include; ./LIRS;)
ADD_SOURCE_DIRS(./; ./LIRS)

ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
