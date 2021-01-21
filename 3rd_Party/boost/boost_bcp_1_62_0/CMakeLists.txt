PROJECT(boost_bcp)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE LIBRARY)
SET(TARGET_NAME boost_bcp)

#版本
SET(BOOST_DIR ./)

#宏定义
ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB
                -DBOOST_ALL_DYN_LINK
                -DBOOST_THREAD_BUILD_DLL=1
                -DBOOST_ATOMIC_DYN_LINK=1
                -DBOOST_SYSTEM_NO_DEPRECATED
                -DBOOST_ATOMIC_SOURCE
                -DBOOST_SYSTEM_SOURCE
                -DBOOST_CHRONO_SOURCE
                -DBOOST_DATE_TIME_SOURCE
                -DBOOST_FILESYSTEM_SOURCE
                -DBOOST_REGEX_SOURCE
                -DBOOST_RANDOM_SOURCE
                )

#依赖头文件
INCLUDE_DIRECTORIES(./${BOOST_DIR})

#编译目录
IF(WIN32)
    SET(boost_thread_dir win32)
ELSE()
    SET(boost_thread_dir pthread)
    SET(EXCLUDE_SOURCE_FILES thread/src/pthread/once_atomic.cpp)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic -Wno-long-long -Wno-variadic-macros")
ENDIF()

ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/atomic/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/chrono/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/date_time/src/posix_time)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/date_time/src/gregorian)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/exception/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/filesystem/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/random/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/regex/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/smart_ptr/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/system/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/thread/src)
ADD_SOURCE_DIRS(./${BOOST_DIR}/libs/thread/src/${boost_thread_dir})


INCLUDE($ENV{MK_MAKE}/end.cmake)