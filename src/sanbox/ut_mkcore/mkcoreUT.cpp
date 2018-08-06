/***************************************************************************************************
Author:liu.hao

Time:2017-6

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkIAllocator.h"

class mkcoreUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};
////////////////////////////////////////////////////////////////////////////////
// mkcoreUT
//

TEST_F(mkcoreUT, NC_NEW)
{
	setlocale(LC_ALL,"CHS");
	printf("hello world!");
	
	locale loc( "chs" );
	//locale loc( "Chinese-simplified" );
	//locale loc( "ZHI" );
	//locale loc( ".936" );
	wcout.imbue( loc );
	std::wcout << L"中国" << endl;

	string* pStr = NC_NEW(mkIAllocator::GetGlobleAllocator(), string)("xxxx刘浩");
	cout<<*pStr<<endl;
	NC_DELETE(mkIAllocator::GetGlobleAllocator(), string, pStr);
	
	
	auto_char* tstr = _T("刘浩");
	wprintf(L"%s\n", tstr);
	wprintf(L"%S\n", tstr);
	
	wstring ab(_T("刘浩"));
	wprintf(L"%s\n", ab.c_str());
	wcout<<ab<<endl;
	
	string cc("刘浩");
	printf("%s\n", cc.c_str());

}


