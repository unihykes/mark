/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(ut_ReferenceCollapsing, typedef)
{
    typedef int&  lRef;
    typedef int&& rRef;
    
    int n = 100;
    
    lRef&  r1 = n; // r1 的类型是 int&, 到左值引用类型(lRef)的左值引用&,折叠为左值引用
    MK_PRINT_MSG("type of r1        is %c-value Ref", std::is_lvalue_reference<lRef&>::value? 'L':'R');
     
    lRef&& r2 = n; // r2 的类型是 int&, 到左值引用类型(lRef)的右值引用&&,折叠为左值引用
    MK_PRINT_MSG("type of r2        is %c-value Ref", std::is_lvalue_reference<lRef&&>::value? 'L':'R');
    
    rRef&  r3 = n; // r3 的类型是 int&, 到右值引用类型(rRef)的左值引用&,折叠为左值引用
    MK_PRINT_MSG("type of r3        is %c-value Ref", std::is_lvalue_reference<rRef&>::value? 'L':'R');
    
    rRef&& r4 = 1; // r4 的类型是 int&&, 到右值引用类型(rRef)的右值引用&&,折叠为右值引用
    MK_PRINT_MSG("type of r4        is %c-value Ref", std::is_lvalue_reference<rRef&&>::value? 'L':'R');
}

TEST(ut_ReferenceCollapsing, decltype)
{
    int n = 1;
    int& v1 = n;
    int&& v2 = 100;
    
    
    MK_PRINT_MSG("type is %c-value Ref", std::is_lvalue_reference<decltype(v1)&>::value? 'L':'R');//L
    MK_PRINT_MSG("type is %c-value Ref", std::is_lvalue_reference<decltype(v1)&&>::value? 'L':'R');//L
    
    MK_PRINT_MSG("type is %c-value Ref", std::is_lvalue_reference<decltype(v2)&>::value? 'L':'R');//L
    MK_PRINT_MSG("type is %c-value Ref", std::is_lvalue_reference<decltype(v2)&&>::value? 'L':'R');//R
}




template<typename T> 
void fun_collapsing_a(T& param_a)
{
    MK_PRINT_MSG("type of param_a    is %c-value Ref", std::is_lvalue_reference<decltype(param_a)>::value? 'L':'R');
}

TEST(ut_ReferenceCollapsing, template1)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    fun_collapsing_a(n);//T推导为int,无需折叠,T&相当于int&
    fun_collapsing_a(nL);//T推导为int,无需折叠,T&相当于int&
    fun_collapsing_a(nR);//T推导为int,无需折叠,T&相当于int&
    //fun_collapsing_a(100);T推导为int,无需折叠,T&相当于int&, 编译错误,左值引用无法接受右值
}





template<typename T> 
void fun_collapsing_b(T&& param_b)
{
    MK_PRINT_MSG("type of param_b    is %c-value Ref", std::is_lvalue_reference<decltype(param_b)>::value? 'L':'R');
}

TEST(ut_ReferenceCollapsing, template2)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    fun_collapsing_b(n);//T推导为int&,无折叠, 此处T&&是universal引用,因此可接受左值和右值
    fun_collapsing_b(nL);//T推导为int,无折叠, 此处T&&是universal引用,因此可接受左值和右值
    fun_collapsing_b(nR);//T推导为int,无折叠, 此处T&&是universal引用,因此可接受左值和右值
    fun_collapsing_b(100);//T推导为int,无折叠, 此处T&&是universal引用,因此可接受左值和右值
    
    
    ///fun_collapsing_b<int>(n);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nL);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nR);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    fun_collapsing_b<int>(100);//T为int,无折叠
    
    
    fun_collapsing_b<int&>(n);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nL);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nR);//T为int&, 触发引用折叠T&&等价于int&
    ///fun_collapsing_b<int&>(100);//T为int&, 触发引用折叠T&&等价于int&, 编译错误,无法将参数 从“int”转换为“int &” 
    
    
    ///fun_collapsing_b<int&&>(n);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nL);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nR);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_b<int&&>(100);//T为int&&, 引用折叠T&&等价于int&&
}





template<typename T> 
void fun_collapsing_c(const T&& param_c)
{
    MK_PRINT_MSG("type of param_c    is %c-value Ref", std::is_lvalue_reference<decltype(param_c)>::value? 'L':'R');
}

TEST(ut_ReferenceCollapsing, template3)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    
    ///fun_collapsing_c(n);//T推导为int, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_c(nL);//T推导为int, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_c(nR);//T推导为int, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_c(100);//T推导为int 
    
    
    
    //fun_collapsing_c<int>(n);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nL);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nR);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_c<int>(100);//T固定为int,不触发引用折叠
    
    
    
    
    fun_collapsing_c<int&>(n);//T为int&,触发了引用折叠,折叠后const T&& 等价于const int&, 
    fun_collapsing_c<int&>(nL);//T为int&,触发了引用折叠,折叠后const T&& 等价于const int&, 
    fun_collapsing_c<int&>(nR);//T为int&,触发了引用折叠,折叠后const T&& 等价于const int&, 
    ///fun_collapsing_c<int&>(100);//T为int&,触发了引用折叠,折叠后const T&& 等价于const int&, 编译错误, 无法将参数 1 从“int”转换为“int &”,暂未搞明白
    
    
    
    
    ///fun_collapsing_c<int&&>(n);//T为int&&,触发了引用折叠,折叠后等价于const int&&, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nL);//T为int&&,触发了引用折叠,折叠后等价于const int&&, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nR);//T为int&&,触发了引用折叠,折叠后等价于const int&&, 编译错误,无法左值绑定到右值
    fun_collapsing_c<int&&>(100);//T为int&&,触发了引用折叠,折叠后等价于const int&&
}



