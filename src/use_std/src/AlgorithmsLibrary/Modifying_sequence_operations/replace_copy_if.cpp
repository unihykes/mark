/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//复制一个范围内的元素，并将满足特定条件的元素替换为另一个值 
TEST(MSQ, replace_copy_if)
{
    std::vector<int> v{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::vector<int> ret;
    std::replace_copy_if(v.begin(), v.end(),
                         back_inserter(ret),
                         [](int n){return n > 5;}, 99);
    for (auto elem : ret) {
        MK_PRINT_MSG("n = %d", elem);
    }
}