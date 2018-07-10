/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//赋值相继的函数调用结果给范围中的 N 个元素 
TEST(MSQ, generate_n)
{
    std::vector<int> v(5);
    std::generate_n(v.begin(),3,[n=0]() mutable{
            return ++n;
        }
    );
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
}