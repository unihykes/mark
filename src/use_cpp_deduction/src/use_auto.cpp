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

Time:2018-5

info:
    采用auto进行变量声明时
    auto的类型推导,与函数模版推导类似, 也分为三种情况:
    1.变量类型是指针或者引用,但不是universal引用;
    2.变量类型是universal引用;
    3.变量类型既非指针也非引用;
    
    但是有一个特例,当用于auto声明变量的表达式是用大括号{}时,推导的类型是std::initializer_list<>;
***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

//情况1
TEST(use_auto, func5)
{
    int x =11;
    
    const auto& rx1 = x;//情况1,auto推导为int,所声明的变量类型为const int&
    MK_PRINT("type of rx1 is : %s", type_id_with_cvr<decltype(rx1)>().pretty_name().c_str());
    
    
    auto& rx2 = rx1;//情况1,auto推导为const int,所声明的变量类型为const int&
    MK_PRINT("type of rx2 is : %s", type_id_with_cvr<decltype(rx2)>().pretty_name().c_str());
}

//情况2
TEST(use_auto, func6)
{
    int x = 11;
    const int cx = x;
    
    auto&& ur1 = x; //情况2,auto推导为int&,所声明的变量类型为int&
    MK_PRINT("type of ur1 is : %s", type_id_with_cvr<decltype(ur1)>().pretty_name().c_str());
    
    
    auto&& ur2 = cx;//情况2,auto推导为const int&,所声明的变量类型为 const int&
    MK_PRINT("type of ur2 is : %s", type_id_with_cvr<decltype(ur2)>().pretty_name().c_str());
    
    
    auto&& ur3 = 11;//情况2,auto推导为int,,所声明的变量类型为int&&
    MK_PRINT("type of ur3 is : %s", type_id_with_cvr<decltype(ur3)>().pretty_name().c_str());
}

//情况3
TEST(use_auto, func7)
{
    auto x = 11;        //情况3,auto推导为int,所声明的变量类型为int
    MK_PRINT("type of x is : %s", type_id_with_cvr<decltype(x)>().pretty_name().c_str());
    
    const auto cx = x;//情况3,auto推导为int,所声明的变量类型为const int
    MK_PRINT("type of cx is : %s", type_id_with_cvr<decltype(cx)>().pretty_name().c_str());
}

//特例
TEST(use_auto, func8)
{
    auto v1 = 11;
    MK_PRINT("type of v1 is : %s", type_id_with_cvr<decltype(v1)>().pretty_name().c_str());//int
    
    auto v2(11);
    MK_PRINT("type of v2 is : %s", type_id_with_cvr<decltype(v2)>().pretty_name().c_str());//int
    
    auto v3 = {11};
    //std::initializer_list<int> 
    MK_PRINT("type of v3 is : %s", type_id_with_cvr<decltype(v3)>().pretty_name().c_str());
    
    auto v4{11};
    //vs2015执行结果是int,gcc结果是std::initializer_list<int> 
    MK_PRINT("type of v4 is : %s", type_id_with_cvr<decltype(v4)>().pretty_name().c_str());
}
