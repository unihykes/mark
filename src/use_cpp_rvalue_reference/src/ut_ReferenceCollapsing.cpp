/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)

Time:2018-4

info:

***************************************************************************************************/

#include <markcore.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(ut_ReferenceCollapsing, typedef)
{
    typedef int&  lRef;
    typedef int&& rRef;
    
    int n = 100;
    
    lRef&  r1 = n;
    MK_PRINT("type of r1 is %s", type_id_with_cvr<decltype(r1)>().pretty_name().c_str());
            
    lRef&& r2 = n;
    MK_PRINT("type of r2 is %s", type_id_with_cvr<decltype(r2)>().pretty_name().c_str());
    
    rRef&  r3 = n; 
    MK_PRINT("type of r3 is %s", type_id_with_cvr<decltype(r3)>().pretty_name().c_str());
    
    rRef&& r4 = 1;
    MK_PRINT("type of r4 is %s", type_id_with_cvr<decltype(r4)>().pretty_name().c_str());
}

TEST(ut_ReferenceCollapsing, decltype)
{
    int n = 1;
    int& v1 = n;
    int&& v2 = 100;
    
    MK_PRINT("type of decltype(v1)& is %s", type_id_with_cvr<decltype(v1)&>().pretty_name().c_str());
    MK_PRINT("type of decltype(v1)&& is %s", type_id_with_cvr<decltype(v1)&&>().pretty_name().c_str());
    
    MK_PRINT("type of decltype(v2)& is %s", type_id_with_cvr<decltype(v2)&>().pretty_name().c_str());
    MK_PRINT("type of decltype(v2)&& is %s", type_id_with_cvr<decltype(v2)&&>().pretty_name().c_str());
}




template<typename T> 
void fun_collapsing_a(T& param_a)
{
    MK_PRINT("T is %s , type of param_a is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_a)>().pretty_name().c_str());
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
    MK_PRINT("T is %s , type of param_b is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_b)>().pretty_name().c_str());
}

TEST(ut_ReferenceCollapsing, template2)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    fun_collapsing_b(n);//n是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(nL);//nL是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(nR);//nR是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(100);//100是右值, T推导为int,形参无折叠,为int&&
    cout<<endl;
    
    ///fun_collapsing_b<int>(n);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nL);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nR);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    fun_collapsing_b<int>(100);//T为int,无折叠
    cout<<endl;
    
    fun_collapsing_b<int&>(n);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nL);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nR);//T为int&, 触发引用折叠T&&等价于int&
    ///fun_collapsing_b<int&>(100);//T为int&, 触发引用折叠T&&等价于int&, 编译错误,无法将参数 从“int”转换为“int &” 
    cout<<endl;
    
    ///fun_collapsing_b<int&&>(n);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nL);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nR);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_b<int&&>(100);//T为int&&, 引用折叠T&&等价于int&&
}





template<typename T> 
void fun_collapsing_c(const T&& param_c)
{
    MK_PRINT("T is %s , type of param_c is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_c)>().pretty_name().c_str());
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
    cout<<endl;
    
    
    //fun_collapsing_c<int>(n);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nL);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nR);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_c<int>(100);//T固定为int,不触发引用折叠
    cout<<endl;
    
    
    
    fun_collapsing_c<int&>(n);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const
    fun_collapsing_c<int&>(nL);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const 
    fun_collapsing_c<int&>(nR);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const
    ///fun_collapsing_c<int&>(100);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const,编译错误
    cout<<endl;
    
    ///fun_collapsing_c<int&&>(n);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nL);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nR);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    fun_collapsing_c<int&&>(100);//T为int&&,触发了引用折叠,折叠后等价于const int&&,去掉了const
}



