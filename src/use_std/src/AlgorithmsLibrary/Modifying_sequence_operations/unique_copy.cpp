/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//删除区间内连续重复的元素并复制 
TEST(MSQ, unique_copy)
{
    std::vector<int> v{1,2,3,1,2,3,3,4,5,4,5,6,7};
    std::sort(v.begin(), v.end());
    std::vector<int> v2; 
    std::unique_copy(v.begin(), v.end(), back_inserter(v2));
    for (auto elem : v2) {
        MK_PRINT_MSG("n = %d", elem);
    }
    
    std::string s1 = "The      string    with many       spaces!";
    std::string s2;
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
                     [](char c1, char c2){ return c1 == ' ' && c2 == ' '; });
    MK_PRINT_MSG("s2 = %s", s2.c_str());
    
}