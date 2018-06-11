/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//检查区间元素是否按升序排列 
TEST(Sorting, is_sorted)
{
    int digits[] = {3, 1, 4, 1, 5};
    MK_PRINT_MSG("is_sorted = %s", std::is_sorted(std::begin(digits), std::end(digits))?"true":"false");
    
    std::sort(std::begin(digits), std::end(digits));
    MK_PRINT_MSG("is_sorted = %s", std::is_sorted(std::begin(digits), std::end(digits))?"true":"false");
}

TEST(Sorting, is_sorted_2)
{
    auto cmp = [](int n1, int n2){return n1>n2;};
    
    int digits[] = {3, 1, 4, 1, 5};
    MK_PRINT_MSG("is_sorted = %s", std::is_sorted(std::begin(digits), std::end(digits), cmp)?"true":"false");
    
    std::sort(std::begin(digits), std::end(digits), cmp);
    MK_PRINT_MSG("is_sorted = %s", std::is_sorted(std::begin(digits), std::end(digits), cmp)?"true":"false");
}
