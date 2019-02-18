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


//检验范围 [first, last) 并寻找始于 first 且为最大堆的最大范围。  
TEST(Heap, is_heap_until)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end());
    // 很可能扰乱堆
    v.push_back(2);
    v.push_back(6);
    
    auto heap_end = std::is_heap_until(v.begin(), v.end());
    for (auto i = v.begin(); i != heap_end; ++i) {
        MK_PRINT_MSG("%d", *i);
    }
}

//检验范围 [first, last) 并寻找始于 first 且为最大堆的最大范围。  
TEST(Heap, is_heap_until_2)
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end(),std::greater<int>());
    // 很可能扰乱堆
    v.push_back(2);
    v.push_back(6);
    
    auto heap_end = std::is_heap_until(v.begin(), v.end(),std::greater<int>());
    for (auto i = v.begin(); i != heap_end; ++i) {
        MK_PRINT_MSG("%d", *i);
    }
}