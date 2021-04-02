include_directories(${MK_DEPS_PKGS}/crc32c/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/crc32c/lib64 crc32c)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} crc32c)