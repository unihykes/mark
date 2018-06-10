/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将范围内的元素随机重新排序 
#include <random>
TEST(MSQ, shuffle)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
