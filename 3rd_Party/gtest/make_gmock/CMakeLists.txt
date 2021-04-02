PROJECT(googlegmock)

CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
CMAKE_POLICY(VERSION 3.18)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_NAME gmock)
SET(TARGET_TYPE LIBRARY)

INCLUDE_DIRECTORIES(../googletest/googletest/include;
					../googletest/googlemock/include;
					../googletest/googlemock;)

#待编译文件(gmock-all.cc会include所有.cc源文件)
SET(INCLUDE_SOURCE_FILES    ../googletest/googlemock/src/gmock-all.cc)

INCLUDE($ENV{MK_MAKE}/end.cmake)

