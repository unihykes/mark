/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//在两个已排序范围 [first1, last1) 与 [first2, last2) 中都找到的元素构成的已排序范围。
TEST(SetOperations, set_intersection)
{
    std::vector<int> v1{1,2,3,4,5,5,6,7,8};
    std::vector<int> v2{5,7,7,9,10};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    std::vector<int> v;
    std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));
    std::copy(v.begin(), v.end(),std::ostream_iterator<int>(std::cout, " "));
    cout<<endl;
    std::vector<int> vEX;
    std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(vEX), [](int n1, int n2){return n1 != n2;});
    std::copy(vEX.begin(), vEX.end(),std::ostream_iterator<int>(std::cout, " "));
}