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

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_mkheaders : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

TEST_F(ut_mkheaders, pragma)
{
	#ifdef __WINDOWS__
		// 链接基础库
		#pragma comment(lib, "shell32.lib")
		#pragma comment(lib, "advapi32.lib")
		#pragma comment(lib, "user32.lib")
		#pragma comment(lib, "Ws2_32.lib")
		#pragma comment(lib, "Mpr.lib")
		#pragma comment(lib, "DbgHelp.lib")
		
		//关闭部分编译警告
		// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
		#pragma warning(disable:4251)
		// 'function': was declared deprecated
		#pragma warning(disable:4996)
		// 'this' : used in base member initializer list
		#pragma warning(disable:4355)
		// 'symbol name': attributes not present on previous declaration.
		#pragma warning(disable: 4985)
		// 'virtual function overrides' : previous versions of the compiler did not override when parameters only differed by const/volatile qualifiers
		#pragma warning(disable: 4373)
		// 'keyword' : ignored on left of 'type' when no variable is declared
		#pragma warning(disable: 4091)
	#endif
}

TEST_F(ut_mkheaders, PrintMacro)
{
	//操作系统版本,在begin.cmake中定义
	#ifdef __WINDOWS__
		MK_PRINT_MSG("__WINDOWS__ = %d", __WINDOWS__);
	#endif
	#ifdef __LINUX__
		MK_PRINT_MSG("__LINUX__ = %d", __LINUX__);
	#endif
	
	
	//编译器版本
	#ifdef _MSC_VER
		MK_PRINT_MSG("_MSC_VER = %d", _MSC_VER);
	#endif
	#ifdef __GNUC__
		MK_PRINT_MSG("__GNUC__ = %d", __GNUC__);
	#endif
	
	
	//VC版本
	#ifdef WINVER
		MK_PRINT_MSG("WINVER = 0x%04x", WINVER);
	#endif
	#ifdef _WIN32_WINNT
		MK_PRINT_MSG("_WIN32_WINNT = 0x%04x", _WIN32_WINNT);
	#endif
	#ifdef _WIN32_WINDOWS
		MK_PRINT_MSG("_WIN32_WINDOWS = 0x%04x", _WIN32_WINDOWS);
	#endif
	#ifdef _WIN32_IE
		MK_PRINT_MSG("_WIN32_IE = 0x%04x", _WIN32_IE);
	#endif
	
	
	//windows常用头文件
	#ifdef _WINSOCK2API_
		MK_PRINT_MSG("_WINSOCK2API_ is used");
	#endif
	#ifdef _WINSOCKAPI_
		MK_PRINT_MSG("_WINSOCKAPI_ is used");
	#endif
	#ifdef _INC_TCHAR
		MK_PRINT_MSG("_INC_TCHAR is used");
	#endif
	
	
	//64位宏
	#ifdef __x86_64__
		MK_PRINT_MSG("__x86_64__ is used");
	#endif
	#ifdef __ia64__
		MK_PRINT_MSG("__ia64__ is used");
	#endif
	#ifdef __PPC64__
		MK_PRINT_MSG("__PPC64__ is used");
	#endif
	#ifdef __powerpc64__
		MK_PRINT_MSG("__powerpc64__ is used");
	#endif
	#ifdef __mips64
		MK_PRINT_MSG("__mips64 is used");
	#endif
	#ifdef __arch64__
		MK_PRINT_MSG("__arch64__ is used");
	#endif
	#ifdef __aarch64__
		MK_PRINT_MSG("__aarch64__ is used");
	#endif
	#ifdef _WIN64
		MK_PRINT_MSG("_WIN64 = %d", _WIN64);
	#endif
	#ifdef __64BIT__
		MK_PRINT_MSG("__64BIT__ is used");
	#endif
	
	
	
	//unicode宏,在begin.cmake中定义
	#ifdef _UNICODE
		MK_PRINT_MSG("_UNICODE = %d", _UNICODE);
	#endif
	#ifdef UNICODE
		MK_PRINT_MSG("UNICODE = %d", UNICODE);
	#endif
	
	
	//debug宏
	#ifdef _DEBUG
		MK_PRINT_MSG("_DEBUG = %d", _DEBUG);
		MK_PRINT_MSG("__DEBUG__ is used");
	#endif
	
	
	//va_copy宏
	#ifdef va_copy
		MK_PRINT_MSG("va_copy is used");
	#endif
	#ifdef __va_copy
		MK_PRINT_MSG("__va_copy is used");
	#endif
	
	
	//__FUNC_NAME__宏
	#ifdef __FUNC_NAME__
		MK_PRINT_MSG(_T("__FUNC_NAME__ = %s"), __FUNC_NAME__);
	#endif
}

TEST_F(ut_mkheaders, auto_char)
{
	const auto_char* ch1 = _T("abcecdrgg");
	MK_PRINT_MSG(_T("ch1 = %s"), ch1);
	
	const auto_char ch3[] = _T("123456789");
    //auto_char长度
    #define CONSTANT_STRING_LEN(str)			((sizeof(str)/sizeof(auto_char)) - 1)
	int size3 = CONSTANT_STRING_LEN(ch3);
	MK_PRINT_MSG(_T("ch3 = %s, size = %d"), ch3, size3);
}

TEST_F(ut_mkheaders, eg_int64)
{
	int64 i1 = -123456;
	uint64 i2 = 123456;
	MK_PRINT_MSG(_T("i1 = %lld, i2 = %lld"), i1, i2);
}

TEST_F(ut_mkheaders, eg_assert)
{
	MK_ASSERT(true);
	//MK_ASSERT(false);
}

TEST_F(ut_mkheaders, eg_LastError)
{
	MK_PRINT_MSG(_T("getLastError() = %d"), getLastError());
	setLastError(12);
	MK_PRINT_MSG(_T("getLastError() = %d"), getLastError());
}

TEST_F(ut_mkheaders, shortToBytes)
{
	short v = 123;
	unsigned char buf[2];
	memset(buf, 0, 2);
	shortToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}


TEST_F(ut_mkheaders, ushortToBytes)
{
	unsigned short v = 456;
	unsigned char buf[2];
	memset(buf, 0, 2);
	ushortToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}

TEST_F(ut_mkheaders, bytesToUShort)
{
	unsigned short v = 789;
	unsigned char buf[2];
	memset(buf, 0, 2);
	ushortToBytes(v, buf);
	unsigned short result = bytesToUShort(buf);
	
	MK_PRINT_MSG("v = 0x%04x, buf = 0x%02x%02x, result = 0x%04x", v, buf[0], buf[1], result);
}

TEST_F(ut_mkheaders, intToBytes)
{
	int v = 2147483647;
	unsigned char buf[4];
	memset(buf, 0, 4);
	intToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST_F(ut_mkheaders, uintToBytes)
{
	unsigned int v = 2147483640;
	unsigned char buf[4];
	memset(buf, 0, 4);
	uintToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST_F(ut_mkheaders, bytesToUInt)
{
	unsigned int v = 2147483600;
	unsigned char buf[4];
	memset(buf, 0, 4);
	uintToBytes(v, buf);
	unsigned int result = bytesToUInt(buf);
	
	MK_PRINT_MSG("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST_F(ut_mkheaders, bytesToInt)
{
	int v = 2147483000;
	unsigned char buf[4];
	memset(buf, 0, 4);
	intToBytes(v, buf);
	int result = bytesToInt(buf);
	
	MK_PRINT_MSG("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST_F(ut_mkheaders, int64ToBytes)
{
	int64 v = 1234567890123;
	unsigned char buf[8];
	memset(buf, 0, 8);
	int64ToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST_F(ut_mkheaders, uint64ToBytes)
{
	uint64 v = 12345678901234;
	unsigned char buf[8];
	memset(buf, 0, 8);
	uint64ToBytes(v, buf);
	
	MK_PRINT_MSG("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST_F(ut_mkheaders, bytesToUInt64)
{
	uint64 v = 123456789012345;
	unsigned char buf[8];
	memset(buf, 0, 8);
	uint64ToBytes(v, buf);
	uint64 result = bytesToUInt64(buf);
	
	MK_PRINT_MSG("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}

TEST_F(ut_mkheaders, bytesToInt64)
{
	int64 v = 1234567890123456;
	unsigned char buf[8];
	memset(buf, 0, 8);
	int64ToBytes(v, buf);
	int64 result = bytesToInt64(buf);
	
	MK_PRINT_MSG("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}

TEST_F(ut_mkheaders, tchar_less)
{
	tchar_less oper;
	bool result1 = oper(_T("abc"), _T("DEF"));
	bool result2 = oper(_T("DEF"), _T("abc"));
	MK_PRINT_MSG("result1 = %u, result2 = %u", result1, result2);
}

TEST_F(ut_mkheaders, tchar_less_nocase)
{
	tchar_less_nocase oper;
	bool result1 = oper(_T("abc"), _T("DEF"));
	bool result2 = oper(_T("DEF"), _T("abc"));
	MK_PRINT_MSG("result1 = %u, result2 = %u", result1, result2);
}

TEST_F(ut_mkheaders, tchars_equal)
{
	tchars_equal oper;
	bool result1 = oper(_T("ABC"), _T("abc"));
	bool result2 = oper(_T("ABC"), _T("ABC"));
	MK_PRINT_MSG("result1 = %u, result2 = %u", result1, result2);
}