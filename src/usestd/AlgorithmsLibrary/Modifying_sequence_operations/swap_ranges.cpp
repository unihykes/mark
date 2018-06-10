/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//交换两个范围的元素 
TEST(MSQ, swap_ranges)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int> l = {-1, -2, -3, -4, -5};
    std::swap_ranges(v.begin(), v.begin()+3, l.begin());
    
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
    for (auto elem : l) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
