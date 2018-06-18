/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//从始于 first 的范围复制 count 个元素到始于 d_first 的未初始化内存区域 
TEST(Uninitialized_memory, uninitialized_copy_n)
{
    std::vector<std::string> v = {"This", "is", "an", "example"};
 
    std::string* p;
    std::size_t sz;
    std::tie(p, sz)  = std::get_temporary_buffer<std::string>(v.size());
    sz = (std::min)(sz, v.size());
 
    std::uninitialized_copy_n(v.begin(), sz, p);
 
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << ' ';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}
