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

Time:2018-3

info:
    [纯右值表达式]
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


TEST(ut_pRvalue, pRvalue1)
{
    /// （除了字符串字面量之外的）字面量，例如 42 、 true 或 nullptr ；
    /// 匿名变量/对象
    {
        MK_PRINT_MSG("42                    is %c-value", IsRight(42));
        MK_PRINT_MSG("true                  is %c-value", IsRight(true));
        MK_PRINT_MSG("nullptr               is %c-value", IsRight(nullptr));
        MK_PRINT_MSG("string()              is %c-value", IsRight(string("")));
    }
}

TEST(ut_pRvalue, pRvalue2)
{
    /// 函数调用或重载运算符表达式，其返回类型是非引用，例如 str.substr(1, 2)、str1 + str2 或 it++ ； 
    {
        MK_PRINT_MSG("pow(2,2)              is %c-value", IsRight(pow(2,2)));
        
        vector<int> v = {1,2,3,4,5};
        auto iter = v.begin();
        MK_PRINT_MSG("iter++                is %c-value", IsRight(iter++));
    }
}

TEST(ut_pRvalue, pRvalue3)
{
    /// a++ 与 a--，内建的后置自增与后置自减表达式； 
    {
        int a = 100;
        MK_PRINT_MSG("a++                   is %c-value", IsRight(a++));
        MK_PRINT_MSG("a--                   is %c-value", IsRight(a--));
    }
}

TEST(ut_pRvalue, pRvalue4)
{
    /// a + b 、 a % b 、 a & b 、 a << b ，以及其他所有内建的算术表达式； 
    /// a && b 、 a || b 、 !a ，内建的逻辑表达式；
    /// a < b 、 a == b 、 a >= b 以及其他所有内建的比较表达式； 
    /// &a，内建的取地址表达式； 
    {
        int a = 10;
        int b = 2;
        
        MK_PRINT_MSG("a+b                   is %c-value", IsRight(a+b));
        MK_PRINT_MSG("a%%b                   is %c-value", IsRight(a%b));
        MK_PRINT_MSG("a&b                   is %c-value", IsRight(a&b));
        MK_PRINT_MSG("a<<b                  is %c-value", IsRight(a<<b));
        
        MK_PRINT_MSG("a&&b                  is %c-value", IsRight(a&&b));
        MK_PRINT_MSG("a||b                  is %c-value", IsRight(a||b));
        MK_PRINT_MSG("!a                    is %c-value", IsRight(!a));
        
        MK_PRINT_MSG("a<b                   is %c-value", IsRight(a<b));
        MK_PRINT_MSG("a==b                  is %c-value", IsRight(a==b));
        MK_PRINT_MSG("a>=b                  is %c-value", IsRight(a>=b));
        
        MK_PRINT_MSG("&a                    is %c-value", IsRight(&a));
    }
}

TEST(ut_pRvalue, pRvalue5)
{
    /// a.m，对象成员表达式，其中 m 是成员枚举符或非静态成员函数
    /// p->m，内建的指针成员表达式，其中 m 为成员枚举符或非静态成员函数
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    {
        ncObj obj;
        MK_PRINT_MSG("obj.NC_OBJ_ENUM0      is %c-value", IsRight(obj.NC_OBJ_ENUM0));//成员枚举符:右值
        MK_PRINT_MSG("obj.fun()             is %c-value", IsRight(obj.fun()));//非静态成员函数表达式:右值
        
        ncObj* p = &obj;
        MK_PRINT_MSG("p->NC_OBJ_ENUM0      is %c-value", IsRight(p->NC_OBJ_ENUM0));
        MK_PRINT_MSG("p->fun()             is %c-value", IsRight(p->fun()));
    }
}

TEST(ut_pRvalue, pRvalue6)
{
    /// a.*mp，对象的成员指针表达式，其中 mp 是指向成员函数的指针 
    /// p->*mp，内建的指针的成员指针表达式，其中 mp 是指向成员函数的指针 
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    {
        //void (ncObj::*pFun)() = &ncObj::fun;
        decltype(&ncObj::fun) pFun = &ncObj::fun;
        
        ncObj obj;
        MK_PRINT_MSG("obj.*pFun             is %c-value", IsRight((obj.*pFun)()) ); //这里如果函数返回void会编译错误,但是返回void的函数表达式也是右值
        
        ncObj* pObj = &obj;
        MK_PRINT_MSG("pObj->*pFun           is %c-value", IsRight((pObj->*pFun)()));
    }
}

TEST(ut_pRvalue, pRvalue7)
{
    /// a, b，内建的逗号表达式，其中 b 是右值； 
    /// a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）；  
    {
        int a = 100;
        MK_PRINT_MSG("a,b                   is %c-value", IsRight((a++, 12)));
        MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?32:12)));
    }
}

TEST(ut_pRvalue, pRvalue8)
{    
    /// 转换为非引用类型的转型表达式，例如 static_cast<double>(x)、std::string{} 或 (int)42； 
    {
        short x = 100;
        MK_PRINT_MSG("static_cast<int>(x)   is %c-value", IsRight(static_cast<int>(x)));
        MK_PRINT_MSG("std::string{}         is %c-value", IsRight(std::string{}));
        MK_PRINT_MSG("(int)42               is %c-value", IsRight((int)42));
    }
}

TEST(ut_pRvalue, pRvalue9)
{
    /// this 指针； 
    {
        struct ncObj
        {
            void fun()
            {
                MK_PRINT_MSG("this                       is %c-value", IsRight(this));
            }
        };
        
        ncObj().fun();
    }
}

TEST(ut_pRvalue, pRvalue10)
{
    /// 枚举项; 
    {
        enum ncObjEnum
        {
            NC_OBJ_ENUM0,
            NC_OBJ_ENUM1
        };
        
        MK_PRINT_MSG("NC_OBJ_ENUM0          is %c-value", IsRight(NC_OBJ_ENUM0));
    }
}
    
TEST(ut_pRvalue, pRvalue11)
{
    /// Lambda 表达式，例如 [](int x){ return x * x; } 
    {
        
        MK_PRINT_MSG("[](int x){ return x * x; }  is %c-value", IsRight([](int x){ return x * x; }) );
        
        auto&& lam = [](int x){ return x * x; };
        bool isRValueRef = std::is_rvalue_reference<decltype(lam)>::value;
        MK_PRINT_MSG("isRValueRef = %d", isRValueRef);
    }
}
