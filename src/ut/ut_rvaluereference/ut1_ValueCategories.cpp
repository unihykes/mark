/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

class ut1_ValueCategories : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

/**T&&属于universal&&,
template<class T>
char IsRight(T&& value)
{
    //当T是确定的类型时，T&&为右值引用。如int&& a;
    //当T不确定类型时, 如果被右值初始化，则T&&为右值引用。
    //当T不确定类型时, 如果被左值初始化，则T&&为左值引用。
    return 'R';
}
*/

template<class T>
char IsRight(const T& value)
{
    return 'L';
}

template<class T>
char IsRight(const T&& value)//添加const以禁用universal&&
{
    return 'R';
}

//for test
string& Categories(string& val)
{
    val = "str";
    return val;
}
void func()
{
}

 ///下列表达式是[左值表达式]
struct ncCategoriesObj{static const int n = 0; void fun(){}};
TEST_F(ut1_ValueCategories, L_value)
{
    ///变量、函数或静态数据成员之名，不论其类型, 即使变量的类型是右值引用，由其名字构成的表达式仍是左值表达式；
    {
        int v1 = 0;
        int&& v2 = 100;
        
        MK_PRINT_MSG("v1 -> %c-value", IsRight(v1));//变量名, 变量的类型是int
        MK_PRINT_MSG("v2 -> %c-value", IsRight(v2));//变量名, 变量的类型是右值引用int&&
        MK_PRINT_MSG("std::cin -> %c-value", IsRight(cin));//变量名
        MK_PRINT_MSG("Categories -> %c-value", IsRight(Categories));//函数名
        MK_PRINT_MSG("ncCategoriesObj::n -> %c-value", IsRight(ncCategoriesObj::n)); //数据成员名
    }
    
    ///返回类型是左值引用的函数调用表达式, 
    ///返回类型是左值引用的重载运算符表达式
    {
        string str;
        int i = 0;
        vector<int> v = {1,2,3,4,5};
        auto iter = v.begin();
        MK_PRINT_MSG("Categories(str) -> %c-value", IsRight(Categories(str)));//返回左值引用的函数表达式
        MK_PRINT_MSG("(str = \"test\") -> %c-value", IsRight(str="test"));//返回左值引用的重载运算符
        MK_PRINT_MSG("++iter -> %c-value", IsRight(++iter));//返回左值引用的重载运算符
    }
    
    ///a = b ， a += b ， a %= b，以及所有其他内建的赋值及复合赋值表达式； 
    {
        int a = 0;
        int b = 1;
        MK_PRINT_MSG("a = b -> %c-value", IsRight(a = b));//赋值表达式
        MK_PRINT_MSG("a += b -> %c-value", IsRight(a += b));//复合赋值表达式
        MK_PRINT_MSG("a = b -> %c-value", IsRight(a %= b));//复合赋值表达式
    }
    
    ///++a 及 --a，内建的前置自增与前置自减表达式； 
    {
        int a = 0;
        MK_PRINT_MSG("++a -> %c-value", IsRight(++a));
        MK_PRINT_MSG("--a -> %c-value", IsRight(--a));
    }
    
    ///*p ，内建的间接寻址表达式； 
    {
        int n = 1;
        int* p = &n;
        MK_PRINT_MSG("*p -> %c-value", IsRight(*p));
    }
    
    ///a[n] 及 p[n] ，内建的下标表达式，
    ///(除了 a 为数组右值的情况[C++11 起]) 
    {
        int array[4] = {0,1,2,3};
        int* p = &array[0];
        MK_PRINT_MSG("array[2] -> %c-value", IsRight(array[2]));
        MK_PRINT_MSG("p[2] -> %c-value", IsRight(p[2]));
        using arrType = int[4];
        MK_PRINT_MSG("arrType[2] -> %c-value", IsRight(arrType{0,1,2,3}[2]));///??todo:这里怎么还是左值arrType{0,1,2,3}[2]
    }
    
    ///a.m ,对象成员表达(除了m 为成员枚举符或非静态成员函数,或者a 为右值且 m 为非引用类型的非静态数据成员的情况)
    ///p->m ，内建的指针成员表达式，除了 m 为成员枚举符或非静态成员函数的情况； 
    {
        struct ncObj
        {
            enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
            int n;
            int fun(){return 0;}
        };
        
        ncObj obj;
        MK_PRINT_MSG("obj.n -> %c-value", IsRight(obj.n));
        MK_PRINT_MSG("obj.NC_OBJ_ENUM0 -> %c-value", IsRight(obj.NC_OBJ_ENUM0));//成员枚举符:右值
        MK_PRINT_MSG("obj.fun() -> %c-value", IsRight(obj.fun()));//非静态成员函数:右值
        MK_PRINT_MSG("ncObj().n -> %c-value", IsRight(ncObj().n));///???todo:这里还是左值,貌似与说明不服
        
        ncObj* p = &obj;
        MK_PRINT_MSG("p->n -> %c-value", IsRight(p->n));
        MK_PRINT_MSG("p->NC_OBJ_ENUM0 -> %c-value", IsRight(p->NC_OBJ_ENUM0));
        MK_PRINT_MSG("p->fun() -> %c-value", IsRight(p->fun()));
    }
    
    ///a.*mp ，对象的成员指针表达式，其中 a 是左值且 mp 是指向数据成员的指针； 
    ///p->*mp ，内建的指针的成员指针表达式，其中 mp 是指向数据成员的指针； 
    {
        struct ncObj
        {
            int n;
        };
        
        ncObj obj;
        int ncObj::*p = &ncObj::n;
        MK_PRINT_MSG("obj.*p -> %c-value", IsRight(obj.*p));
        
        ncObj* pObj = &obj;
        MK_PRINT_MSG("pObj->*p -> %c-value", IsRight(pObj->*p));
    }
    
    ///a, b ，内建的逗号表达式，其中 b 是左值； 
    ///a ? b : c ，某些 b 和 c 的三元条件表达式（例如，它们都是同类型左值时，但细节见定义）； 
    {
        int b = 100;
        MK_PRINT_MSG("a,b -> %c-value", IsRight((12, b)));
        MK_PRINT_MSG("a,b -> %c-value", IsRight((true?b:b)));
    }
    
    ///字符串字面量，例如 "Hello, world!"； 
    {
        MK_PRINT_MSG("\"hello world\" -> %c-value", IsRight("hello world"));
    }
    
    ///转换为左值引用类型的转型表达式，例如 static_cast<int&>(x)；
    {
        int x = 100;
        MK_PRINT_MSG("static_cast<int&>(x) -> %c-value", IsRight(static_cast<int&>(x)));
    }
    
    ///函数调用表达式或重载的运算符表达式，其返回类型是到函数的右值引用； (C++11 起)
    {
        
    }
    
    ///转换为函数的右值引用类型的转型表达式，如 static_cast<void (&&)(int)>(x) 。 (C++11 起)
    {
        MK_PRINT_MSG("static_cast<void(&&)()>(func) -> %c-value", IsRight(static_cast<void(&&)()>(func) ));
    }
}


///下列表达式是[纯右值表达式]
TEST_F(ut1_ValueCategories, pR_value)
{
    
}

///下列表达式是[亡值表达式]
TEST_F(ut1_ValueCategories, xR_value)
{
    
}


