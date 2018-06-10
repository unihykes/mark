/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    返回范围 [first, last) 中满足特定判别标准的首个元素： 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, find_if)
{
    vector<int> v = {2,4,6,8,10};
    auto ret = std::find_if(v.begin(), v.end(), [](int i){return i % 2 == 0;} );
    if(ret != v.end()) {
        MK_PRINT_MSG("ret = %d", *ret);
    }
    else {
        MK_PRINT_MSG("end of v");
    }
}