/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//交换两个迭代器所指向的元素 
TEST(MSQ, iter_swap)
{
    vector<int> v{3,5,7,1,4,6,9,3,6};
    //选择排序
    for(auto iter = v.begin(); iter != v.end(); ++iter) {
        std::iter_swap(iter, std::min_element(iter, v.end()) );
    }
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
}