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
