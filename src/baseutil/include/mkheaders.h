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

//windows常用头文件
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
	
	//使用_T("")宏，定义于tchar.h下。
	#ifndef _INC_TCHAR
		#include <tchar.h>
	#endif
	
//linux常用头文件
#else
	//linux下定义_T()宏，为了与windows保持一致
	#if !defined(_T)
		#define _T(str)		str
	#endif
	#include <unistd.h>
	#include <errno.h>
#endif



////////////////////////////////////////////////////////////////////////////////////////////////////
// define
//

//定义64位宏
#ifdef _MSC_VER
	#ifdef _WIN64
		#define __64BIT__
	#else
		#undef __64BIT__
	#endif
#else
	#if(defined(__GNUC__) && (defined(__x86_64__)													\
							|| defined (__ia64__) || defined (__PPC64__) || defined (__powerpc64__) \
							|| defined (__mips64) || defined(__arch64__) || defined(__aarch64__)))
		#if !defined(__64BIT__)
			#define __64BIT__
		#endif
	#else
		#if defined(__64BIT__)
			#undef __64BIT__
		#endif
	#endif
#endif



//定义unicode字符串
#ifdef __WINDOWS__
	typedef wchar_t			auto_char;
#else
	typedef char			auto_char;
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

//定义dll导出符号宏
#ifdef __WINDOWS__
	#define DLL_EXPORT			__declspec(dllexport)
	#define DLL_IMPORT			__declspec(dllimport)
#else 
	#define DLL_EXPORT
	#define DLL_IMPORT
#endif
#ifdef __MAKE_MONK_DLL__
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


//定义strlen和printf
#ifdef __WINDOWS__
	#define t_strlen			wcslen
#else
	#define t_strlen			strlen
#endif



////////////////////////////////////////////////////////////////////////////////////////////////////
// 自定义公共头文件
//
#include "mkMiscellaneous.h"
#include "mkOutputMsg.h"
#include "mkException.h"

#endif // __mkheaders
