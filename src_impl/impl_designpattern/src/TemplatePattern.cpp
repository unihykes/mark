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
	模板方法模式
	对于某一个业务逻辑（算法实现）在不同的对象中有不同的细节实现，
	但是逻辑（算法）的框架（或通用的应用算法）是相同的。模板方法提供了这种情况的一个实现框架。
	模板方法模式是采用继承的方式实现这一点：将逻辑（算法）框架放在抽象基类中，并定义好细节的接口，子类中实现细节。
	
	模板方法模式获得一种反向控制结构效果，
	这也是面向对象系统的分析和设计中一个原则 DIP（依赖倒置：Dependency Inversion Principles）。
	其含义就是父类调用子类的操作（高层模块调用低层模块的操作），低层模块实现高层模块声明的接口。
	这样控制权在父类（高层模块），低层模块反而要依赖高层模块。
	
	对比：
	Strategy 模式解决的是和模板方法模式类似的问题，
	但是 Strategy 模式是将逻辑（算法）封装到一个类中，并采取组合（委托）的方式解决这个问题。 
	
	缺点：
	继承的强制性约束关系也让模板方法模式有不足的地方，
	我们可以看到对于 ConcreteClass 类中的实现的原语方法 PrimitiveOperation1()，是不能被别的类复用。
	假设我们要创建一个 AbstractClass 的变体 AnotherAbstractClass，并且两者只是通用算法不一样，
	其原语操作想复用 AbstractClass 的子类的实现。但是这是不可能实现的，
	因为 ConcreteClass 继承自AbstractClass，也就继承了 AbstractClass 的通用算法，
	AnotherAbstractClass 是复用不了ConcreteClass 的实现，因为后者不是继承自前者。
	模板方法模式暴露的问题也正是继承所固有的问题，
	策略模式则通过组合（委托）来达到和模板方法模式类似的效果，其代价就是空间和时间上的代价，
	关于策略模式的详细讨论请参考 Strategy 模式解析。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace TemplatePattern {
class AbstractClass 
{
public:
	virtual void TemplateMethod() 
	{
		PrimitiveOperation1();
		PrimitiveOperation2();
	}
	virtual ~AbstractClass() { }
protected:
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
	AbstractClass() { }
};

class ConcreteClass1 :public AbstractClass 
{
public:
	void PrimitiveOperation1() {cout << "ConcreteClass1::PrimitiveOperation1" << endl;}
	void PrimitiveOperation2() {cout << "ConcreteClass1::PrimitiveOperation2" << endl;}
};

class ConcreteClass2 :public AbstractClass {
public:
	void PrimitiveOperation1() {cout << "ConcreteClass2::PrimitiveOperation1" << endl;}
	void PrimitiveOperation2() {cout << "ConcreteClass2::PrimitiveOperation2" << endl;}
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace TemplatePattern;
class ut_TemplatePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_TemplatePattern, Operation)
{
	AbstractClass *p1 = new ConcreteClass1();
	p1->TemplateMethod();
	delete p1;
	
	AbstractClass *p2 = new ConcreteClass2();
	p2->TemplateMethod();
	delete p2;
}