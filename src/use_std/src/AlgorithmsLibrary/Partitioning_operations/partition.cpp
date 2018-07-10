/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//快速排序
template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
    if(first == last) {
        return;
    }
    
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last, [pivot](const decltype(pivot)& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last, [pivot](const decltype(pivot)& em){ return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

//把一个区间的元素分为两组 
#include <forward_list>
TEST(Partitioning, partition)
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    
    auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;});
    for(auto& elem : v) {
        MK_PRINT_MSG("%d", elem);
    }
    MK_PRINT_MSG("\n");
    
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    quicksort(std::begin(fl), std::end(fl));
    for(auto& elem : fl) {
        MK_PRINT_MSG("%d", elem);
    }
}