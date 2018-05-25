PROJECT(ut_98)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME ut_98)
SET(AUTO_RUN OFF)

#gtest
ADD_DEFINITIONS(-D__USING_GTEST__)
INCLUDE_DIRECTORIES(${MONK_PATH}/3rd_Party/gtest/googletest/googletest/include)
SET(LINK_GTEST_LIBS gtest)

# 编译目录
ADD_SOURCE_DIRS(../;)

IF(WIN32)
    MESSAGE(FATAL_ERROR "do not support windows.")
ELSE()
    #指定使用c++98, 该选项目前仅支持linux
    SET(MONK_STD_VERSION c++98)
    
    #禁用返回值优化RVO
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
ENDIF()

INCLUDE($ENV{MONK_MAKE}/end.cmake)



