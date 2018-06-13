/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//复制来自已排序范围 [first1, last1) 并且不在已排序范围 [first2, last2) 中找到的元素
TEST(SetOperations, set_difference)
{
    std::vector<int> v1 {1, 2, 5, 5, 5, 9};
    std::vector<int> v2 {2, 5, 7};
    std::vector<int> diff;
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), 
                        std::inserter(diff, diff.begin()));
    std::copy(diff.begin(), diff.end(),std::ostream_iterator<int>(std::cout, " "));
}

TEST(SetOperations, set_difference_2)
{
    std::vector<int> v1 {1, 2, 5, 5, 5, 9};
    std::vector<int> v2 {2, 5, 7};
    std::vector<int> diff;
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), 
        std::inserter(diff, diff.begin()), [](int n1, int n2){return n1 != n2;});
    std::copy(diff.begin(), diff.end(),std::ostream_iterator<int>(std::cout, " "));
}
