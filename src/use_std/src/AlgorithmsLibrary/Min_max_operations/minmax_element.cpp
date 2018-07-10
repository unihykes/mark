/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//返回区间内的最小元素和最大元素 
TEST(MinMax, minmax_element)
{
    std::vector<int> v{ 3, 1, -14, 1, 5, 9 }; 
    auto ret1 = minmax_element(v.begin(), v.end());
    auto ret2 = minmax_element(v.begin(), v.end(),std::greater<int>());
    MK_PRINT_MSG("min = %d, max = %d", *ret1.first, *ret1.second);
    MK_PRINT_MSG("min = %d, max = %d", *ret2.first, *ret2.second);
}

