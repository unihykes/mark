/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将区间内的元素排序，同时保持相等的元素之间的顺序 
TEST(Sorting, stable_sort)
{
    std::vector<pair<int,string>> v{make_pair(11,"aaa"), make_pair(6,"bbb"), make_pair(11,"ccc")};
    std::stable_sort(std::begin(v), std::end(v));
    for(auto elem : v) {
        MK_PRINT_MSG("%d->%s", elem.first, elem.second.c_str());
    }
    
    auto cmp = [](pair<int,string> n1, pair<int,string> n2){return n1.first>n2.first;};
    std::stable_sort(std::begin(v), std::end(v), cmp);
    for(auto elem : v) {
        MK_PRINT_MSG("%d->%s", elem.first, elem.second.c_str());
    }
}