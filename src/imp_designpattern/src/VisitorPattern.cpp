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
	访问者模式
	在面向对象系统的开发和设计过程，经常会遇到一种情况就是需求变更（Requirement Changing），
	经常我们做好的一个设计、实现了一个系统原型，咱们的客户又会有了新的需求。
	我们又因此不得不去修改已有的设计，
	最常见就是解决方案就是给已经设计、实现好的类添加新的方法去实现客户新的需求，
	这样就陷入了设计变更的梦魇：不停地打补丁，其带来的后果就是设计根本就不可能封闭、编译永远都是整个系统代码。
	访问者模式则提供了一种解决方案：
	将更新（变更）封装到一个类中（访问操作），并由待更改类提供一个接收接口，则可达到效果。 
	
	访问者模式在不破坏类的前提下，为类提供增加新的新操作。
	在访问者模式中 Accept()操作是一个双分派的操作。
	具体调用哪一个具体的 Accept()操作，有两个决定因素：
	1）Element 的类型，需要具体的 Element 类型的子类才可以决定到底调用哪一个 Accept（）实现；
	2）访问者的类型。
	
	Accept()操作有一个参数（Visitor* vis），
	要决定了实际传进来的访问者的实际类别才可以决定具体是调用哪个 ConcreteVisit()实现。
	
	角色分析
	抽象访问者（Visitor）角色：声明了一个或者多个访问操作，形成所有的具体元素角色必须实现的接口。
	具体访问者（ConcreteVisitor）角色：实现抽象访问者角色所声明的接口，也就是抽象访问者所声明的各个访问操作。
	抽象节点（Element）角色：声明一个接受操作，接受一个访问者对象作为一个参量。
	具体节点（ConcreteElement）角色：实现了抽象元素所规定的接受操作。
	结构对象（ObiectStructure）角色：有如下的一些责任，可以遍历结构中的所有元素；
		如果需要，提供一个高层次的接口让访问者对象可以访问每一个元素；
		如果需要，可以设计成一个复合对象或者一个聚集，如列（List）或集合（Set）。 
	
	特点:
	问者模式把数据结构和作用于结构上的操作解耦合，使得操作集合可相对自由地演化
	访问者模式适用于数据结构相对稳定算法又易变化的系统。因为访问者模式使得算法操作增加变得容易。
	若系统数据结构对象易于变化，经常有新的数据对象增加进来，则不适合使用访问者模式。
	访问者模式的优点是增加操作很容易，因为增加操作意味着增加新的访问者。
	访问者模式将有关行为集中到一个访问者对象中，其改变不影响系统数据结构。其缺点就是增加新的数据结构很困难。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <list>
using namespace std;

namespace VisitorPattern {
	

////////////////////////////////////////////////////////////////////////////////////////////////////

class Visitor;
//元素接口
class Element 
{
public:
	Element(){}
	virtual ~Element(){}
	virtual void Accept(Visitor* vis) = 0;
};

class ConcreteElementA;
class ConcreteElementB;
//访问者接口
class Visitor 
{
public:
	virtual ~Visitor(){}
	virtual void VisitConcreteElementA(ConcreteElementA* elm) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB* elm) = 0;
protected:
	Visitor(){}
};

//具体元素A
class ConcreteElementA :public Element 
{
public:
	void Accept(Visitor* vis)
	{
		cout << __FUNCTION__ << endl;
		vis->VisitConcreteElementA(this);
	}
	
	void OperationA(){cout << __FUNCTION__ << endl;}
};

//具体元素B
class ConcreteElementB :public Element 
{
public:
	void Accept(Visitor* vis)
	{
		cout << __FUNCTION__ << endl;
		vis->VisitConcreteElementB(this);
	}
	void OperationB(){cout << __FUNCTION__ << endl;}
};

////////////////////////////////////////////////////////////////////////////////////////////////////

//具体访问者
class ConcreteVisitor1 :public Visitor 
{
public:
	void VisitConcreteElementA(ConcreteElementA* elm)
	{
		cout << __FUNCTION__ << endl;
		elm->OperationA();
	}
	
	void VisitConcreteElementB(ConcreteElementB* elm)
	{
		cout << __FUNCTION__ << endl;
		elm->OperationB();
	}
};

//具体访问者
class ConcreteVisitor2 :public Visitor 
{
public:
	void VisitConcreteElementA(ConcreteElementA* elm)
	{
		cout << __FUNCTION__ << endl;
		elm->OperationA();
	}
	
	void VisitConcreteElementB(ConcreteElementB* elm)
	{
		cout << __FUNCTION__ << endl;
		elm->OperationB();
	}
};

// "ObjectStructure"
class ObiectStructure
{
public: 
	void Attach( Element *elem ){vElem.push_back(elem);}
	void Detach( Element *elem ){vElem.remove(elem);}
	void Accept( Visitor *visitor)
	{
		for (std::list<Element*>::iterator iter=vElem.begin(); iter != vElem.end(); ++iter){
			(*iter)->Accept(visitor);
		}
	}
private:
	list< Element*> vElem;
};

}//end namespace


////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace VisitorPattern;
class ut_VisitorPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_VisitorPattern, Operation)
{
	/*liu.hao
	访问者模式优缺点:
	访问者模式使得易于增加新的操作，仅需增加一个新的访问者即可在一个对象结构上定义一个新的操作，例如添加访问者3
	增加新的ConcreteElement类很困难，如要添加，则基类Visitor接口需要添加新接口，其下所有派生类也必须添加对应实现；
	所以在应用访问者模式时考虑关键的问题是系统的哪个部分会经常变化，
	是作用于对象 结构上的算法呢还是构成该结构的各个对象的类。
	如果老是有新的ConcreteElement类加入进来 的话，Vistor类层次将变得难以维护，或者说这种情况下不适合用访问者模式；
	*/
	
	//创建对象结构
	ObiectStructure* elems = new ObiectStructure();
	elems->Attach(new ConcreteElementA());
	elems->Attach(new ConcreteElementB());
	
	//访问者1
	Visitor *vis1 = new ConcreteVisitor1();
	elems->Accept(vis1);
	cout<<""<<endl;
	
	//访问者2
	Visitor *vis2 = new ConcreteVisitor2();
	elems->Accept(vis2);
	
	//todo:
	//delete xx
}
