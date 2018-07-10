/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//如果一个集合是另外一个集合的子集则返回true 
#include <cctype>
TEST(SetOperations, includes)
{
    std::vector<char> v1 {'a', 'b', 'c', 'f', 'h', 'x'};
    std::vector<char> v2 {'a', 'b', 'c'};
    std::vector<char> v3 {'a', 'c'};
    
    bool ret = std::includes(v1.begin(), v1.end(), v2.begin(), v2.end());
    MK_PRINT_MSG("ret = %d", ret);
    
    ret = std::includes(v1.begin(), v1.end(), v3.begin(), v3.end());
    MK_PRINT_MSG("ret = %d", ret);
    
    auto cmp_nocase = [](char a, char b) {
        return std::tolower(a) < std::tolower(b);
    };
    std::vector<char> v4 {'A', 'B', 'C'};
    ret = std::includes(v1.begin(), v1.end(), v3.begin(), v3.end(), cmp_nocase);
    MK_PRINT_MSG("ret = %d", ret);
}
