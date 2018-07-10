/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	外观模式
	实际上在软件系统开发中也经常回会遇到这样的情况，
	可能你实现了一些接口（模块），而这些接口（模块）都分布在几个类中（比如 A 和 B、C、D）：
	A 中实现了一些接口，B 中实现一些接口（或者 A 代表一个独立模块，B、C、D 代表另一些独立模块）。
	然后你的客户程序员（使用你设计的开发人员）只有很少的要知道你的不同接口到底是在那个类中实现的，
	绝大多数只是想简单的组合你的 A－D 的类的接口，他并不想知道这些接口在哪里实现的。
	
	外观模式的想法、思路和实现都非常简单，但是其思想却是非常有意义的。
	并且外观设计模式在实际的开发设计中也是应用最广、最多的模式之一。
	
	对比：
	外观模式在高层提供了一个统一的接口，解耦了系统。
	设计模式中还有另一种模式中介者也和外观有类似的地方。
	但是中介者主要目的是对象间的访问的解耦（通讯时候的协议）。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace FacadePattern {
class SubSystem1 
{
public:
	void Operation() {cout << "SubSystem1 operation..." << endl;}
};

class SubSystem2 
{
public:
	void Operation() {cout << "SubSystem2 operation..." << endl;}
};

class Facade 
{
public:
	Facade() 
	{
		_sub1 = new SubSystem1();
		_sub2 = new SubSystem2();
	}
	
	~Facade() 
	{
		delete _sub1;
		delete _sub2;
	}

	void OperationWrapper() 
	{
		_sub1->Operation();
		_sub2->Operation();
	}
private:
	SubSystem1 *_sub1;
	SubSystem2 *_sub2;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace FacadePattern;

class ut_FacadePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_FacadePattern, Operation)
{
	Facade *facade = new Facade();
	facade->OperationWrapper();

	delete facade;
}