/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(MSQ, replace_if)
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::replace_if(s.begin(), s.end(), [](int n){return n<5;}, 22);
    
    for (auto elem : s) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
