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

class ut_Statements : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

//基于范围的 for 循环 (C++11 起)
TEST_F(ut_Statements, range_for)
{
    /**
    在范围上执行 for 循环。 
    在一个范围的值，例如一个容器中所有元素上操作时，用作传统 for 循环的更加可读的等价物。
    
    首表达式 与 尾表达式 定义如下： 
    若 范围表达式 是数组类型表达式，则 首表达式 为 __range 而 尾表达式 为 (__range + __bound) ，
        其中 __bound 是数组的元素数目（若数组大小未知或拥有不完整类型，则程序不合法） 
    若 范围表达式 是拥有名为 begin 以及 end 成员的类类型 C 的表达式（不管该成员的类型或可见性），
        则 首表达式 为 __range.begin() 且 尾表达式 为 __range.end() ； 
    否则， 首表达式 为 begin(__range) 且 尾表达式 为 end(__range) ，通过参数依赖查找寻找（不进行非 ADL 查找）。 
    */
    
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (const int& i : v) // 以 const 引用访问
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto i : v) // 以值访问， i 的类型是 int
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto& i : v) // 以引用访问， i 的类型是 int&
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (int n : {0, 1, 2, 3, 4, 5}) // 初始化器可以是花括号初始化列表
        std::cout << n << ' ';
    std::cout << '\n';
 
    int a[] = {0, 1, 2, 3, 4, 5};
    for (int n : a) // 初始化器可以是数组
        std::cout << n << ' ';
    std::cout << '\n';
 
    for (int n : a)  
        std::cout << 1 << ' '; // 循环变量不必使用
    std::cout << '\n';
}
