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

Time:2018-4

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 std::move 可能的实现,大致如下面所示:
*/
namespace example_std
{
    template< class T > 
    struct remove_reference
    {
        typedef T type;
    };

    template< class T > 
    struct remove_reference<T&>
    {
        typedef T type;
    };

    template< class T > 
    struct remove_reference<T&&> 
    {
        typedef T type;
    };

    template<typename T>
    typename remove_reference<T>::type&& move(T&& param)
    {
        using ReturnType = typename remove_reference<T>::type&&;
        return static_cast<ReturnType>(param);
    }
}

/**
示例1:
为了容易理解 remove_reference的工作原理,我们山寨一个 remove_reference
*/
template< class T > 
struct my_remove_reference
{
    using type = T;
    static const int id = 1;
};

template< class T > 
struct my_remove_reference<T&>
{
    using type = T;
    static const int id = 2;
};

template< class T > 
struct my_remove_reference<T&&> 
{
    using type = T;
    static const int id = 3;
};

TEST(ut_move, my_remove_reference)
{
   {
        using ReturnType = my_remove_reference<int>::type&&;//int&&
        int id = my_remove_reference<int>::id;//1
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
   
   {
        using ReturnType = my_remove_reference<int&>::type&&;//int&&
        int id = my_remove_reference<int&>::id;//2
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
   
   {
        using ReturnType = my_remove_reference<int&&>::type&&;//int&&
        int id = my_remove_reference<int&&>::id;//3
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
}


/**
示例2:
为了容易理解 std::move的工作原理,我们再山寨一个 move 模板函数
*/
template<typename T>
typename my_remove_reference<T>::type&& my_move(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(), 
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
     
    using ReturnType = typename my_remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

TEST(ut_move, my_move)
{
    int n = 5;
    auto&& ret1 = my_move(n);
    MK_PRINT_MSG("type of ret1 is %s\n", type_id_with_cvr<decltype(ret1)>().pretty_name().c_str());
    
    const int m = 12;
    auto&& ret2 = my_move(m);
    MK_PRINT_MSG("type of ret2 is %s\n", type_id_with_cvr<decltype(ret2)>().pretty_name().c_str());
    
    auto&& ret3 = my_move(100);
    MK_PRINT_MSG("type of ret3 is %s\n", type_id_with_cvr<decltype(ret3)>().pretty_name().c_str());
    
    int n2 = 11;
    int& nL = n2;
    auto&& ret4 = my_move(nL);
    MK_PRINT_MSG("type of ret4 is %s\n", type_id_with_cvr<decltype(ret4)>().pretty_name().c_str());
}

/**
总结:
以上示例代码虽然简陋, 但是std::move()的工作原理大抵如此;

移动语义作用:
替换复制操作,提高性能;
使得创建只移型对象成为可能,例如std::unique_ptr, std::thread;

std::move()有几个要点:
1.std::move函数中的T&&是个universal引用,可以接受任意左值和右值;
2.std::move实际上并不进行任何移动, 仅仅执行强制类型转换;
3.std::move无条件的将实参强制转为右值; const实参会转为const T&&类型的右值;
4.std::move调用之后,所转移的对象及引用变为未定义状态,不可再次使用;
*/


    
