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

class utLanguage : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};




//预处理器
TEST_F(utLanguage, define)
{
    /**
    ///#line
    cout<<__LINE__<<endl;//正确行数
    //更改当前行号为777
    #line 777
    cout<<__LINE__<<endl;
    cout<<__LINE__<<endl;
    
    cout<<__FILE__<<":"<<__LINE__<<endl;//D:\monk\src\ut\ut_std\ut_language.cpp:xxx
    //更改当前行号为xxx,并且文件名改为test.cpp
    #line 777 "test.cpp"
    cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:xxx
    cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:xxx
    
    //恢复行号
    #line 211
    */
    
    //# 与 ## 运算符
    #define showlist(...) printf(#__VA_ARGS__)
    showlist(xx\n);            // 展开成 printf("xx\n")
    
    #define FUNCTION(name, a) int fun_##name() { return a;}
}


//直接赋值
TEST_F(utLanguage, assign)
{
    int i = 100;
    int j = {};
    int k = {100};
}


struct mk_Foo
{
    int     i;
    float   f;
    char    c;
};
struct mk_Empty {};
struct alignas(64) mk_Empty64 {};

//查询类型的对齐要求:c++11
TEST_F(utLanguage, alignof)
{
    std::cout << "Alignment of"  "\n"
        "- char             : " << alignof(char)        << "\n"
        "- pointer          : " << alignof(int*)        << "\n"
        "- class mk_Foo     : " << alignof(mk_Foo)      << "\n"
        "- empty class      : " << alignof(mk_Empty)    << "\n"
        "- alignas(64) Empty: " << alignof(mk_Empty64)  << "\n";
}

struct Base {}; // 非多态
struct Derived : Base {};
struct Base2 { virtual void foo() {} }; // 多态
struct Derived2 : Base2 {};


//typeid
TEST_F(utLanguage, typeid)
{
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
    } catch (const std::bad_typeid& e) {
         std::cout << " caught " << e.what() << '\n';
    }
}


//显式类型转换
TEST_F(utLanguage, Conversions)
{
    /**
    ( new_type ) expression (1) 
    new_type ( expression ) (2) 
    new_type ( expressions ) (3) 
    new_type ( ) (4) 
    new_type { expression-list(可选) } (5) (C++11 起) 
    template ( expressions(可选) ) (6) (C++17 起) 
    template { expressions(可选) } (7) (C++17 起)
    */
}

//字符
TEST_F(utLanguage, character)
{
    char ch1 = 'a';
    char ch2 = u8'a';//utf8
    
    char16_t ch3 = u'中';
    char32_t ch4 = U'中';
    
    wchar_t ch5 = L'中';
    int ch6 = '中';
    
    //todo:输出目前不准确
    cout<<ch1 <<endl;
    cout<<ch2 <<endl;
    cout<<ch3 <<endl;
    cout<<ch4 <<endl;
    cout<<ch5 <<endl;
    cout<<ch6 <<endl;
    
    const char* str1 = "abc";
    const char* str2 = u8"abc";//utf8
    
    const char16_t* str3 = u"中文";
    const char32_t* str4 = U"中文";
    
    const wchar_t* str5 = L"中文";
    const char* str6 = R"foo(www)foo";
    
    //todo:输出目前不准确
    cout<<str1 <<endl;
    cout<<str2 <<endl;
    cout<<str3 <<endl;
    cout<<str4 <<endl;
    cout<<str5 <<endl;
    cout<<str6 <<endl;
}

//用户定义字面量 (C++11 起)
// 用作转换
constexpr long double operator"" _deg ( long double deg )
{
    return deg*3.141592/180;
}
// 用于自定义类型
struct mytype
{
    mytype ( unsigned long long m):m(m){}
    unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}
// 用作副效应
void operator"" _print ( const char* str )
{
    std::cout << str;
}

//字面量运算符:C++11
TEST_F(utLanguage, userdefined)
{
    double x = 90.0_deg;
    std::cout << std::fixed << x << '\n';
    mytype y = 123_mytype;
    std::cout << y.m << '\n';
    0x123ABC_print;
}

//左值引用,右值引用
TEST_F(utLanguage, Lvalue_rvalue)
{
    //c++11
    //引用折叠
    //容许通过模板或 typedef 中的类型操作组成到引用的引用，该情况下应用引用折叠规则：
    //到右值引用的右值引用折叠成右值引用，
    //所有其他组合折叠成左值引用： 
    typedef int&  lref;
    typedef int&& rref;
    int n = 100;
    lref&  r1 = n; // 到左值引用的左值引用, r1 的类型是 int&
    lref&& r2 = n; // 到左值引用的右值引用, r2 的类型是 int&
    rref&  r3 = n; // 到右值引用的左值引用, r3 的类型是 int&
    rref&& r4 = 1; // 到右值引用的右值引用, r4 的类型是 int&&
    
    //int&& r5 = n; //error C2440: “初始化”: 无法从“int”转换为“int &&”
    //int&&& r6 = n;    //error C2529: “r6”: 引用的引用非法 
    //int&&& r7 = n;    //error C2529: “r7”: 引用的引用非法
    //int&&&& r8 = 1;   //error C2529: “r8”: 引用的引用非法
    
    
    //转发引用
    //todo:
    
    
    //悬垂引用
    //注意右值引用和到 const 的左值引用能延长临时对象的生存期（参阅临时量生存期的规则和例外）。 
    
}


