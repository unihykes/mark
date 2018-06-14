/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    std::equal 不可应用到由 
    std::unordered_set 、 
    std::unordered_multiset 、 
    std::unordered_map 或 
    std::unordered_multimap 的迭代器构成的范围，
    因为即使此类容器存储相同的元素，在容器内元素存储的顺序也可能不同。 
    比较整个容器是否相等时，针对该容器的 operator== 重载通常是更好的选择。 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//确定两个元素集合是否是相同的

TEST(Comparison, equal)
{
    //下面的代码使用 equal() 来测试字符串是否是回文 
    std::string s("radar");
    
    bool ret = std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
    MK_PRINT_MSG("ret = %d", ret);
    
    ret = std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin(), 
        [](const char& a, const char& b){return a == b;});
    MK_PRINT_MSG("ret = %d", ret);
    
    ret = std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin(), s.rbegin()+ s.size()/2);
    MK_PRINT_MSG("ret = %d", ret);
    
    ret = std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin(),s.rbegin()+ s.size()/2, 
        [](const char& a, const char& b){return a == b;});
    MK_PRINT_MSG("ret = %d", ret);
}

