/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//检查范围 [first, last) 中的元素是否为最大堆。  
TEST(Heap, is_heap)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    
    std::make_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    
    bool ret = std::is_heap(v.begin(), v.end());
    MK_PRINT_MSG("ret = %d", ret);
}

//检查范围 [first, last) 中的元素是否为最大堆。  
TEST(Heap, is_heap_2)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    
    std::make_heap(v.begin(), v.end(),std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    
    bool ret = std::is_heap(v.begin(), v.end(),std::greater<int>());
    MK_PRINT_MSG("ret = %d", ret);
}






