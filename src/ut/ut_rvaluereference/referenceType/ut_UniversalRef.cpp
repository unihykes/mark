/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> 
void fun_universal_a(T&& param_a)
{
    MK_PRINT_MSG("type of param_a    is %c-value Ref", std::is_lvalue_reference<decltype(param_a)>::value? 'L':'R');
}

void fun_universal_b(int&& param_b)
{
    MK_PRINT_MSG("type of param_b    is %c-value Ref", std::is_lvalue_reference<decltype(param_b)>::value? 'L':'R');
}

template<typename T> 
void fun_universal_c(const T&& param_c)
{
    MK_PRINT_MSG("type of param_c    is %c-value Ref", std::is_lvalue_reference<decltype(param_c)>::value? 'L':'R');
}

TEST(ut_UniversalRef, template)
{
    
    int n = 10;
    fun_universal_a(n);//传入左值,  T&&存在类型推导, 是universal引用
    fun_universal_a(10);//传入右值, T&&存在类型推导, 是universal引用
    
    //fun_universal_b(n);//编译错误,int&&是右值引用类型,不能接受左值
    fun_universal_b(10);//传入右值
    
    //fun_universal_c(n);//编译错误,const T&&尽管存在类型推导,但他不符合universal规则,因此此处是const右值引用;
    fun_universal_c(10);//传入右值
}

TEST(ut_UniversalRef, auto)
{
    //给auto&& 传入左值
    int n = 100;
    auto&& v1 = n;
    MK_PRINT_MSG("type of v1         is %c-value Ref", std::is_lvalue_reference<decltype(v1)>::value? 'L':'R');
    
    //给auto&& 传入右值
    auto&& v2 = 512;
    MK_PRINT_MSG("type of v2         is %c-value Ref", std::is_lvalue_reference<decltype(v2)>::value? 'L':'R');
}

