MESSAGE(STATUS "find wxWidgets libs...")

#deps路径
SET(WXLIBS_PATH ${ABDEPS}/wxWidgets/build_target)

#添加宏定义
ADD_DEFINITIONS(-DWXUSINGDLL -DwxMONOLITHIC=1 -DwxNO_GL_LIB)

#设置头文件路径
INCLUDE_DIRECTORIES(${WXLIBS_PATH}/include;
                    ${WXLIBS_PATH}/include/msvc)

                    
#设置静态库(wxmsw31ud.lib)路径
link_directories(${WXLIBS_PATH}/lib/vc_x64_dll)

#copy动态库(wxmsw312u_vc_x64_custom.dll)到运行目录
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    SET(WXLIBS_DLL_NAME wxmsw312ud_vc_x64_custom.dll)
ELSE ()
    SET(WXLIBS_DLL_NAME wxmsw312u_vc_x64_custom.dll)
ENDIF ()
seek_deps_file_no_install(${LIBS_PATH}  ${WXLIBS_PATH}/lib/vc_x64_dll ${WXLIBS_DLL_NAME})
#seek_deps_library(${LIBS_PATH} ${WXLIBS_PATH}/lib/vc_x64_dll ${WXLIBS_DLL_NAME})
