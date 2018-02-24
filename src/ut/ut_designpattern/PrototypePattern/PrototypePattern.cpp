/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	原型模式
	原型模式提供了自我复制的功能，就是说新对象的创建可以通过已有对象进行创建。
	原型模式提供了一个通过已存在对象进行新对象创建的接口（Clone），
	Clone()实现和具体的实现语言相关，在 C++中我们将通过拷贝构造函数实现之。 
	
	对比：
	原型模式通过复制原型（原型）而获得新对象创建的功能，这里原型本身就是"对象工厂"（因为能够生产对象），
	实际上原型模式和 Builder 模式、AbstractFactory 模式都是通过一个类（对象实例）来专门负责对象的创建工作（工厂对象），
	它们之间的区别是：
	Builder 模式重在复杂对象的一步步创建（并不直接返回对象），
	AbstractFactory 模式重在产生多个相互依赖类的对象，
	而原型模式重在从自身复制自己创建新类。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace PrototypePattern {
// Prototype
class Prototype 
{
public:
	virtual Prototype* Clone() = 0;
	virtual ~Prototype() { }
};

class ConcretePrototype :public Prototype 
{
public:
	ConcretePrototype() { }

	ConcretePrototype(const ConcretePrototype&cp) 
	{
		cout << "ConcretePrototype copy..." << endl;
	}

	Prototype* Clone() 
	{
		return new ConcretePrototype(*this);
	}
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace PrototypePattern;
class ut_PrototypePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_PrototypePattern, Operation)
{
	Prototype *prototype = new ConcretePrototype();
	cout << prototype << endl;
	
	Prototype* prototype1 = prototype->Clone();
	cout << prototype1 << endl;
	
	Prototype* prototype2 = prototype->Clone();
	cout << prototype2 << endl;

	delete prototype;
	delete prototype1;
	delete prototype2;
}