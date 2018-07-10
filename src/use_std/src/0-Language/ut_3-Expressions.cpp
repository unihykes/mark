/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Expressions : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


//直接赋值
TEST_F(ut_Expressions, direct_assignment)
{
    /**C++11
    若右运算数为花括号初始化器列表
    若表达式 E1 拥有标量类型， 
    则表达式 E1 = {} 等价于 E1 = T{} ，其中 T 是 E1 的类型。 
    表达式 E1 = {E2} 等价于 E1 = T{E2} ，其中 T 是 E1 的类型。 
    若表达式 E1 拥有类类型，则语法 E1 = {args...} 生成对以花括号初始化器列表为参数的赋值运算符的调用，
    然后遵循重载决议的规则选择适合的赋值运算符。
    注意若以某非类类型为参数的非模板赋值运算符可用，则它胜过 E1 = {} 中的移动赋值，
    因为从 {} 到非类类型是恒等转换，它优先于从 {} 到类类型的用户定义转换。 
    */
    int i = 100;
    int j = {};     //C++11
    int k = {100};  //C++11
}

//复合赋值
TEST_F(ut_Expressions, compound_assignment)
{
    int i = 0;
    i += 100;
}

//alignof  C++11
TEST_F(ut_Expressions, alignof)
{
    struct mk_Foo
    {
        int     i;
        float   f;
        char    c;
    };
    
    struct mk_Empty {};
    
    struct alignas(64) mk_Empty64 {};
    
    MK_PRINT_MSG("alignof(char) = %d", alignof(char));
    MK_PRINT_MSG("alignof(int*) = %d", alignof(int*));
    MK_PRINT_MSG("alignof(mk_Foo) = %d", alignof(mk_Foo));
    MK_PRINT_MSG("alignof(mk_Empty) = %d", alignof(mk_Empty));
    MK_PRINT_MSG("alignof(mk_Empty64) = %d", alignof(mk_Empty64));
}

//typeid
TEST_F(ut_Expressions, typeid)
{
    struct Base {}; // 非多态
    struct Derived : Base {};
    struct Base2 { virtual void foo() {} }; // 多态
    struct Derived2 : Base2 {};
    
    
    int myint = 50;
    std::string mystr = "string";
    double *mydoubleptr = nullptr;

    std::cout << "myint has type: " << typeid(myint).name() << '\n'
              << "mystr has type: " << typeid(mystr).name() << '\n'
              << "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';

    // std::cout << myint 为多态类型的泛左值表达式；求值它
    const std::type_info& r1 = typeid(std::cout << myint);
    std::cout << '\n' << "std::cout<<myint has type : " << r1.name() << '\n';

    // std::printf() 不是多态类型的泛左值表达式；不求值
    const std::type_info& r2 = typeid(std::printf("%d\n", myint));
    std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n';

    // 非多态左值为静态类型
    Derived d1;
    Base& b1 = d1;
    std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

    Derived2 d2;
    Base2& b2 = d2;
    std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';

    try {
        // 解引用空指针：对于非多态表达式 OK
        std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n'; 
        // 解引用空指针：对多态左值不 OK
        Derived2* bad_ptr = nullptr;
        std::cout << "bad_ptr points to... ";
        std::cout << typeid(*bad_ptr).name() << '\n';
    } 
    catch (const std::bad_typeid& e) {
         std::cout << " caught " << e.what() << '\n';
    }
}


//运算符优先级
TEST_F(ut_Expressions, Precedence)
{
/**
    优先级 运算符               描述                          结合性
    1       ::                  作用域解析                    从左到右
    
    2       a++   a--           后缀自增与自减
            type() type{}       函数风格转型
            a()                 函数调用
            a[]                 下标
            .   ->              成员访问
    
    3       ++a   --a           前缀自增与自减                从右到左
            +a   -a             一元加与减
            !   ~               逻辑非和逐位非
            (type)              C 风格转型
            *a                  间接（解引用）
            &a                  取址
            sizeof              取大小 
            new   new[]         动态内存分配
            delete   delete[]   动态内存分配
    
    4       .*   ->*            指向成员指针                  从左到右
    
    5       a*b   a/b   a%b     乘法、除法与余数
    
    6       a+b   a-b           加法与减法
    
    7       <<   >>             逐位左移与右移
    
    8       <=>                 三路比较运算符(C++20 起)
    
    9       <   <=              分别为 < 与 ≤ 的关系运算符
            >   >=              分别为 > 与 ≥ 的关系运算符
    
    10      ==   !=             分别为 = 与 ≠ 的关系运算符 
    
    11      a&b                 逐位与 
    
    12      ^                   逐位异或（排除或）
    
    13      |                   逐位或（包含或）
    
    14      &&                  逻辑与 
    
    15      ||                  逻辑或 
    
    16      a?b:c               三元条件[注 2]                 从右到左
            throw               throw 运算符   
            =                   直接赋值（ C++ 类默认提供）    
            +=  -=              以和及差复合赋值    
            *=   /=   %=        以积、商及余数复合赋值 
            <<=   >>=           以逐位左移及右移复合赋值    
            &=   ^=   |=        以逐位与、异或及或复合赋值   
    
    17      ,                   逗号  从左到右
*/
}


//显式类型转换
TEST_F(ut_Expressions, Conversions)
{
    /**
    ( new_type ) expression (1) 
    new_type ( expression ) (2) 
    new_type ( expressions ) (3) 
    new_type ( ) (4) 
    new_type { expression-list(可选) } (5) (C++11 起) 
    */
}


//用户定义转换
TEST_F(ut_Expressions, user_defined_conversion)
{
    struct X {
        //声明用户定义的转换函数，它参与所有隐式和显式转换
        operator int() const { return 7; }
     
        // 声明用户定义的转换函数，它仅参与直接初始化和显式转换。
        explicit operator int*() const { return nullptr; }//(C++11 起) 
     
        //错误：数组运算符不允许出现于 conversion-type-id 中
        //operator int(*)[3]() const { return nullptr; }
        
        using arr_t = int[3];
        operator arr_t*() const { return nullptr; } // OK 若通过 typedef 进行
        
        //operator arr_t () const; // 错误：不允许任何情况下转换到数组
    };
    
    X x;
    int n = static_cast<int>(x);   // OK ：设 n 为 7
    int m = x;                     // OK ：设 m 为 7
 
    int* p = static_cast<int*>(x);  // OK ：设 p 为 null
    //int* q = x; // 错误：无隐式转换
 
    int (*pa)[3] = x;  // OK
}


//字符&&字符串
#include <cstdlib>//for itoa
TEST_F(ut_Expressions, character)
{
    /**
    'c-char' (1)
    u8'c-char' (2) (C++17 起) 
    u 'c-char' (3) (C++11 起) 
    U 'c-char' (4) (C++11 起) 
    L 'c-char' (5) 
    ' c-char-sequence ' (6) 
    
    1) 窄字符字面量或通常字符字面量，例如 'a' 或 '\n' 或 '\13' 。
        这种字面量拥有 char 类型和等 c-char 的表示在执行字符集中的值。
        若 c-char 在执行字符集中不可以单字节表示，则字面量拥有 int 类型和实现定义的值。
    2) UTF-8 字符字面量，例如 u8'a' 。
        这种字面量拥有 char 类型和 c-char 的 ISO 10646 码点值，只要码点值能以单个 UTF-8 代码单元。
        若 c-char 不是基本拉丁或 C0 控制 Unicode 块，则程序为病态。
    3) UCS-2 字符字面量，例如 u'猫' ，但不是 u'🍌' （ u'\U0001f34c' ）。
        这种字面量拥有 char16_t 类型和等于 c-char 在 Unicode 中的值，若它是基本多语言平面的一部分。
        若 c-char 不是基本多语言平面的一部分，则程序为病态。
    4) UCS-4 字符字面量，例如 U'猫' 或 U'🍌' 。
        这种字面量拥有 char32_t 类型和等于 c-char 在 Unicode 中的值。
    5) 宽字符字面量，例如 L'β' 或 L'猫' 。
        这种字面量拥有 wchar_t 类型和等于 c-char 在执行宽字符集中的值。
        若 c-char 不可以执行宽字符集表示（例如在 wchar_t 为 16 位的 Windows 上的非 BMP 值），则字面量的值是实现定义的。
    6) 多字符字面量，例如 'AB' ，拥有 int 类型和实现定义值。
    */
    
    
    size_t len = 0;
    
    //1 窄字符字面量
    char ch1 = 'M';
    auto v1 = '中';
    MK_PRINT_MSG("ch1 = 0x%02x, sizeof(ch1) = %d", ch1, sizeof(ch1));
    MK_PRINT_MSG("v1 = %d = 0x%04x", v1, v1);
    MK_PRINT_MSG("v1 = %d = 0x%02x %02x %02x %02x", v1, ((char*)&v1)[0], ((char*)&v1)[1], ((char*)&v1)[2], ((char*)&v1)[3]);
    char s[33];
    
    //for itoa
    #ifdef __WINDOWS__
        itoa(v1, s, 2);
        MK_PRINT_MSG("s = %s", s);
    #endif
    /**2 UTF-8 字符字面量
    C++17起
    char ch2 = u8'M';
    auto v2 = u8'中';
    MK_PRINT_MSG("sizeof(ch2) = %d", sizeof(ch2));
    MK_PRINT_MSG("sizeof(v2) = %d", sizeof(v2));//int
    */
    
    //3 UCS-2 字符字面量
    char16_t ch3_en = u'M';
    char16_t ch3_zh = u'中';
    const char* ch3_en_char = reinterpret_cast<const char*> (&ch3_en);
    const char* ch3_zn_char = reinterpret_cast<const char*> (&ch3_zh);
    MK_PRINT_MSG("ch3_en = 0x%02x %02x, sizeof(ch3_en) = %d", ch3_en_char[0], ch3_en_char[1], sizeof(ch3_en));//2byte
    MK_PRINT_MSG("ch3_zh = 0x%02x %02x, sizeof(ch3_zh) = %d", ch3_zn_char[0], ch3_zn_char[1], sizeof(ch3_zh));//2byte
    
    //4 UCS-4 字符字面量
    char32_t ch4_en = U'M';
    char32_t ch4_zh = U'中';
    const char* ch4_en_char = reinterpret_cast<const char*> (&ch4_en);
    const char* ch4_zn_char = reinterpret_cast<const char*> (&ch4_zh);
    MK_PRINT_MSG("ch4_en = 0x%02x %02x %02x %02x, sizeof(ch4_en) = %d", ch4_en_char[0], ch4_en_char[1], ch4_en_char[2], ch4_en_char[3], sizeof(ch4_en));//4byte
    MK_PRINT_MSG("ch4_zh = 0x%02x %02x %02x %02x, sizeof(ch4_zh) = %d", ch4_zn_char[0], ch4_zn_char[1], ch4_zn_char[2], ch4_zn_char[3], sizeof(ch4_zh));//4byte
    
    //5 宽字符字面量
    wchar_t ch5_en = L'M';
    wchar_t ch5_zh = L'中';
    const char* ch5_en_char = reinterpret_cast<const char*> (&ch5_en);
    const char* ch5_zn_char = reinterpret_cast<const char*> (&ch5_zh);
    MK_PRINT_MSG("ch5_en = 0x%02x %02x, sizeof(ch5_en) = %d", ch5_en_char[0], ch5_en_char[1], sizeof(ch5_en));//2byte
    MK_PRINT_MSG("ch5_zh = 0x%02x %02x, sizeof(ch5_zh) = %d", ch5_zn_char[0], ch5_zn_char[1], sizeof(ch5_zh));//2byte
    
    //6 多字符字面量,拥有 int类型,最多包含4个字符;
    //auto ch6_1 = 'ABCDE';//编译错误error C2015: 常量中的字符太多
    auto ch6_1 = 'abcd';
    auto ch6_2 = '\1\2\3\4';
    auto ch6_3 = '1234';
    MK_PRINT_MSG("ch6_1 = %d = 0x%02x %02x %02x %02x", ch6_1, ((char*)&ch6_1)[0], ((char*)&ch6_1)[1], ((char*)&ch6_1)[2], ((char*)&ch6_1)[3]);//0x64 63 62 61
    MK_PRINT_MSG("ch6_2 = %d = 0x%02x %02x %02x %02x", ch6_2, ((char*)&ch6_2)[0], ((char*)&ch6_2)[1], ((char*)&ch6_2)[2], ((char*)&ch6_2)[3]);//0x01 02 03 04
    MK_PRINT_MSG("ch6_3 = %d = 0x%02x %02x %02x %02x", ch6_3, ((char*)&ch6_3)[0], ((char*)&ch6_3)[1], ((char*)&ch6_3)[2], ((char*)&ch6_3)[3]);//0x34 33 32 31
}

//字符&&字符串
TEST_F(ut_Expressions, string)
{
    /**
    " (unescaped_character|escaped_character)* " (1) 
    L " (unescaped_character|escaped_character)* " (2) 
    u8 " (unescaped_character|escaped_character)* " (3) (C++11 起) 
    u " (unescaped_character|escaped_character)* " (4) (C++11 起) 
    U " (unescaped_character|escaped_character)* " (5) (C++11 起) 
    prefix(可选) R "delimiter( raw_characters )delimiter" (6) (C++11 起) 
    
        1) 窄多字节字符串字面量。无前缀字符串字面量的类型是 const char[] 。
        2) 宽字符串字面量。 L"..." 字符串字面量的类型是 const wchar_t[] 。
        3) UTF-8 编码的字符串字面量。 u8"..." 字符串字面量的类型是 const char[] 。
        4) UTF-16 编码的字符串字面量。 u"..." 字符串字面量的类型是 const char16_t[] 。
        5) UTF-32 编码的字符串字面量。 U"..." 字符串字面量的类型是 const char32_t[] 。
        6) 生字符串字面量。用于避免转义任何字符。分隔符间的任何内容都成为字符串的一部分。 
            prefix 若存在则拥有与上述相同的含义。
    */
    
    //1 窄多字节字符串字面量, 字符串字面量的类型是 const char[] 
    const char* str1_cn = "abcd";
    const char* str1_zh = "中文";
    MK_PRINT_MSG("str1_cn = %s = 0x%02x %02x %02x %02x", str1_cn, str1_cn[0], str1_cn[1], str1_cn[2], str1_cn[3]);
    MK_PRINT_MSG("str1_zh = %s = 0x%02x %02x %02x %02x", str1_zh, str1_zh[0], str1_zh[1], str1_zh[2], str1_zh[3]);
    
    //2 宽字符串字面量, 符串字面量的类型是 const wchar_t[] 
    const wchar_t* str2_cn = L"ab";
    const wchar_t* str2_zh = L"中文";
    MK_PRINT_MSG("str2_cn = 0x%02x %02x %02x %02x", ((char*)str2_cn)[0], ((char*)str2_cn)[1], ((char*)str2_cn)[2], ((char*)str2_cn)[3]);
    MK_PRINT_MSG("str2_zh = 0x%02x %02x %02x %02x", ((char*)str2_zh)[0], ((char*)str2_zh)[1], ((char*)str2_zh)[2], ((char*)str2_zh)[3]);
    
    //3 UTF-8 编码的字符串字面量, 字符串字面量的类型是 const char[] 。
    const char* str3 = u8"中文";//utf8
    MK_PRINT_MSG("str3 = %s = 0x%02x %02x %02x %02x %02x %02x", str3, ((char*)str3)[0], ((char*)str3)[1], ((char*)str3)[2], ((char*)str3)[3], ((char*)str3)[4], ((char*)str3)[5]);
    
    //4 UTF-16 编码的字符串字面量。字符串字面量的类型是 const char16_t[] 。
    const char16_t* str4 = u"中文";
    MK_PRINT_MSG("str4 = 0x%02x %02x %02x %02x", ((char*)str4)[0], ((char*)str4)[1], ((char*)str4)[2], ((char*)str4)[3]);
    
    //5 UTF-32 编码的字符串字面量。 U"..." 字符串字面量的类型是 const char32_t[] 
    const char32_t* str5 = U"中文";
    MK_PRINT_MSG("str5 = 0x%02x %02x %02x %02x %02x %02x %02x %02x"
                , ((char*)str5)[0], ((char*)str5)[1], ((char*)str5)[2], ((char*)str5)[3]
                , ((char*)str5)[4], ((char*)str5)[5], ((char*)str5)[6], ((char*)str5)[7]);
    
    //6  生字符串字面量。用于避免转义任何字符。分隔符间的任何内容都成为字符串的一部分。 prefix 若存在则拥有与上述相同的含义。
    const char* str6 = R"foo(abcd)foo";
    MK_PRINT_MSG("str6 = %s = 0x%02x %02x %02x %02x", str6, str6[0], str6[1], str6[2], str6[3]);
}

//用户定义字面量 (C++11 起)
constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}
struct mytype
{
    mytype ( unsigned long long m):m(m){}
    unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}
void operator"" _print ( const char* str )
{
    std::cout << str;
}

//字面量运算符:C++11
TEST_F(ut_Expressions, userdefined_literals)
{
    double x = 90.0_deg;
    std::cout << std::fixed << x << '\n';
    
    mytype y = 123_mytype;
    std::cout << y.m << '\n';
    
    0x123ABC_print;
}