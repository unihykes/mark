/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//转换最大堆 [first, last) 为以升序排序的范围。产生的范围不再拥有堆属性。  
TEST(Heap, sort_heap)
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9}; 
    std::make_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::sort_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

TEST(Heap, sort_heap_2)
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9}; 
    std::make_heap(v.begin(), v.end(), std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::sort_heap(v.begin(), v.end(),std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}