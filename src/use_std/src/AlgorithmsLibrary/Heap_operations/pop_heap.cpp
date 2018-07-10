/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将堆中的最大元素删除 
TEST(Heap, pop_heap)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::pop_heap(v.begin(), v.end()); // 移动最大元素到结尾
    int largest = v.back();
    v.pop_back();  // 实际移出最大元素
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

//将堆中的最大元素删除 
TEST(Heap, pop_heap_2)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end(), std::greater<int>());
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::pop_heap(v.begin(), v.end(), std::greater<int>()); // 移动最大元素到结尾
    int largest = v.back();
    v.pop_back();  // 实际移出最大元素
    for_each(v.begin(),v.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}
