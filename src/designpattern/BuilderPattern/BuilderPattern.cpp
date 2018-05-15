/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	建造者模式（生成器模式）
	意图：
	将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
	（在示例代码中可以通过传入不同的参数实现这一点）。
	
	适用性：
	当同时满足以下情况的时候可以使用Builder模式
	a. 当创建复杂对象的算法应该独立于该对象的组成部分以及他们的装配方式；
	b. 当构造过程必须允许构造的对象有不同的表示；
	
	对比：
	建造者模式和抽象工厂模式在功能上很相似，因为都是用来创建大的复杂的对象，
	它们的区别是：建造者模式强调的是一步步创建对象，并通过相同的创建过程可以获得不同的结果对象，
	一般来说建造者模式中对象不是直接返回的。
	而在 AbstractFactory 模式中对象是直接返回的，
	抽象工厂模式强调的是为创建多个相互依赖的对象提供一个同一的接口。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace BuilderPattern {
// Product
class Product 
{
public:
	Product() {cout << "Product..." << endl;}
	
	void setPartA(const string& s){cout <<s<< endl; m_partA = s;}
	void setPartB(const string& s){cout <<s<< endl; m_partB = s;}
	void setPartC(const string& s){cout <<s<< endl; m_partC = s;}
private:
	string m_partA;
	string m_partB;
	string m_partC;
};

// Builder:给出一个抽象接口，以规范产品对象的各个组成成分的建造。
class Builder 
{
public:
	virtual void BuildPartA() = 0;
	virtual void BuildPartB() = 0;
	virtual void BuildPartC() = 0;
	virtual Product* GetProduct() = 0;
	virtual ~Builder() { }
};

//具体建造者:担任这个角色的是于应用程序紧密相关的类，它们在应用程序调用下创建产品实例。
class ConcreteBuilder1 :public Builder 
{
public:
	ConcreteBuilder1() {m_pProduct = new Product();}
	~ConcreteBuilder1(){delete m_pProduct;}
	
	void BuildPartA() {m_pProduct->setPartA("A"); cout << "BuildPartA..." << endl;}
	void BuildPartB() {m_pProduct->setPartA("B"); cout << "BuildPartB..." << endl;}
	void BuildPartC() {m_pProduct->setPartA("C"); cout << "BuildPartC..." << endl;}

	Product* GetProduct() 
	{
		return m_pProduct;
	}
	
private:
	Product* m_pProduct;
};

class ConcreteBuilder2 :public Builder 
{
public:
	ConcreteBuilder2() {m_pProduct = new Product();}
	~ConcreteBuilder2(){delete m_pProduct;}
	
	void BuildPartA() {m_pProduct->setPartA("aa"); cout << "BuildPartA..." << endl;}
	void BuildPartB() {m_pProduct->setPartA("bb"); cout << "BuildPartB..." << endl;}
	void BuildPartC() {m_pProduct->setPartA("cc"); cout << "BuildPartC..." << endl;}

	Product* GetProduct() 
	{
		return m_pProduct;
	}
	
private:
	Product* m_pProduct;
};

// 指导者:担任这个角色的类调用具体建造者角色以创建产品对象。
class Director 
{
public:
	Director(Builder* pBuilder) {_builer = pBuilder;}

	void Construct() 
	{
		_builer->BuildPartA();
		_builer->BuildPartB();
		_builer->BuildPartC();
	}

private:
	Builder *_builer;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace BuilderPattern;

class ut_BuilderPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_BuilderPattern, Operation)
{
	{
		auto builder = new ConcreteBuilder1();
		auto director = new Director(builder);
		director->Construct();
		Product* product = builder->GetProduct();
		
		delete builder;
		delete director;
	}
	
	{
		auto builder = new ConcreteBuilder2();
		auto director = new Director(builder);
		director->Construct();
		Product* product = builder->GetProduct();
		
		delete builder;
		delete director;
	}
}