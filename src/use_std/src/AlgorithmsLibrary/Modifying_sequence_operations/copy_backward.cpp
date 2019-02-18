/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)

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