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
ADD_SOURCE_DIRS(./0-Language;
                ./0-Language/0-BasicConcepts;
                ./0-Language/1-Keywords;
                ./0-Language/2-Preprocessor;
                ./0-Language/3-Expressions;
                ./0-Language/4-Declaration;
                )

INCLUDE($ENV{MONK_MAKE}/end.cmake)



