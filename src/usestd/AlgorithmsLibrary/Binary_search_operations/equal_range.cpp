/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//返回范围 [first, last) 中含有所有等价于 value 的元素的范围。  
TEST(BinarySearch, equal_range)
{
    std::vector<int> v{1,2,3,3,3,4,5};
    auto ret = std::equal_range(v.begin(), v.end(), 3);
    for(auto iter = ret.first; iter != ret.second; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
}

