PROJECT(use_designpattern)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)



INCLUDE($ENV{MK_PATH}/make/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME use_designpattern)
SET(AUTO_RUN OFF)

#������
SET(NEED_GTEST TRUE)


INCLUDE($ENV{MK_PATH}/make/end.cmake)



