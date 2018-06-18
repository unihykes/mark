/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//复制来自范围 [first, last) 的元素到始于 d_first 的未初始化内存 
TEST(Uninitialized_memory, uninitialized_copy)
{
    std::vector<std::string> v = {"This", "is", "an", "example"};
    std::string* p;
    std::size_t sz;
    std::tie(p, sz)  = std::get_temporary_buffer<std::string>(v.size());
    sz = (std::min)(sz, v.size());
    
    std::uninitialized_copy(v.begin(), v.begin() + sz, p);
    
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << ' ';
        i->~basic_string<char>();
    }
    
    std::return_temporary_buffer(p);
}


