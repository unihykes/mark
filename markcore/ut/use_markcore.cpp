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

#include <markcore.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(mkheaders, pragma)
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

TEST(mkheaders, PrintMacro)
{
	//操作系统版本,在begin.cmake中定义
	#ifdef __WINDOWS__
		MK_PRINT("__WINDOWS__ = %d", __WINDOWS__);
	#endif
	#ifdef __LINUX__
		MK_PRINT("__LINUX__ = %d", __LINUX__);
	#endif
	
	
	//编译器版本
	#ifdef _MSC_VER
		MK_PRINT("_MSC_VER = %d", _MSC_VER);
	#endif
	#ifdef __GNUC__
		MK_PRINT("__GNUC__ = %d", __GNUC__);
	#endif
	
	
	//VC版本
	#ifdef WINVER
		MK_PRINT("WINVER = 0x%04x", WINVER);
	#endif
	#ifdef _WIN32_WINNT
		MK_PRINT("_WIN32_WINNT = 0x%04x", _WIN32_WINNT);
	#endif
	#ifdef _WIN32_WINDOWS
		MK_PRINT("_WIN32_WINDOWS = 0x%04x", _WIN32_WINDOWS);
	#endif
	#ifdef _WIN32_IE
		MK_PRINT("_WIN32_IE = 0x%04x", _WIN32_IE);
	#endif
	
	
	//windows常用头文件
	#ifdef _WINSOCK2API_
		MK_PRINT("_WINSOCK2API_ is used");
	#endif
	#ifdef _WINSOCKAPI_
		MK_PRINT("_WINSOCKAPI_ is used");
	#endif
	#ifdef _INC_TCHAR
		MK_PRINT("_INC_TCHAR is used");
	#endif
	
	
	//64位宏
	#ifdef __x86_64__
		MK_PRINT("__x86_64__ is used");
	#endif
	#ifdef __ia64__
		MK_PRINT("__ia64__ is used");
	#endif
	#ifdef __PPC64__
		MK_PRINT("__PPC64__ is used");
	#endif
	#ifdef __powerpc64__
		MK_PRINT("__powerpc64__ is used");
	#endif
	#ifdef __mips64
		MK_PRINT("__mips64 is used");
	#endif
	#ifdef __arch64__
		MK_PRINT("__arch64__ is used");
	#endif
	#ifdef __aarch64__
		MK_PRINT("__aarch64__ is used");
	#endif
	#ifdef _WIN64
		MK_PRINT("_WIN64 = %d", _WIN64);
	#endif
	#ifdef __64BIT__
		MK_PRINT("__64BIT__ is used");
	#endif
	
	
	
	//unicode宏,在begin.cmake中定义
	#ifdef _UNICODE
		MK_PRINT("_UNICODE = %d", _UNICODE);
	#endif
	#ifdef UNICODE
		MK_PRINT("UNICODE = %d", UNICODE);
	#endif
	
	
	//debug宏
	#ifdef _DEBUG
		MK_PRINT("_DEBUG = %d", _DEBUG);
		MK_PRINT("__DEBUG__ is used");
	#endif
	
	
	//va_copy宏
	#ifdef va_copy
		MK_PRINT("va_copy is used");
	#endif
	#ifdef __va_copy
		MK_PRINT("__va_copy is used");
	#endif
	
	
	//__FUNC_NAME__宏
	#ifdef __FUNC_NAME__
		MK_PRINT(_T("__FUNC_NAME__ = %s"), __FUNC_NAME__);
	#endif
}

TEST(mkheaders, mk_char)
{
	const mk_char* ch1 = _T("abcecdrgg");
	MK_PRINT(_T("ch1 = %s"), ch1);
	
	const mk_char ch3[] = _T("123456789");
    //mk_char 长度
    #define CONSTANT_STRING_LEN(str)			((sizeof(str)/sizeof(mk_char)) - 1)
	int size3 = CONSTANT_STRING_LEN(ch3);
	MK_PRINT(_T("ch3 = %s, size = %d"), ch3, size3);
}

TEST(mkheaders, int64)
{
	int64 i1 = -123456;
	uint64 i2 = 123456;
	MK_PRINT(_T("i1 = %lld, i2 = %lld"), i1, i2);
}

TEST(mkheaders, MK_ASSERT)
{
	MK_ASSERT(true);
	//MK_ASSERT(false);
}

TEST(mkModuleInstance, LastError)
{
	MK_PRINT(_T("getLastError() = %d"), mkModuleInstance::GetLastError());
	mkModuleInstance::SetLastError(12);
	MK_PRINT(_T("getLastError() = %d"), mkModuleInstance::GetLastError());
}

TEST(mkTypeCast, shortToBytes)
{
	short v = 123;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::shortToBytes(v, buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}


TEST(mkTypeCast, ushortToBytes)
{
	unsigned short v = 456;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::ushortToBytes(v, buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}

TEST(mkTypeCast, bytesToUShort)
{
	unsigned short v = 789;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::ushortToBytes(v, buf);
	unsigned short result = mkTypeCast::bytesToUShort(buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x, result = 0x%04x", v, buf[0], buf[1], result);
}

TEST(mkTypeCast, intToBytes)
{
	int v = 2147483647;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::intToBytes(v, buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST(mkTypeCast, uintToBytes)
{
	unsigned int v = 2147483640;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::uintToBytes(v, buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST(mkTypeCast, bytesToUInt)
{
	unsigned int v = 2147483600;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::uintToBytes(v, buf);
	unsigned int result = mkTypeCast::bytesToUInt(buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST(mkTypeCast, bytesToInt)
{
	int v = 2147483000;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::intToBytes(v, buf);
	int result = mkTypeCast::bytesToInt(buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST(mkTypeCast, int64ToBytes)
{
	int64 v = 1234567890123;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::int64ToBytes(v, buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST(mkTypeCast, uint64ToBytes)
{
	uint64 v = 12345678901234;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::uint64ToBytes(v, buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST(mkTypeCast, bytesToUInt64)
{
	uint64 v = 123456789012345;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::uint64ToBytes(v, buf);
	uint64 result = mkTypeCast::bytesToUInt64(buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}

TEST(mkTypeCast, bytesToInt64)
{
	int64 v = 1234567890123456;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::int64ToBytes(v, buf);
	int64 result = mkTypeCast::bytesToInt64(buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}

TEST(mkTablePrinter, func)
{
	mkTablePrinter pr;
	//std::shared_ptr<TablePrinter> printGrid(new TablePrinter("xx", 4, 3));
}

TEST(mkException, null)
{
    try {
        try {
            MK_THROW(128, "aaa");
        }
        catch(mkException& e) {
            MK_PRINT(e.what());
            MK_THROW(128, "%s", e.what());
        }
    }
    catch(mkException& e) {
        MK_PRINT(e.what());
    }
}


TEST(mkTrace, run)
{
    mkTrace trace("test");
    trace(__FILE__, __LINE__, __func__, "%s_%d", "abc", 123);
    trace(__FILE__, __LINE__, __func__, L"%s_%d", L"def", 456);
}

TEST(mkOptionSwitch, run)
{
    class mkOptionA final : public mkIOption
    {
    public:
        mkOptionA() 
        {
        }
        
        virtual bool OnSetValue (const string& key, const string& value) override
        {
            return true;
        }
    };
    
    mkOptionSwitch switchs;
    switchs.ClearOption<mkOptionA>();
    
    //设置选项
    switchs.SetOptions("aaa", "test_value1", false);
    switchs.SetOptions("ddd", "test_value2", false);
    switchs.SetOptions("fff", "test_value3", false);
    switchs.SetOptions("hhh", "test_value4", false);
    switchs.Applys();
    
    //使用选项
    {
        auto pOption = switchs.GetOption<mkOptionA>();

    }
    
    //修改选项
    {
        switchs.SetOption<mkOptionA>("aaa", "test_valuexxx");
        switchs.Apply<mkOptionA>();
    }
}

