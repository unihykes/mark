/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//复制一定数目的元素到新的位置 
TEST(MSQ, copy_n)
{
    std::string in = "1234567890";
    std::string out;
    std::copy_n(in.begin(), 4, std::back_inserter(out));
    
    MK_PRINT_MSG("out = %s", out.c_str());
}