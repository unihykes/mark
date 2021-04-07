
ADD_DEFINITIONS(-D__USING_GTEST__)
ADD_DEFINITIONS(-D__USING_GMOCK__)

IF(WIN32)
    include_directories(${MK_PATH}/3rd_Party/gtest/googletest/googlemock/include)
    include_directories(${MK_PATH}/3rd_Party/gtest/googletest/googletest/include)
    SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} gmock)
    SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} gtest)
ELSE()
    include_directories(${MK_DEPS_PKGS}/gtest/include)
    LINK_LIBRARIES(pthread)
    seek_deps_library(${LIBS_PATH} ${MK_DEPS_PKGS}/gtest/lib64 gtest gmock)
    SET(LINK_CUSTOM_LIBS ${LINK_CUSTOM_LIBS} gtest gmock)
ENDIF()

