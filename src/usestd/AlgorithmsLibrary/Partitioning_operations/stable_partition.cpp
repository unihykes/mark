/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将元素分为两组，同时保留其相对顺序 
TEST(Partitioning, stable_partition)
{
    std::vector<int> v{0, 0, 3, 0, 2, 4, 5, 0, 7};
    auto iter = std::stable_partition(v.begin(), v.end(), [](int n) {return n>0;});
    for(auto& elem : v) {
        MK_PRINT_MSG("%d", elem);
    }
}
