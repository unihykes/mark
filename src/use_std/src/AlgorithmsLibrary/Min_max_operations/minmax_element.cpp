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

//返回区间内的最小元素和最大元素 
TEST(MinMax, minmax_element)
{
    std::vector<int> v{ 3, 1, -14, 1, 5, 9 }; 
    auto ret1 = minmax_element(v.begin(), v.end());
    auto ret2 = minmax_element(v.begin(), v.end(),std::greater<int>());
    MK_PRINT_MSG("min = %d, max = %d", *ret1.first, *ret1.second);
    MK_PRINT_MSG("min = %d, max = %d", *ret2.first, *ret2.second);
}

