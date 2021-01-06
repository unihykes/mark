PROJECT(markcore)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME markcore)

IF(WIN32)
	set(3rdparty_os 3rdparty/_win)
ELSE()
	set(3rdparty_os 3rdparty/_unix)
ENDIF()

INCLUDE_DIRECTORIES(../include;
                    ./3rdparty;
                    ./${3rdparty_os};
)

ADD_SOURCE_DIRS(./module;
                ./print;
                ./thread;
                ./language;
                ./utility;
)


ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

INCLUDE($ENV{MK_MAKE}/end.cmake)
