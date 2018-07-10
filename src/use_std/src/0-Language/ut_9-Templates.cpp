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

class ut_Templates : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};


TEST_F(ut_Templates, Templates)
{
    /**
    模板是定义下列之一的C++实体:
    一个类族, 类模板
    一个函数族, 函数模板
    一个类型的别名族, 别名模板 (C++11起)
    一个变量族, 变量模板(C++14起)
    */
    
    /**
    全特化,偏特化,
    */
}

template<int N = 1>
void ut_Templates_fun1()
{
    MK_PRINT_MSG("N = %d", N);
}

TEST_F(ut_Templates, parameters_arguments)
{
    /**
    形参
    非类型模板形参:模板参数不是一个类型
    类型模板形参:模板参数是一个class或者typename
    模板模板形参。模板参数是一个template    
    
    实参:
    非类型实参
    类型实参
    模板实参
    
    C++11后,模板参数可以为变长参数;
    */
    
    //非类型形参
    ut_Templates_fun1();
    ut_Templates_fun1<>();
    ut_Templates_fun1<100>();
    
    
    //类型形参
    
    //模板形参, 模板形参只能用关键词 class 而不能用 typename 。 
}

//类模板定义
template<class T>
class ut_Templates_1
{
};

//类模板实例化
template class ut_Templates_1<int>;//显式实例化定义
extern template class ut_Templates_1<string>;//显式实例化声明 (C++11 起) 

TEST_F(ut_Templates, class)
{
    /**
    显式实例化声明（ extern 模板）跳过隐式实例化的步骤：
    使用其他地方提供的显式实例化定义替代此外情况下产生的隐式实例化（若不存在这种实例化则产生链接错误）。
    这可用于减少编译时间，通过显式声明所有模板实例化于使用模板的源文件中，并在剩余文件中显式定义它。
    */
}


template<typename T>
void f(T s)
{
    std::cout << s << '\n';
}
template void f<double>(double); // 实例化 f<double>(double)
template void f<>(char); // 实例化 f<char>(char) ，推导出模板实参
template void f(int); // 实例化 f<int>(int) ，推导出模板实参

//函数模板
TEST_F(ut_Templates, function)
{
    
}



//变长参数模版函数
template<typename T1, typename... T2>
double VariableSum(T1 p, T2... arg)
{
#ifdef __ENABLE_CXX14__
    double ret = p + VariableSum(arg...);
    return ret;
#else
    return 0;
#endif
}

//递归边界
double VariableSum()
{
    return 0;
}


template<typename T, typename... Args>
void mk_printf(const char* s, T value, Args... args)
{
    while (*s) {
        if (*s == '%' && *(++s) != '%') {
          std::cout << value;
          #ifdef __ENABLE_CXX14__
          mk_printf(*s ? ++s : s, args...); // 即便当 *s == 0 也会产生调用，以检测更多的类型参数。
          #endif
          return;
        }
        std::cout << *s++;
    }
    
    throw std::logic_error("extra arguments provided to mk_printf");
}

//递归边界
void mk_printf(const char *s)
{
    while (*s) {
        if (*s == '%' && *(++s) != '%') {
            throw std::runtime_error("invalid format string: missing arguments");
        }
        
        std::cout << *s++;
    }
}

//变长参数
TEST_F(ut_Templates, VariableParameters)
{
    double ret1 = VariableSum(1.0, 2.0, 3.0, 4.0);
    //double ret2 = VariableSum(1.0, 2.0, 3.0, 4.0, "wfw");//编译错误:error C2111: “+”: 指针加法要求整型操作数
    
    mk_printf("int = %d, string = %s\n", 100, "ischar");
    try {
        mk_printf("int = %d, string = %s\n", 100, "ischar", 200);
    }
    catch(exception& e) {
        //error: C++ exception with description "extra arguments provided to mk_printf" 
        MK_PRINT_MSG(e.what());
    }
    
    try {
        // invalid format string: missing arguments
        mk_printf("int = %d, string = %s, val = %d\n", 100, "ischar");
    }
    catch(exception& e) {
        MK_PRINT_MSG(e.what());
    }
    
    printf("int = %d, string = %s\n", 100, "ischar");
    
    //int = 100, string = ischar
    //printf("int = %d, string = %s\n", 100, "ischar", 200);// warning C4474: printf: 格式字符串中传递的参数太多
    
    //int = 100, string = ischar, val = 0
    //printf("int = %d, string = %s, val = %d\n", 100, "ischar");// warning C4473: “printf”: 没有为格式字符串传递足够的参数
}



template<typename T>   // 初等模板
struct mk_is_void : public std::false_type
{
};

template<>  // 对 T = void 显式特化
struct mk_is_void<void> : public std::true_type
{
};

//显示特化
TEST_F(ut_Templates, Explicit_specialization)
{
    // 对于任何异于 void 的类型 T ，类导出自 false_type
    std::cout << mk_is_void<char>::value << '\n';
    
    // 但当 T 为 void 时类导出自 true_type
    std::cout << mk_is_void<void>::value << '\n';
}

//部分模板特化
template<class T1, class T2, int I>
class A {};            // 初等模板
 
template<class T, int I>
class A<T, T*, I> {};  // #1 ：部分特化，其中 T2 是指向 T1 的指针
 
template<class T, class T2, int I>
class A<T*, T2, I> {}; // #2 ：部分特化，其中 T1 是指针
 
template<class T>
class A<int, T*, 5> {}; // #3 ：部分特化，其中 T1 是 int ， I 是 5 ，而 T2 是指针
 
template<class X, class T, int I>
class A<X, T*, I> {};   // #4 ：部分特化，其中 T2 是指针

//部分模板特化
TEST_F(ut_Templates, Partial_specialization)
{
    //标准库中的部分特化示例包含 std::unique_ptr ，它对数组类型有部分特化。
}

//参数包 Parameter packs  C++11
TEST_F(ut_Templates, Parameter_packs)
{
    /**
    模板参数包是接受零或更多模板实参（非类型、类型或模板）的模板形参。
    函数模板形参包是接受零或更多函数实参的函数形参。 
    至少有一个参数包的模板被称作变参数模板。 
    */
    
    //pattern ... 
    //模板参数包展开：展开成零或更多 pattern 的逗号分隔列表。模式必须包含至少一个形式参数包。
    
    /**包展开
    后随省略号的模式，其中至少一个参数包名出现至少一次者，
    被展开成零或更多个逗号分隔的模式实例，其中参数包被按顺序替换成每个来自包的元素。 
    */
    
    //todo
}

TEST_F(ut_Templates, sizeof)
{
    //sizeof...( parameter_pack ) (C++11 起) 
    
}

//“替换失败不是错误”（Substitution Failure Is Not An Error） 
TEST_F(ut_Templates, SFINAE)
{
    
}