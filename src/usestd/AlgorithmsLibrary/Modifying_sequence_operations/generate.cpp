/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//赋值相继的函数调用结果给范围中的每个元素
TEST(MSQ, generate)
{
    std::vector<int> v(5);
    std::generate(v.begin(),v.end(),[](){
            static int i = 0;
            return ++i;
        }
    );
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
}