####################################################################################################
MESSAGE(STATUS "\n**funs_macros----------------------------------------------------------------------")

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
MESSAGE(STATUS "function(ADD_SOURCE_DIRS)")


#copy文件
function(install_file source dest)
    if(${ARGC} LESS 1)
        message(FATAL_ERROR "install_file() ARGC error")
    endif()
    
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        message(FATAL_ERROR "install_file() dest error")
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
MESSAGE(STATUS "function(install_file source dest)")

function(install_files dest source)
	list(LENGTH  ARGV  argv_len)
	set(i 1)
	while(i LESS ${argv_len})
		list(GET ARGV ${i} argv_value)
		message(STATUS "argv${i}: ${argv_value}")
		install_file(${argv_value} ${dest})
		math(EXPR i "${i} + 1")
	endwhile() 
endfunction()
MESSAGE(STATUS "function(install_files dest source)")



# copy目录
function(install_dir source dest)
    if(${ARGC} LESS 1)
        message(FATAL_ERROR "install_dir() ARGC error")
    endif()
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        message(FATAL_ERROR "install_dir() dest error")
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
MESSAGE(STATUS "function(install_dir source dest)")




#  copy指定类型的文件
function(install_target type target_name dest)
    if(${ARGC} LESS 2)
        message(FATAL_ERROR "install_target() ARGC error")
    endif()
    if(DEFINED dest AND IS_ABSOLUTE ${dest})
        message(FATAL_ERROR "install_target() dest error")
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
MESSAGE(STATUS "function(install_target type target_name dest)")




# 拷贝依赖库到指定目录，但是不打入安装包
function(seek_deps_library_no_install path1 path2)
    if(${ARGC} LESS 3)
        message(FATAL_ERROR "seek_deps_library_no_install(), argc error")
    else()
        # 第一次从${path1}查找
        find_library(FIRST_LIB  NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_LIB}" STREQUAL "FIRST_LIB-NOTFOUND")
                # 第二次从${path2}查找
                find_library(SECOND_LIB NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                if("${SECOND_LIB}" STREQUAL "SECOND_LIB-NOTFOUND")
                    message(FATAL_ERROR "seek_deps_library_no_install(), Can not found lib ${ARGN}")
                else()
                    message(STATUS "seek_deps_library_no_install(), found lib ${ARGN} in ${path2}")
                    file(INSTALL ${path2}/ DESTINATION ${path1} 
                        FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                         GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                endif()
                # 清除缓存
                unset(SECOND_LIB CACHE)
            else()
                message(STATUS "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
            endif()
        # 清除缓存
        unset(FIRST_LIB CACHE)
    endif()
endfunction()
MESSAGE(STATUS "function(seek_deps_library_no_install path1 path2)")

function(seek_deps_library path1 path2)
    seek_deps_library_no_install (${path1} ${path2} ${ARGN})
endfunction()
MESSAGE(STATUS "function(seek_deps_library path1 path2)")


## 拷贝文件到指定目录，但是不打入安装包
function(seek_deps_file_no_install path1 path2)
    if(${ARGC} LESS 3)
        message(FATAL_ERROR "seek_deps_file_no_install(), argc error")
    else()
        # 第一次从${path1}查找
        find_file(FIRST_FILE NAMES ${ARGN} PATHS ${path1} NO_DEFAULT_PATH)
            if("${FIRST_FILE}" STREQUAL "FIRST_FILE-NOTFOUND")
                # 第二次从${path2}查找
                find_file(SECOND_FILE NAMES ${ARGN} PATHS ${path2} NO_DEFAULT_PATH)
                    if("${SECOND_FILE}" STREQUAL "SECOND_FILE-NOTFOUND")
                        message(FATAL_ERROR "seek_deps_file_no_install() Can not found file ${ARGN}")
                    else()
                        file(INSTALL ${path2}/ DESTINATION ${path1} 
                            FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
                                             GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
                    endif()
                # 清除缓存
                unset(SECOND_FILE CACHE)
            endif()
			    message(STATUS "seek_deps_library_no_install(), found lib ${ARGN} in ${path1} values [${FIRST_LIB}]")
        # 清除缓存
        unset(FIRST_FILE CACHE)
    endif()
endfunction()
MESSAGE(STATUS "function(seek_deps_file_no_install path1 path2)")

function(seek_deps_file path1 path2)
    seek_deps_file_no_install(${path1} ${path2} ${ARGN})
    if(ENABLE_PACKAGE)
        install_dir (${path2}/ .)
    endif()
endfunction()
MESSAGE(STATUS "function(seek_deps_file path1 path2)")


## copy资源文件
macro(add_res_files_target sour dest CLEAN_FILES dest_name)
    IF(WIN32)
        SET(MSGFMT ${MONK_MAKE}/script_win/bin/msgfmt.exe)
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
MESSAGE(STATUS "macro(add_res_files_target sour dest CLEAN_FILES dest_name) ")

