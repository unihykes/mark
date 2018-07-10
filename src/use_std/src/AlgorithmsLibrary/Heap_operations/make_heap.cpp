/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//根据区间内的元素创建出一个堆
TEST(Heap, make_heap)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

//根据区间内的元素创建出一个堆
TEST(Heap, make_heap_2)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    
    std::make_heap(v.begin(), v.end(),std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}