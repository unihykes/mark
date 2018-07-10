/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//按从后往前的顺序移动某一范围的元素到新的位置 
TEST(MSQ, move_backward)
{
    vector<string> vObj1{"aa", "bb", "cc"};
    vector<string> vObj2{"dd", "ee", "ff"};
    std::move_backward(vObj1.begin(), vObj1.end(), end(vObj2));
    
    for(auto& elem : vObj1){
        MK_PRINT_MSG("vObj1----elem = %s", elem.c_str());
    }
    for(auto& elem : vObj2){
        MK_PRINT_MSG("vObj2----elem = %s", elem.c_str());
    }
}