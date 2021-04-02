include_directories(${MK_DEPS_PKGS}/gflags/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/gflags/lib gflags)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} gflags)