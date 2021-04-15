/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)
   
Time:2017-6

info:

***************************************************************************************************/

#ifndef __mkheaders
#define __mkheaders

//c头文件
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdint>

// std头文件
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <bitset>
#include <array>
using namespace std;

//平台特有头文件
#ifdef __WINDOWS__
	//Visual C++ WIN32_LEAN_AND_MEAN, 这个定义通过排除一些不太常用的 API,减小了 Win32 头文件的大小 
	#define WIN32_LEAN_AND_MEAN
		#ifndef _WINDOWS_
			#include <windows.h>
		#endif
		
		#if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_)
			#include <winsock2.h>
		#endif
	#undef WIN32_LEAN_AND_MEAN
//linux常用头文件
#else
	#include <unistd.h>
	#include <errno.h>
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// define
//

//定义宏: __64BIT__
#ifdef _MSC_VER
	#ifdef _WIN64
		#define __64BIT__
	#else
		#undef __64BIT__
	#endif
#else
	#if(defined(__GNUC__)                       \
        && ( defined(__x86_64__)                \
            || defined (__ia64__)               \
            || defined (__PPC64__)              \
            || defined (__powerpc64__)          \
            || defined (__mips64)               \
            || defined(__arch64__)              \
            || defined(__aarch64__)             \
            ) )
		#if !defined(__64BIT__)
			#define __64BIT__
		#endif
	#else
		#if defined(__64BIT__)
			#undef __64BIT__
		#endif
	#endif
#endif


//定义宏: _T
#ifdef __WINDOWS__
	//使用_T("")宏，定义于tchar.h下。
	#ifndef _INC_TCHAR
		#include <tchar.h>
	#endif
#else
	//linux下定义_T()宏，为了与windows保持一致
	#if !defined(_T)
		#define _T(str)		str
	#endif
#endif

//定义跨平台字符类型
#ifdef __WINDOWS__
	typedef wchar_t			mkChar;
#else
	typedef char			mkChar;
#endif

//定义int64
typedef int64_t				int64;
typedef uint64_t			uint64;


//定义debug
#ifdef _DEBUG
	#define __DEBUG__
#endif

#ifdef __DEBUG__
	#include <cassert>
	#define MK_ASSERT(f)	assert(f)
#else 
	#define MK_ASSERT(f)	((void)(f))
#endif

//定义动态库导出符号宏
#ifdef __WINDOWS__
        #define MK_VISIBILITY_HIDDEN
        #define DLL_EXPORT              __declspec(dllexport)
        #define DLL_IMPORT              __declspec(dllimport)
#else 
    #if __GNUC__ >= 4 && !defined(__AIX__)
        #define MK_VISIBILITY_HIDDEN    __attribute__ ((visibility ("hidden")))
        #define DLL_EXPORT              __attribute__ ((visibility ("default")))
        #define DLL_IMPORT              __attribute__ ((visibility ("default")))
    #else
        #define MK_VISIBILITY_HIDDEN
        #define DLL_EXPORT
        #define DLL_IMPORT
    #endif
#endif

#ifdef __MAKE_MK_DLL__
	//导出c动态库
	#define MK_CDLL_EXPORT		extern "C" DLL_EXPORT
	//导出c++动态库
	#define MK_DLL_EXPORT		DLL_EXPORT
#else
	//导入c动态库
	#define MK_CDLL_EXPORT		extern "C" DLL_IMPORT
	//导入c++动态库
	#define MK_DLL_EXPORT		DLL_IMPORT
#endif

//定义func
#ifdef __WINDOWS__
#define __FUNC_NAME__			_T(__FUNCTION__)
#else
#define __FUNC_NAME__			__func__
#endif


////static对象初始化理论伤比 std::call_once 更高效
#define MK_CALL_ONCE_BEGIN                  \
    struct mkCallOnce                       \
    {                                       \
        mkCallOnce()                        \
        {

#define MK_CALL_ONCE_END                    \
        }                                   \
    };                                      \
    static const mkCallOnce __mk_call_once__;
    
    
    
    
    

#endif // __mkheaders
