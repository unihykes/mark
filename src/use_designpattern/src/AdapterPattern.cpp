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
	适配器模式
	
	别名：包装器 Wrapper
	
	动机：有时，为复用而设计的工具箱类不能够被复用的原因仅仅是因为它的接口与专业应用领 域所需要的接口不匹配。
	
	适用性：
	以下情况使用Adapter模式：
	•你想使用一个已经存在的类，而它的接口不符合你的需求。 
	•你想创建一个可以复用的类，该类可以与其他不相关的类或不可预见的类（即那些接口可能不一定兼容的类）协同工作。 
	•（仅适用于对象Adapter）你想使用一些已经存在的子类，但是不可能对每一个都进行子类化以匹配它们的接口。对象适配器可以适配它的父类接口
	
	结构：
	类适配器使用多重继承对一个接口与另一个接口进行匹配。
	对象适配器依赖于对象组合。
	
	参与者
	•Target:定义Client使用的与特定领域相关的接口。
	Client:与符合Target接口的对象协同。
	Adaptee:定义一个已经存在的接口，这个接口需要适配。
	Adapter:对Adaptee的接口与Target接口进行适配;
	
	与其他模式区别:
	适配器Adapter为它所适配的对象提供了一个不同的接口。相反，代理Proxy提供了与它的实体相同的接口;
***************************************************************************************************/

#include <gtest/gtest.h>
#include <iostream>
using namespace std;

namespace AdapterPattern {
////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

//client可见接口
class Target
{
public:
	virtual void Request() {cout << "Target::Request()" << endl;}
	virtual ~Target() { }
};

//待适配类:可能是第三方接口
class Adaptee 
{
public:
	void SpecificRequest() {cout << "Adaptee::SpecificRequest()" << endl;}
};

//对象模式适配器
//备注1:Adapter对Target是public继承，接口继承；
//备注2:Adapter对Adaptee是组合调用
class Adapter1 :public Target
{
public:
	Adapter1(Adaptee* ade) {_ade = ade;}
	void Request() {_ade->SpecificRequest();}
private:
	Adaptee*	_ade;
};

//类模式适配器
//备注1:Adapter对Target是public继承，接口继承；
//备注2:Adapter对Adaptee是private继承，实现继承；
class Adapter2 :public Target, private Adaptee 
{
public:
	Adapter2() {}
	void Request() {this->SpecificRequest();}
};

}//namespace end

////////////////////////////////////////////////////////////////////////////////////////////////////
// ut
//
class ut_AdapterPattern : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

TEST(ut_AdapterPattern, Operation)
{
	//对象模式
	{
		AdapterPattern::Adaptee* adaptee = new AdapterPattern::Adaptee();
		AdapterPattern::Target* adapter = new AdapterPattern::Adapter1(adaptee);

		adapter->Request();

		delete adapter;
		delete adaptee;
	}
	
	//类模式适配器
	{
		AdapterPattern::Target* adapter = new AdapterPattern::Adapter2();
		adapter->Request();

		delete adapter;
	}
}
