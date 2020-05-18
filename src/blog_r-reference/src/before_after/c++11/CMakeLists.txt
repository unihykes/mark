#g++ main.cpp  -o testVector_11   -fno-elide-constructors -std=c++11
#g++ main.cpp  -o testVector_98   -fno-elide-constructors -std=c++98

PROJECT(ut_11)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME ut_11)
SET(AUTO_RUN OFF)

#gtest
#gtest
SET(NEED_GTEST TRUE)

# 编译目录
ADD_SOURCE_DIRS(../;)

IF(WIN32)
    MESSAGE(FATAL_ERROR "do not support windows.")
ELSE()
    #指定使用c++11
    SET(MONK_STD_VERSION c++11)

    #禁用返回值优化RVO
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
ENDIF()

INCLUDE($ENV{MONK_MAKE}/end.cmake)



