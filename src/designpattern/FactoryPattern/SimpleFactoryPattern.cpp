/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	简单工厂模式
	
	简单工厂模式一般应该于程序中大部分地方都只使用其中一种产品，工厂类也不用频繁创建产品类的情况。
	这样修改的时候只需要修改有限的几个地方即可。
	
	客户只需要知道SimpleFactory就可以了，使用的时候也是使用的AbstractFactory，
	这样客户端只在第一次创建工厂的时候是知道具体的细节的，其他时候它都只知道AbstractFactory，
	这样就完美的达到了依赖倒转的原则。
	
	优点
	1.隐藏了对象创建的细节，将产品的实例化推迟到子类中实现。
	2.客户端基本不用关心使用的是哪个产品，只需要知道用哪个工厂就行了，提供的类型也可以用比较便于识别的字符串。
	3.方便添加新的产品子类，每次只需要修改工厂类传递的类型值就行了。
	4.遵循了依赖倒转原则。
	缺点
	1.要求产品子类的类型差不多，使用的方法名都相同，如果类比较多，而所有的类又必须要添加一种方法，则会是非常麻烦的事情。
		或者是一种类另一种类有几种方法不相同，客户端无法知道是哪一个产品子类，也就无法调用这几个不相同的方法。
	2.每添加一个产品子类，都必须在工厂类中添加一个判断分支，这违背了开放-封闭原则。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>

namespace SimpleFactoryPattern {
////////////////////////////////////////////////////////////////////////////////////////////////////
// 产品接口和工厂接口
//

class AbstractProduct 
{
public:
	virtual ~AbstractProduct() { }
	virtual void Operation() = 0;
};

class AbstractFactory 
{
public:
	virtual AbstractProduct* CreateProduct(int type) = 0;
	virtual ~AbstractFactory() { }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 具体产品实现
//

class ProductA1 :public AbstractProduct 
{
public:
	ProductA1() {}
	~ProductA1(){}
	
	void Operation() {std::cout << "ProductA1::Operation()" << std::endl;}
};

class ProductA2 :public AbstractProduct 
{
public:
	ProductA2() {}
	~ProductA2(){}
	
	void Operation() {std::cout << "ProductA2::Operation()" << std::endl;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// 简单工厂实现
//
class SimpleFactory :public AbstractFactory 
{
public:
	SimpleFactory() {}
	~SimpleFactory() {}
	
	AbstractProduct* CreateProduct(int type) 
	{
		AbstractProduct* result = nullptr;
		
		switch(type) {
		case 1:
			result = new ProductA1();
			break;
		case 2:
			result = new ProductA2();
			break;
		case 3:
			//result = new ProductA3();
			break;
		default:
			break;
		}
		
		return result;
	}
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//
class ut_SimpleFactoryPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_SimpleFactoryPattern, Operation)
{
	SimpleFactoryPattern::AbstractFactory *factory = new SimpleFactoryPattern::SimpleFactory();
	
	{
		SimpleFactoryPattern::AbstractProduct *product = factory->CreateProduct(1);
		product->Operation();
		delete product;
	}
	
	{
		SimpleFactoryPattern::AbstractProduct *product = factory->CreateProduct(2);
		product->Operation();
		delete product;
	}
	
	delete factory;
}