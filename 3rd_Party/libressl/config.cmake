include_directories(${MK_DEPS_PKGS}/libressl/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/libressl/lib64 crypto ssl tls)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} crypto ssl tls)