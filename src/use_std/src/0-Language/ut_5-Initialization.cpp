/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Initialization : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


//初始化类别
TEST_F(ut_Initialization, Initialization)
{
    //值初始化，例如 
    std::string s1{}; 
    
    //直接初始化，例如 
    std::string s2("hello"); 
    
    //复制初始化，例如 
    std::string s3 = "hello"; 
    
    //列表初始化，例如 
    std::string s4{'a', 'b', 'c'}; 
    
    //聚合初始化，例如 
    char a[3] = {'a', 'b'}; 
    
    //引用初始化，例如 
    char& c = a[0]; 
}


//值初始化
TEST_F(ut_Initialization, Value_initialization)
{
    /**
    T(); (1) 
    new T (); (2) 
    Class::Class(...) : member() { ... } (3) 
    T object {}; (4) (C++11 起)
    T{}; (5) (C++11 起) 
    new T {}; (6) (C++11 起) 
    Class::Class(...) : member{} { ... } (7) (C++11 起) 
    */
    
    
    //从 C++11 起，值初始化无用户提供构造函数，并拥有用户提供的类类型成员的类，会在调用成员的构造函数前对成员清零： 
    struct A
    {
        int i;
        A() { } // 用户提供的默认构造函数，不初始化 i
    };
     
    struct B { A a; }; // 隐式定义的默认构造函数
    std::cout << B().a.i << '\n'; // 值初始化 B 临时量 // C++03 中令 b.a.i 为未初始化, // C++11 中设 b.a.i 为零
    std::cout<< B{}.a.i << '\n';// （注意 C++11 中 B{}.a.i 保留 b.a.i 为未初始化，但因为不同原因
    // ：在 DR1301 后的 C++11 中， B{} 是聚合初始化，它值初始化拥有用户提供构造函数的 A）
}

//聚合初始化
TEST_F(ut_Initialization, Aggregate_initialization)
{
    /**
    T object {arg1, arg2, ...}; (C++11 起) 
    */
    
    std::string ars[] = {std::string("one"), // 复制初始化
                         "two",              // 转换，然后复制初始化
                         {'t', 'h', 'r', 'e', 'e'} }; // 列表初始化
}

//列表初始化 (C++11 起)
TEST_F(ut_Initialization, List_initialization)
{

}

//引用初始化
TEST_F(ut_Initialization, Reference_initialization)
{

}

//静态非局部初始化
TEST_F(ut_Initialization, Static_non_local_initialization)
{

}

//动态非局部初始化
TEST_F(ut_Initialization, Dynamic_non_local_initialization)
{

}

