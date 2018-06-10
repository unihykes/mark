/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//从范围 [first, last) 移除所有满足特定判别标准的元素，并返回范围新结尾的尾后迭代器。 
TEST(MSQ, remove)
{
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());
    MK_PRINT_MSG("str1 = %s", str1.c_str());

}