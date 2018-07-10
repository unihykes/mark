/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//按从后往前的顺序复制一个范围内的元素 
/**复制来自 [first, last) 所定义范围的元素，到终于 d_last 的范围。
以逆序复制元素（首先复制末元素），但保持其相对顺序。 
若 d_last 在 (first, last] 中则行为未定义。该情况下必须用 std::copy 取代 std::copy_backward 。 
*/
TEST(MSQ, copy_backward)
{
    std::string in = "1234567890";
    std::string out = "abcdefghijk";
    std::copy_backward(in.begin(), in.end(), out.end());
    
    MK_PRINT_MSG("out = %s", out.c_str());
}