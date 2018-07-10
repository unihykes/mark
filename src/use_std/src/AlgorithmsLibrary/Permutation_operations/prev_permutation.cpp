/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//变换范围 [first, last) 为来自所有按相对于 operator< 或 comp 的字典序的下个排列。
TEST(Permutation, prev_permutation)
{
    //下列代码打印字符串 "abc" 的全部三种排列 
    std::string s = "abc";
    
    std::sort(s.begin(), s.end(),std::greater<char>());
    do {
        MK_PRINT_MSG("s = %s", s.c_str());
    } while(std::prev_permutation(s.begin(), s.end()));
    cout<<endl;
    
    std::sort(s.begin(), s.end());
    do {
        MK_PRINT_MSG("s = %s", s.c_str());
    } while(std::prev_permutation(s.begin(), s.end(), std::greater<char>()));
}