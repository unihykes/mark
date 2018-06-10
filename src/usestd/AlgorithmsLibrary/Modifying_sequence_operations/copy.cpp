/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(MSQ, copy)
{
    vector<int> v = {2,4,6,8,10};
    vector<int> t(v.size());
    std::copy(v.begin(), v.end(), t.begin());
    std::for_each(t.begin(), t.end(),[](int n){
        MK_PRINT_MSG("n = %d", n);}
    );
}

TEST(MSQ, copy2)
{
    vector<int> v = {2,4,6,8,10};
    vector<int> t;
    std::copy(v.begin(), v.end(), std::back_inserter(t));
    for(const auto elem : t) {
        MK_PRINT_MSG("n = %d", elem);
    }
}