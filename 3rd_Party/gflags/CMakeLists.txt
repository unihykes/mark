PROJECT(gflags)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE ARCHIVE)
SET(TARGET_NAME gflags)

INCLUDE_DIRECTORIES(./gflags/src; ./include; ./include/gflags;)

set(libgflags_files
  ./gflags/src/gflags.cc
  ./gflags/src/gflags_reporting.cc
  ./gflags/src/gflags_completions.cc
)

if(WIN32)
  list(APPEND libgflags_files  ./gflags/src/windows_port.cc)
endif()

SET(INCLUDE_SOURCE_FILES ${libgflags_files})

INCLUDE($ENV{MK_MAKE}/end.cmake)
