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



//对区间内的元素进行复制并部分排序 
TEST(Sorting, partial_sort_copy)
{
    std::vector<int> v0{4, 2, 5, 1, 3};
    std::vector<int> v1{10, 11, 12};
    
    auto it = std::partial_sort_copy(v0.begin(), v0.end(), v1.begin(), v1.end());
    for(auto elem : v1) {
        MK_PRINT_MSG("%d", elem);
    }
    
    std::vector<int> v2{10, 11, 12, 13, 14, 15, 16};
    it = std::partial_sort_copy(v0.begin(), v0.end(), v2.begin(), v2.end(), std::greater<int>());
    for(auto elem : v2) {
        MK_PRINT_MSG("%d", elem);
    }
}