/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <cctype>//for std::isspace

//复制一个范围内不满足特定条件的元素 
TEST(MSQ, remove_copy_if)
{
    std::string str = "Text with some   spaces";
    std::string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret), [](unsigned char x){return std::isspace(x);});
    MK_PRINT_MSG("ret = %s", ret.c_str());
}