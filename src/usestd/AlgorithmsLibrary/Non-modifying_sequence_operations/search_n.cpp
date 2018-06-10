/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value 。
    返回:指向范围 [first, last) 中找到的序列起始的迭代器。若找不到这种序列，则返回 last 。 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, search_n_1)
{
    const char sequence[] = "1001010100010101001010101";
    auto ret = std::search_n(std::begin(sequence), std::end(sequence), 3, '0');
    if(ret == std::end(sequence)) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(std::begin(sequence), ret));
    }
}

TEST(NMSQ, search_n_2)
{
    const char sequence[] = "1001010100010101001010101";
    auto ret = std::search_n(std::begin(sequence), std::end(sequence), 3, '0', [](char src, char dest){return src == dest;});
    if(ret == std::end(sequence)) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(std::begin(sequence), ret));
    }
}