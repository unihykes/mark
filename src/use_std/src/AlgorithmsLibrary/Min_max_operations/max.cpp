/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//std::min,std::max 与 windows下宏冲突
#undef max
#undef min

//返回两个元素中的较大者 
TEST(MinMax, max)
{
    MK_PRINT_MSG("result = %d", std::max(1,99));
    
    MK_PRINT_MSG("result = %d", std::max(1,99,std::greater<int>()));
    
    auto list = {1,2,3,4,5,6,7,8};
    MK_PRINT_MSG("result = %d", std::max(list));
    
    MK_PRINT_MSG("result = %d", std::max(list, std::greater<int>()));
}

