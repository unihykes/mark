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

class ut_Exceptions : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


//函数 try 块
int ut_Exceptions_fun(int n = 2) 
try {
    ++n; // 自增函数参数
    throw n;
} 
catch(...) {
   ++n; // n 在作用域中并依旧指代函数参数
   assert(n == 4);
   return n;
}

//函数 try 块
TEST_F(ut_Exceptions, function_try_block)
{
    /**
    若在非委托构造函数成功完成前，委托构造函数以异常退出，则调用此对象的析构函数。 (C++11 起)
    
    若函数 try 块在委托构造函数上，而它调用了成功完成的非委托构造函数，但之后委托构造函数的体抛出，
    则此对象的析构函数将在进入任何函数 try 块的 catch 子句前完成。(C++11 起)
    
    线程的顶层函数的函数 try 块不捕捉从线程局域对象的构造函数和析构函数抛出的异常
    （除了是函数作用域的线程局域对象的构造函数）。
    */
    
    /**
    函数 try 块的基础目的是记录或修改，然后重抛从构造函数中成员初始化器列表抛出的异常。它们稀少地用于析构函数或常规函数。 
    函数 try 块不捕捉从按值传递的函数参数的复制/移动构造函数和析构函数抛出的异常：这些异常在调用方的语境抛出。 
    */
    ut_Exceptions_fun(4);
}
