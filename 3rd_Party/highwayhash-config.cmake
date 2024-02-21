include_directories(${MK_DEPS_PKGS}/highwayhash/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/highwayhash/lib64 highwayhash)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} highwayhash)