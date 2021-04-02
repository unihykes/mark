include_directories(${MK_DEPS_PKGS}/zlib/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/zlib/lib z)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} z)