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
    //std::string&& s2 = s1;           // 错误：不能绑定到左值
    const std::string& s2 = s1 + s1; // okay ：到 const 的左值引用延长生存期
    //s2 += "Test";                    // 错误：不能通过到 const 的引用修改
    std::string&& s3 = s1 + s1;      // okay ：右值引用延长生存期
    s3 += "Test";                    // okay ：能通过到非 const 的引用修改
    std::cout << s3 << '\n';
}

// 转发引用 Forwarding references C++11
TEST_F(ut_Declaration,  Forwarding_references)
{
    /**转发引用 Forwarding references (C++11 起)
    1) 声明为到无 cv 限定的右值引用的同一函数模板的模板参数的函数参数： 
    2) auto&& ，除非从花括号初始化器列表推导。 
    */
}

// 枚举声明
enum ut_Declaration_Color_1
{
    red = 100, 
    green = 200, 
    blue = 201
};

enum class ut_Declaration_Color_2
{
    red = 100, 
    green = 200, 
    blue = 201
};

enum ut_Declaration_Color_3 : int16_t
{
    red2 = 100, 
    green2 = 200, 
    blue2 = 201
};

enum class ut_Declaration_Color_4 : char
{
    red2 = 'r', 
    green2 = 'g', 
    //blue2 = 129, // 枚举数的值“129”不能表示为“char”，值是“-127” 
    blue2 = 127, // C++11 允许尾随逗号
};

enum class ut_Declaration_Color_5 : bool
{
    red2 = 0, 
    green2 = 1, 
    blue2 = 0, // C++11 允许尾随逗号
};

//枚举声明
TEST_F(ut_Declaration,  enumeration)
{
    //枚举声明
}


//属性指定符序列(C++11 起)
TEST_F(ut_Declaration,  Attributes)
{
    /**属性指定符序列(C++11 起)
    为类型、对象、代码等引入实现定义的属性。 
    
    */
    
}
