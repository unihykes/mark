include_directories(${MK_DEPS_PKGS}/libexpat/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/libexpat/lib64 expat)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} expat)