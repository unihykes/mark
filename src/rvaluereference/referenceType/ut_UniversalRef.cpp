/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:
    如何判断是否为universal引用?
    一个简单的判断条件是, 参数既能是右值又可以是左值,则是universal引用;
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;
////////////////////////////////////////////////////////////////////////////////////////////////////

//universal引用
TEST(ut_UniversalRef, auto)
{
    int n = 100;
    auto&& v1 = n;
    MK_PRINT_MSG("type of v1 is  %s", type_id_with_cvr<decltype(v1)>().pretty_name().c_str());
    
    auto&& v2 = 512;
    MK_PRINT_MSG("type of v2 is  %s", type_id_with_cvr<decltype(v2)>().pretty_name().c_str());
}

//universal引用
template<typename T> 
void fun_universal_a(T&& param_a)
{
    MK_PRINT_MSG("T is %s, type of param_a is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_a)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_a)
{
    
    int n = 10;
    fun_universal_a(n);//存在类型推导, 是universal引用,可接受左值
    fun_universal_a(10);//存在类型推导, 是universal引用,可接受右值
    
    //fun_universal_a<int>(n);//T类型固定为int,编译错误
    fun_universal_a<int>(10);//T类型固定为int, 非universal引用
    
    
    fun_universal_a<int&>(n);//T类型固定为int&,存在引用折叠(下文再述),非universal引用
    //fun_universal_a<int&>(10);//T类型固定为int&,存在引用折叠(下文再述),非universal引用, 编译错误
    
    //fun_universal_a<int&&>(n);//T类型固定为int&,存在引用折叠, 非universal引用, 编译错误
    fun_universal_a<int&&>(10);//类型固定,存在引用折叠,非universal引用
}



//非universal引用
void fun_universal_b(int&& param_b)
{
    MK_PRINT_MSG("type of param_b is %s",   type_id_with_cvr<decltype(param_b)>().pretty_name().c_str());
}
TEST(ut_UniversalRef, fun_universal_b)
{
    int n = 10;
    //fun_universal_b(n);//编译错误,int&&是右值引用类型,不能接受左值
    fun_universal_b(10);//传入右值
}


//非universal引用,因为const
template<typename T> 
void fun_universal_c(const T&& param_c)
{
    MK_PRINT_MSG("T is %s, type of param_c is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_c)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_c)
{
    
    int n = 10;
    //fun_universal_c(n);//编译错误,const T&&尽管存在类型推导,但不符合universal规则,编译错误
    fun_universal_c(10);//传入右值,T推导为int,函数形参类型const int&&
    
    //fun_universal_c<int>(n);//T类型固定int,非universal引用,编译错误
    fun_universal_c<int>(10);//T类型固定int,非universal引用, 函数形参类型const int&&
    
    
    fun_universal_c<int&>(n);//T为int&, 函数形参类型为int&     todo:没搞懂这里的规则,const去哪了?
    //fun_universal_c<int&>(10);/param_c的类型为int&,不能接受右值,编译错误
    
    
    //fun_universal_c<int&&>(n);//T为int&&, 函数形参类型为int&&,编译错误,右值引用无法接受左值;
    fun_universal_c<int&&>(10);//T为int&&, 函数形参类型为int&&, 这里函数形参的const被忽略了.
}


//非universal引用, 因为当给func传入实参时，T被推导后vector<T>&&的类型是确定的。
template<typename T>
void fun_universal_d(vector<T>&& param_d)
{
    MK_PRINT_MSG("T is %s, type of param_d is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_d)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_d)
{
    vector<int> v;
    
    //fun_universal_d(v);//非universal引用,编译错误,无法将左值绑定到右值引用
    fun_universal_d(vector<int>());//非universal引用
}



struct ncLittleObj
{
    ncLittleObj(int&& a, int&& b)
    {
        MK_PRINT_MSG("type of a is %s", type_id_with_cvr<decltype(a)>().pretty_name().c_str());
    }
    
    ncLittleObj(const int& a, const int& b)
    {
        MK_PRINT_MSG("type of a is %s", type_id_with_cvr<decltype(a)>().pretty_name().c_str());
    }
};

template<class T, class Allocator=allocator<T>>
class Vector_Lite
{
public:
    //虽然push_back的形参符合T&&格式，但不是universal引用
    //因为 Vector_Lite<T> 实例化后，push_back的形参类型就确定下来
    //所以在调用时push_back函数时并不存在类型推导。
    void push_back(T&& param)
    {
        MK_PRINT_MSG("T is %s, type of param is %s", 
            type_id_with_cvr<T>().pretty_name().c_str(),
            type_id_with_cvr<decltype(param)>().pretty_name().c_str());
    }
    
    //Arg&&存在类型推导，所以args的参数是universal引用。
    //因为参数Args独立于vector的类型参数T，所以每次emplace_back被调用的时候，Args必须被推导。
    template<class ...Args>
    void emplace_back(Args&&...  args)
    {
        ncLittleObj obj(std::forward<Args>(args)...);
    }
};


TEST(ut_UniversalRef, Vector_Lite)
{
    Vector_Lite<int> v;
    int n = 1;
    
    //v.push_back(n);//非universal引用
    v.push_back(100);//非universal引用
    
    v.emplace_back(n, n);//universal引用,可接受左值
    v.emplace_back(34, 46);//universal引用,可接受右值
}


