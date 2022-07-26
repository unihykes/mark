MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "include begin.cmake")

# ����������תΪcmake��ʱ����
SET(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE} CACHE STRING "")
SET(MK_SYSTEM_TYPE $ENV{MK_SYSTEM_TYPE} CACHE STRING "")
SET(MK_PATH $ENV{MK_PATH} CACHE STRING "")
SET(MK_PACKAGE $ENV{MK_PACKAGE} CACHE STRING "")
SET(MK_DEPS_PKGS $ENV{MK_DEPS_PKGS} CACHE STRING "")


# ���� make package target ��Ĭ�ϴ��·��
SET(INSTALL_PATH .)

#���� LIBS_PATH
SET(LIBS_PATH ${MK_PACKAGE}/target/${CMAKE_BUILD_TYPE})

#����cmake�� include() or find_package() �Ĳ���·��
SET(CMAKE_MODULE_PATH ${MK_PATH}/make)

#����if��else�Ŀ��ƿ���ѡ��
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

# ����Cmake�������·��
SET(CMAKE_USE_RELATIVE_PATHS TRUE)

#����ǰԴ�ļ�Ŀ¼�Զ���ӵ�ͷ�ļ�����·����
SET(CMAKE_INCLUDE_CURRENT_DIR ON) 

#���á����������ϸ��Ϣ = ON"
SET(CMAKE_VERBOSE_MAKEFILE ON)

# ���� cmake rpath ѡ��
SET(CMAKE_INSTALL_RPATH .;..)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# ����cmake install����
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# ����Ĭ�ϵĴ����·��
SET(INSTALL_SUB_PATH ".")

# Ĭ��Դ�ļ�Ŀ¼����ǰĿ¼
SET(SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "SET SOURCE_DIRS = ${SOURCE_DIRS}")


#Ԥ�����
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
    IF("${MK_SYSTEM_TYPE}" STREQUAL "x86")
        #linux�����²����ش��ļ� -D_FILE_OFFSET_BITS=64, ����fopen��open�������ļ���С���ܳ���2G��
        ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 
                        -D_LARGEFILE64_SOURCE=1)
    ENDIF()
ENDIF()

#����ѡ��
#pragma warnind( disable: 4251 )
IF(WIN32)
    #����������:https://docs.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2008/8x5x43k7(v%3dvs.90)
    #����������:4181:Ӧ�õ��������͵��޶������ѽ�����Խ��޶������� const��Ӧ������ typedef ������������͡�
    #����������:4099:������Ϊ�ṹ�Ķ�����Ϊ�࣬������Ϊ��Ķ�����Ϊ�ṹ��������ʹ���ڶ����и��������͡�
    #����������:4819:���ļ����������ڵ�ǰ����ҳ(936)�б�ʾ���ַ��� �뽫���ļ�����Ϊ Unicode ��ʽ�Է�ֹ���ݶ�ʧ
    #����������:4251: class��std::basic_string<char,std::char_traits<char>,std::allocator<char>>����Ҫ�� dll �ӿ��� class��xxx���Ŀͻ���ʹ��
    #windows����ѡ��:https://msdn.microsoft.com/en-us/library/thxezb7y.aspx
    #/wd n : Disables the specified compiler warning where nis the compiler warning number.
    #/wo n : Reports the error only once where n is a compiler warning.
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /vmm /vmg /MP /wo4067 /wo4244 /wo4267 /wo4181 /wd4099 /wd4819 /wd4251 /wd4275")
    STRING(REPLACE "/EHsc" "/EHa /GS" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
ELSE()
    IF("${MK_SYSTEM_TYPE}" STREQUAL "x86")
        SET(CMAKE_C_FLAGS "-m32 -pipe -pthread -Wall ${CMAKE_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "-m32 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
    ELSE()
        SET(CMAKE_C_FLAGS "-m64 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
        SET(CMAKE_CXX_FLAGS "-m64 -pipe -pthread -Wall ${CMAKE_CXX_FLAGS}")
    ENDIF()
    #linux����������
    IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET(CMAKE_SHARED_LINKER_FLAGS "-rdynamic -Wl,-E ${CMAKE_SHARED_LINKER_FLAGS}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "SET CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
    ENDIF()
ENDIF()


#debug��release�������ض�ѡ��
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
##����Ϊ��ѡ��

#Ԥ�����С�˺�
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

# ����Ƿ����configĿ¼,����Ŀ¼�ļ�������lib�����ڵ�Ŀ¼��
SET(DEFAULT_CONFIG_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/config)
IF(EXISTS ${DEFAULT_CONFIG_PATH})
    FILE(INSTALL ${DEFAULT_CONFIG_PATH}/ DESTINATION ${LIBS_PATH} PATTERN ".svn" EXCLUDE)
    install_dir(${DEFAULT_CONFIG_PATH}/ "")
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "install_dir(${DEFAULT_CONFIG_PATH})")
ENDIF()

# ���C++�汾
IF(WIN32)
    IF(MSVC_VERSION EQUAL 1929)
        SET(CXX_VERSION -D__ENABLE_CXX20__
                        -D__ENABLE_CXX17__ 
                        -D__ENABLE_CXX14__ 
                        -D__ENABLE_CXX11__  
                        -D__ENABLE_CXX0X__)
        ADD_DEFINITIONS(${CXX_VERSION})
        #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
        
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "MSVC_VERSION = ${MSVC_VERSION}, CXX_VERSION = ${CXX_VERSION}")
    ENDIF()
ELSE()
    #δָ��std�汾,cmake�Զ���ѯ
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
    #ָ��std�汾
    ELSE()
        #֧���Զ���g++��std�汾, Ĭ�Ϲر�, ��cmake�Զ�ѡ��
        #�����CmakeLists.txt�����������²���,��cmake�����Զ�����
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


#  ����Զ��������Ŀ¼
function(ADD_SOURCE_DIRS)
	if(${ARGC} LESS 1)
		return()
	else()
		foreach(elem ${ARGN})
			# cmakelists����·��
			if("${elem}" STREQUAL ".")
			
			#����·��, APPEND will append elements to the list.
			elseif(IS_ABSOLUTE ${elem})
				list(APPEND elem_list ${elem})
			
			#���·��,ת��Ϊ����·��
			else() 
				list(APPEND elem_list ${CMAKE_CURRENT_SOURCE_DIR}/${elem})
			endif()
		endforeach()
		set(SOURCE_DIRS ${SOURCE_DIRS} ${elem_list} PARENT_SCOPE)
	endif()
endfunction(ADD_SOURCE_DIRS)
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(ADD_SOURCE_DIRS)")


#copy�ļ�
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



# copyĿ¼
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




#  copyָ�����͵��ļ�
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


# ���������⵽ָ��Ŀ¼�����ǲ����밲װ��
function(seek_deps_library_no_install path1 path2)
    if(${ARGC} LESS 3)
        MESSAGE(FATAL_ERROR "seek_deps_library_no_install(), argc error")
    else()
        # ��һ�δ�${path1}����
        find_library(FIRST_LIB  NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_LIB}" STREQUAL "FIRST_LIB-NOTFOUND")
                # �ڶ��δ�${path2}����
                find_library(SECOND_LIB NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                if("${SECOND_LIB}" STREQUAL "SECOND_LIB-NOTFOUND")
                    MESSAGE(FATAL_ERROR "seek_deps_library_no_install(), Can not found lib ${ARGN}")
                else()
                    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path2}")
                    file(INSTALL ${path2}/ DESTINATION ${path1} 
                        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                         GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                endif()
                # �������
                unset(SECOND_LIB CACHE)
            else()
                MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
            endif()
        # �������
        unset(FIRST_LIB CACHE)
    endif()
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_library_no_install path1 path2)")

function(seek_deps_library path1 path2)
    seek_deps_library_no_install (${path1} ${path2} ${ARGN})
endfunction()
MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "function(seek_deps_library path1 path2)")


## �����ļ���ָ��Ŀ¼�����ǲ����밲װ��
function(seek_deps_file_no_install path1 path2)
    if(${ARGC} LESS 3)
        MESSAGE(FATAL_ERROR "seek_deps_file_no_install(), argc error")
    else()
        # ��һ�δ�${path1}����
        find_file(FIRST_FILE NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_FILE}" STREQUAL "FIRST_FILE-NOTFOUND")
                # �ڶ��δ�${path2}����
                find_file(SECOND_FILE NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                    if("${SECOND_FILE}" STREQUAL "SECOND_FILE-NOTFOUND")
                        MESSAGE(FATAL_ERROR "seek_deps_file_no_install() Can not found file ${ARGN}")
                    else()
                        file(INSTALL ${path2}/ DESTINATION ${path1} 
                            FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                             GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                    endif()
                # �������
                unset(SECOND_FILE CACHE)
            endif()
			    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
        # �������
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


## copy��Դ�ļ�
macro(add_res_files_target sour dest CLEAN_FILES dest_name)
    IF(WIN32)
        SET(MSGFMT ${MK_PATH}/make/script_win/bin/msgfmt.exe)
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






