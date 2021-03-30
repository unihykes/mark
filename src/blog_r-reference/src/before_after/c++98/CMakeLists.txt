PROJECT(ut_98)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME ut_98)
SET(AUTO_RUN OFF)

#gtest
SET(NEED_GTEST TRUE)

# 编译目录
ADD_SOURCE_DIRS(../;)

IF(WIN32)
    MESSAGE(FATAL_ERROR "do not support windows.")
ELSE()
    #指定使用c++98, 该选项目前仅支持linux
    SET(MK_STD_VERSION c++98)
    
    #禁用返回值优化RVO
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
ENDIF()

INCLUDE($ENV{MK_MAKE}/end.cmake)



