/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:
    [亡值表达式]
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


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


TEST(ut_xRvalue, xRvalue1)
{
    /// 函数调用或重载运算符表达式，其返回类型为右值引用，例如 std::move(x) ； 
    {
        int x = 100;
        MK_PRINT_MSG("std::move(x)          is %c-value", IsRight(std::move(x)));
    }
    
    /// a[n]，内建的下标表达式，其操作数之一是数组右值； 
    {
        using arrType = int[4];
        MK_PRINT_MSG("arrType[2]            is %c-value", IsRight(arrType{0,1,2,3}[2]));///??todo:这里怎么还是左值arrType{0,1,2,3}[2]
    }
    
    /// a.m，对象成员表达式，其中 a 是右值且 m 是非引用类型的非静态数据成员； 
    {
        struct ncObj
        {
            enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
            int n;
            int fun(){return 0;}
        };
        &ncObj().n;
        MK_PRINT_MSG("ncObj().n             is %c-value", IsRight(ncObj().n));///经在vs2015测试, 这里是左值(C++11起)
    }
    
    /// a.*mp，对象的成员指针表达式，其中 a 为右值且 mp 为指向数据成员的指针； 
    {
        struct ncObj
        {
            int n;
            int fun(){return 0;}
        };
        
        int ncObj::*pn = &ncObj::n;
        MK_PRINT_MSG("obj.*pn               is %c-value", IsRight(ncObj().*pn));///经vs2015测试,这里是L-value
    }
    
    /// a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）； 
    {
        int a = 100;
        MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?std::move(a):std::move(a))));
    }
    
    /// 转换为对象的右值引用类型的转型表达式，例如 static_cast<char&&>(x)； 
    {
        char x = 'x';
        MK_PRINT_MSG("static_cast<char&&>(x)          is %c-value", IsRight(static_cast<char&&>(x)));
    }
    
    
}
