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
    在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value 。
    返回:指向范围 [first, last) 中找到的序列起始的迭代器。若找不到这种序列，则返回 last 。 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, search_n_1)
{
    const char sequence[] = "1001010100010101001010101";
    auto ret = std::search_n(std::begin(sequence), std::end(sequence), 3, '0');
    if(ret == std::end(sequence)) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(std::begin(sequence), ret));
    }
}

TEST(NMSQ, search_n_2)
{
    const char sequence[] = "1001010100010101001010101";
    auto ret = std::search_n(std::begin(sequence), std::end(sequence), 3, '0', [](char src, char dest){return src == dest;});
    if(ret == std::end(sequence)) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found elem at %d", std::distance(std::begin(sequence), ret));
    }
}