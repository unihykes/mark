

include(${MK_PATH}/3rd_Party/gflags/config.cmake)
include(${MK_PATH}/3rd_Party/leveldb/config.cmake)
include(${MK_PATH}/3rd_Party/protobuf/config.cmake)


include_directories(${MK_DEPS_PKGS}/brpc/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/brpc/lib64 brpc)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} brpc)