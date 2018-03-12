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

class ut_Declaration : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


//左值引用,右值引用
TEST_F(ut_Declaration, Lvalue_rvalue)
{
    //c++11
    //引用折叠
    //容许通过模板或 typedef 中的类型操作组成到引用的引用，该情况下应用引用折叠规则：
    //到右值引用的右值引用折叠成右值引用，
    //所有其他组合折叠成左值引用： 
    typedef int&  lref;
    typedef int&& rref;
    int n = 100;
    lref&  r1 = n; // 到左值引用的左值引用, r1 的类型是 int&
    lref&& r2 = n; // 到左值引用的右值引用, r2 的类型是 int&
    rref&  r3 = n; // 到右值引用的左值引用, r3 的类型是 int&
    rref&& r4 = 1; // 到右值引用的右值引用, r4 的类型是 int&&
    
    //int&& r5 = n; //error C2440: “初始化”: 无法从“int”转换为“int &&”
    //int&&& r6 = n;    //error C2529: “r6”: 引用的引用非法 
    //int&&& r7 = n;    //error C2529: “r7”: 引用的引用非法
    //int&&&& r8 = 1;   //error C2529: “r8”: 引用的引用非法
    
    //右值引用可用于为临时对象延长生存期（注意，左值引用亦能延长临时对象生存期，但不能通过左值引用修改他们）： 
    std::string s1 = "Test";
    //std::string&& r1 = s1;           // 错误：不能绑定到左值
    const std::string& r2 = s1 + s1; // okay ：到 const 的左值引用延长生存期
    //r2 += "Test";                    // 错误：不能通过到 const 的引用修改
    std::string&& r3 = s1 + s1;      // okay ：右值引用延长生存期
    r3 += "Test";                    // okay ：能通过到非 const 的引用修改
    std::cout << r3 << '\n';
}

// 转发引用 Forwarding references C++11
TEST_F(ut_Declaration,  Forwarding_references)
{
    //转发引用 Forwarding references
    //todo:
    http://zh.cppreference.com/w/cpp/language/reference
    
}

