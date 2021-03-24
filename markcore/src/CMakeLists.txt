PROJECT(markcore)

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
CMAKE_POLICY(VERSION 3.17)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME markcore)

set(NEED_BOOST_FULL true)

IF(WIN32)
	set(3rdparty_os 3rdparty/_win)
    ADD_SOURCE_DIRS(./${3rdparty_os}/win-iconv;)
    SET(EXCLUDE_SOURCE_FILES ./${3rdparty_os}/win-iconv/win_iconv_test.c)
ELSE()
	set(3rdparty_os 3rdparty/_unix)
ENDIF()

INCLUDE_DIRECTORIES(../include;
                    ./3rdparty;
                    ./${3rdparty_os};
)

ADD_SOURCE_DIRS(./algorithm;
                ./gof;
                ./module;
                ./print;
                ./string;
                ./thread;
                ./utility;
)

ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

INCLUDE($ENV{MK_MAKE}/end.cmake)
