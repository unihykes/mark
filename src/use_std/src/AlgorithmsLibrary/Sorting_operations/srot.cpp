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

//将区间按升序排序 
TEST(Sorting, sort)
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
    std::sort(s.begin(), s.end());
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
    
    std::sort(s.begin(), s.end(), std::greater<int>());
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
    
    auto cmp = [](int n1, int n2){return n1>n2;};
    std::sort(s.begin(), s.end(), cmp);
    for(auto elem : s) {
        MK_PRINT_MSG("%d", elem);
    }
}