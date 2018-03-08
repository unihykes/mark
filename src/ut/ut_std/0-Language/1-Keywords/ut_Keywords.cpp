/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

template<class T> class Y { void mf() { } }; // 模板定义
template class Y<int>;              //显式实例化定义
template void Y<double>::mf();      //显式实例化定义
extern template class Y<string>;    //显式实例化声明

constexpr int factorial(int n)
{
    return n <= 1? 1 : (n * factorial(n - 1));
}

template<typename... Ts>
constexpr auto make_array(Ts&&... ts)-> std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
    return { std::forward<Ts>(ts)... };
}

namespace mk{
    namespace mk_utLanguage1
    {
        struct A
        {
            int _val;
            A():_val(10){}
        };
    }
    
    //当你需要管理多个版本的类库的时候，可以用inline修饰namespace，来达到指定默认版本的目的，
    inline namespace mk_utLanguage2
    {
        struct A
        {
            int _val;
            A():_val(23){}
        };
    }
}
//命名空间别名
namespace mk_lan1 = mk::mk_utLanguage1;
namespace mk_lan2 = mk::mk_utLanguage2;


//模版特化
template<class T>
using Vec = vector<T, std::allocator<T>>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Keywords : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

///C++ 关键词 C++ Keywords 
TEST_F(ut_Keywords, Keywords)
{
    /**
    标注(1):C++11 中含义改变或添加新含义。注意：关键词 export 亦为模块 TS 所用。 
    标注(2):C++17 中含义改变。 
    TM TS:实验性特性, 事务性内存技术规范 Transactional Memory Technical Specification, ISO/IEC TS 19841:2015 的一部分 (TM TS) 
    */
    #if 0
        alignas (C++11 起)          do                      reinterpret_cast
        alignof (C++11 起)          double                  register(2)
        and                         dynamic_cast            requires (C++20 起)
        and_eq                      else                    return
        asm                         enum                    short
        atomic_cancel (TM TS)       explicit                signed
        atomic_commit (TM TS)       export(1)               sizeof(1)
        atomic_noexcept (TM TS)     extern(1)               static
        auto(1)                     false                   static_assert (C++11 起)
        bitand                      float                   static_cast
        bitor                       for                     struct(1)
        bool                        friend                  switch
        break                       goto                    synchronized (TM TS)
        case                        if                      template
        catch                       import (模块 TS)        this
        char                        inline(1)               thread_local (C++11 起)
        char16_t (C++11 起)         int                     throw
        char32_t (C++11 起)         long                    true
        class(1)                    module (模块 TS)        try
        compl                       mutable(1)              typedef
        concept (C++20 起)          namespace               typeid
        const                       new                     typename
        constexpr (C++11 起)        noexcept (C++11 起)     union
        const_cast                  not                     unsigned
        continue                    not_eq                  using(1)
        co_await (协程 TS)          nullptr (C++11 起)      virtual
        co_return (协程 TS)         operator                void
        co_yield (协程 TS)          or                      volatile
        decltype (C++11 起)         or_eq                   wchar_t
        default(1)                  private                 while
        delete(1)                   protected               xor
                                    public                  xor_eq
    #endif
}

///分类
TEST_F(ut_Keywords, Sort)
{
    #if 0
        ///0.去除TM TS, C++20, C++17,asm
        
        //1.常见的不解释:
        bool break case catch char const const_cast continue do double dynamic_cast else enum explicit
        false float for friend goto if int long namespace new operator private protected public
        reinterpret_cast register return short signed static static_cast switch template this throw true try
        typedef typeid typename union unsigned virtual void volatile wchar_t while
        
        ///2.替代运算符, 为了一些欧、非、拉等非英语国家保留的关键字, windows VS对此C++标准不兼容;
        and     and_eq  //用作 && 和&= 的替用 
        bitand  bitor   //用作 &  和|  的替用
        not     not_eq  //用作 !  和!= 的替用 
        or      or_eq   //用作 || 和|= 的替用
        xor     xor_eq  //作为 ^  和^= 的替用
        compl           //用作 ~       的替用 
        
        /// 3.C++11 中含义改变或添加新含义
        auto        class       default     delete          export      extern
        inline      mutable     sizeof      struct          using
        
        ///4.c++11新增
        alignas     alignof     char16_t    char32_t        constexpr
        decltype    noexcept    nullptr     static_assert   thread_local
    #endif
}

///C++11中有修改
TEST_F(ut_Keywords, Modify_In_Cplusplus11)
{
    /**auto
    auto 自动存储期指定符 (C++11 前)
    auto 指定符 (C++11 起)
    */
    //auto int x = 10;  //C++98在此处等价于int x = 10;表示x变量为当前代码段的局部变量;
                        //C++11 起编译错误:“auto”不能与任何其他类型说明符组合
    auto lambda = [](int x) { return x + 3; };
    
    
    /**class 
    //C++11中,可以定义有作用域枚举, 没有从有作用域枚举项到整数类型的隐式转换，尽管 static_cast 可用于获得枚举项的数值。 
    */
    enum class Color 
    {
        red, 
        green = 20, 
        blue 
    };
    Color r = Color::blue;
    // int n = r; // 错误：无有作用域枚举到 int 的转换
    int n = static_cast<int>(r); // OK, n = 21
    
    
    /**default
    显式默认化的函数定义：作为令编译器为类生成[特殊成员函数]的显式指令。(C++11 起) 
    特殊成员函数是仅有能被默认化的函数,即使用 = default 替代函数体定义,具体指的是以下几种:
    默认构造函数 
    复制构造函数 
    移动构造函数 (C++11 起) 
    复制赋值运算符 
    移动赋值运算符 (C++11 起) 
    析构函数 
    */
    class A
    {
    public:
        A()=default;
        A(const string& str){}
    private:
    };
    
    A aa1;
    A aa2("str");
    aa2 = aa1;
    
    
    /**delete
    1.因为后随delete的一对方括号始终转译为 delete数组形式，故在delete后的拥有空捕获列表的 lambda 表达式必须用括号环绕。 
    2.表示被删除的函数,若取代函数体使用特殊语法 = delete ; 则函数定义为被删除。调用被删除函数编译错误;
    */
    //delete []{return new int; }(); // 剖析错误
    delete ([]{return new int; })(); // OK
    struct sometype
    {
        void* operator new(std::size_t) = delete;
        void* operator new[](std::size_t) = delete;
    };
    //sometype* p = new sometype; // 编译错误：尝试引用已删除的函数 sometype::operator new
    
    
    /**export
    1.用于标注一个模板定义被导出，这允许在其它翻译单元中声明，但不定义同一模板。(C++11 前)
        export template < parameter-list > class-declaration (C++11 前)
        export 是一个可选的修饰符，声明模板为被导出（用于类模板时，它声明所有成员为导出）。
        带有实例化被导出模板的文件不需要包含其定义：有声明就足够了。 
        export 的实现稀少而且在细节上互不一致。 
    2.不使用，并保留该关键词。(C++11 起)
    */
    
    
    /**extern
    显示模板实例化声明: extern template class|struct template-name < argument-list > ; (C++11 起) 
    显式实例化声明（ extern 模板）跳过隐式实例化的步骤：
        使用其他地方提供的显式实例化定义替代此外情况下产生的隐式实例化（若不存在这种实例化则产生链接错误）。
        这可用于减少编译时间，通过显式声明所有模板实例化于使用模板的源文件中，并在剩余文件中显式定义它。
    */
    //参考template<class T> class Y 模版类;
    
    /**inline
    当你需要管理多个版本的类库的时候，可以用inline修饰namespace，来达到指定默认版本的目的，
    */
    //A a1;     //编译错误: 未声明的标识符
    mk::mk_utLanguage1::A a2;//使用mk_utLanguage1
    cout<<a2._val<<endl;
    mk::A a3;   //默认使用 mk_utLanguage2
    cout<<a3._val<<endl;
    mk::mk_utLanguage2::A a4;//显示指定 mk_utLanguage2
    cout<<a4._val<<endl;
    
    
    /**mutable
    移除以[=]捕获参数 const 限定的 lambda 声明器 (C++11 起) 
        在调用时执行 lambda 表达式体。
        访问变量时，访问其被捕获的副本（对于以复制捕获的实体）或原对象（对于以引用捕获的实体）。
        除非于 lambda 表达式使用关键词 mutable ，
        否则函数调用表达式为 const 限定，且以复制捕获的对象从此operator() 的内部不可修改。
        函数调用运算符非 volatile 限定且非虚。 
    */
    {
        int a = 1, b = 1, c = 1;
        auto m1 = [a, &b, &c]() {
            //a = 4;              //编译错误:“a”: 无法在非可变 lambda 中修改 通过复制捕获
            b = 4; c = 4;
            std::cout << "mutable testB" << a << b << c << endl;
        };
        m1();
        std::cout << "mutable testD"<<  a << b << c << endl;
    }
    {
        int a = 1, b = 1, c = 1;
        auto m1 = [a, &b, &c]() mutable {
            std::cout << "mutable testA" << a << b << c << endl;
            a = 4; b = 4; c = 4;
            std::cout << "mutable testB" << a << b << c << endl;
        };
        
        std::cout << "mutable testC"<<  a << b << c << endl;
        m1();
        std::cout << "mutable testD"<<  a << b << c << endl;
    }
    
    
    /**sizeof
    查询形式参数包中的元素数量,返回 std::size_t 类型常量 sizeof...( parameter_pack ) (C++11 起) 
    */
    auto arr = make_array(1, 2, 3);
    for (auto i : arr) {
        std::cout << i << ' ';
    }
    
    
    /**struct
    有作用域枚举类型的声明 (C++11 起)
    同class
    */
    enum class Color2
    {
        red, 
        green = 20, 
        blue 
    };
    Color2 r2 = Color2::blue;
    
    
    
    /**using
    类型别名与别名模板声明 (C++11 起) 
    类型别名是指代先前定义类型的名称（同 typedef ）。 
    别名模版是指代一族类型的名称。别名模板是特化时等价于以别名模板实参替换 type-id 中形参的结果。 
    */
    using func = void (*) (int, int);// 类型别名，等同于 typedef void (*func)(int, int);
    Vec<int> v; // 别名模版, Vec<int> 同 vector<int, Alloc<int>>
}


///C++11中新增
TEST_F(ut_Keywords, Add_In_Cplusplus11)
{
    //alignas
    struct alignas(8) S {};
    
    
    //alignof
    MK_PRINT_MSG("alignof(S) = %d", alignof(S));
    
    
    /**constexpr 
    const expression的简写,常量表达式,
    */
    cout<<factorial(4)<<endl; // 在编译时计算
}

TEST_F(ut_Keywords, volatile)
{
    //防止优化编译器把变量从内存装入CPU寄存器中
    //volatile的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值
    volatile int i = 0x10;
    int a = i;
    MK_PRINT_MSG("i = %d", a);
    //do something
    int b = i;
    MK_PRINT_MSG("i = %d", b);
    
    
    
    //这个语句用来测试空循环的速度的, 但是编译器肯定要把它优化掉，根本就不执行
    for ( int i=0; i<100000; i++); 
    //如果添加volatile,它就会执行了
    for ( volatile int i=0; i<100000; i++); 
}




