/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将区间按升序排序 
TEST(Sorting, sort)
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
    std::sort(s.begin(), s.end());
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
    
    std::sort(s.begin(), s.end(), std::greater<int>());
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
    
    auto cmp = [](int n1, int n2){return n1>n2;};
    std::sort(s.begin(), s.end(), cmp);
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
}