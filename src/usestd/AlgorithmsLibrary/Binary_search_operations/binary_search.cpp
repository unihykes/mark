/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//检查等价于 value 的元素是否出现于范围 [first, last) 中。  
TEST(BinarySearch, binary_search)
{
    std::vector<int> v {1, 3, 4, 5, 9};
    
    bool ret = std::binary_search(v.begin(), v.end(), 3);
    MK_PRINT_MSG("%d", ret);
}