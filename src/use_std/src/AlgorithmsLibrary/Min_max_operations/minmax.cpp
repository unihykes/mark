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


//返回两个元素中的的较大者和较小者 
TEST(MinMax, minmax)
{
    int a = 11;
    int b = 33;
    auto ret1 = std::minmax(a,b);
    auto ret2 = std::minmax(a,b,std::greater<int>());
    MK_PRINT_MSG("min = %d, max = %d", ret1.first,ret1.second);
    MK_PRINT_MSG("min = %d, max = %d", ret2.first,ret2.second);
    
    auto list = {1,2,3,4,5,6,7,8};
    auto ret3 = std::minmax(list);
    auto ret4 = std::minmax(list,std::greater<int>());
    MK_PRINT_MSG("min = %d, max = %d", ret3.first,ret3.second);
    MK_PRINT_MSG("min = %d, max = %d", ret4.first,ret4.second);
}