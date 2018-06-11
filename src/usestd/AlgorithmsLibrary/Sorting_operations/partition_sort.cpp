/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将区间内较小的N个元素排序  
TEST(Sorting, partition_sort)
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::partial_sort(s.begin(), s.begin() + 3, s.end());
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
}

TEST(Sorting, partition_sort_2)
{
    auto cmp = [](int n1, int n2){return n1>n2;};
    
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::partial_sort(s.begin(), s.begin() + 3, s.end(), cmp);
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
}
