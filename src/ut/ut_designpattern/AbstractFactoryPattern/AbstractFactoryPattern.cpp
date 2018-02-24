/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	抽象工厂模式:
	提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
	1个产品族包含了几种不同产品，每个具体工厂均会生产产品族中的每个产品；
	
	抽象工厂模式就变得比工厂模式更为复杂，
	就像上面提到的缺点一样，工厂模式和简单工厂模式要求产品子类必须要是同一类型的，拥有共同的方法，这就限制了产品子类的扩展。
	于是为了更加方便的扩展，抽象工厂模式就将同一类的产品子类归为一类，
	让他们继承同一个抽象子类，我们可以把他们一起视作一组，然后好几组产品构成一族。
	此时，客户端要使用时必须知道是哪一个工厂并且是哪一组的产品抽象类。
	每一个工厂子类负责产生一族产品，而子类的一种方法产生一种类型的产品。
	在客户端看来只有AbstractProductA和AbstractProductB两种产品，使用的时候也是直接使用这两种产品。
	而通过工厂来识别是属于哪一族产品。
	
	优点
	1.封装了产品的创建，使得不需要知道具体是哪种产品，只需要知道是哪个工厂就行了。
	2.可以支持不同类型的产品，使得模式灵活性更强。
	3.可以非常方便的使用一族中间的不同类型的产品。
	缺点
	1.结构太过臃肿，如果产品类型比较多，或者产品族类比较多，就会非常难于管理。
	2.每次如果添加一组产品，那么所有的工厂类都必须添加一个方法，这样违背了开放-封闭原则。
		所以一般适用于产品组合产品族变化不大的情况。
***************************************************************************************************/

#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace AbstractFactoryPattern {
////////////////////////////////////////////////////////////////////////////////////////////////////
//客户可见接口
//

//抽象产品接口类A
class AbstractProductA
{
public:
	virtual ~AbstractProductA(){}
	virtual void OperationA() = 0;
};

//抽象产品接口类B
class AbstractProductB
{
public:
	virtual ~AbstractProductB(){}
	virtual void OperationB() = 0;
};

// 抽象工厂接口类
class AbstractFactory 
{
public:
    virtual ~AbstractFactory() { }
    virtual AbstractProductA* CreateProductA() = 0;
    virtual AbstractProductB* CreateProductB() = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 具体工厂1及其产品族
//

//产品A实现类A1
class ProductA1 :public AbstractProductA 
{
public:
	void OperationA(){cout << "ProductA1::OperationA()" << endl;}
};

//产品B实现类B1
class ProductB1 :public AbstractProductB 
{
public:
	void OperationB(){cout << "ProductB1::OperationB()" << endl;}
};

//具体工厂1的实现类
class ConcreteFactory1 :public AbstractFactory 
{
public:
	AbstractProductA* CreateProductA() {return new ProductA1();}
	AbstractProductB* CreateProductB() {return new ProductB1();}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 具体工厂2及其产品族
//

//产品A实现类A2
class ProductA2 :public AbstractProductA 
{
public:
	void OperationA(){cout << "ProductA2::OperationA()" << endl;}
};

//产品B实现类B2
class ProductB2 :public AbstractProductB 
{
public:
	void OperationB(){cout << "ProductB2::OperationB()" << endl;}
};

//具体工厂2的实现类
class ConcreteFactory2 :public AbstractFactory 
{
public:
	AbstractProductA* CreateProductA() {return new ProductA2();}
	AbstractProductB* CreateProductB() {return new ProductB2();}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// 具体工厂3及其产品族
//

//具体工厂3的实现类
class ConcreteFactory3 :public AbstractFactory 
{
public:
	//工厂3生成的A产品，是工厂1代工的。。。
	AbstractProductA* CreateProductA() {return new ProductA1();}
	
	//工厂3生成的B产品，是工厂2代工的。。。
	AbstractProductB* CreateProductB() {return new ProductB2();}
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//
class ut_AbstractFactoryPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_AbstractFactoryPattern, Operation)
{
	auto ShowProduct = [](AbstractFactoryPattern::AbstractFactory *factory)->void{
		//该工厂生产的产品A
		AbstractFactoryPattern::AbstractProductA* productA = factory->CreateProductA();
		productA->OperationA();
		delete productA;
		
		//该工厂生产的产品B
		AbstractFactoryPattern::AbstractProductB* productB = factory->CreateProductB();
		productB->OperationB();
		delete productB;
		
		cout << "\n" << endl;
	};
	
	{
		//工厂1的产品族
		AbstractFactoryPattern::AbstractFactory *factory = new AbstractFactoryPattern::ConcreteFactory1();
		ShowProduct(factory);
		delete factory;
	}
	
	{
		////工厂2的产品族
		AbstractFactoryPattern::AbstractFactory *factory = new AbstractFactoryPattern::ConcreteFactory2();
		ShowProduct(factory);
		delete factory;
	}
	
	{
		////工厂3的产品族
		AbstractFactoryPattern::AbstractFactory *factory = new AbstractFactoryPattern::ConcreteFactory3();
		ShowProduct(factory);
		delete factory;
	}
}

