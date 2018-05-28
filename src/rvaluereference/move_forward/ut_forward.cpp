/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 std::forward 可能的实现,大致如下面所示:
*/
namespace example_std
{
    template<typename T>
    T&& forward(typename std::remove_reference<T>::type& param)
    {
        return static_cast<T&&>(param);
    }
}



/**
示例1:
为了容易理解 std::forward 的工作原理,我们再山寨一个 forward 模板函数
*/
template<typename T>
T&& my_forward(typename std::remove_reference<T>::type& param)
{
    MK_PRINT_MSG("T is %s, T&& is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<T&&>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
    
    return static_cast<T&&>(param);
}

template<typename T>
void funcAAA(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
        
    funcBBB(my_forward<T>(param));
}

template<typename T>
void funcBBB(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}


TEST(ut_forward, my_forward)
{
    //传给funcAAA的实参为左值;
    int s1 = 100;
    funcAAA(s1);
    
    cout<<endl;
    
    //传给funcAAA的实参为右值
    funcAAA(100);
}


/**
总结:

完美转发:
转发函数的实参到目标函数, 使目标函数接受到与转发函数完全相同的实参;

特性:
std::forward并不进行任何转发
std::forward仅在某个特定条件满足时,才会执行强制转换将实参转为右值:
当传入的实参被绑定到左值时,std::forward未做任何事情;
当传入的实参被绑定到右值时,std::forward执行强制转换将实参转为右值;
*/