/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	备忘录模式
	备忘录模式的关键就是要在不破坏封装行的前提下，捕获并保存一个类的内部状态，这样就可以利用该保存的状态实施恢复操作。
	
	在命令模式中，备忘录模式经常被用来维护可以撤销（Undo）操作的状态。
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;

namespace MementoPattern {

//备忘录
class Memento 
{
	//我们将 Originator 的状态保存在备忘录类中，而将备忘录接口 private 起来，也就达到了封装的功效。
private:
	//这是最关键的地方，将 Originator 为 friend 类，可以访问内部信息，但是其他类不能访问
	friend class Originator;
	Memento(const string& st) {_st = st;}
	void SetState(const string& st) {_st = st;}
	string GetState() {return _st;}
private:
	string _st;
};

//原发器
class Originator 
{
public:
	Originator() {_mt = nullptr;}
	Originator(const string &st) {_st = st;_mt = nullptr;}

	Memento* CreateMemento() {return new Memento(_st);}
	void SetMemento(Memento* mt) {_mt = mt;}
	void RestoreToMemento(Memento* mt) {_st = mt->GetState();}
	
	string GetState() {return _st;}
	void SetState(const string& st) {_st = st;}
	void PrintState() {cout << _st << "..." << endl;}

private:
	string _st;
	Memento *_mt;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
using namespace MementoPattern;
class ut_MementoPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST_F(ut_MementoPattern, Operation)
{
	Originator *o = new Originator();
	o->SetState("old");
	o->PrintState();
	Memento *m = o->CreateMemento();
	o->SetState("new");
	o->PrintState();
	o->RestoreToMemento(m);
	o->PrintState();

	delete o;
	delete m;
}
