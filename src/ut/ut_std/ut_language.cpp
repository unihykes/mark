/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class utLanguage : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

TEST_F(utLanguage, Fundamental_types)
{
	cout << "sizeof(bool) = " << sizeof(bool) << ", ptr = "<< *(new bool(true))<<endl;
	cout << "sizeof(char) = " << sizeof(char) <<endl;
	cout << "sizeof(wchar_t) = " << sizeof(wchar_t) <<endl;
	cout << "sizeof(char16_t) = " << sizeof(char16_t) <<endl;
	cout << "sizeof(char32_t) = " << sizeof(char32_t) <<endl;
	cout << "sizeof(int) = " << sizeof(int) <<endl;
	cout << "sizeof(short) = " << sizeof(short) <<endl;
	cout << "sizeof(long) = " << sizeof(long) <<endl;
	cout << "sizeof(float) = " << sizeof(float) <<endl;
	cout << "sizeof(double) = " << sizeof(double) <<endl;
	
	cout << "sizeof(void*) = " << sizeof(void*) <<endl;
	cout << "sizeof(std::nullptr_t) = " << sizeof(std::nullptr_t) <<endl;
}

