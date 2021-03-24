CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
CMAKE_POLICY(VERSION 3.1)
PROJECT(boost_full)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME boost_full)

set(BOOST_ROOT ./boost_1_75_0)

INCLUDE_DIRECTORIES(${BOOST_ROOT})

IF(WIN32)
    # windows下强制生成.lib文件,否则无法被link
    ADD_DEFINITIONS("-D__MAKE_MK_DLL__")
    ADD_SOURCE_DIRS(./)
ENDIF()

#宏定义
ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB
                -DBOOST_ALL_DYN_LINK
                -DBOOST_THREAD_BUILD_DLL=1
                -DBOOST_ATOMIC_DYN_LINK=1
                -DBOOST_SYSTEM_NO_DEPRECATED
                )

#atomic
ADD_DEFINITIONS(-DBOOST_ATOMIC_SOURCE)
IF(UNIX)
    #需要安装openssl:yum -y install openssl-devel
    INCLUDE_DIRECTORIES(${BOOST_ROOT}/libs/atomic/src)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/atomic/src)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -mssse3 -msse4.1")
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/atomic/src/wait_ops_windows.cpp)
ENDIF()

#chrono
ADD_DEFINITIONS(-DBOOST_CHRONO_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/chrono/src)
ENDIF()

#container
ADD_DEFINITIONS(-DBOOST_CONTAINER_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/container/src)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/container/src/dlmalloc_2_8_6.c)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/container/src/dlmalloc_ext_2_8_6.c)
ENDIF()

#context
ADD_DEFINITIONS(-DBOOST_USE_UCONTEXT)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/context/src)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/context/src/posix)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/context/src/untested.cpp)
ENDIF()

#contract
ADD_DEFINITIONS(-DBOOST_CONTRACT_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/contract/src)
ENDIF()

#coroutine
ADD_DEFINITIONS(-DBOOST_COROUTINES_SOURCE)
IF(UNIX)
    #todo:暂未解决运行时 undefined reference to `jump_fcontext'
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/coroutine/src)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/coroutine/src/posix)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/coroutine/src/detail)
ENDIF()

# date_time
ADD_DEFINITIONS(-DBOOST_DATE_TIME_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/date_time/src/posix_time)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/date_time/src/gregorian)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/date_time/src/gregorian/date_generators.cpp)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/date_time/src/gregorian/greg_weekday.cpp)
ENDIF()

#exception
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/exception/src)
ENDIF()

#fiber
ADD_DEFINITIONS(-DBOOST_FIBERS_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/fiber/src)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/fiber/src/algo)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/fiber/src/numa/linux)
ENDIF()

#filesystem
ADD_DEFINITIONS(-DBOOST_FILESYSTEM_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/filesystem/src)
ENDIF()

#graph
ADD_DEFINITIONS(-DBOOST_GRAPH_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/graph/src)
ENDIF()

#graph_parallel
IF(UNIX)
    #需要安装mpi:yum -y install openmpi-devel 
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/graph_parallel/src)
    INCLUDE_DIRECTORIES(/usr/include/openmpi-x86_64)
    LINK_DIRECTORIES(/usr/lib64/openmpi/lib)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmpi")
ENDIF()

#iostreams
ADD_DEFINITIONS(-DBOOST_IOSTREAMS_SOURCE)
IF(UNIX)
    #需要安装bzip2(zlib.h):yum -y install bzip2-devel
    #需要安装xz(lzma.h): yum -y install xz-devel
    #需要安装zstd(zstd.h): todo
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/iostreams/src)
    
    #todo:暂未安装zstd
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/iostreams/src/zstd.cpp)
ENDIF()

#json
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/json/src)
ENDIF()

#locale
ADD_DEFINITIONS(-DBOOST_LOCALE_SOURCE)
IF(UNIX)
    #todo:暂未解决链接问题
    #INCLUDE_DIRECTORIES(${BOOST_ROOT}/libs/locale/src)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/locale/src/encoding)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/locale/src/posix)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/locale/src/shared)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/locale/src/util)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/locale/src/std)
ENDIF()

#log
IF(UNIX)
    #todo:暂未解决编译问题
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/log/src)
ENDIF()

#math
IF(UNIX)
    #todo:暂未解决编译问题
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/math/src/tr1)
ENDIF()

#mpi
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/mpi/src)
ENDIF()

#nowide
ADD_DEFINITIONS(-DBOOST_NOWIDE_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/nowide/src)
ENDIF()

#program_options
ADD_DEFINITIONS(-DBOOST_PROGRAM_OPTIONS_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/program_options/src)
ENDIF()

#python
IF(UNIX)
    #todo:暂未解决编译问题
ENDIF()

#random 
ADD_DEFINITIONS(-DBOOST_RANDOM_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/random/src)
ENDIF()

#regex
ADD_DEFINITIONS(-DBOOST_REGEX_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/regex/src)
ENDIF()

#serialization
ADD_DEFINITIONS(-DBOOST_ARCHIVE_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/serialization/src)
ENDIF()

#stacktrace
IF(UNIX)
    #todo:暂未解决编译问题
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/stacktrace/src)
ENDIF()

#system
ADD_DEFINITIONS(-DBOOST_SYSTEM_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/system/src)
ENDIF()

#test
ADD_DEFINITIONS(-DBOOST_TEST_SOURCE)
IF(UNIX)
    #todo:暂未解决 undefined reference to `test_main(int, char**)'
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/test/src)
ENDIF()

#thread
IF(WIN32)
    #ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/thread/src/win32)
ELSE()
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/thread/src)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/thread/src/pthread)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ${BOOST_ROOT}/libs/thread/src/pthread/once_atomic.cpp)
ENDIF()

#timer
ADD_DEFINITIONS(-DBOOST_TIMER_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/timer/src)
ENDIF()

#type_erasure
ADD_DEFINITIONS(-DBOOST_TYPE_ERASURE_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/type_erasure/src)
ENDIF()

#wave
ADD_DEFINITIONS(-DBOOST_WAVE_SOURCE)
IF(UNIX)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/wave/src)
    ADD_SOURCE_DIRS(${BOOST_ROOT}/libs/wave/src/cpplexer/re2clex)
ENDIF()

INCLUDE($ENV{MK_MAKE}/end.cmake)