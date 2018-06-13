/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//计算两个集合的并集 
//由存在于一或两个已排序范围 [first1, last1) 和 [first2, last2) 中的所有元素构成的已排序范围。
TEST(SetOperations, set_union)
{
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 4, 5, 6, 7};
    std::vector<int> dest1;
 
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),
                   std::back_inserter(dest1));
    
    std::copy(dest1.begin(), dest1.end(),std::ostream_iterator<int>(std::cout, " "));
}

