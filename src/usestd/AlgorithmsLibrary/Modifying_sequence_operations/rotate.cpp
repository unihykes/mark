/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将区间内的元素旋转 
TEST(MSQ, rotate)
{
    std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
    // 插入排序
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
}