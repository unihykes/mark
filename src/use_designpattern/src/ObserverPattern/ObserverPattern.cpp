/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	观察者模式
	观察者模式应该可以说是应用最多、影响最广的模式之一，
	因为 观察者的一个实例 Model/View/Control（MVC）结构在系统开发架构设计中有着很重要的地位和意义，MVC实现了业务逻辑和表示层的解耦。
	当然，MVC 只是 观察者模式的一个实例。观察者模式要解决的问题为：
	建立一个一（Subject）对多（Observer）的依赖关系，并且做到当"一"变化的时候，依赖这个"一"的多也能够同步改变。
	
	最常见的一个例子就是：
	对同一组数据进行统计分析时候，我们希望能够提供多种形式的表示（例如以表格进行统计显示、柱状图统计显示、百分比统计显示等）。
	这些表示都依赖于同一组数据，我们当然需要当数据改变的时候，所有的统计的显示都能够同时改变。观察者模式就是解决了这一个问题。 
	
	目标 Subject 提供依赖于它的观察者的注册（Attach）和注销（Detach）操作，
	并且提供了使得依赖于它的所有观察者同步的操作（Notify）。
	观察者则提供一个 Update 操作，注意这里的 观察者的 Update 操作并不在 观察者改变了 Subject 目标状态的时候就对自己进行更新，
	这个更新操作要延迟到 Subject 对象发出 Notify 通知所有观察者进行修改（调用 Update）。 
	
	观察者模式也称为发布－订阅（publish-subscribe），目标就是通知的发布者，观察者则是通知的订阅者（接受通知）。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <string>
using namespace std;

namespace ObserverPattern {

class Subject;
////////////////////////////////////////////////////////////////////////////////////////////////////

class Observer 
{
public:
	virtual ~Observer(){}
	virtual void Update(Subject* sub) = 0;
	virtual void PrintInfo() = 0;
	
protected:
	Observer(){}
	string _st;
};

class Subject 
{
public:
	virtual ~Subject(){/*_obvs.clear();*/}
	
	virtual void SetState(const string& st) = 0;
	virtual string GetState() = 0;
	
	virtual void Attach(Observer* obv)
	{
		_obvs.push_front(obv);
	}
	virtual void Detach(Observer* obv)
	{
		if (obv != nullptr) {
			_obvs.remove(obv);
		}
	}
	virtual void Notify()
	{
		for (auto obv : _obvs) {
			obv->Update(this);
		}
	}
	
protected:
	Subject(){}
private:
	list<Observer*> _obvs;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class ConcreteSubject :public Subject 
{
public:
	string GetState(){return _st;}
	void SetState(const string& st){_st = st;}
private:
	string _st;
};

class ConcreteObserverA :public Observer 
{
public:
	ConcreteObserverA(Subject* sub)
	{
		_sub = sub;
		_sub->Attach(this);
	}

	~ConcreteObserverA()
	{
		_sub->Detach(this);
		//if (_sub != nullptr) {
		//	  delete _sub;
		//}
	}
	virtual Subject* GetSubject()
	{
		return _sub;
	}
	
	void Update(Subject* sub)
	{
		_st = sub->GetState();
		PrintInfo();
	}
	void PrintInfo()
	{
		cout << "ConcreteObserverA::PrintInfo\t" << _sub->GetState() << endl;
	}
	
private:
	Subject *_sub;
};

class ConcreteObserverB :public Observer 
{
public:
	ConcreteObserverB(Subject* sub)
	{
		_sub = sub;
		_sub->Attach(this);
	}

	~ConcreteObserverB()
	{
		_sub->Detach(this);
		//if (_sub != nullptr) {
		//	  delete _sub;
		//}
	}
	virtual Subject* GetSubject()
	{
		return _sub;
	}
	
	void Update(Subject* sub)
	{
		_st = sub->GetState();
		PrintInfo();
	}
	void PrintInfo()
	{
		cout << "ConcreteObserverB::PrintInfo\t" << _sub->GetState() << endl;
	}
	
private:
	Subject *_sub;
};

}//end namespace

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace ObserverPattern;
class ut_ObserverPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_ObserverPattern, Operation)
{
	Subject *sub = new ConcreteSubject();
	Observer *a1 = new ConcreteObserverA(sub);
	Observer *a2 = new ConcreteObserverA(sub);
	
	Observer *b1 = new ConcreteObserverB(sub);
	Observer *b2 = new ConcreteObserverB(sub);
	
	sub->SetState("old");
	sub->Notify();
	
	sub->SetState("new");
	sub->Notify();

	delete a1;
	delete a2;
	delete b1;
	delete b2;
	
	delete sub;
}
