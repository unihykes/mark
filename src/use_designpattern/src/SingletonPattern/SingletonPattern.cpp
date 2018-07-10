/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	单例模式
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace SingletonPattern {

class Singleton 
{
public:
	static Singleton& Instance() 
	{
		static Singleton instance;
		return instance;
	}

private:
	Singleton() {}
	Singleton(const Singleton &another);
};

}


////////////////////////////////////////////////////////////////////////////////
// ut
//
using namespace SingletonPattern;

class ut_SingletonPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_SingletonPattern, Operation)
{
	Singleton &singleton1 = Singleton::Instance();
	Singleton &singleton2 = Singleton::Instance();
	
	cout << &singleton1 << endl;
	cout << &singleton2 << endl;
}
