PROJECT(markcore)

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
CMAKE_POLICY(VERSION 3.17)

INCLUDE($ENV{MK_PATH}/make/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME markcore)

set(NEED_BOOST_FULL true)

find_package(highwayhash)
find_package(spdlog)

IF(WIN32)
	set(3rdparty_os 3rdparty/_win)
    SET(MK_BUILD_SOURCE_FILES ./${3rdparty_os}/win-iconv/win_iconv.c)
ELSE()
    set(NEED_LIBUUID true)
	set(3rdparty_os 3rdparty/_unix)
ENDIF()

INCLUDE_DIRECTORIES(../include;
                    ./3rdparty;
                    ./${3rdparty_os};
)

ADD_SOURCE_DIRS(./algorithm;
                ./gof;
                ./print;
                ./string;
                ./thread;
                ./utility;
)

ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

INCLUDE($ENV{MK_PATH}/make/end.cmake)
