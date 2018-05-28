/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:
    某些场景下,显式指定函数模板参数为引用类型, 触发引用折叠, 会有一些反直觉的情况发生,特此记录一下:
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////////////////////////////////////

//例1:const T&
template<typename T>
void funcCall_A(const T& param)
{
    param += 10;
    
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(ut_explicitCall, funcCall_A)
{
    int n = 1;
    
    funcCall_A<int&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
    
    funcCall_A<int&&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
}



//例2:const T&&
template<typename T>
void funcCall_B(const T&& param)
{
    param += 10;
    
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(ut_explicitCall, funcCall_B)
{
    int n = 5;
    
    funcCall_B<int&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
    
    funcCall_B<int&&>(100);//const被丢弃, 修改了一个临时对象(右值)
}


