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


//定位已划分的区域的划分点
TEST(Partitioning, partition_point)
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto is_even = [](int i){ return i % 2 == 0; };
    
    auto q = std::partition(v.begin(), v.end(), is_even);
    for(auto iter = v.begin(); iter != q; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
    
    auto p = std::partition_point(v.begin(), v.end(), is_even);
    for(auto iter = v.begin(); iter != p; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
}

