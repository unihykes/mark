PROJECT(markcore)

CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
CMAKE_POLICY(VERSION 3.17)

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

ADD_SOURCE_DIRS(./gof;
                ./module;
                ./print;
                ./string;
                ./thread;
                ./language;
                ./utility;
)


ADD_DEFINITIONS("-D__MAKE_MK_DLL__")

INCLUDE($ENV{MK_MAKE}/end.cmake)
