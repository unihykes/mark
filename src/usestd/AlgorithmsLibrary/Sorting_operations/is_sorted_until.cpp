/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围  
TEST(Sorting, is_sorted_until)
{
    int digits[] = {3, 1, 4, 1, 5};
    auto iter = std::is_sorted_until(std::begin(digits), std::end(digits));
    int64_t sortedSize = std::distance(std::begin(digits), iter);
    
    MK_PRINT_MSG("sortedSize = %d", sortedSize);
}

TEST(Sorting, is_sorted_until_2)
{
    auto cmp = [](int n1, int n2){return n1>n2;};
    
    int digits[] = {3, 1, 4, 1, 5};
    auto iter = std::is_sorted_until(std::begin(digits), std::end(digits), cmp);
    int64_t sortedSize = std::distance(std::begin(digits), iter);
    
    MK_PRINT_MSG("sortedSize = %d", sortedSize);
}






