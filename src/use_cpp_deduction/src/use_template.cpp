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
    对于:函数模板
    T的类型推导,不仅依赖实参expr的类型,还依赖形参ParamType的类型,
    具体分三种情况:
    1.形参类型ParamType具有指针或引用类型,但不是universal引用;
    2.形参类型ParamType是一个universal引用;
    3.形参类型ParamType既非指针也非引用;

    template<typename T>
    void func(ParamType param)
    {
    }
    
    func(expr);
***************************************************************************************************/

#include <markcore.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////////////////////////////////////
///
//

/** 1.形参类型ParamType具有指针或引用类型,但不是universal引用;
    推导规则:
    若实参expr具有引用类型,先将引用部分忽略;
    然后,对实参expr和形参ParamType类型执行模式匹配,决定T的类型;
*/
template<typename T>
void func1(T& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func1)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func1(x);   //实参类型为int,        T类型推导为int,       形参类型int&
    func1(cx);  //实参类型为const int,  T类型推导为const int, 形参类型const int&
    func1(rx);  //实参类型为const int&, T类型推导为const int, 形参类型const int&
}

template<typename T>
void func2(const T& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func2)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func2(x);   //实参类型为int,        T类型推导为int, 形参类型const int&
    func2(cx);  //实参类型为const int,  T类型推导为int, 形参类型const int&
    func2(rx);  //实参类型为const int&, T类型推导为int, 形参类型const int&
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///
//
/** 2.形参类型ParamType是一个universal引用;
    推导规则:
    如果expr是个左值,T和ParamType都会被推导为左值引用;
    如果expr是个右值,则应用常规规则(同情形1);
*/

template<typename T>
void func3(T&& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func3)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func3(x);   //实参x是左值,       T类型推导为int&, 形参类型int&
    func3(cx);  //实参cx是左值,      T类型推导为const int&, 形参类型const int&
    func3(rx);  //实参rx是左值,      T类型推导为const int&, 形参类型const int&
    func3(11);  //实参11是右值,      T类型推导为int,        形参类型int&&
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///
//
/** 3.形参类型ParamType既非指针也非引用(按值传递);
    推导规则:
    若expr具有引用类型,则忽略其引用部分;
    忽略引用性之后,若expr是个const对象或volatile对象,也忽略之;
*/

template<typename T>
void func4(T param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func4)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    func4(x);   //T类型推导为int, 形参类型int
    func4(cx);  //T类型推导为int, 形参类型int
    func4(rx);  //T类型推导为int, 形参类型int
    func4(11);  //T类型推导为int, 形参类型int
}
