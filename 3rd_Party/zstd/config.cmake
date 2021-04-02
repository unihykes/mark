include_directories(${MK_DEPS_PKGS}/zstd/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/zstd/lib64 zstd)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} zstd)