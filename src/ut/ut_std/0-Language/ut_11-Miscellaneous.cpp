﻿/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Miscellaneous : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


TEST_F(ut_Miscellaneous, start)
{
    /**
    声明标准库类模板的任何成员函数的完全特化是未定义行为 
    声明标准库类或类模板的任何成员函数模板的完全特化是未定义行为 
    声明标准库类或类模板的任何成员类模板的完全或偏特化是未定未定义行为。
    声明任何标准库变量模板的全特化或偏特化是未定义行为。 
    */
}

//空基类优化
TEST_F(ut_Miscellaneous, Empty_base_optimization)
{
    //允许空的基类子对象大小为零。 
}

TEST_F(ut_Miscellaneous, PImpl)
{
    /**
    "Pointer to implementation" or "pImpl" is a C++ programming technique[1]
    “指向实现的指针”或“ pImpl ”是一种 C++ 编程技巧[1]，
    它将类的实现细节放到分离的、以不透明指针访问的类中，以从其对象表示中移除实现细节： 
    */
}


