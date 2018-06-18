/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <numeric>

//用从起始值开始连续递增的值填充区间  
TEST(Numeric, iota)
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
    for_each(l.begin(),l.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

TEST(Numeric, iota_2)
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
    
    std::vector<std::list<int>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());
    for_each(v.begin(),v.end(),[](auto& elem){MK_PRINT_MSG("%d", *elem);});
}

