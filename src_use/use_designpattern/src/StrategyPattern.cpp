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
	策略模式
	定义一系列的算法,把它们一个个封装起来, 并且使它们可相互替换。本模式使得算法可独 立于使用它的客户而变化。 
	
	适用性
	许多相关的类仅仅是行为有异。“策略”提供了一种用多个行为中的一个行为来配置一 个类的方法。 
	算法使用客户不应该知道的数据。可使用策略模式以避免暴露复杂的、与算法相关的数 据结构。 
	一个类定义了多种行为 , 并且这些行为在这个类的操作中以多个条件语句的形式出现。 
		将相关的条件分支移入它们各自的Strategy类中以代替这些条件语句。 
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace StrategyPattern {
class Strategy 
{
public:
	virtual void Interface() = 0;
	virtual ~Strategy() { }
};

class ConcreteStrategyA :public Strategy 
{
public:
	void Interface() {cout << "ConcreteStrategyA::Interface..." << endl;}
};

class ConcreteStrategyB :public Strategy 
{
public:
	void Interface() {cout << "ConcreteStrategyB::Interface..." << endl;}
};

class Context 
{
public:
	Context(Strategy *stg) 
	{
		_stg = stg;
	}

	void DoAction()
	{
		_stg->Interface();
	}
private:
	Strategy *_stg;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace StrategyPattern;
class ut_StrategyPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_StrategyPattern, Operation)
{
	Strategy *ps = new ConcreteStrategyA();
	Context *pc = new Context(ps);
	pc->DoAction();

	delete pc;
	delete ps;
}
