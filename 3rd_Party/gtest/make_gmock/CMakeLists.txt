PROJECT(googlegmock)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_NAME gmock)
SET(TARGET_TYPE ARCHIVE)

INCLUDE_DIRECTORIES(../googletest/googletest/include;
					../googletest/googlemock/include;
					../googletest/googlemock;)

#待编译文件(gmock-all.cc会include所有.cc源文件)
SET(INCLUDE_SOURCE_FILES    ../googletest/googlemock/src/gmock-all.cc)

INCLUDE($ENV{MONK_MAKE}/end.cmake)

