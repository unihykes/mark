PROJECT(ut_std)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME ut_std)
SET(AUTO_RUN OFF)

#“¿¿µø‚
SET(NEED_GTEST TRUE)

# ±‡“Îƒø¬º
ADD_SOURCE_DIRS(./0-Language/0-BasicConcepts;
                ./0-Language/1-Keywords)

INCLUDE($ENV{MONK_MAKE}/end.cmake)



