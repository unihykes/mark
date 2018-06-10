/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将区间内的元素旋转并复制 
TEST(MSQ, rotate_copy)
{
    std::vector<int> src = {1, 2, 3, 4, 5}; 
    std::vector<int> dest(src.size()); 
    
    auto pivot = std::find(src.begin(), src.end(), 3); 
    std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());
    for (auto elem : dest) {
        MK_PRINT_MSG("n = %d", elem);
    }
}