/***************************************************************************************************
Author:liu.hao

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
	typedef wchar_t			tchar_t;
	typedef wchar_t			utchar_t;

#else
	typedef char			tchar_t;
	typedef unsigned char	utchar_t;
#endif


//tchar_t长度
#define CONSTANT_STRING_LEN(str)			((sizeof(str)/sizeof(tchar_t)) - 1)


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



//for兼容性:定义可变参数列表之va_copy 
//va_copy(dest, src)：dest，src的类型都是va_list，va_copy()用于复制参数列表指针，将dest初始化为src。
//http://blog.chinaunix.net/uid-677314-id-3476440.html
#ifndef va_copy
	#ifdef __va_copy
		#define va_copy			__va_copy
	#else
		#define va_copy(dest, src)	memcpy(&(dest), &(src), sizeof(va_list))
	#endif
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
	#define t_snwprintf			_snwprintf
#else
	#define t_strlen			strlen
	#define t_snwprintf			printfToStr
	
	inline int printfToStr (tchar_t* buf, size_t bufSize, const tchar_t* fmt, ...)
	{
		va_list ap;
		va_start (ap, fmt);
		int len = nc_vsnprintf (buf, bufSize, fmt, ap);
		va_end (ap);
		return len;
	}
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// function
//

inline int getLastError (void)
{
	#ifdef __WINDOWS__
		return ::GetLastError();
	#else
		return errno;
	#endif
}

inline void setLastError (int err)
{
	#ifdef __WINDOWS__
		::SetLastError(err);
	#else
		errno = err;
	#endif
}

//http://blog.csdn.net/sunnyfans/article/details/8286906
//OUT size must >= 2 bytes
inline void shortToBytes (short v, unsigned char* buf)
{
	*buf++ = ((int)(v >> 8) & 0xFF);
	*buf++ = ((int)(v >> 0) & 0xFF);
}

//OUT size must >= 2 bytes
inline void ushortToBytes (unsigned short v, unsigned char* buf)
{
	*buf++ = ((int)(v >> 8) & 0xFF);
	*buf++ = ((int)(v >> 0) & 0xFF);
}

//IN size must >= 2 bytes
inline unsigned short bytesToUShort (const unsigned char* buf)
{
	int v1 = buf[0];
	int v2 = buf[1];
	
	return ((unsigned short) ((v1 << 8) + (v2 << 0)));
}

//OUT size must >= 4 bytes
inline void intToBytes (int i, unsigned char* b)
{
	b[0] = ((unsigned char)(i >> 24) & 0xFF);
	b[1] = ((unsigned char)(i >> 16) & 0xFF);
	b[2] = ((unsigned char)(i >> 8) & 0xFF);
	b[3] = ((unsigned char)(i >> 0) & 0xFF);
}

//OUT size must >= 4 bytes
inline void uintToBytes (unsigned int u, unsigned char* b)
{
	b[0] = ((int)(u >> 24) & 0xFF);
	b[1] = ((int)(u >> 16) & 0xFF);
	b[2] = ((int)(u >> 8) & 0xFF);
	b[3] = ((int)(u >> 0) & 0xFF);
}

//IN size must >= 4 bytes
inline unsigned int bytesToUInt (const unsigned char* buf)
{
	int v1 = buf[0];
	int v2 = buf[1];
	int v3 = buf[2];
	int v4 = buf[3];
	
	return ((unsigned int) ((v1 << 24) + (v2 << 16) + (v3 << 8) + (v4 << 0)));
}

//IN size must >= 4 bytes
inline int bytesToInt (const unsigned char* buf)
{
	return (int) (bytesToUInt (buf));
}

//OUT size must >= 8 bytes
inline void int64ToBytes (int64 u, unsigned char* b)
{
	b[0] = ((int)(u >> 56) & 0xFF);
	b[1] = ((int)(u >> 48) & 0xFF);
	b[2] = ((int)(u >> 40) & 0xFF);
	b[3] = ((int)(u >> 32) & 0xFF);
	b[4] = ((int)(u >> 24) & 0xFF);
	b[5] = ((int)(u >> 16) & 0xFF);
	b[6] = ((int)(u >> 8) & 0xFF);
	b[7] = ((int)(u >> 0) & 0xFF);
}

//OUT size must >= 8 bytes
inline void uint64ToBytes (uint64 u, unsigned char* b)
{
	b[0] = ((int)(u >> 56) & 0xFF);
	b[1] = ((int)(u >> 48) & 0xFF);
	b[2] = ((int)(u >> 40) & 0xFF);
	b[3] = ((int)(u >> 32) & 0xFF);
	b[4] = ((int)(u >> 24) & 0xFF);
	b[5] = ((int)(u >> 16) & 0xFF);
	b[6] = ((int)(u >> 8) & 0xFF);
	b[7] = ((int)(u >> 0) & 0xFF);
}

//IN size must >= 8 bytes
inline uint64 bytesToUInt64 (const unsigned char* buf)
{
	uint64 v,t;
	v = t = buf[0];
	v <<= 56;

	t = buf[1];
	v |= (t << 48);

	t = buf[2];
	v |= (t << 40);

	t = buf[3];
	v |= (t << 32);

	t = buf[4];
	v |= (t << 24);

	t = buf[5];
	v |= (t << 16);

	t = buf[6];
	v |= (t << 8);

	t = buf[7];
	v |= t;

	return v;
}

//IN size must >= 8 bytes
inline int64 bytesToInt64 (const unsigned char* buf)
{
	return (int64)bytesToUInt64 (buf);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// functor 
//
namespace std {
struct tchar_less : public binary_function<const tchar_t*, const tchar_t*, bool>
{
	bool operator()(const tchar_t* const _Left, const tchar_t* const _Right) const
	{
#ifdef __WINDOWS__
		return (::wcscmp (_Left, _Right) < 0);
#else
		return (strcmp (_Left, _Right) < 0);
#endif
	}
};

struct tchar_less_nocase : public binary_function<const tchar_t*, const tchar_t*, bool>
{
	bool operator()(const tchar_t* const _Left, const tchar_t* const _Right) const
	{
#ifdef __WINDOWS__
	return (::_wcsicmp (_Left, _Right) < 0);
#else
	return (::strcasecmp (_Left, _Right) < 0);
#endif

	}
};

class tchars_equal : public std::binary_function<const tchar_t*, const tchar_t*, bool>
{
public:
	bool operator() (const tchar_t* left, const tchar_t* right) const
	{
#ifdef __WINDOWS__
		if (::wcscmp (left, right) == 0)
#else
		if (::strcmp (left, right) == 0)
#endif
			return true;
		else
			return false;
	}
};
}// namespace std

////////////////////////////////////////////////////////////////////////////////////////////////////
// 自定义公共头文件
//
#include "mkoutputmsg.h"


#endif // __mkheaders
