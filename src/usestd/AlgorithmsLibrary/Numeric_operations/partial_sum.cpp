/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <numeric>



//计算范围 [first, last) 的子范围中元素的部分和 
TEST(Numeric, partial_sum)
{
    std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 或 std::vector<int>v(10, 2);
    std::vector<int> ret;
    std::partial_sum(v.begin(), v.end(), back_inserter(ret));
    for_each(ret.begin(),ret.end(),[](auto& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
    for_each(v.begin(),v.end(),[](auto& elem){MK_PRINT_MSG("%d", elem);});
}

