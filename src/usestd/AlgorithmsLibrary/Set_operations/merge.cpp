/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//合并两个已排序的区间 
TEST(SetOperations, merge)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2{1,2,3,4,5,6,7,8,9};
    
    //归并
    std::vector<int> dest;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest));
    std::copy(dest.begin(),dest.end(),std::ostream_iterator<int>(std::cout, ""));
}

//合并两个已排序的区间 
TEST(SetOperations, merge_2)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2{1,2,3,4,5,6,7,8,9};
    
    //归并
    std::vector<int> dest;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),std::greater<int>());
    std::copy(dest.begin(),dest.end(),std::ostream_iterator<int>(std::cout, ""));
}




