/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//归并排序
template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}


//就地合并两个有序的区间 
TEST(SetOperations, inplace_merge)
{
    std::vector<int> v{8, 2, -2, 0, 11, 11, 1, 7, 3};
    merge_sort(v.begin(),v.end());
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout, " "));
}
