MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "include begin.cmake")

# 将环境变量转为cmake临时变量
SET(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE} CACHE STRING "")
SET(CMAKE_BUILD_VERSION $ENV{CMAKE_BUILD_VERSION} CACHE STRING "")
SET(CMAKE_PLATFORM_NAME $ENV{CMAKE_PLATFORM_NAME} CACHE STRING "")
SET(CMAKE_PLATFORM_VERSION $ENV{CMAKE_PLATFORM_VERSION} CACHE STRING "")

SET(MK_PATH $ENV{MK_PATH} CACHE STRING "")
SET(MK_PLATFORM $ENV{MK_PLATFORM} CACHE STRING "")
SET(MK_TARGET $ENV{MK_TARGET} CACHE STRING "")
SET(MK_MAKE $ENV{MK_PATH}/make CACHE STRING "")
SET(MK_DEPS_PKGS $ENV{MK_DEPS_PKGS} CACHE STRING "")


# 设置 make package target 的默认存放路径
SET(INSTALL_PATH .)

#设置 LIBS_PATH
SET(LIBS_PATH ${MK_TARGET}/${CMAKE_BUILD_TYPE})

#设置cmake的 include() or find_package() 的查找路径
SET(CMAKE_MODULE_PATH ${MK_MAKE})

#设置if和else的控制开关选项
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

# 设置Cmake采用相对路径
SET(CMAKE_USE_RELATIVE_PATHS TRUE)

#将当前源文件目录自动添加到头文件引用路径下
SET(CMAKE_INCLUDE_CURRENT_DIR ON) 

#设置“输出编译详细信息 = ON"
SET(CMAKE_VERBOSE_MAKEFILE ON)

# 设置 cmake rpath 选项
SET(CMAKE_INSTALL_RPATH .;..)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# 设置cmake install属性
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# 设置默认的打包子路径
SET(INSTALL_SUB_PATH ".")

# 默认源文件目录，当前目录
SET(SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "SET SOURCE_DIRS = ${SOURCE_DIRS}")


#预定义宏
IF(WIN32)
    ADD_DEFINITIONS(/D _UNICODE 
                    /D UNICODE 
                    /D WIN32 
                    /D __WINDOWS__ 
                    /D _CRT_SECURE_NO_WARNINGS 
                    /D _CRT_SECURE_NO_DEPRECATE 
                    /D _CRT_NONSTDC_NO_DEPRECATE)
ELSE()
    ADD_DEFINITIONS(-D__LINUX__ 
                    -D_GNU_SOURCE)
    IF("${CMAKE_BUILD_VERSION}" STREQUAL "i386")
        #linux环境下操作特大文件 -D_FILE_OFFSET_BITS=64, 否则fopen和open操作的文件大小不能超过2G。
        ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                        -D_LARGEFILE64_SOURCE=1)
    ENDIF()
ENDIF()

#编译选项
#pragma warnind( disable: 4251 )
IF(WIN32)
    #编译器错误:https://docs.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2008/8x5x43k7(v%3dvs.90)
    #编译器警告:4181:应用到引用类型的限定符；已将其忽略将限定符（如 const）应用于由 typedef 定义的引用类型。
    #编译器警告:4099:将声明为结构的对象定义为类，或将声明为类的对象定义为结构。编译器使用在定义中给定的类型。
    #编译器警告:4819:该文件包含不能在当前代码页(936)中表示的字符。 请将该文件保存为 Unicode 格式以防止数据丢失
    #编译器警告:4251: class“std::basic_string<char,std::char_traits<char>,std::allocator<char>>”需要有 dll 接口由 class“xxx”的客户端使用
    #windows编译选项:https://msdn.microsoft.com/en-us/library/thxezb7y.aspx
    #/wd n : Disables the specified compiler warning where nis the compiler warning number.
    #/wo n : Reports the error only once where n is a compiler warning.
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /vmm /vmg /MP /wo4067 /wo4244 /wo4267 /wo4181 /wd4099 /wd4819 /wd4251 /wd4275")
    STRING(REPLACE "/EHsc" "/EHa /GS" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
ELSE()
    IF("${CMAKE_BUILD_VERSION}" STREQUAL "i386")
        SET(CMAKE_C_FLAGS "-m32 -pipe -pthread -Wall ${CMAKE_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "-m32 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
    ELSE()
        SET(CMAKE_C_FLAGS "-m64 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
        SET(CMAKE_CXX_FLAGS "-m64 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
    ENDIF()
    #linux下链接属性
    IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET(CMAKE_SHARED_LINKER_FLAGS "-rdynamic -Wl,-E ${CMAKE_SHARED_LINKER_FLAGS}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "SET CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
    ENDIF()
ENDIF()


#debug或release环境下特定选项
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    IF(WIN32)
        ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=1)
    ELSE()
        ADD_DEFINITIONS(-D_DEBUG)
    ENDIF()
ELSEIF("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    IF(WIN32)
        ADD_DEFINITIONS(-D_RELEASE)
    ELSE()
        ADD_DEFINITIONS(-D_RELEASE -DG_DISABLE_ASSERT)
        
        IF(CMAKE_COMPILER_IS_GNUCXX)
            SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing ${CMAKE_CXX_FLAGS}")
            SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
        ENDIF()
    ENDIF()
ELSE()
    MESSAGE(FATAL_ERROR "Must have a build type")
ENDIF()


####################################################################################################
##以下为可选项

#预定义大小端宏
IF(NOT NO_TESTENDIAN)
    IF(WIN32)
        ADD_DEFINITIONS(-D__LITTLE_ENDIAN__ -D__IS_LITTLE_ENDIAN__)
    ELSE()
        #CMake\share\cmake-3.7\Modules\TestBigEndian.cmake
        INCLUDE(TestBigEndian)
        TEST_BIG_ENDIAN(TEST_ENDIAN)
        IF(TEST_ENDIAN)
            ADD_DEFINITIONS(-D__BIG_ENDIAN__ -D__IS_BIG_ENDIAN__)
        ELSE()
            ADD_DEFINITIONS(-D__LITTLE_ENDIAN__ -D__IS_LITTLE_ENDIAN__)
        ENDIF()
    ENDIF()
ENDIF()

# 检查是否存在config目录,并将目录文件到生成lib库所在的目录下
SET(DEFAULT_CONFIG_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/config)
IF(EXISTS ${DEFAULT_CONFIG_PATH})
    FILE(INSTALL ${DEFAULT_CONFIG_PATH}/ DESTINATION ${LIBS_PATH} PATTERN ".svn" EXCLUDE)
    install_dir(${DEFAULT_CONFIG_PATH}/ "")
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "install_dir(${DEFAULT_CONFIG_PATH})")
ENDIF()

# 检查C++版本
IF(WIN32)
    IF(MSVC_VERSION EQUAL 1928)
        SET(CXX_VERSION -D__ENABLE_CXX20__
                        -D__ENABLE_CXX17__ 
                        -D__ENABLE_CXX14__ 
                        -D__ENABLE_CXX11__  
                        -D__ENABLE_CXX0X__)
        ADD_DEFINITIONS(${CXX_VERSION})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "MSVC_VERSION = ${MSVC_VERSION}, CXX_VERSION = ${CXX_VERSION}")
    ENDIF()
ELSE()
    #未指定std版本,cmake自动查询
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "Get MK_STD_VERSION = ${MK_STD_VERSION}")
    IF("${MK_STD_VERSION}" STREQUAL "")
        #C:\Program Files\CMake\share\cmake-3.7\Modules\CheckCXXCompilerFlag.cmake
        INCLUDE(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
        CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
        CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
        IF(COMPILER_SUPPORTS_CXX14)
            MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "enable c++14 ......")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
            ADD_DEFINITIONS(-D__ENABLE_CXX14__  -D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
        ELSEIF(COMPILER_SUPPORTS_CXX11)
            MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "enable c++11 ......")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
            ADD_DEFINITIONS(-D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
        ELSEIF(COMPILER_SUPPORTS_CXX0X)
            MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "enable c++0x ......")
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
            ADD_DEFINITIONS(-D__ENABLE_CXX0X__)
        ELSE()
            MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "enable c++98 ......")
        ENDIF()
    #指定std版本
    ELSE()
        #支持自定义g++下std版本, 默认关闭, 由cmake自动选择
        #如果在CmakeLists.txt中设置了如下参数,则cmake不再自动处理
        #SET(MK_STD_VERSION c++14)
        #SET(MK_STD_VERSION c++11)
        #SET(MK_STD_VERSION c++0x)
        #SET(MK_STD_VERSION c++98)
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "enable ${MK_STD_VERSION} ......")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${MK_STD_VERSION}")
        IF("${MK_STD_VERSION}" STREQUAL "c++14")
            ADD_DEFINITIONS(-D__ENABLE_CXX14__  -D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
        ELSEIF("${MK_STD_VERSION}" STREQUAL "c++11")
            ADD_DEFINITIONS(-D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
        ELSEIF("${MK_STD_VERSION}" STREQUAL "c++0x")
            ADD_DEFINITIONS(-D__ENABLE_CXX0X__)
        ELSE()
            ADD_DEFINITIONS(-D__ENABLE_CXX98__)
        ENDIF()
    ENDIF()
ENDIF()


#  添加自定义待编译目录
function(ADD_SOURCE_DIRS)
	if(${ARGC} LESS 1)
		return()
	else()
		foreach(elem ${ARGN})
			# cmakelists所在路径
			if("${elem}" STREQUAL ".")
			
			#绝对路径, APPEND will append elements to the list.
			elseif(IS_ABSOLUTE ${elem})
				list(APPEND elem_list ${elem})
			
			#相对路径,转换为绝对路径
			else() 
				list(APPEND elem_list ${CMAKE_CURRENT_SOURCE_DIR}/${elem})
			endif()
		endforeach()
		set(SOURCE_DIRS ${SOURCE_DIRS} ${elem_list} PARENT_SCOPE)
	endif()
endfunction(ADD_SOURCE_DIRS)
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(ADD_SOURCE_DIRS)")


#copy文件
function(install_file source dest)
    if(${ARGC} LESS 1)
        MESSAGE(FATAL_ERROR "install_file() ARGC error")
    endif()
    
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        MESSAGE(FATAL_ERROR "install_file() dest error")
    endif()
    
    FOREACH(subdir ${INSTALL_SUB_PATH})
        if(NOT "${subdir}" STREQUAL ".")
            set(target ${INSTALL_PATH}/${subdir})
        else()
            set(target ${INSTALL_PATH})
        endif()
        
        if(NOT "${dest}" STREQUAL "." AND NOT "${dest}" STREQUAL "")
            set(target ${target}/${dest})
        endif()
        
        INSTALL(FILES ${source} DESTINATION ${target}
                PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                            GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
    ENDFOREACH(subdir)
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(install_file source dest)")

function(install_files dest source)
	list(LENGTH  ARGV  argv_len)
	set(i 1)
	while(i LESS ${argv_len})
		list(GET ARGV ${i} argv_value)
		MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "argv${i}: ${argv_value}")
		install_file(${argv_value} ${dest})
		math(EXPR i "${i} + 1")
	endwhile() 
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(install_files dest source)")



# copy目录
function(install_dir source dest)
    if(${ARGC} LESS 1)
        MESSAGE(FATAL_ERROR "install_dir() ARGC error")
    endif()
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        MESSAGE(FATAL_ERROR "install_dir() dest error")
    endif()
    
    FOREACH(subdir ${INSTALL_SUB_PATH})
        if(NOT "${subdir}" STREQUAL ".")
            set(target ${INSTALL_PATH}/${subdir})
        else()
            set(target ${INSTALL_PATH})
        endif()
        
        if(NOT "${dest}" STREQUAL "." AND NOT "${dest}" STREQUAL "")
            set(target ${target}/${dest})
        endif()
        
        install(DIRECTORY ${source} DESTINATION ${target}
                    PATTERN "*.lib" EXCLUDE
                    PATTERN "*.def" EXCLUDE
                    PATTERN "*.a" EXCLUDE
                    PATTERN "*.po" EXCLUDE
                    PATTERN "*.sql" EXCLUDE
                    PATTERN "*.dll.manifest" EXCLUDE
                    PATTERN "CMakeLists.txt" EXCLUDE
                    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                                GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
                )
    ENDFOREACH(subdir)
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(install_dir source dest)")




#  copy指定类型的文件
function(install_target type target_name dest)
    if(${ARGC} LESS 2)
        MESSAGE(FATAL_ERROR "install_target() ARGC error")
    endif()
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        MESSAGE(FATAL_ERROR "install_target() dest error")
    endif()
    FOREACH(subdir ${INSTALL_SUB_PATH})
        if(NOT "${subdir}" STREQUAL ".")
            set(target ${INSTALL_PATH}/${subdir})
        else()
            set(target ${INSTALL_PATH})
        endif()
        if(NOT "${dest}" STREQUAL "." AND NOT "${dest}" STREQUAL "")
            set(target ${target}/${dest})
        endif()
        INSTALL(TARGETS ${target_name} ${type} DESTINATION ${target}
                PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                            GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
        IF(WIN32)
            INSTALL(FILES ${LIBS_PATH}/${dest}/${target_name}.pdb DESTINATION ${target}
                            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                        GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
            )
        ENDIF()
    ENDFOREACH(subdir)
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(install_target type target_name dest)")


# 拷贝依赖库到指定目录，但是不打入安装包
function(seek_deps_library_no_install path1 path2)
    if(${ARGC} LESS 3)
        MESSAGE(FATAL_ERROR "seek_deps_library_no_install(), argc error")
    else()
        # 第一次从${path1}查找
        find_library(FIRST_LIB  NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_LIB}" STREQUAL "FIRST_LIB-NOTFOUND")
                # 第二次从${path2}查找
                find_library(SECOND_LIB NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                if("${SECOND_LIB}" STREQUAL "SECOND_LIB-NOTFOUND")
                    MESSAGE(FATAL_ERROR "seek_deps_library_no_install(), Can not found lib ${ARGN}")
                else()
                    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path2}")
                    file(INSTALL ${path2}/ DESTINATION ${path1} 
                        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                         GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                endif()
                # 清除缓存
                unset(SECOND_LIB CACHE)
            else()
                MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
            endif()
        # 清除缓存
        unset(FIRST_LIB CACHE)
    endif()
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_library_no_install path1 path2)")

function(seek_deps_library path1 path2)
    seek_deps_library_no_install (${path1} ${path2} ${ARGN})
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_library path1 path2)")


## 拷贝文件到指定目录，但是不打入安装包
function(seek_deps_file_no_install path1 path2)
    if(${ARGC} LESS 3)
        MESSAGE(FATAL_ERROR "seek_deps_file_no_install(), argc error")
    else()
        # 第一次从${path1}查找
        find_file(FIRST_FILE NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_FILE}" STREQUAL "FIRST_FILE-NOTFOUND")
                # 第二次从${path2}查找
                find_file(SECOND_FILE NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                    if("${SECOND_FILE}" STREQUAL "SECOND_FILE-NOTFOUND")
                        MESSAGE(FATAL_ERROR "seek_deps_file_no_install() Can not found file ${ARGN}")
                    else()
                        file(INSTALL ${path2}/ DESTINATION ${path1} 
                            FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                             GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                    endif()
                # 清除缓存
                unset(SECOND_FILE CACHE)
            endif()
			    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
        # 清除缓存
        unset(FIRST_FILE CACHE)
    endif()
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_file_no_install path1 path2)")

function(seek_deps_file path1 path2)
    seek_deps_file_no_install(${path1} ${path2} ${ARGN})
    if(ENABLE_PACKAGE)
        install_dir (${path2}/ .)
    endif()
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_file path1 path2)")


## copy资源文件
macro(add_res_files_target sour dest CLEAN_FILES dest_name)
    IF(WIN32)
        SET(MSGFMT ${MK_MAKE}/script_win/bin/msgfmt.exe)
    ELSE()
        SET(MSGFMT msgfmt)
    ENDIF()

    SET(LANG_DATA_PATH "locale")
    SET(LANG_TYPE "en_US" "zh_CN" "zh_TW_CN")
    SET(LANG_PATH_EXTEND "LC_MESSAGES")
    #SET(EXISTS_LANG_PATH_EXTEND FALSE)
    FOREACH(THE_LANG_TYPE ${LANG_TYPE})
        # c++
        SET(IN_LANG_REAL_PATH ${sour}/${THE_LANG_TYPE}/${LANG_PATH_EXTEND})
        SET(OUT_LANG_REAL_PATH ${dest}/${LANG_DATA_PATH}/${THE_LANG_TYPE}/${LANG_PATH_EXTEND})
        SET(INSTALL_LANG_PATH ${LANG_DATA_PATH}/${THE_LANG_TYPE}/${LANG_PATH_EXTEND})
        if(NOT EXISTS ${IN_LANG_REAL_PATH})
            SET(IN_LANG_REAL_PATH ${sour}/${THE_LANG_TYPE})
            SET(OUT_LANG_REAL_PATH ${dest}/${LANG_DATA_PATH}/${THE_LANG_TYPE})
            SET(INSTALL_LANG_PATH ${LANG_DATA_PATH}/${THE_LANG_TYPE})
        endif()
        # get po file list
        FILE(GLOB po_file_list "${IN_LANG_REAL_PATH}/*.po")
        FOREACH(the_po_file ${po_file_list})
            if("${dest_name}" STREQUAL "-")
                GET_FILENAME_COMPONENT(the_po_file_name ${the_po_file} NAME_WE)
            else()
                set(the_po_file_name ${dest_name})
            endif()
            if(EXISTS ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo)
                file(REMOVE_RECURSE ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo)
            endif()
            if(NOT EXISTS ${OUT_LANG_REAL_PATH})
                FILE(MAKE_DIRECTORY ${OUT_LANG_REAL_PATH})
            endif()
            ADD_CUSTOM_COMMAND(OUTPUT ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo
                               COMMAND ${MSGFMT} ${the_po_file} -o ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo
                               WORKING_DIRECTORY ${IN_LANG_REAL_PATH})
            LIST(APPEND CLEAN_FILES ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo)
            LIST(APPEND RES_FILES ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo)
            install_files(${INSTALL_LANG_PATH} ${OUT_LANG_REAL_PATH}/${the_po_file_name}.mo)
        ENDFOREACH()
    ENDFOREACH()
endmacro()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "macro(add_res_files_target sour dest CLEAN_FILES dest_name) ")






