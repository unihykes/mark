include_directories(${MK_DEPS_PKGS}/spdlog/include)
seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/spdlog/lib64 spdlog)
SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} spdlog)