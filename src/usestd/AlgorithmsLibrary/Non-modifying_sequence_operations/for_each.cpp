/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, for_each)
{
    vector<int> v{2,4,6,8,10};
    auto print = [](const int& n) { MK_PRINT_MSG("n = %d", n); };
    
    std::for_each(v.begin(), v.end(), print);
    std::for_each(v.begin(), v.end(), [](int &n){ n++;});
    std::for_each(v.begin(), v.end(), print);
}

