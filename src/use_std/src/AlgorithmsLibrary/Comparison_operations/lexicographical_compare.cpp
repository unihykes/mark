/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

//检查第一个范围 [first1, last1) 是否按字典序小于第二个范围 [first2, last2) 。  
TEST(Comparison, lexicographical_compare)
{
    std::vector<char> v1 {'a', 'b', 'c', 'd'};
    std::vector<char> v2 {'a', 'b', 'c', 'd'};
    
    bool ret1 = std::lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end());
    MK_PRINT_MSG("ret1 = %d", ret1);
    
    bool ret2 = std::lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end(),
        [](const char a, const char b){return a < b;});
    MK_PRINT_MSG("ret2 = %d", ret2);
}