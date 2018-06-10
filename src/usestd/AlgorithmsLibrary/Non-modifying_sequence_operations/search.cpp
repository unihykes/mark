/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    搜索范围 [first, last - (s_last - s_first)) 中元素子序列 [s_first, s_last) 的首次出现。
    返回值:指向范围中 [first, last - (s_last - s_first)) ，首个子序列 [s_first, s_last) 起始的迭代器。
        若找不到这种子序列，则返回 last 。
        若 [s_first, s_last) 为空，则返回 first 。(C++11 起)
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, search_1)
{
    std::vector<int> v{0, 1, 2, 3, 40, 40, 41, 41, 5};
    std::vector<int> t{40,41};
    auto ret = std::search(v.begin(), v.end(),t.begin(), t.end());
    if(ret == v.end()) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(v.begin(), ret));
    }
}

TEST(NMSQ, search_2)
{
    std::vector<int> v{0, 1, 2, 3, 40, 40, 41, 41, 5};
    std::vector<int> t{40,41};
    auto ret = std::search(v.begin(), v.end(),t.begin(), t.end(), [](int n1, int n2){return n1 == n2;});
    if(ret == v.end()) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(v.begin(), ret));
    }
}
