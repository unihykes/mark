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
	工厂方法模式 Factory Method
	工厂模式基本与简单工厂模式差不多，
	由于简单工厂模式下，每次添加一个产品子类都必须在工厂类中添加一个判断分支，这样违背了开放-封闭原则，
	因此，工厂模式就是为了解决这个问题而产生的。
	既然每次都要判断，那我就把这些判断都生成一个工厂子类，
	这样，每次添加产品子类的时候，只需再添加一个工厂子类就可以了。这样就完美的遵循了开放-封闭原则。
	
	同样工厂模式一般应该于程序中大部分地方都只使用其中一种产品，工厂类也不用频繁创建产品类的情况。
	这样修改的时候只需要修改有限的几个地方即可。
	
	优点
	基本与简单工厂模式一致，多的一点优点就是遵循了开放-封闭原则，使得模式的灵活性更强。
	缺点
	与简单工厂模式差不多。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>

namespace FactoryPattern {
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
	virtual AbstractProduct* CreateProduct() = 0;
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
// 具体工厂实现
//
class ConcreteFactory1 :public AbstractFactory 
{
public:
	ConcreteFactory1() {}
	~ConcreteFactory1() {}
	
	AbstractProduct* CreateProduct() {return new ProductA1();}
};

class ConcreteFactory2 :public AbstractFactory 
{
public:
	ConcreteFactory2() {}
	~ConcreteFactory2() {}
	
	AbstractProduct* CreateProduct() {return new ProductA2();}
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//
class ut_FactoryPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_FactoryPattern, Operation)
{
	{
		FactoryPattern::AbstractFactory *factory = new FactoryPattern::ConcreteFactory1();
		FactoryPattern::AbstractProduct *product = factory->CreateProduct();
		product->Operation();
		delete factory;
		delete product;
	}
	{
		FactoryPattern::AbstractFactory *factory = new FactoryPattern::ConcreteFactory2();
		FactoryPattern::AbstractProduct *product = factory->CreateProduct();
		product->Operation();
		delete factory;
		delete product;
	}
}