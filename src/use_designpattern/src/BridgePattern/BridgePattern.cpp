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
	桥接模式
	我们将Abstraction与AbstractionImp之间的关系称之为桥接，因为它在抽象类与它的实现之间起到了桥梁作用，使它们可以独立地变化。
	4. 适用性 以下一些情况使用Bridge模式: 
		你不希望在抽象和它的实现部分之间有一个固定的绑定关系。例如这种情况可能是因为，在程序运行时刻实现部分应可以被选择或者切换。 
		类的抽象以及它的实现都应该可以通过生成子类的方法加以扩充。这时Bridge模式使你可以对不同的抽象接口和实现部分进行组合，并分别对它们进行扩充。 
		对一个抽象的实现部分的修改应对客户不产生影响，即客户的代码不必重新编译。
		（C + +）你想对客户完全隐藏抽象的实现部分。在C++中，类的表示在类接口中是可见的。
		正如在意图一节的第一个类图中所示的那样，有许多类要生成。这样一种类层次结构说明你必须将一个对象分解成两个部分。 R u m b a u g h称这种类层次结构为“嵌套的普化” （nested generalizations）。
		你想在多个对象间共享实现（可能使用引用计数），但同时要求客户并不知道这一点。 一个简单的例子便是Coplien的String类[Cop92]，在这个类中多个对象可以共享同一个字符串表示（StringRep）
		
	B r i d g e模式有以下一些优点：
	1) 分离接口及其实现部分 一个实现未必不变地绑定在一个接口上。抽象类的实现可以 在运行时刻进行配置，一个对象甚至可以在运行时刻改变它的实现。 
		将Abstraction与AbstractionImp分离有助于降低对实现部分编译时刻的依赖性，当改变一个 实现类时，并不需要重新编译Abstraction类和它的客户程序。
		为了保证一个类库的不同版本之间的二进制兼容性，一定要有这个性质。 
		另外，接口与实现分离有助于分层，从而产生更好的结构化系统，系统的高层部分仅需 知道Abstraction和AbstractionImp即可。 
	2) 提高可扩充性 你可以独立地对Abstraction和AbstractionImp层次结构进行扩充。 
	3 ) 实现细节对客户透明 你可以对客户隐藏实现细节，例如共享AbstractionImp对象以及相应的引用计数机制（如果有的话）
***************************************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace BridgePattern {

//  定义抽象类的接口
class Abstraction 
{
public:
	virtual void Operation() = 0;
	virtual ~Abstraction() { }
protected:
	Abstraction() { }
};

// 定义实现类的接口，该接口不一定要与Abstraction的接口完全一致；
//事实上这两个 接口可以完全不同。
//一般来讲， AbstractionImp接口仅提供基本操作，而 Abstraction则定义了基于这些基本操作的较高层次的操作。
class AbstractionImp
{
public:
	virtual void Imp_Operation() = 0;
	virtual ~AbstractionImp() { }
protected:
	AbstractionImp() { }
};

//实现AbstractionImp接口并定义它的具体实现
class ConcreteAbstractionImpA :public AbstractionImp 
{
public:
	void Imp_Operation() {cout << "ConcreteAbstractionImpA Imp_Operation..." << endl;}
};

//实现AbstractionImp接口并定义它的具体实现
class ConcreteAbstractionImpB :public AbstractionImp 
{
public:
	void Imp_Operation() {cout << "ConcreteAbstractionImpB Imp_Operation..." << endl;}
};

//扩充由Abstraction定义的接口
class RefinedAbstractionA :public Abstraction 
{
public:
	RefinedAbstractionA(AbstractionImp *imp){_imp = imp;}
	void Operation() 
	{
		cout << "RefinedAbstractionA::Operation()" << endl;
		_imp->Imp_Operation();
	}
	
private:
	AbstractionImp *_imp;
};

//扩充由Abstraction定义的接口
class RefinedAbstractionB :public Abstraction 
{
public:
	RefinedAbstractionB(AbstractionImp *imp){_imp = imp;}
	void Operation() 
	{
		cout << "RefinedAbstractionB::Operation()" << endl;
		_imp->Imp_Operation();
	}
	
private:
	AbstractionImp *_imp;
};

}//namespace end

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//
using namespace BridgePattern;

class ut_BridgePattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_BridgePattern, Operation)
{
	/*
	liu.hao:
	举个例子:
	对一个文件或者目录进行操作：
	ConcreteAbstractionImp可以分为window和linux或其他多种实现；
	RefinedAbstraction可以分为待操作的对象是file或者dir
	*/
	
	
	//调用windows下file的操作
	{
		AbstractionImp *windows_Imp = new ConcreteAbstractionImpA();
		Abstraction *file = new RefinedAbstractionA(windows_Imp);
		file->Operation();
		delete windows_Imp;
		delete file;
	}
	
	//调用linux下file的操作
	{
		AbstractionImp *linux_Imp = new ConcreteAbstractionImpB();
		Abstraction *file = new RefinedAbstractionA(linux_Imp);
		file->Operation();
		delete linux_Imp;
		delete file;
	}
	
	//调用windows下dir的操作
	{
		AbstractionImp *windows_Imp = new ConcreteAbstractionImpA();
		Abstraction *dir = new RefinedAbstractionB(windows_Imp);
		dir->Operation();
		delete windows_Imp;
		delete dir;
	}
	
	//调用linux下dir的操作
	{
		AbstractionImp *linux_Imp = new ConcreteAbstractionImpB();
		Abstraction *dir = new RefinedAbstractionB(linux_Imp);
		dir->Operation();
		delete linux_Imp;
		delete dir;
	}
}
