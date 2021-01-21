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

#todo
#ADD_DEFINITIONS(-DBOOST_ATOMIC_SOURCE)
#ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/atomic/src)

#chrono!
#ADD_DEFINITIONS(-DBOOST_CHRONO_SOURCE)
#ADD_SOURCE_DIRS(./libs/chrono/src)

#container todo
#ADD_DEFINITIONS(-DBOOST_CONTAINER_SOURCE)
#ADD_SOURCE_DIRS(./libs/container/src)

#context todo

#contract todo

#coroutine todo

# date_time todo
#ADD_DEFINITIONS(-DBOOST_DATE_TIME_SOURCE)
#ADD_SOURCE_DIRS(./libs/date_time/src/posix_time)
#ADD_SOURCE_DIRS(./libs/date_time/src/gregorian)

#exception !
#ADD_SOURCE_DIRS(./libs/exception/src)


#fiber todo

#filesystem
#ADD_DEFINITIONS(-DBOOST_FILESYSTEM_SOURCE)
#ADD_SOURCE_DIRS(./libs/filesystem/src)

#graph todo

#graph_parallel  todo



#iostreams todo
#json todo
#locale todo

#log todo
#ADD_SOURCE_DIRS(./libs/log/src)

#math todo
#mpi todo
#nowide todo
#program_options todo
#python todo

#random  todo
#ADD_DEFINITIONS(-DBOOST_RANDOM_SOURCE)
#ADD_SOURCE_DIRS(./libs/random/src)

#regex todo
#ADD_DEFINITIONS(-DBOOST_REGEX_SOURCE)
#ADD_SOURCE_DIRS(./libs/regex/src)

#serialization todo
#stacktrace todo

#system todo
#ADD_DEFINITIONS(-DBOOST_SYSTEM_SOURCE)
#ADD_SOURCE_DIRS(./libs/system/src)

#test todo

#thread todo
# IF(WIN32)
    # SET(boost_thread_dir win32)
# ELSE()
    # SET(boost_thread_dir pthread)
    # SET(EXCLUDE_SOURCE_FILES thread/src/pthread/once_atomic.cpp)
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic -Wno-long-long -Wno-variadic-macros  -march=native")
# ENDIF()
# ADD_SOURCE_DIRS(./libs/thread/src)
# ADD_SOURCE_DIRS(./libs/thread/src/${boost_thread_dir})

#timer todo
#type_erasure todo
#wave todo

INCLUDE($ENV{MK_MAKE}/end.cmake)