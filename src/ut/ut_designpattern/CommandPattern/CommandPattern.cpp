/***************************************************************************************************
Author:liu.hao

Time:2017-12

info:
	命令模式
	命令模式通过将请求封装到一个对象（Command）中，
	并将请求的接受者存放到具体的 Concrete命令类中（Receiver）中，
	从而实现调用操作的对象和操作的具体实现者之间的解耦。 
	
	命令模式结构图中，将请求的接收者（处理者）放到命令的具体子类ConcreteCommand命令中，
	当请求到来时（Invoker 发出 Invoke 消息激活命令对象），
	ConcreteCommand命令将处理请求交给 Receiver 对象进行处理。 
	
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace CommandPattern {

class Reciever 
{
public:
	void Action() {cout << "Reciever::Action..." << endl;}
};

class Command 
{
public:
	virtual ~Command() { }
	virtual void Excute() = 0;
};

class ConcreteCommand :public Command 
{
public:
	ConcreteCommand(Reciever *rev) 
	{
		_rev = rev;
	}
	
	void Excute() 
	{
		_rev->Action();
	}
private:
	Reciever *_rev;
};

class Invoker 
{
public:
	Invoker(Command* cmd) 
	{
		_cmd = cmd;
	}
	void Invoke() 
	{
		_cmd->Excute();
	}

private:
	Command *_cmd;
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//

using namespace CommandPattern;

class ut_CommandPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_CommandPattern, Operation)
{
	//实际上，命令模式关键就是提供一个抽象的命令类，并将执行操作封装到 Command类接口中，
	//命令类中一般就是只是一些接口的集合，并不包含任何的数据属性
	Reciever *rev = new Reciever();
	Command* cmd = new ConcreteCommand(rev);
	Invoker *inv = new Invoker(cmd);
	inv->Invoke();

	delete rev;
	delete cmd;
	delete inv;
	/*
	命令模式将调用操作的对象和知道如何实现该操作的对象解耦。
	Invoker 对象根本就不知道具体的是那个对象在处理 Excute操作（当然要知道是命令类别的对象，也仅此而已）。
	在命令要增加新的处理操作对象很容易，我们可以通过创建新的继承自命令的子类来实现这一点。
	命令模式可以和 Memento 模式结合起来，支持取消的操作。
	*/
}
