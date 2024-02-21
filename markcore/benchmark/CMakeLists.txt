PROJECT(benchmark_markcore)

#version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)

#begin
INCLUDE($ENV{MK_PATH}/make/begin.cmake)

#目标类型
SET(TARGET_NAME benchmark_markcore)
SET(TARGET_TYPE RUNTIME)

#依赖库
SET(NEED_GTEST TRUE)
SET(NEED_BENCHMARK TRUE)
SET(NEED_MARKCORE TRUE)

IF(WIN32)
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors") #禁用返回值优化RVO
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable") #忽略一些警告
    #include(${MK_PATH}/3rd_Party/ai/config.cmake)
    #ADD_SOURCE_DIRS(./ai)
ENDIF()

#end
INCLUDE($ENV{MK_PATH}/make/end.cmake)
