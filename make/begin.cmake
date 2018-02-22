MESSAGE(STATUS "\n**include begin.cmake-------------------------------------------------------------")

# ����������תΪcmake��ʱ����
SET(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE} CACHE String "")
SET(CMAKE_BUILD_VERSION $ENV{CMAKE_BUILD_VERSION} CACHE String "")
SET(CMAKE_PLATFORM_NAME "$ENV{CMAKE_PLATFORM_NAME}" CACHE type String)
SET(CMAKE_PLATFORM_VERSION $ENV{CMAKE_PLATFORM_VERSION} CACHE String "")

SET(MONK_PATH $ENV{MONK_PATH} CACHE String "")
SET(MONK_PLATFORM $ENV{MONK_PLATFORM} CACHE String "")
SET(MONK_TARGET $ENV{MONK_TARGET} CACHE String "")
SET(MONK_MAKE $ENV{MONK_MAKE} CACHE String "")
SET(MONK_DEPS $ENV{MONK_DEPS} CACHE String "")
SET(MONK_SRC $ENV{MONK_SRC} CACHE String "")

# ���� make package target ��Ĭ�ϴ��·��
SET(INSTALL_PATH .)

#���� LIBS_PATH
SET(LIBS_PATH ${MONK_TARGET}/${CMAKE_BUILD_TYPE})

####################################################################################################
MESSAGE(STATUS "\n**set cmake--------------------------------------------------------------------------")
SET(CMAKE_MODULE_PATH ${MONK_MAKE})

#����if��else�Ŀ��ƿ���ѡ��
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

# ����Cmake�������·��
SET(CMAKE_USE_RELATIVE_PATHS TRUE)

#����ǰԴ�ļ�Ŀ¼�Զ����ӵ�ͷ�ļ�����·����
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
MESSAGE(STATUS "SET SOURCE_DIRS = ${SOURCE_DIRS}")

####################################################################################################
MESSAGE(STATUS "\n**define---------------------------------------------------------------------------")

#Ԥ�����
IF(WIN32)
	ADD_DEFINITIONS(/D _UNICODE /D UNICODE /D WIN32 /D __WINDOWS__ /D _CRT_SECURE_NO_WARNINGS /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE)
ELSE()
    ADD_DEFINITIONS(-D__LINUX__ -D_GNU_SOURCE)
    IF("${CMAKE_BUILD_VERSION}" STREQUAL "i386")
		#linux�����²����ش��ļ� -D_FILE_OFFSET_BITS=64, ����fopen��open�������ļ���С���ܳ���2G��
		ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE=1)
    ENDIF()
ENDIF()

#����ѡ��
IF(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /vmm /vmg /MP /wo4067 /wo4244 /wo4267 /wo4181 /wd4099")
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
	#linux����������
	IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
		SET(CMAKE_SHARED_LINKER_FLAGS "-rdynamic -Wl,-E ${CMAKE_SHARED_LINKER_FLAGS}")
		MESSAGE(STATUS "SET CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
	ENDIF()
ENDIF()

# ���C++�汾
IF(WIN32)
    SET(MSVC_2015 "_MSC_VER >= 1900")
    IF(MSVC_2015)
        ADD_DEFINITIONS(-D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
		MESSAGE(STATUS "c++11: -D__ENABLE_CXX11__ -D__ENABLE_CXX0X__")
    ENDIF()
ELSE()
	#C:\Program Files\CMake\share\cmake-3.7\Modules\CheckCXXCompilerFlag.cmake
    INCLUDE(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    IF(COMPILER_SUPPORTS_CXX14)
        MESSAGE(STATUS "enable c++14 ......")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
        ADD_DEFINITIONS(-D__ENABLE_CXX14__  -D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
    ELSEIF(COMPILER_SUPPORTS_CXX11)
        MESSAGE(STATUS "enable c++11 ......")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        ADD_DEFINITIONS(-D__ENABLE_CXX11__  -D__ENABLE_CXX0X__)
    ELSEIF(COMPILER_SUPPORTS_CXX0X)
        MESSAGE(STATUS "enable c++0x ......")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        ADD_DEFINITIONS(-D__ENABLE_CXX0X__)
    ELSE()
        MESSAGE(STATUS "enable c++98 ......")
    ENDIF()
ENDIF()

#debug��release�������ض�ѡ��
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    IF(WIN32)
        ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)
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
	MESSAGE(STATUS "install_dir(${DEFAULT_CONFIG_PATH})")
ENDIF()


INCLUDE($ENV{MONK_MAKE}/define.cmake)
####################################################################################################
MESSAGE(STATUS "\n**begin.cmake end----------------------------------------------------------------")




