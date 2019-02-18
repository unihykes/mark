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

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Functions : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

// 拥有默认参数的简单函数，不返回内容
void f0(const std::string& arg = "world")
{
    std::cout << "Hello, " << arg << '\n';
}
 
// 返回指向 f0 指针的函数
auto fp11() -> void(*)(const std::string&)
{
    return f0;
}
 
// 返回指向 f0 指针的函数， C++11 前风格
void (*fp03())(const std::string&)
{
    return f0;
}

auto ut_Functions_fun() ->bool
{
    return true;
    
}

//初始化类别
TEST_F(ut_Functions, Declaring)
{
    /**
    函数声明
    noptr-declarator ( parameter-list ) cv(可选) ref(可选) except(可选) attr(可选) (1) 
    noptr-declarator ( parameter-list ) cv(可选) ref(可选) except(可选) attr(可选) -> trailing (2) (C++11 起) 
    
    1) 常规函数声明语法
    2) 尾随返回类型声明：尾随返回类型仅允许在最外层函数声明器。此情况下的 decl-specifier-seq 必须包含关键词 auto 
    
    
    尾随返回类型，在返回类型依赖于参数名的情况有用，例如:
    template <class T, class U> auto add(T t, U u) -> decltype(t + u); 
    或在类型复杂的情况，例如在 auto fpif(int)->int(*)(int) 中 
    */
    
    f0();
    fp11()("test");
    fp03()("again");
    ut_Functions_fun();
}


TEST_F(ut_Functions, Lambda)
{
 
}

TEST_F(ut_Functions, inline_specifier)
{
    /**
    声明有 constexpr 的函数是隐式的 inline 函数。 (C++11 起)
    被删除函数是隐式的内联函数：其（被删除的）定义可出现在多于一个翻译单元中。 (C++11 起)
    
    */
}

//运算符重载
TEST_F(ut_Functions, Operator_overloading)
{
    /**
    op 可重载下列 38 (C++20 前)39 (C++20 起) 个运算符之一： 
    + - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=> (C++20 起) && || ++ -- , ->* -> ( ) [ ] 
    
    */
}