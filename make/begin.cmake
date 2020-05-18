MESSAGE(STATUS "\n**include begin.cmake-------------------------------------------------------------")

# 将环境变量转为cmake临时变量
SET(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE} CACHE String "")
SET(CMAKE_BUILD_VERSION $ENV{CMAKE_BUILD_VERSION} CACHE String "")
SET(CMAKE_PLATFORM_NAME "$ENV{CMAKE_PLATFORM_NAME}" CACHE type String)
SET(CMAKE_PLATFORM_VERSION $ENV{CMAKE_PLATFORM_VERSION} CACHE String "")

SET(MK_PATH $ENV{MK_PATH} CACHE String "")
SET(MK_PLATFORM $ENV{MK_PLATFORM} CACHE String "")
SET(MK_TARGET $ENV{MK_TARGET} CACHE String "")
SET(MK_MAKE $ENV{MK_PATH}/make CACHE String "")
SET(MK_SRC $ENV{MK_PATH}/src CACHE String "")

# 设置 make package target 的默认存放路径
SET(INSTALL_PATH .)

#设置 LIBS_PATH
SET(LIBS_PATH ${MK_TARGET}/${CMAKE_BUILD_TYPE})

####################################################################################################
MESSAGE(STATUS "\n**set cmake--------------------------------------------------------------------------")
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
MESSAGE(STATUS "SET SOURCE_DIRS = ${SOURCE_DIRS}")

####################################################################################################
MESSAGE(STATUS "\n**define---------------------------------------------------------------------------")

#预定义宏
IF(WIN32)
	ADD_DEFINITIONS(/D _UNICODE /D UNICODE /D WIN32 /D __WINDOWS__ 
					/D _CRT_SECURE_NO_WARNINGS 
					/D _CRT_SECURE_NO_DEPRECATE 
					/D _CRT_NONSTDC_NO_DEPRECATE)
ELSE()
    ADD_DEFINITIONS(-D__LINUX__ -D_GNU_SOURCE)
    IF("${CMAKE_BUILD_VERSION}" STREQUAL "i386")
		#linux环境下操作特大文件 -D_FILE_OFFSET_BITS=64, 否则fopen和open操作的文件大小不能超过2G。
		ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE=1)
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
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /vmm /vmg /MP /wo4067 /wo4244 /wo4267 /wo4181 /wd4099 /wd4819 /wd4251")
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
		MESSAGE(STATUS "SET CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
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
		#linux
        IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
            SET(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
            SET(CMAKE_C_FLAGS "-g ${CMAKE_C_FLAGS}")
            SET(NEED_DEBUGINFO TRUE)
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
	MESSAGE(STATUS "install_dir(${DEFAULT_CONFIG_PATH})")
ENDIF()


INCLUDE($ENV{MK_MAKE}/define.cmake)
####################################################################################################
MESSAGE(STATUS "\n**begin.cmake end----------------------------------------------------------------")





