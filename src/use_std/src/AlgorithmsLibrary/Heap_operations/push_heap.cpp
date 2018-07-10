/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将元素加入到堆 
TEST(Heap, push_heap)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end());
    
    v.push_back(6);
    std::push_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

//将元素加入到堆 
TEST(Heap, push_heap_2)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end(),std::greater<int>());
    
    v.push_back(6);
    std::push_heap(v.begin(), v.end(), std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}
