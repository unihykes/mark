include_directories(${MK_DEPS_PKGS}/snappy/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/snappy/lib64 snappy)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} snappy)