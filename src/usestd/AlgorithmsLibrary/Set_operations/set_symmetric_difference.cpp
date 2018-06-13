/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>





//计算二个已排序范围的对称差：复制在任一范围中，但不在两个范围中找到的元素
TEST(SetOperations, set_symmetric_difference)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8};
    std::vector<int> v2{5,7,9,10};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    std::vector<int> v_symDifference;
    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference));
    std::copy(v_symDifference.begin(), v_symDifference.end(),std::ostream_iterator<int>(std::cout, " "));
}

TEST(SetOperations, set_symmetric_difference_2)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8};
    std::vector<int> v2{5,7,9,10};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    std::vector<int> v_symDifference;
    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference),
        [](int n1,int n2){return n1 != n2;});
    std::copy(v_symDifference.begin(), v_symDifference.end(),std::ostream_iterator<int>(std::cout, " "));
}