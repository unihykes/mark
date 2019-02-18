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
	迭代器模式
	迭代器模式也正是用来解决对一个聚合对象的遍历问题，将对聚合的遍历封装到一个类中进行，这样就避免了暴露这个聚合对象的内部表示的可能。 
	
	适用性 
	迭代器模式可用来：
	访问一个聚合对象的内容而无需暴露它的内部表示。
	支持对聚合对象的多种遍历。
	为遍历不同的聚合结构提供一个统一的接口 (即, 支持多态迭代)。
	
	迭代器模式有三个重要的作用： 
	1 ) 它支持以不同的方式遍历一个聚合 复杂的聚合可用多种方式进行遍历。
		例如 , 代码生 成和语义检查要遍历语法分析树。代码生成可以按中序或者按前序来遍历语法分析树。
		迭代 器模式使得改变遍历算法变得很容易 : 
		仅需用一个不同的迭代器的实例代替原先的实例即可。 你也可以自己定义迭代器的子类以支持新的遍历。 
	2) 迭代器简化了聚合的接口 有了迭代器的遍历接口，聚合本身就不再需要类似的遍历接口了。这样就简化了聚合的接口。 
	3) 在同一个聚合上可以有多个遍历每个迭代器保持它自己的遍历状态。因此你可以同时进行多个遍历。
	
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
namespace IteratorPattern {
class Iterator;
typedef int Object;

//聚合:聚合定义创建相应迭代器对象的接口
class Aggregate 
{
public:
	Aggregate(){};
	virtual ~Aggregate(){};
	virtual Iterator* CreateIterator() = 0;
	virtual Object GetItem(int idx) = 0;
	virtual int GetSize() = 0;
};

// 迭代器定义访问和遍历元素的接口。 
class Iterator 
{
public:
	Iterator(){}
	virtual ~Iterator(){}
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Object CurrentItem() = 0;
};

//具体迭代器
class ConcreteIterator :public Iterator 
{
public:
	ConcreteIterator(Aggregate *ag, int idx  = 0)
	{
		_ag = ag;
		_idx = idx;
	}

	void First(){_idx = 0;}
	
	void Next()
	{
		if (_idx < _ag->GetSize()) {
			_idx++;
		}
	}
	bool IsDone()
	{
		return (_idx == _ag->GetSize());
	}
	
	Object CurrentItem()
	{
		return _ag->GetItem(_idx);
	}
	
private:
	Aggregate* _ag;
	int _idx;
};

//具体聚合实现创建相应迭代器的接口，该操作返回ConcreteIterator的一个适当的实例。 
class ConcreteAggreaget :public Aggregate 
{
public:
	enum { SIZE = 3 };
	ConcreteAggreaget()
	{
		for (int i = 0; i < SIZE; i++) {
			_objs[i] = i;
		}
	}
	Iterator* CreateIterator()
	{
		return new ConcreteIterator(this);
	}
	
	Object GetItem(int idx)
	{
		if (idx < this->GetSize()) {
			return _objs[idx];
		}
		else {
			return -1;
		}
	}
	
	int GetSize()
	{
		return SIZE;
	}
private:
	Object _objs[SIZE];
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace IteratorPattern;
class ut_IteratorPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_IteratorPattern, Operation)
{
	Aggregate* ag = new ConcreteAggreaget();
	Iterator *it = ag->CreateIterator();
	
	for (; !(it->IsDone()); it->Next()) {
		cout << it->CurrentItem() << endl;
	}
	delete it;
	delete ag;
}