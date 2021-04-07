
#helpers
include_directories(${MK_PATH}/3rd_Party/benchmark/helpers)

IF(WIN32)
    include_directories(${MK_PATH}/3rd_Party/benchmark/benchmark/include)
    seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/__build/benchmark/src/Release benchmark)
ELSE()
    include_directories(${MK_DEPS_PKGS}/benchmark/include)
    seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/benchmark/lib64 benchmark)
ENDIF()
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} benchmark)