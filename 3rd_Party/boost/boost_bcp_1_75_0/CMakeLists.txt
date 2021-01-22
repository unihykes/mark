CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)
PROJECT(boost_bcp)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME boost_bcp)


INCLUDE_DIRECTORIES(./)

#宏定义
ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB
                -DBOOST_ALL_DYN_LINK
                -DBOOST_THREAD_BUILD_DLL=1
                -DBOOST_ATOMIC_DYN_LINK=1
                -DBOOST_SYSTEM_NO_DEPRECATED
                )

#atomic
#需要安装openssl:yum -y install openssl-devel
ADD_DEFINITIONS(-DBOOST_ATOMIC_SOURCE)
INCLUDE_DIRECTORIES(./libs/atomic/src)
ADD_SOURCE_DIRS(./libs/atomic/src)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -msse3 -mssse3 -msse4.1")
IF(UNIX)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/atomic/src/wait_ops_windows.cpp)
ENDIF()

#chrono
ADD_DEFINITIONS(-DBOOST_CHRONO_SOURCE)
ADD_SOURCE_DIRS(./libs/chrono/src)

#container
ADD_DEFINITIONS(-DBOOST_CONTAINER_SOURCE)
ADD_SOURCE_DIRS(./libs/container/src)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/container/src/dlmalloc_2_8_6.c)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/container/src/dlmalloc_ext_2_8_6.c)

#context
ADD_DEFINITIONS(-DBOOST_USE_UCONTEXT)
ADD_SOURCE_DIRS(./libs/context/src)
ADD_SOURCE_DIRS(./libs/context/src/posix)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/context/src/untested.cpp)

#contract
ADD_DEFINITIONS(-DBOOST_CONTRACT_SOURCE)
ADD_SOURCE_DIRS(./libs/contract/src)


#coroutine
ADD_DEFINITIONS(-DBOOST_COROUTINES_SOURCE)
ADD_SOURCE_DIRS(./libs/coroutine/src)
ADD_SOURCE_DIRS(./libs/coroutine/src/posix)
ADD_SOURCE_DIRS(./libs/coroutine/src/detail)

# date_time
ADD_DEFINITIONS(-DBOOST_DATE_TIME_SOURCE)
ADD_SOURCE_DIRS(./libs/date_time/src/posix_time)
ADD_SOURCE_DIRS(./libs/date_time/src/gregorian)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/date_time/src/gregorian/date_generators.cpp)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/date_time/src/gregorian/greg_weekday.cpp)

#exception
ADD_SOURCE_DIRS(./libs/exception/src)


#fiber
ADD_DEFINITIONS(-DBOOST_FIBERS_SOURCE)
ADD_SOURCE_DIRS(./libs/fiber/src)
ADD_SOURCE_DIRS(./libs/fiber/src/algo)
ADD_SOURCE_DIRS(./libs/fiber/src/numa/linux)

#filesystem
ADD_DEFINITIONS(-DBOOST_FILESYSTEM_SOURCE)
ADD_SOURCE_DIRS(./libs/filesystem/src)

#graph
ADD_DEFINITIONS(-DBOOST_GRAPH_SOURCE)
ADD_SOURCE_DIRS(./libs/graph/src)


#graph_parallel
#需要安装mpi:yum -y install openmpi-devel 
INCLUDE_DIRECTORIES(/usr/include/openmpi-x86_64)
ADD_SOURCE_DIRS(./libs/graph_parallel/src)


#iostreams
#需要安装bzip2(zlib.h):yum -y install bzip2-devel
#需要安装xz(lzma.h): yum -y install xz-devel
#需要安装zstd(zstd.h): todo
ADD_DEFINITIONS(-DBOOST_IOSTREAMS_SOURCE)
ADD_SOURCE_DIRS(./libs/iostreams/src)
SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/iostreams/src/zstd.cpp)#todo:需要zstd支持

#json
ADD_SOURCE_DIRS(./libs/json/src)

#locale
INCLUDE_DIRECTORIES(./libs/locale/src)
ADD_DEFINITIONS(-DBOOST_LOCALE_SOURCE)
ADD_SOURCE_DIRS(./libs/locale/src/posix)
ADD_SOURCE_DIRS(./libs/locale/src/shared)
ADD_SOURCE_DIRS(./libs/locale/src/util)
ADD_SOURCE_DIRS(./libs/locale/src/std)

#log todo
#ADD_SOURCE_DIRS(./libs/log/src)

#math todo
#ADD_SOURCE_DIRS(./libs/math/src/tr1)

#mpi
ADD_SOURCE_DIRS(./libs/mpi/src)

#nowide
ADD_DEFINITIONS(-DBOOST_NOWIDE_SOURCE)
ADD_SOURCE_DIRS(./libs/nowide/src)

#program_options
ADD_DEFINITIONS(-DBOOST_PROGRAM_OPTIONS_SOURCE)
ADD_SOURCE_DIRS(./libs/program_options/src)

#python todo

#random 
ADD_DEFINITIONS(-DBOOST_RANDOM_SOURCE)
ADD_SOURCE_DIRS(./libs/random/src)

#regex
ADD_DEFINITIONS(-DBOOST_REGEX_SOURCE)
ADD_SOURCE_DIRS(./libs/regex/src)

#serialization
ADD_DEFINITIONS(-DBOOST_ARCHIVE_SOURCE)
ADD_SOURCE_DIRS(./libs/serialization/src)


#stacktrace todo
#ADD_SOURCE_DIRS(./libs/stacktrace/src)

#system
ADD_DEFINITIONS(-DBOOST_SYSTEM_SOURCE)
ADD_SOURCE_DIRS(./libs/system/src)

#test
ADD_DEFINITIONS(-DBOOST_TEST_SOURCE)
ADD_SOURCE_DIRS(./libs/test/src)

#thread
IF(WIN32)
    SET(boost_thread_dir win32)
ELSE()
    SET(boost_thread_dir pthread)
    SET(EXCLUDE_SOURCE_FILES ${EXCLUDE_SOURCE_FILES} ./libs/thread/src/pthread/once_atomic.cpp)
ENDIF()
ADD_SOURCE_DIRS(./libs/thread/src)
ADD_SOURCE_DIRS(./libs/thread/src/${boost_thread_dir})

#timer
ADD_DEFINITIONS(-DBOOST_TIMER_SOURCE)
ADD_SOURCE_DIRS(./libs/timer/src)

#type_erasure
ADD_DEFINITIONS(-DBOOST_TYPE_ERASURE_SOURCE)
ADD_SOURCE_DIRS(./libs/timer/src)

#wave
ADD_DEFINITIONS(-DBOOST_WAVE_SOURCE)
ADD_SOURCE_DIRS(./libs/wave/src)


INCLUDE($ENV{MK_MAKE}/end.cmake)