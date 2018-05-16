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
    typedef int&  lRef;
    typedef int&& rRef;
    
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
    
    fun_collapsing_a(n);//n不是引用类型, 没有触发引用折叠, 此时T&就是int&
    fun_collapsing_a(nL);//nL是左值引用,此时T的类型是int&, 则T&表示到左值引用类型(int&)的左值引用&, [int&]& 折叠为int&
    fun_collapsing_a(nR);//nR是右值引用,此时T的类型是int&&, 则T&表示到右值引用类型(int&&)的左值引用&, [int&&]& 折叠为int&
    //fun_collapsing_a(100);//编译错误,100不是引用类型, 此时T&就是int&, 左值引用无法接受右值,因此编译错误
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
    
    fun_collapsing_b(n);//此处T&&是universal引用,n是左值,等价于fun_collapsing_a(n); param_b是int&类型;
    fun_collapsing_b(nL);//此处T&&是universal引用,nL是左值,等价于fun_collapsing_a(nL); param_b是int&类型;
    fun_collapsing_b(nR);//此处T&&是universal引用,nR是左值,等价于fun_collapsing_a(nR); param_b是int&类型;
    fun_collapsing_b(100);//此处T&&是universal引用,100是右值,因为100不是引用类型,此处T&&就是int&&,没有触发引用折叠; param_b是int&&类型;
    
    ///fun_collapsing_b<int>(n);//编译错误
    fun_collapsing_b<int&>(nL);
    ///fun_collapsing_b<int&&>(nR);编译错误
    fun_collapsing_b<int>(100);
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
    
    //编译错误: n不是引用类型,没有触发引用折叠, 此时const T&&就是const int&&, const int&&不能接受左值,因此编译错误
    ///fun_collapsing_c<int>(n);
    
    //nL是左值引用,此时T的类型是int&, 则const T&&表示到左值引用类型的右值引用, const [int&]&& 折叠为const int&,
    fun_collapsing_c<int&>(nL);
    
    
    //编译错误: nR是右值引用,此时T的类型是int&&, 则const T&&表示到右值引用类型的右值引用, 
    //const [int&&]&& 折叠为const int&&, nR是左值,无法绑定到const右值引用上,编译错误; 
    ///fun_collapsing_c<int&&>(nR);
    
    fun_collapsing_c<int&&>(100);//100不是引用类型,没有触发引用折叠,此时constT&&就是const int&&, 100是右值,成功绑定到param_c上;
}



