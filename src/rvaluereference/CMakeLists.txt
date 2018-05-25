PROJECT(rvaluereference)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME rvaluereference)
SET(AUTO_RUN OFF)

#依赖库
SET(NEED_GTEST TRUE)

# 编译目录
ADD_SOURCE_DIRS(./valueType;
                ./referenceType;
                ./usage;
                ./collapsing;)

IF(WIN32)
ELSE()
    #禁用返回值优化RVO
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
ENDIF()

INCLUDE($ENV{MONK_MAKE}/end.cmake)



