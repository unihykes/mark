/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    在范围 [first, last) 中搜索最后的元素子列 [s_first, s_last) 。 
    返回值:指向范围 [first, last) 中最后的子列 [s_first, s_last) 起始的迭代器。 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, find_end1)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{1,2,3};
    vector<int>::iterator ret = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if(ret == v.end()) {
        MK_PRINT_MSG("subsequence not found.");
    }
    else {
        MK_PRINT_MSG("last subsequence is at %d", std::distance(v.begin(), ret));
    }
}

TEST(NMSQ, find_end2)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{4,5,6};
    vector<int>::iterator ret = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if(ret == v.end()) {
        MK_PRINT_MSG("subsequence not found.");
    }
    else {
        MK_PRINT_MSG("last subsequence is at %d", std::distance(v.begin(), ret));
    }
}

TEST(NMSQ, find_end3)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{1,2,3};
    vector<int>::iterator ret = std::find_end(v.begin(), v.end(), t1.begin(), t1.end(), [](int n1, int n2){return n1 == n2;});
    if(ret == v.end()) {
        MK_PRINT_MSG("subsequence not found.");
    }
    else {
        MK_PRINT_MSG("last subsequence is at %d", std::distance(v.begin(), ret));
    }
}