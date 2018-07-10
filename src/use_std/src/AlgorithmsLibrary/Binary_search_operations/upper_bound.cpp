/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//返回指向范围 [first, last) 中首个大于 value 的元素的迭代器，或若找不到这种元素则返回 last 。 
TEST(BinarySearch, upper_bound)
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);
    
    std::vector<int> v;
    std::copy(lower, upper, back_inserter(v));
    for(auto elem : v) {
        MK_PRINT_MSG("%d", elem);
    }
}