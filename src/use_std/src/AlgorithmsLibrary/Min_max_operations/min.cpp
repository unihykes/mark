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

//std::min,std::max 与 windows下宏冲突
#undef max
#undef min

//返回两个元素中的较小者 
TEST(MinMax, min)
{
    MK_PRINT_MSG("result = %d", std::min(1,99));
    
    MK_PRINT_MSG("result = %d", std::min(1,99,std::greater<int>()));
    
    auto list = {1,2,3,4,5,6,7,8};
    MK_PRINT_MSG("result = %d", std::min(list));
    
    MK_PRINT_MSG("result = %d", std::min(list, std::greater<int>()));
}