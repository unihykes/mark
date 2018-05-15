/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	代理模式
	适用性：
	远程代理（Remote Proxy）为一个对象在不同的地址空间提供局部代表。 
	虚代理（Virtual Proxy）根据需要创建开销很大的对象。在
	保护代理（Protection Proxy）控制对原始对象的访问。保护代理用于对象应该有不同 的访问权限的时候。
	智能指引（Smart Reference）取代了简单的指针，它在访问对象时执行一些附加操作。
	
	与其他模式区别:
	适配器Adapter为它所适配的对象提供了一个不同的接口。相反，代理Proxy提供了与它的实体相同的接口;
	Decorator的实现部分与代理相似，但Decorator的目的不一样:Decorator为对象添加一个或多个功能，而代理则控制对对象的访问。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace ProxyPattern {
	
class Subject 
{
public:
	virtual void Request() = 0;
	virtual ~Subject() { }
};

class ConcreteSubject :public Subject 
{
public:
	void Request() {cout << "ConcreteSubject::Request..." << endl;}
};

class Proxy 
{
public:
	Proxy(Subject* subject) 
	{
		_sub = subject;
	}

	void Reuqest() 
	{
		cout << "Proxy::Request..." << endl;
		_sub->Request();
	}
	
private:
	Subject *_sub;
};

}//namespace end


////////////////////////////////////////////////////////////////////////////////
// ut
//
class ut_ProxyPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_ProxyPattern, Operation)
{
	ProxyPattern::Subject *sub = new ProxyPattern::ConcreteSubject();
	ProxyPattern::Proxy *p = new ProxyPattern::Proxy(sub);
	p->Reuqest();

	delete sub;
	delete p;
}

