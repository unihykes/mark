/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	享元模式
	享元模式（Flyweight）就是维护一个对象实例的共享池，实现对象实例的共享和回收利用。
	
	享元模式在实现过程中主要是要为共享对象提供一个存放的"仓库"（对象池），
	这里是通过 C++ STL 中 Vector 容器，当然就牵涉到 STL 编程的一些问题。
	另外应该注意的就是对对象"仓库"（对象池）的管理策略（查找、插入等），
	这里是通过直接的顺序遍历实现的，当然我们可以使用其他更加有效的索引策略，
	例如 Hash 表的管理策略，当时这些细节已经不是享元模式本身要处理的了。
	
	对比：
	我们在状态模式和策略模式中会产生很多的对象，因此我们可以通过享元模式来解决这个问题。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace FlyweightPattern {

class Flyweight 
{
public:
	Flyweight(string state)
		:_state(state) 
	{
	}
	virtual ~Flyweight() { }
	
	virtual void Operation(const string&state) { }
	string GetState()const { return _state; }
private:
	string _state;
};

class ConcreteFlyweight :public Flyweight 
{
public:
	ConcreteFlyweight(string state)
		:Flyweight(state) 
	{
		cout << "ConcreteFlyweight Build..." << state << endl;
	}

	void Operation(const string& state) 
	{
		cout << "ConcreteFlyweight " << GetState() << " \\ " << state << endl;
	}
};

//lyweightFactory 拥有一个管理、存储对象的"仓库"（或者叫对象池），
//GetFlyweight（）消息会遍历对象池中的对象，如果已经存在则直接返回给 Client，否则创建一个新的对象返回给 Client。
class FlyweightFactory 
{
public:
	Flyweight *GetFlyweight(std::string key) 
	{
		for (auto fly : _flys) {
			if (fly->GetState() == key) {
				cout << "already created by users..." << endl;
				return fly;
			}
		}
		Flyweight *fn = new ConcreteFlyweight(key);
		_flys.push_back(fn);
		return fn;
	}
private:
	std::vector<Flyweight*> _flys;
};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace FlyweightPattern;

class ut_FlyweightPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_FlyweightPattern, Operation)
{
	FlyweightFactory *fc = new FlyweightFactory();
	
	//我们可以为将对象的状态分为"外部状态"和"内部状态"，
	//将可以被共享（不会变化）的状态作为内部状态存储在对象中，例如下面的:hello、world
	//而外部对象我们可以在适当的时候将外部对象最为参数传递给对象;例如下面的:aaa,bbb,ccc
	Flyweight *fw1 = fc->GetFlyweight("hello");
	fw1->Operation("aaa");
	
	Flyweight *fw2 = fc->GetFlyweight("world");
	fw2->Operation("bbb");
	
	Flyweight *fw3 = fc->GetFlyweight("hello");
	fw3->Operation("ccc");
	
	delete fw1;
	delete fw2;
	//delete fw3;
	delete fc;
}
