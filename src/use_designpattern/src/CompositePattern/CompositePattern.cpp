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
	组合模式
	在开发中，我们经常可能要递归构建树状的组合结构，组合模式则提供了很好的解决方案。
	
	对比：
	组合模式通过和装饰模式有着类似的结构图，
	但是组合模式旨在构造类，而 Decorator 模式重在不生成子类即可给对象添加职责。
	装饰模式重在修饰，而组合模式重在表示。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
using namespace std;

namespace CompositePattern {

class Component 
{
public:
	virtual ~Component() { }
	
	virtual void Operation() { }
	virtual void Add(const Component& com) { }
	virtual void Remove(const Component& com) { }
	virtual Component* GetChild(int index) {return 0;}
};

class Composite :public Component 
{
public:
	void Add(Component* com) 
	{
		_coms.push_back(com);
	}

	void Operation() 
	{
		for (auto com : _coms)
			com->Operation();
	}

	void Remove(Component* com) 
	{
		//_coms.erase(&com);
	}

	Component* GetChild(int index) 
	{
		return _coms[index];
	}

private:
	std::vector<Component*> _coms;
};

class Leaf :public Component 
{
public:
	void Operation()
	{
		cout << "Leaf::Operation..." << endl;
	}
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace CompositePattern;

class ut_CompositePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_CompositePattern, Operation)
{
	//组合模式在实现中有一个问题就是要提供对于子节点（Leaf）的管理策略，
	//这里使用的是 STL 中的 vector，可以提供其他的实现方式，如数组、链表、Hash 表等。
	
	Leaf *leaf = new Leaf();
	leaf->Operation();
	Composite *com = new Composite();
	com->Add(leaf);
	com->Operation();
	Component *leaf_ = com->GetChild(0);
	leaf_->Operation();

	delete leaf;
	delete com;
}