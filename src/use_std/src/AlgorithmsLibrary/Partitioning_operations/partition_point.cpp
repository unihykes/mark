/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//定位已划分的区域的划分点
TEST(Partitioning, partition_point)
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto is_even = [](int i){ return i % 2 == 0; };
    
    auto q = std::partition(v.begin(), v.end(), is_even);
    for(auto iter = v.begin(); iter != q; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
    
    auto p = std::partition_point(v.begin(), v.end(), is_even);
    for(auto iter = v.begin(); iter != p; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
}

