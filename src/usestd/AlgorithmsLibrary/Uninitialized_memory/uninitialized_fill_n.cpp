/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//复制给定值 value 到始于 first 的未初始化内存区域的首 count 个元素
TEST(Uninitialized_memory, uninitialized_fill_n)
{
    std::string* p;
    std::size_t sz;
    std::tie(p, sz) = std::get_temporary_buffer<std::string>(4);
    std::uninitialized_fill_n(p, sz, "Example");
 
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << '\n';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}