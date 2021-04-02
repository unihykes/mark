
ADD_DEFINITIONS(-D__USING_GTEST__)
ADD_DEFINITIONS(-D__USING_GMOCK__)

IF(WIN32)
    #todo
ELSE()
    include_directories(${MK_DEPS_PKGS}/gtest/include)
    LINK_LIBRARIES(pthread)
    seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/gtest/lib64 gtest gmock)
ENDIF()

SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} gtest gmock)