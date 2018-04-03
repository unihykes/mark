/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

class ut_RvalueReference : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


class Widget{};
template<typename T>
class Foo
{
public:
    typedef T&& RvalueRefToT;  //RvalueRefToT为universal引用
};

//universal引用： T&&存在类型推导
template<typename T>
void func(T&& param)    //存在类型推导param为universal引用
{};

//非universal引用：形参必须是严格的T&&格式。
template<typename T>
void func(vector<T>&& param){}; //param是一个右值引用，因为当给func传入实参时，T被推导后vector<T>&&的类型是确定的。
                                
//非universal引用：形参必须是严格的T&&格式。
//哪怕被const修饰也不行
template<typename T>
void func(const T&& param);  //param是一个右值引用

//比较universal引用和右值引用
//假设实例化后为:Vector<Widget> v;
template<class T, class Allocator=allocator<T>>
class Vector{

public:
    //虽然push_back的形参符合T&&格式，但不是universal引用因为Vector实例化后，push_back的形参类型就确定下来
    //所以在调用时push_back函数时并不存在类型推导。
    void push_back(T&& x);
    
    //Arg&&存在类型推导，所以args的参数是universal引用。因为参数Args独立于vector的类型参数T，所以每次emplace_back被调用的时候，Args必须被推导。
    template<class ...Args>
    void emplace_back(Args&&...args);
};

TEST_F(ut_RvalueReference, Start)
{
    void f(Widget&& param);   //没有类型推导，param为右值引用
    Widget&& var1 = Widget(); //没有类型推导，var1为右值引用
    
    //1. auto中可能发生引用折叠
    auto&& var2 = var1;   //存在类型推导，var2为universal引用。var2被左值初始化,auto被推导为Widget& &&，折叠后为Widget&
    int w1, w2;
    auto&& v1 = w1;           //v1是universal引用。被左值初始化，所以其类型为int&
    auto&& v2 = std::move(w1);//v2为universal引用，被右值初始化，所以类型为int&&
    
    //2. decltype中可能发生引用折叠：decltype(x)会先取出x的类型，再通过引用折叠规则来定义变量
    decltype(v1)&& v3 = w2;            //v1的类型为int&，所以v3为int& &&，折叠后为int&
    decltype(v2)&& v4 = std::move(w2); //v2的类型为int&&，所以v4为int&& &&，折叠后为int&&
    decltype(w1)&& v5 = std::move(w2); //w1的类型为int，所以v5为int&&
    
    //3. typedef时可能发生的引用折叠
    Foo<int&> f1;  //==>typedef int& && RvalueRefToT; 折叠后：typedef int& RvalueRefToT;
    Foo<int&&> f2; //typedef int&& && RvalueRefToT;   折叠后：typedef int&& RvalueRefToT;
    
    int i = 0;
    int& r1 = i; //ok
    //int& &r2 = r1; //error，不能直接定义引用的引用
    
    typedef int& rint;
    rint r2 = i; //ok，r1为int&类型
    rint &r3 = i; //间接定义引用的引用时，会发生引用折叠。如int& &r3 ==>int& r3
    
    //4. 函数模板参数中可能发生引用折叠
    Widget w;
    func(w);   //用左值w初始化T&&，存在类型推导T为Widget&,传入func后为Widget& &&，折叠后为Widget&，所以param的类型为Widget&，是个左值引用
    func(std::move(w)); //用右值初始化T&&，T被推导为Widget，传入
                        //func后为Widget&&，所以param为右值引用。
    vector<int> v;                
    func(std::move(v));   //调用右值引用的版本：func(vector<T>&& param)。
}



