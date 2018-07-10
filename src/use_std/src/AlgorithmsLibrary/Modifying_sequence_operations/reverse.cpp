/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将区间内的元素颠倒顺序 
TEST(MSQ, reverse)
{
    int a[] = {4, 5, 6, 7};
    std::reverse(std::begin(a), std::end(a));
    for (auto elem : a) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
