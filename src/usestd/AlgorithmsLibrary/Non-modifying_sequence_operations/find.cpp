/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    返回范围 [first, last) 中满足特定判别标准的首个元素： 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, find)
{
    vector<int> v = {2,4,6,8,10};
    auto ret = std::find(v.begin(), v.end(), 6);
    if(ret != v.end()) {
        MK_PRINT_MSG("ret = %d", *ret);
    }
    else {
        MK_PRINT_MSG("end of v");
    }
}