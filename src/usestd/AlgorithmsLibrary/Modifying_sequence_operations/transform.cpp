/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <cctype>//for std::toupper

//将一个函数应用于某一范围的元素 
TEST(MSQ, transform)
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
    for (auto elem : s) {
        MK_PRINT_MSG("n = %c", elem);
    }
    
    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
    for (auto elem : ordinals) {
        MK_PRINT_MSG("n = %d", elem);
    }
    
    std::vector<int> vRet;
    std::transform(s.begin(), s.end(), ordinals.begin(), std::back_inserter(vRet),[](unsigned char c, size_t n) {
            return c + int(n);
        }
    );
    for (auto elem : vRet) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
