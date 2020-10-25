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


//将区间内的元素排序，同时保持相等的元素之间的顺序 
TEST(Sorting, stable_sort)
{
    std::vector<pair<int,string>> v{make_pair(11,"aaa"), make_pair(6,"bbb"), make_pair(11,"ccc")};
    std::stable_sort(std::begin(v), std::end(v));
    for(auto elem : v) {
        MK_PRINT_MSG("%d->%s", elem.first, elem.second.c_str());
    }
    
    auto cmp = [](pair<int,string> n1, pair<int,string> n2){return n1.first>n2.first;};
    std::stable_sort(std::begin(v), std::end(v), cmp);
    for(auto elem : v) {
        MK_PRINT_MSG("%d->%s", elem.first, elem.second.c_str());
    }
}