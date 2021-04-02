include_directories(${MK_DEPS_PKGS}/libuuid/include/uuid)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/libuuid/lib uuid)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} uuid)