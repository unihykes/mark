PROJECT(usestd)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME usestd)
SET(AUTO_RUN OFF)

#“¿¿µø‚
SET(NEED_GTEST TRUE)

# ±‡“Îƒø¬º
ADD_SOURCE_DIRS(./0-Language;
                ./UtilitiesLibrary;
                )

INCLUDE($ENV{MONK_MAKE}/end.cmake)



