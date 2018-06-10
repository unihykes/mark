/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>




//复制一个范围内的元素，并将满足特定条件的元素替换为另一个值 
TEST(MSQ, replace_copy)
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::vector<int> ret;
    std::replace_copy(s.begin(), s.end(), back_inserter(ret), 2, 222);
    
    for (auto elem : ret) {
        MK_PRINT_MSG("n = %d", elem);
    }
}