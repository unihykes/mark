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

//左/右值以及左/右值引用
struct ncTest
{
    int m;
    
    ncTest(){cout << "ncTest()" << endl;}
    ncTest(const ncTest& t){cout << "ncTest(const ncTest&)" << endl;}
    ncTest(ncTest&& t){cout << "ncTest(ncTest&&)" << endl;}
    ~ncTest(){cout << "~ncTest()" << endl;}
};

ncTest&& ReturnRvalueRef()
{
    return ncTest(); //不安全！返回局部对象的引用（用于演示）！
}

ncTest ReturnRvalue()
{
    return ncTest(); 
}

TEST_F(ut_RvalueReference, Start)
{
    //1. 左、右值判断
    int i = 0;
    int&& ri = i++; //i++为右值，表达式返回是i的拷贝，是个匿名变量。故为右值。
    int&  li = ++i; //++i返回的是i本身，是具名变量，故为左值。
    
    int* p = &i;
    int& lp = *p;    //*p是左值，因为可以取*p的地址，即&(*p);
    int* && rp = &i; //取地址表达式结果是个地址值，故&i是纯右值。
    
    int&& xi1 = std::move(i); //std::move(i)是个xvalue
    int&& xi2 = static_cast<int&&>(i); // static_cast<int&&>(i)是个xvalue
    
    auto&& fn = [](int x){ return x * x; }; //lambda表达式是右值,可以用来初始化右值引用
    cout << std::is_rvalue_reference<decltype(fn)>::value << endl; //1
    
    ncTest t;
    int& rm1  = t.m; //由于t是左值，而m为普通成员变量，所以m也为左值。
    int&& rm2 = ncTest().m; //由于Test()是个右值，所以m也是右值
    
    int ncTest::*pm = &ncTest::m; //定义指向成员变量的指针，指向non-static member data;
    //int&& rm3 = t.*pm; //error，由于t是左值，*pm也是左值，不能用来初始化右值引用。
    int& rm3 = t.*pm;    //ok
    
    ///windows下编译错误:error C2440: “初始化”: 无法从“int”转换为“int &&”
    ///int&& rm4 = ncTest().*pm; //ok，Test()是临时变量，为右值。所以*pm也是右值
    
    //2. 左/右值引用的初始化
    int a;
    int&  b = a;  //ok
    //int&& b = a;  //error，右值引用只能绑定到右值上    
    
    ncTest&& t1 = ReturnRvalue();  //返回值是个临时对象(右值) 被绑定到t1上，使其“重获新生”，
                                 //生命期与t1一样。
    ncTest   t2 = ReturnRvalue();  //返回值是个临时对象(右值)，用于构造t2，之后该临时对象
                                 //就会马上被释放。
    //ncTest&  t3 = ReturnRvalue();    //普通左值引用不能绑定到右值
    const ncTest& t4 = ReturnRvalue(); //常左值引用是个“万能引用”，可以绑定到右值    
}



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

TEST_F(ut_RvalueReference, Start2)
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



