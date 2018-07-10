/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将区间内的元素颠倒顺序并复制 
TEST(MSQ, reverse_copy)
{
    std::vector<int> v({1,2,3});
    std::vector<int> dest(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(dest));
    for (auto elem : dest) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
