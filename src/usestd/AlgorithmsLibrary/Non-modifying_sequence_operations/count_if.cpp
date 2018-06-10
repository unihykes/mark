/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, count_if)
{
    vector<int> v{1,2,3,3,4,6,8};
    int64_t ret = std::count_if(v.begin(), v.end(), [](int i){return i%2 == 0;});
    MK_PRINT_MSG("ret = %lld", ret);
}

