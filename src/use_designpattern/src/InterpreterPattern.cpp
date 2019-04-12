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
	解释器模式
	一些应用提供了内建（Build-In）的脚本或者宏语言来让用户可以定义他们能够在系统中进行的操作。
	解释器模式的目的就是使用一个解释器为用户提供一个一门定义语言的语法表示的解释器，
	然后通过这个解释器来解释语言中的句子。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;

namespace InterpreterPattern {
	
class Context 
{ 
};

class Expression 
{
public:
	virtual ~Expression() { }
	virtual void Interpret(const Context& c) = 0;
};

class TerminalExpression :public Expression 
{
public:
	TerminalExpression(const string& statement) 
	{
		_statement = statement;
	}

	void Interpret(const Context& c) 
	{
		cout << this->_statement << " -- TerminalExpression" << endl;
	}

private:
	string _statement;
};

class NonterminalExpression :public Expression 
{
public:
	NonterminalExpression(Expression* expression, int times) 
	{
		_expression = expression;
		_times = times;
	}

	void Interpret(const Context& c) 
	{
		for (int i = 0; i < _times; i++) {
			_expression->Interpret(c);
		}
	}

private:
	Expression *_expression;
	int _times;
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace InterpreterPattern;
class ut_InterpreterPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_InterpreterPattern, Operation)
{
	//解释器模式中使用类来表示文法规则，因此可以很容易实现文法的扩展。
	//另外对于终结符我们可以使用享元模式来实现终结符的共享。
	Context *c = new Context();
	Expression *tp = new TerminalExpression("echo");
	Expression *ntp = new NonterminalExpression(tp, 4);
	ntp->Interpret(*c);

	delete ntp;
	delete tp;
	delete c;
}
