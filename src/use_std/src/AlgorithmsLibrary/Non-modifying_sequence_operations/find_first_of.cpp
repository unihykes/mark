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
    在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素。 
    返回值:指向范围 [first, last) 中等于来自范围 [s_first; s_last) 中一个元素的首个元素。若找不到这种元素，则返回 last 。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, find_first_of_1)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{1,2,3};
    vector<int>::iterator ret = std::find_first_of(v.begin(), v.end(), t1.begin(), t1.end());
    if(ret == v.end()) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found a match at %d", std::distance(v.begin(), ret));
    }
}

TEST(NMSQ, find_first_of2)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{4,5,6};
    vector<int>::iterator ret = std::find_first_of(v.begin(), v.end(), t1.begin(), t1.end());
    if(ret == v.end()) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found a match at %d", std::distance(v.begin(), ret));
    }
}

TEST(NMSQ, find_first_of1)
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int> t1{1,2,3};
    vector<int>::iterator ret = std::find_first_of(v.begin(), v.end(), t1.begin(), t1.end(), [](int n1, int n2){return n1 == n2;});
    if(ret == v.end()) {
        MK_PRINT_MSG("not found.");
    }
    else {
        MK_PRINT_MSG("found a match at %d", std::distance(v.begin(), ret));
    }
}