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

class ut_Classes : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

//成员变量初始化
TEST_F(ut_Classes, date_members)
{
    /**
    非静态数据成员可以用下列二种方式之一初始化： 
    1) 在构造函数的成员初始化器列表中。 
    2) 通过默认成员初始化器，它是简单的包含于成员声明的花括号或等号初始化器，在成员初始化器列表中忽略该成员的情况下使用(C++11)
        若成员拥有默认成员初始化器，并且亦出现于构造函数的成员初始化器列表总，则忽略默认成员初始化器。 
    struct S
    {
        int n = 7;
        std::string s{'a', 'b', 'c'};
        S() // 复制初始化 n ，列表初始化 s
        { }
    };
    
    */
}

//局部类
TEST_F(ut_Classes, Local)
{
    /**
    局部类:
    声明可出现于命名空间作用域中（该情况下它定义通常类）、其他类定义中（该情况下它定义嵌套类）
    及函数体内，该情况下它定义局部类。这种类的名称只存在于函数作用域中，且不可在函数外访问。
        局部类不能拥有静态数据成员 
        局部类的成员函数无链接 
        局部类的成员函数必须完全定义在类体内 
        闭包类型以外的 (C++14 起)局部类不能拥有成员模板 
        局部类不能拥有友元模板 
        局部类不能在类定义内定义友元函数 
        函数内的局部类（含成员函数）能访问同外围函数能访问的名称。 
        局部类不能用作模板实参 (C++11 前)
    */
    
   std::vector<int> v{1,2,3};
    struct Local {
       bool operator()(int n, int m) {
           return n > m;
       }
    };
    std::sort(v.begin(), v.end(), Local()); // C++11 起
    for(int n: v) std::cout << n << ' ';
}

//override 指定符(C++11 起)
TEST_F(ut_Classes, override)
{
    
    /**override 指定符(C++11 起)
    指定一个虚函数覆写另一个虚函数。 
    标识符 override ，若紧随成员函数声明或类定义内成员函数定义语法中的声明器之后使用。 
    
    解释
    在成员函数声明或定义中， override 确保该函数为虚并覆写来自基类的虚函数。若此非真则生成编译错误。 
    override 是在成员函数声明器后使用时拥有特殊含义的标识符：其他情况下它不是保留的关键词。 
    */
    
    struct A
    {
        virtual void foo(){MK_PRINT_MSG("");}
        void bar(){MK_PRINT_MSG("");}
    };
     
    struct B : A
    {
        /** 错误： B::foo 不覆写 A::foo, （签名不匹配 const）
        void foo() const override {MK_PRINT_MSG("");}
        */
        
        // OK ： B::foo 覆写 A::foo
        void foo() override{MK_PRINT_MSG("");}; 
        
        /** 错误： A::bar 非虚
        void bar() override{MK_PRINT_MSG("");}
        */
    };
    
    A* a = new B;
    a->foo();
    a->bar();
    delete a;
}

//final 指定符 (C++11 起)
TEST_F(ut_Classes, final)
{
    /**final 指定符 (C++11 起)
    指定派生类不能覆写虚函数，或类不能被继承。
    应用到成员函数时，标识符 final 在类定义中的成员函数声明或成员函数定义的语法中，立即出现于声明器后。 
    应用到类时，标识符 final 出现在类定义的起始，立即在类名后。 
    
    解释:
    在虚函数声明或定义中使用时， final 确保函数为虚且不可被派生类覆写。若这么做则生成编译时错误。 
    在类定义中使用时， final 指定此类不可出现于另一类的定义的 base-specifier-list 中（换言之，不能派生它）。
    */
    
    struct Base
    {
        virtual void foo(){}
    };
     
    struct A : Base
    {
        void foo() final{} // A::foo 被覆写且是最终覆写
        //void bar() final{} // 错误：非虚函数不能被覆写或是 final
    };
     
    struct B final : A // struct B 为 final
    {
        //void foo() override {} // 错误： foo 不能被覆写，因为它在 A 中是 final
    };
     
    /**
    struct C : B // 错误： B 为 final
    {
    };
    */
}

TEST_F(ut_Classes, Constructors)
{
    //若非静态数据成员拥有 默认成员初始化器且亦出现于成员初始化器列表，则执行成员初始化器列表，而忽略默认成员初始化器：
    
    struct S {
        int n = 42;   // 默认成员初始化器
        string x = "ABCDE";
        S() 
            : n(7) 
        {
        } // 将设置 n 为 7 ，而非 42
    };
    
    
    S s;
    MK_PRINT_MSG("s.n = %d, s.x = %s", s.n, s.x.c_str());
}

//move构造函数 和 move复制运算符
TEST_F(ut_Classes, Move_constructor_assignment)
{
    /** 移动构造函数 C++11
    类 T 的移动构造函数是非模板构造函数，
    其首参数是 T&& 、 const T&& 、 volatile T&& 或 const volatile T&& ，且无其他参数，或剩余参数均有默认值。 
    class_name ( class_name && ) (1) (C++11 起) 
    class_name ( class_name && ) = default; (2) (C++11 起) 
    class_name ( class_name && ) = delete; (3) (C++11 起) 
    */
    
    /**移动赋值运算符 C++11
    类 T 的移动赋值运算符是名为 operator= 并正好接受一个 
    T&& 、 const T&& 、 volatile T&& 或 const volatile T&& 类型参数的非模板非静态成员函数。 
    
    class_name & class_name :: operator= ( class_name && ) (1) (C++11 起) 
    class_name & class_name :: operator= ( class_name && ) = default; (2) (C++11 起) 
    class_name & class_name :: operator= ( class_name && ) = delete; (3) (C++11 起) 
    */
}

//转换构造函数
TEST_F(ut_Classes, Converting_constructor)
{
    /**
    不以指定符 explicit 声明且能以单参数调用 (C++11 前)的构造函数被称为转换构造函数。
    
    */
    
    struct A
    {
        A() { }         // 转换构造函数 (C++11 起)  
        A(int) { }      // 转换构造函数
        A(int, int) { } // 转换构造函数 (C++11 起)
    };
     
    struct B
    {
        explicit B() { }
        explicit B(int) { }
        explicit B(int, int) { }
    };
    
    A a1 = 1;      // OK ：复制初始化选择 A::A(int)
    A a2(2);       // OK ：直接初始化选择 A::A(int)
    A a3{4, 5};    // OK ：直接列表初始化选择 A::A(int, int)
    A a4 = {4, 5}; // OK ：复制列表初始化选择 A::A(int, int)
    A a5 = (A)1;   // OK ：显式转型进行 static_cast ，直接初始化
 
//  B b1 = 1;      // 错误：复制初始化不考虑 B::B(int)
    B b2(2);       // OK ：直接初始化选择 B::B(int)
    B b3{4, 5};    // OK ：直接列表初始化选择 B::B(int, int)
//  B b4 = {4, 5}; // 错误：复制列表初始化选择了 explicit 构造函数 B::B(int, int)
    B b5 = (B)1;   // OK ：显式转型进行 static_cast ，直接初始化
    B b6;          // OK ：默认初始化
    B b7{};        // OK ：直接列表初始化
//  B b8 = {};     // 错误：复制列表初始化选择了 explicit 构造函数 B::B()
}

