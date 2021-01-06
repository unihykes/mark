PROJECT(markcore)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME markcore)

#引用路径
INCLUDE_DIRECTORIES(../include;)
INCLUDE_DIRECTORIES(./3rdparty)
IF(WIN32)
	INCLUDE_DIRECTORIES(./3rdparty/_win)
ELSE()
	INCLUDE_DIRECTORIES(./3rdparty/_unix)
ENDIF()

# 编译目录
ADD_SOURCE_DIRS(./module;
                ./print;
                ./thread;
                ./types;
                ./utility;
)


#添加自定义的选项
ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

INCLUDE($ENV{MK_MAKE}/end.cmake)
