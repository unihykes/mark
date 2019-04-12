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
	状态模式
	
	状态模式在实现中，有两个关键点： 
	将 State 声明为 Context 的友元类（friend class），其作用是让 State 访问 Context的 protected 接口 ChangeSate()。
	状态及其子类中的操作都将 Context*传入作为参数，其主要目的是状态类可以通过这个指针调用 Context 中的方法。
		这也是状态模式和 Strategy模式的最大区别所在。
	
	优劣：
	状态模式很好地实现了对象的状态逻辑和动作实现的分离，
	状态逻辑分布在状态的派生类中实现，而动作实现则可以放在 Context 类中实现（这也是为什么状态派生类需要拥有一个指向 Context 的指针）。这使得两者的变化相互独立，改变状态的状态逻辑可以很容易复用 Context 的动作，也可以在不影响状态派生类的前提下创建 Context 的子类来更改或替换动作实现。
	状态模式问题主要是逻辑分散化，状态逻辑分布到了很多的状态的子类中，很难看到整个的状态逻辑图，这也带来了代码的维护问题。

	对比：
	状态模式和策略模式又很大程度上的相似：
	它们都有一个 Context 类，都是通过委托（组合）给一个具有多个派生类的多态基类实现 Context 的算法逻辑。
	两者最大的差别就是状态模式中派生类持有指向 Context 对象的引用，并通过这个引用调用 Context 中的方法，
	但在策略模式中就没有这种情况。因此可以说一个状态实例同样是策略模式的一个实例，反之却不成立。
	实际上状态模式和 Strategy 模式的区别还在于它们所关注的点不尽相同：
	状态模式主要是要适应对象对于状态改变时的不同处理策略的实现，
	而策略则主要是具体算法和实现接口的解耦（coupling），
	Strategy 模式中并没有状态的概念（虽然很多时候有可以被看作是状态的概念），并且更加不关心状态的改变了。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace StatePattern {
class Context;
class State 
{
public:
	virtual void OperationChangeState(Context*) = 0;
	virtual void OperationInterface(Context*) = 0;
	virtual ~State() { }
protected:
	bool ChangeState(Context* con, State *st);
};

class ConcreteStateA :public State
{
public:
	void OperationChangeState(Context* con);
	void OperationInterface(Context* con) {cout << "ConcreteStateA::OperationInterface..." << endl;}
};

class ConcreteStateB :public State 
{
public:
	void OperationChangeState(Context* con);
	void OperationInterface(Context* con) {cout << "ConcreteStateB::OperationInterface..." << endl;}
};

class Context 
{
public:
	Context(State* st) {_st = st;}
	void OperationInterface() {_st->OperationInterface(this);}
	void OperationChangeState() {_st->OperationChangeState(this);}
private:
	friend class State;//表明在 State 类中可以访问 Context 类的 private 字段
	bool ChangeState(State* st) {_st = st;return true;}
	State *_st;
};

bool 
State::ChangeState(Context* con, State *st) 
{
	con->ChangeState(st); 
	return true;
}

void 
ConcreteStateA::OperationChangeState(Context* con) 
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateB());
}

void 
ConcreteStateB::OperationChangeState(Context* con) 
{
	OperationInterface(con);
	this->ChangeState(con, new ConcreteStateA());
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace StatePattern;
class ut_StatePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_StatePattern, Operation)
{
	State *st = new ConcreteStateA();
	Context *con = new Context(st);
	
	con->OperationInterface();
	con->OperationInterface();
	con->OperationInterface();
	
	con->OperationChangeState();
	con->OperationInterface();
	
	delete con;
	delete st;
}