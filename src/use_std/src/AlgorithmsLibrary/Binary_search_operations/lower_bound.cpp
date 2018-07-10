/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器，
//或若找不到这种元素则返回 last 。 
TEST(BinarySearch, lower_bound)
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);
    
    std::vector<int> v;
    std::copy(lower, upper, back_inserter(v));
    for(auto elem : v) {
        MK_PRINT_MSG("%d", elem);
    }
}

// 经典二分搜索，仅若存在才返回值
template<class ForwardIt, class T, class Compare=std::less<>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
    // 注意：类型 T 和 Forward 解引用后的类型都必须可隐式转换为用于 Compare 的 Type1 和 Type2 。
    
    first = std::lower_bound(first, last, value, comp);
    return first != last && !comp(value, *first) ? first : last;
}

TEST(BinarySearch, lower_bound_2)
{
    std::vector<int> data = { 1, 2, 4, 6, 9, 10 }; 
    auto it = binary_find(data.cbegin(), data.cend(), 4); // 选择 '5' 的 < 将返回 end()
    
    if(it != data.cend()) {
        MK_PRINT_MSG("found at index : %d", std::distance(data.cbegin(), it));
    }
}






