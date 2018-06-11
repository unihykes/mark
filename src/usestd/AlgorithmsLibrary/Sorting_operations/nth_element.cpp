/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//将给定的区间部分排序，确保区间被给定的元素划分 
TEST(Sorting, nth_element)
{
    std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
    MK_PRINT_MSG("the median is %d", v[v.size()/2]);
    for(auto elem : v) {
        MK_PRINT_MSG("%d", elem);
    }
}


TEST(Sorting, nth_element2)
{
    vector<int> v2;
    for(int i = 0; i != 1000; ++i) {
        v2.push_back(i);
    }
    
    std::nth_element(v2.begin(), v2.begin()+1, v2.end(), std::greater<int>());
    MK_PRINT_MSG("the second largest elem is %d", v2[1]);
    for(auto elem : v2) {
        //vs2015下还是全部排序了.
        //gcc下只保证v.begin()+1个元素是排序的,后面的元素不保证
        MK_PRINT_MSG("%d", elem);
    }
}