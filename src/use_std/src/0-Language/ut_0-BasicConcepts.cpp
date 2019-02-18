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

class ut_BasicConcepts : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

///ASCII 码表 ASCII chart
TEST_F(ut_BasicConcepts, ASCII)
{
    for(int i = 32; i != 128; ++i) {
        unsigned char ch = i;
        MK_PRINT_MSG("%d = 0x%02x = %c", i, i, ch);
        ++ch;
    }
}

///名称与标识符 Names and identifiers
TEST_F(ut_BasicConcepts, Names_Identifiers)
{
    /**
    任何位置带有双下划线的标识符都是被保留的；
    以一个下划线跟着一个大写字母开头的标识符是被保留的； 
    以一个下划线开头的标识符在全局命名空间中是被保留的。 
    对等同于关键字的标识符进行 #define 或 #undef，是未定义行为。
    */
}

///类型 Types
TEST_F(ut_BasicConcepts, Types)
{
    /**
    基础类型
        void类型:std::is_void
            void
        nullptr_t 类型:std::is_null_pointer (C++11 起) 
            nullptr_t
        算术类型:std::is_arithmetic 
            浮点类型:std::is_floating_point 
                float
                double
                long double
            整数类型: std::is_integral
                bool类型
                    bool
                字符类型
                    窄字符类型
                        char
                        signed char
                        unsigned char
                    宽字符类型
                        char16_t
                        char32_t
                        wchar_t
                有符号整数类型
                    short int
                    int
                    long int
                    long long int
                无符号类型
                    unsigned short int
                    unsigned int
                    unsigned long int
                    unsigned long long int
    合成类型:std::is_compound
        引用类型:std::is_reference
            左值引用:std::is_lvalue_reference
            右值引用:std::is_rvalue_reference
        指针类型:std::is_pointer 
            指向对象指针
            指向函数指针
        指向成员指针类型:std::is_member_pointer
            指向数据成员指针:std::is_member_object_pointer
            指向成员函数指针:std::is_member_function_pointer
        数组类型:std::is_array 
        函数类型:std::is_function
        枚举类型:std::is_enum
        类类型
            非联合类型:std::is_class 
            联合类型:std::is_union
    */
}


///基础类型:std::is_fundamental
TEST_F(ut_BasicConcepts, Fundamental_types)
{
    MK_PRINT_MSG("sizeof(void*) =  %d", sizeof(void*));
    MK_PRINT_MSG("sizeof(std::nullptr_t) =  %d", sizeof(std::nullptr_t));//c++11
    MK_PRINT_MSG("sizeof(bool) =  %d", sizeof(bool));
    
    //字符
    MK_PRINT_MSG("sizeof(char) =  %d", sizeof(char));
    MK_PRINT_MSG("sizeof(signed char) =  %d", sizeof(signed char));
    MK_PRINT_MSG("sizeof(unsigned char) =  %d", sizeof(unsigned char));
    MK_PRINT_MSG("sizeof(wchar_t) =  %d", sizeof(wchar_t));
    
    //表示 UTF-16 字符的类型,它拥有与 std::uint_least16_t 相同的大小、符号性和对齐，但它是独立的类型。
    MK_PRINT_MSG("sizeof(char16_t) =  %d", sizeof(char16_t));//c++11
    MK_PRINT_MSG("sizeof(std::uint_least16_t) =  %d", sizeof(std::uint_least16_t));
    
    //表示 UTF-32 字符的类型,它拥有与 std::uint_least32_t 相同的大小、符号性和对齐，但它是独立的类型。
    MK_PRINT_MSG("sizeof(char32_t) =  %d", sizeof(char32_t));//c++11
    MK_PRINT_MSG("sizeof(std::uint_least32_t) =  %d", sizeof(std::uint_least32_t));
    
    //以下等价于 short int
    MK_PRINT_MSG("sizeof(short) =  %d", sizeof(short));
    MK_PRINT_MSG("sizeof(short int) =  %d", sizeof(short int));
    MK_PRINT_MSG("sizeof(signed short) =  %d", sizeof(signed short));
    MK_PRINT_MSG("sizeof(signed short int) =  %d", sizeof(signed short int));
    
    //以下等价于 unsigned short int
    MK_PRINT_MSG("sizeof(unsigned short) =  %d", sizeof(unsigned short));
    MK_PRINT_MSG("sizeof(unsigned short int) =  %d", sizeof(unsigned short int));
    
    //以下等价于int
    MK_PRINT_MSG("sizeof(int) =  %d", sizeof(int));
    MK_PRINT_MSG("sizeof(signed) =  %d", sizeof(signed));
    MK_PRINT_MSG("sizeof(signed int) =  %d", sizeof(signed int));
    
    //以下等价于 unsigned int
    MK_PRINT_MSG("sizeof(unsigned) =  %d", sizeof(unsigned));
    MK_PRINT_MSG("sizeof(unsigned int) =  %d", sizeof(unsigned int));
    
    //以下等价于long int
    MK_PRINT_MSG("sizeof(long) =  %d", sizeof(long));
    MK_PRINT_MSG("sizeof(long int) =  %d", sizeof(long int));
    MK_PRINT_MSG("sizeof(signed long) =  %d", sizeof(signed long));
    MK_PRINT_MSG("sizeof(signed long int) =  %d", sizeof(signed long int));
    
    //以下等价于 unsigned long int
    MK_PRINT_MSG("sizeof(unsigned long) =  %d", sizeof(unsigned long));
    MK_PRINT_MSG("sizeof(unsigned long int) =  %d", sizeof(unsigned long int));
    
    //以下等价于 long long int
    MK_PRINT_MSG("sizeof(long long) =  %d", sizeof(long long)); //(C++11)
    MK_PRINT_MSG("sizeof(long long int) =  %d", sizeof(long long int)); //(C++11)
    MK_PRINT_MSG("sizeof(signed long long) =  %d", sizeof(signed long long)); //(C++11)
    MK_PRINT_MSG("sizeof(signed long long int) =  %d", sizeof(signed long long int)); //(C++11)
    
    //以下等价于 unsigned long long int (C++11) 
    MK_PRINT_MSG("sizeof(unsigned long long) =  %d", sizeof(unsigned long long)); //(C++11)
    MK_PRINT_MSG("sizeof(unsigned long long int) =  %d", sizeof(unsigned long long int)); //(C++11)
    
    //浮点类型
    MK_PRINT_MSG("sizeof(float) =  %d", sizeof(float));
    MK_PRINT_MSG("sizeof(double) =  %d", sizeof(double));
    MK_PRINT_MSG("sizeof(long double) =  %d", sizeof(long double));
    
    /**
    数据模型
    每个实现关于基础类型大小所做的选择被统称为数据模型。有四个数据模型广为接受：
    32 位系统： 
        LP32 或 2/4/4 （int 为 16 位， long 和指针为 32 位） 
            Win16 API 
        ILP32 或 4/4/4 （ int 、 long 和指针为 32 位） 
            Win32 API 
            Unix 和类 Unix 系统（ Linux 、 Mac OS X ） 
    64 位系统：
        LLP64 或 4/4/8 （ int 和 long 为 32 位，指针为 64 位） 
            Win64 API 
        LP64 或 4/8/8 （ int 为 32 位， long 和指针为 64 位） 
            Unix 和类 Unix 系统（ Linux 、 Mac OS X ） 
    */
    
    MK_PRINT_MSG("字符值域:  8位有符号(反码), 取值范围:(-127, 127)");
    MK_PRINT_MSG("字符值域:  8位有符号(补码), 取值范围:(-128, 127)");
    MK_PRINT_MSG("字符值域:  8位无符号,       取值范围:(0, 255)");
    MK_PRINT_MSG("字符值域: 16位无符号,       取值范围:(0, 65535 )");
    MK_PRINT_MSG("字符值域: 32位无符号,       取值范围:(0, 1114111(0x10ffff) )");
    
    MK_PRINT_MSG("整数值域: 16位有符号(反码), 取值范围:(-32767, 32767)");
    MK_PRINT_MSG("整数值域: 16位有符号(补码), 取值范围:(-32768, 32767)");
    MK_PRINT_MSG("整数值域: 16位无符号,       取值范围:(0, 65535 )");
    
    MK_PRINT_MSG("整数值域: 32位有符号(反码), 取值范围:(-2,147,483,647, 2,147,483,647)");
    MK_PRINT_MSG("整数值域: 32位有符号(补码), 取值范围:(-2,147,483,648, 2,147,483,647)");
    MK_PRINT_MSG("整数值域: 32位无符号,       取值范围:(0, 4,294,967,295 )");
    
    MK_PRINT_MSG("整数值域: 64位有符号(反码), 取值范围:(-9,223,372,036,854,775,807, 9,223,372,036,854,775,807)");
    MK_PRINT_MSG("整数值域: 64位有符号(补码), 取值范围:(-9,223,372,036,854,775,808, 9,223,372,036,854,775,807)");
    MK_PRINT_MSG("整数值域: 64位无符号,       取值范围:(0, 18,446,744,073,709,551,615 )");
}


/// 对象 Object
TEST_F(ut_BasicConcepts, Object)
{
    /**
    对象表示与值表示:
    对于一个 T 类型的对象，其对象表(object representation)是和它开始于同一个地址，
    且长度为 sizeof(T) 的一段 unsigned char 类型的对象序列;
    对于TriviallyCopyable类型，其值表示是对象表示的一部分，
    这意味着复制该对象在存储中所占据的字节就足以产生另一个具有相同值的对象;
    */
    
    struct temp_Object
    {
        char c;     // 1 个字节的值
                    // 3 个字节的填充
        float f;    // 4 个字节的值
        bool operator==(const temp_Object& arg) const { // 基于值的相等性
            return c == arg.c && f == arg.f;
        }
    };
    
    assert(sizeof(temp_Object) == 8);
    temp_Object obj1 = {'a', float(3.14)};
    temp_Object obj2 = obj1;
    reinterpret_cast<char*>(&obj1)[2] = 'b'; // 改变其第二个字节
    assert(obj1 == obj2); // 值并未变化
    
    /**
    对齐:
    每个对象类型都具有被称为对齐要求（alignment requirement）的性质，
    它是一个整数（类型为 std::size_t，总为 2 的幂），表示这个类型的对象所能分配的相邻地址之间的字节数。
    */
    MK_PRINT_MSG("alignof(temp_Object) =  %d", alignof(temp_Object));
}

///作用域 Scope 
TEST_F(ut_BasicConcepts, Scope)
{
}


///生存期 Lifetime
TEST_F(ut_BasicConcepts, Lifetime)
{
    /**
    临时对象的生存期，可以通过绑定到 const 左值引用或右值引用 (C++11 起)而得以扩展;
    对数组元素初始化时所使用的默认构造函数的默认实参所进行的求值，
    其所创建的临时对象的生存期，将在数组的下一个元素的初始化开始之前终止;
    */
    
    //非类对象和类对象在生存期终止方面的规则的差别(存储期的终止和与构造相反顺序)：
    struct ut_BasicConcepts_Lifetime
    {
        int* p;
        ~ut_BasicConcepts_Lifetime() 
        {
            MK_PRINT_MSG("p = %d", *p);// 如果 n 比 a 活得长，将会打印 123, 实际测试结果的确打印了
        }
    };
    
    ut_BasicConcepts_Lifetime a;
    int n = 123; // 如果 n 不比 a 活得长，则这会被优化掉（死存储）
    a.p = &n;
}


/// 定义与 ODR   Definitions and ODR
TEST_F(ut_BasicConcepts, Definitions)
{
    /**
    在 C++ 中，为相同类型的声明所使用的源代码记号必须是相同的：
    如果一个.cpp文件定义了 struct S { int x; }; 
    而另一个.cpp文件定义了 struct S { int y; };
    将它们链接起来之后的程序的行为就是未定义的。
    */
}

