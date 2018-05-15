/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	中介者模式
	中介者模式提供将对象间的交互和通讯封装在一个类中，
	各个对象间的通信不必显势去声明和引用，大大降低了系统的复杂性能（了解一个对象总比深入熟悉 n 个对象要好）。
	另外中介者模式还带来了系统对象间的松耦合。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;

namespace MediatorPattern {
class Person;

class Mediator 
{
public:
	virtual void Send(const string& msg, Person* person) = 0;
	virtual ~Mediator() { }
	
	void BuildRelation(Person *a, Person *b) 
	{
		m_a = a;
		m_b = b;
	}

protected:
	Person *m_a;
	Person *m_b;
};

class ConcreteMediator :public Mediator 
{
public:
	void Send(const string& msg, Person* person) 
	{
		if (person == m_a) {
			cout << msg << "--Mediator--PersonB" << endl;
		}
		else if (person == m_b) {
			cout << msg << "--Mediator--PersonA" << endl;
		}
	}
};

class Person 
{
public:
	Person(Mediator*md):_md(md) { }
	virtual void SendMessage(const string& msg) = 0;
	virtual ~Person() { }
protected:
	Mediator* _md;
};

class ConcretePersonA :public Person 
{
public:
	ConcretePersonA(Mediator* md):Person(md) { }

	void SendMessage(const string& msg) 
	{
		_md->Send(msg, this);
	}
};

class ConcretePersonB :public Person 
{
public:
	ConcretePersonB(Mediator* md):Person(md) { }

	void SendMessage(const string& msg) 
	{
		_md->Send(msg, this);
	}
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace MediatorPattern;
class ut_MediatorPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_MediatorPattern, Operation)
{
	/*
	中介者模式是一种很有用并且很常用的模式，
	它通过将对象间的通信封装到一个类中，将多对多的通信转化为一对多的通信，降低了系统的复杂性。
	
	中介者还获得系统解耦的特性，
	通过 Mediator，各个 Colleague 就不必维护各自通信的对象和通信协议，降低了系统的耦合性，中介者和各个 Colleague 就可以相互独立地修改了。
	
	中介者模式还有一个很显著额特点就是将控制集中，集中的优点就是便于管理，也正式符合了 OO 设计中的每个类的职责要单一和集中的原则。
	*/
	Mediator *mediator = new ConcreteMediator();
	Person *personA = new ConcretePersonA(mediator);
	Person *personB = new ConcretePersonB(mediator);

	mediator->BuildRelation(personA, personB);
	personA->SendMessage("PersonA");
	personB->SendMessage("PersonB");

	delete personA;
	delete personB;
	delete mediator;
}
