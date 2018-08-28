MESSAGE(STATUS "find wxWidgets libs...")

set(SUBSYSTEM WINDOWS)
set(WX_DYNAMIC_LINK ON)

#debug相关的宏
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    #begin.cmake中debuging设置为0,导致无法正确链接wx的.lib库文件
    ADD_DEFINITIONS(-D__WXMSW__ -D__WXDEBUG__ -D_HAS_ITERATOR_DEBUGGING=1)
ENDIF()


IF("${WX_DYNAMIC_LINK}" STREQUAL "ON")
    #动态链接使用dll
    SET(WXLIBS_PATH ./build_target)
    ADD_DEFINITIONS(-DWXUSINGDLL -DwxMONOLITHIC=1 -DwxNO_GL_LIB)
    INCLUDE_DIRECTORIES(${WXLIBS_PATH}/include; ${WXLIBS_PATH}/include/msvc)
    link_directories(${WXLIBS_PATH}/lib/vc_x64_dll)
    
    IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        seek_deps_file_no_install(${LIBS_PATH} ${WXLIBS_PATH}/lib/vc_x64_dll wxmsw312ud_vc_x64_custom.dll)
    ENDIF ()
ELSE()
    #静态链接使用lib
    INCLUDE_DIRECTORIES(./wxWidgets/include;./wxWidgets/include/msvc)
    link_directories(./wxWidgets/lib/vc_x64_lib)
    link_libraries(
        wxbase31ud.lib
        wxbase31ud_net.lib
        wxbase31ud_xml.lib
        wxexpatd.lib
        wxjpegd.lib
        wxmsw31ud_adv.lib
        wxmsw31ud_aui.lib
        wxmsw31ud_core.lib
        wxmsw31ud_gl.lib
        wxmsw31ud_html.lib
        wxmsw31ud_media.lib
        wxmsw31ud_propgrid.lib
        wxmsw31ud_qa.lib
        wxmsw31ud_ribbon.lib
        wxmsw31ud_richtext.lib
        wxmsw31ud_stc.lib
        wxmsw31ud_webview.lib
        wxmsw31ud_xrc.lib
        wxpngd.lib
        wxregexud.lib
        wxscintillad.lib
        wxtiffd.lib
        wxzlibd.lib
    )
    #可选静态库
    #"kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" 
    # "shell32.lib" "ole32.lib" "oleaut32.lib"  "uuid.lib" "odbc32.lib" "odbccp32.lib"
ENDIF()










