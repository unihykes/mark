/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, count)
{
    vector<int> v{1,2,3,3,4,6,8};
    int64_t ret = std::count(v.begin(), v.end(), 3);
    MK_PRINT_MSG("ret = %lld", ret);
}

