/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//判断一个序列是否为另一个序列的排列组合 
TEST(Permutation, is_permutation)
{
    std::vector<int> v1{1,2,3,4,5};
    std::vector<int> v2{3,5,4,1,2};
    
    bool ret1 = std::is_permutation(v1.begin(),v1.end(),v2.begin());
    MK_PRINT_MSG("ret1 = %d", ret1);
    
    bool ret2 = std::is_permutation(v1.begin(),v1.end(),v2.begin(), std::greater<int>());
    MK_PRINT_MSG("ret2 = %d", ret2);
    
    bool ret3 = std::is_permutation(v1.begin(),v1.end(),v2.begin(),v2.end());
    MK_PRINT_MSG("ret3 = %d", ret3);
    
    bool ret4 = std::is_permutation(v1.begin(),v1.end(),v2.begin(),v2.end(), std::greater<int>());
    MK_PRINT_MSG("ret4 = %d", ret4);
}

