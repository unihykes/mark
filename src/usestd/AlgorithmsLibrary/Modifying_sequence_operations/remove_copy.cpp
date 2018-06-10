/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//复制一个范围内不满足特定条件的元素  
TEST(MSQ, remove_copy)
{
    std::string str = "Text with some   spaces";
    std::string ret;
    std::remove_copy(str.begin(), str.end(), std::back_inserter(ret), ' ');
    MK_PRINT_MSG("ret = %s", ret.c_str());
}