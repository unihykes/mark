
FUNCTION(COMPILE_PROTO  proto_files  proto_in_dir  proto_out_dir  deps_proto_path  srcs  hdrs)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]:  "COMPILE_PROTO::${proto_files} ${proto_in_dir} ${proto_out_dir} ${deps_proto_path} ${srcs} ${hdrs}")
    
    #创建gen_proto目录
    FILE(MAKE_DIRECTORY ${proto_out_dir})
    
    SET(proto_include ${MK_DEPS_PKGS}/protobuf/include)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "proto_include = ${proto_files}")
    
    IF(WIN32)
        SET(protoc_cmd ${MK_DEPS_PKGS}/protobuf/bin/protoc.exe)
    ELSE()
        SET(protoc_cmd ${MK_DEPS_PKGS}/protobuf/bin/protoc)
    ENDIF()
    IF(NOT EXISTS ${protoc_cmd})
         MESSAGE(FATAL_ERROR "Not found  ${protoc_cmd}")
    ELSE()
        IF(UNIX)
            SET(pre_proto_cmd test -x ${protoc_cmd} || chmod +x ${protoc_cmd})
        ENDIF()
    ENDIF()
    
    #重置out类型变量
    SET(${srcs})
    SET(${hdrs})
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "srcs = ${srcs}, ${srcs} = ${${srcs}}")
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "hdrs = ${hdrs}, ${hdrs} = ${${hdrs}}")
    
    #若 proto_in_dir 不是绝对路径,则将其转换为绝对路径
    IF(NOT IS_ABSOLUTE ${proto_in_dir})
        get_filename_component(_abs_in_dir ${proto_in_dir} ABSOLUTE)
        set(proto_in_dir ${_abs_in_dir})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "proto_in_dir = ${proto_in_dir}")
    ENDIF()
    
    FOREACH(pb_file ${proto_files})
        #获取 xxx.proto 文件的绝对路径
        get_filename_component(_abs_file ${pb_file} ABSOLUTE)
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "_abs_file = ${_abs_file}")
        
        #获取 xxx.proto 文件所在目录的绝对路径
        get_filename_component(_abs_dir ${_abs_file} DIRECTORY)
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "_abs_dir = ${_abs_dir}")
        
        #获取 xxx.proto 文件的名称(不带后缀)
        get_filename_component(_basename ${pb_file} NAME_WE)
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "_basename = ${_basename}")
        
        #推断出指定文件相对于特定目录的路径
        file(RELATIVE_PATH _rel_dir ${proto_in_dir} ${_abs_dir})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "_rel_dir = ${_rel_dir}")
        
        #设置生成的c++文件的名称及路径,并将其加入到列表中
        set(FIL_WE ${_basename}.pb)
        IF("null${_rel_dir}" STREQUAL "null")
            set(gen_proto_file_path ${proto_out_dir}/${FIL_WE})
        ELSE()
            set(gen_proto_file_path ${proto_out_dir}/${_rel_dir}/${FIL_WE})
        ENDIF()
        
        list(APPEND ${hdrs} "${gen_proto_file_path}.h")
        list(APPEND ${srcs} "${gen_proto_file_path}.cc")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "srcs = ${srcs}, ${srcs} = ${${srcs}}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "hdrs = ${hdrs}, ${hdrs} = ${${hdrs}}")
        
        LIST(APPEND ${clean_proto_files} "${gen_proto_file_path}.h")
        LIST(APPEND ${clean_proto_files} "${gen_proto_file_path}.cc")
        
        # 清除旧文件
        FILE(REMOVE ${gen_proto_file_path}.h)
        FILE(REMOVE ${gen_proto_file_path}.cc)
        
        #将proto文件编译为c++文件-方式1
        execute_process(COMMAND ${protoc_cmd} --cpp_out=${proto_out_dir}  --proto_path=${proto_in_dir}   ${_abs_file})
        
        #将proto文件编译为c++文件-方式2
        #todo:方式2哪里出问题了,c++文件生成不出来
        #add_custom_command(OUTPUT ${gen_proto_file_path}.h ${gen_proto_file_path}.cc
        #    #COMMAND ${CMAKE_COMMAND} -E env ${protoc_cmd}
        #    ARGS --cpp_out=${proto_out_dir}  --proto_path=${proto_in_dir} ${_abs_file}
        #    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        #    DEPENDS ${_abs_file}
        #)
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "pre_proto_cmd = ${pre_proto_cmd}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "CMAKE_COMMAND = ${CMAKE_COMMAND}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "proto_out_dir = ${proto_out_dir}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "proto_in_dir = ${proto_in_dir}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "proto_include = ${proto_include}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "_abs_file = ${_abs_file}")
    ENDFOREACH()
    
    #将 gen_prpto 目录添加到头文件依赖路径
    INCLUDE_DIRECTORIES(${proto_out_dir})
    
    # 
    set_source_files_properties(${${srcs}} ${${hdrs}} PROPERTIES GENERATED TRUE)
    
    SET(${srcs} ${${srcs}} PARENT_SCOPE)
    SET(${hdrs} ${${hdrs}} PARENT_SCOPE)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "srcs = ${srcs}, ${srcs} = ${${srcs}}")
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "hdrs = ${hdrs}, ${hdrs} = ${${hdrs}}")
ENDFUNCTION()

MACRO(ADD_BUILD_PROTO_FILES_WITH_GEN_DIR  proto_dir  gen_dir_name)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "ARGN = ${ARGN}")
    
    FOREACH(proto_file ${ARGN})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "COMPILE_PROTO::${proto_file} ${proto_dir} ${PROJECT_BINARY_DIR}/${gen_dir_name} ${proto_dir} CUR_PROTO3_GEN_CPP_SRCS CUR_PROTO3_GEN_CPP_HDRS")
        COMPILE_PROTO(${proto_file} ${proto_dir} ${PROJECT_BINARY_DIR}/${gen_dir_name} ${proto_dir} CUR_PROTO3_GEN_CPP_SRCS CUR_PROTO3_GEN_CPP_HDRS)
        
        SET(PROTO3_GEN_CPP_SRCS ${PROTO3_GEN_CPP_SRCS} ${CUR_PROTO3_GEN_CPP_SRCS})
        SET(PROTO3_GEN_CPP_HDRS ${PROTO3_GEN_CPP_HDRS} ${CUR_PROTO3_GEN_CPP_HDRS})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "PROTO3_GEN_CPP_SRCS = ${PROTO3_GEN_CPP_SRCS}")
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "PROTO3_GEN_CPP_HDRS = ${PROTO3_GEN_CPP_HDRS}")
        
        #编译生成的.pd.cc文件
        SET(INCLUDE_SOURCE_FILES    ${INCLUDE_SOURCE_FILES} ${PROTO3_GEN_CPP_SRCS})
        MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "INCLUDE_SOURCE_FILES = ${INCLUDE_SOURCE_FILES}")
        
    ENDFOREACH()
ENDMACRO()

MACRO(ADD_BUILD_PROTO_FILES proto_dir)
    MESSAGE([${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE}]: "ADD_BUILD_PROTO_FILES_WITH_GEN_DIR::${proto_dir} gen_proto  ${ARGN}")
    ADD_BUILD_PROTO_FILES_WITH_GEN_DIR(${proto_dir} gen_proto ${ARGN})
ENDMACRO()

