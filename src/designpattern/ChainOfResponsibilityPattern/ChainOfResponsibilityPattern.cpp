/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	责任链模式
	责任链模式的最大的一个优点就是给系统降低了耦合性，
	请求的发送者完全不必知道该请求会被哪个应答对象处理，极大地降低了系统的耦合性。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace ChainOfResponsibilityPattern {

class Handle 
{
public:
	virtual ~Handle() { }
	virtual void HandleRequest() = 0;
	
	void SetSuccessor(Handle *succ) {_succ = succ;}
	Handle* GetSuccessor()const {return _succ;}

protected:
	Handle() { _succ = nullptr; }
	Handle(Handle* succ) {_succ = succ;}
private:
	Handle* _succ;
};

class ConcreteHandleA :public Handle 
{
public:
	ConcreteHandleA() { }
	ConcreteHandleA(Handle* succ):Handle(succ) {}

	void HandleRequest() {
		if (this->GetSuccessor() != 0) {
			cout << "ConcreteHandleA--Successor" << endl;//把处理权给后继节点
			GetSuccessor()->HandleRequest();
		}
		else {
			cout << "ConcreteHandleA::HandleRequest" << endl;//没有后继节点，需要自己处理
		}
	}
};

class ConcreteHandleB :public Handle 
{
public:
	ConcreteHandleB() { }
	ConcreteHandleB(Handle* succ):Handle(succ) {}

	void HandleRequest() {
		if (this->GetSuccessor() != 0) {
			cout << "ConcreteHandleB--Successor" << endl;////把处理权给后继节点
			GetSuccessor()->HandleRequest();
		}
		else {
			cout << "ConcreteHandleB::HandleRequest" << endl;//没有后继节点，需要自己处理
		}
	}
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace ChainOfResponsibilityPattern;

class ut_ChainOfResponsibilityPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_ChainOfResponsibilityPattern, Operation)
{
	//ConcreteHandleA 的对象h1拥有一个后继 ConcreteHandleB 的对象 h2,
	//当一个请求到来时候，h1 检查看自己有后继，
	//于是 h1 直接将请求传递给其后继 h2 进行处理，
	//h2 因为没有后继，当请求到来时候，就只有自己提供响应了。
	Handle *h1 = new ConcreteHandleA();
	Handle *h2 = new ConcreteHandleB();
	h1->SetSuccessor(h2);
	
	h1->HandleRequest();
	h2->HandleRequest();

	delete h1;
	delete h2;
}
