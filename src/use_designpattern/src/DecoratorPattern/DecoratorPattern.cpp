/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	装饰模式
	在 OO 设计和开发过程，可能会经常遇到以下的情况：
	我们需要为一个已经定义好的类添加新的职责（操作），
	通常的情况我们会给定义一个新类继承自定义好的类,这样会带来一个问题:
	{
		为了多态，通过父类指针指向其具体子类，
		当具体子类要添加新的职责，就必须向其父类添加一个这个职责的抽象接口，否则是通过父类指针是调用不到这个方法了。
		这样处于高层的父类就承载了太多的特征（方法），
		并且继承自这个父类的所有子类都不可避免继承了父类的这些接口，但是可能这并不是这个具体子类所需要的。
	}
	另外通过继承的方式解决这样的情况还带来了系统的复杂性，因为继承的深度会变得很深。
	而装饰提供了一种给类增加职责的方法，不是通过继承实现的，而是通过组合。
	
	在 OO 设计和分析经常有这样一种情况：

	而在装饰模式提供了一种较好的解决方法，当需要添加一个操作的时候就可以通过装饰模式来解决，你可以一步步添加新的职责。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace DecoratorPattern {
	
class Component 
{
public:
	virtual void Operation() = 0;
	virtual ~Component() { }
};

class ConcreteComponent :public Component 
{
public:
	void Operation() {cout << "ConcreteComponent::Operation()" << endl;}
};

class Decorator 
{
public:
	virtual void Operation() = 0;
	virtual void AddBehavior() = 0;
	virtual ~Decorator() { }
};

class ConcreteDecorator :public Decorator 
{
public:
	ConcreteDecorator(Component *com) 
	{
		_com = com;
	}

	void AddBehavior() 
	{
		cout << "ConcreteDecorator::AddBehavior..." << endl;
	}
	
	void Operation() 
	{
		cout << "ConcreteDecorator::Operation..." << endl;
		AddBehavior();
		_com->Operation();
	}
private:
	Component *_com;
};

}//namespace end


////////////////////////////////////////////////////////////////////////////////
// ut
//
using namespace DecoratorPattern;
class ut_DecoratorPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_DecoratorPattern, Operation)
{
	Component *con = new ConcreteComponent();
	Decorator *dec = new ConcreteDecorator(con);
	dec->Operation();

	delete con;
	delete dec;
}
