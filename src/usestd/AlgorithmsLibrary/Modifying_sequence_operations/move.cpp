/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>



//将某一范围的元素移动到一个新的位置
TEST(MSQ, move)
{
    vector<string> vObj1{"aa", "bb", "cc"};
    vector<string> vObj2{};
    std::move(vObj1.begin(), vObj1.end(), std::back_inserter(vObj2));
    
    for(auto& elem : vObj1){
        MK_PRINT_MSG("vObj1----elem = %s", elem.c_str());
    }
    for(auto& elem : vObj2){
        MK_PRINT_MSG("vObj2----elem = %s", elem.c_str());
    }
}