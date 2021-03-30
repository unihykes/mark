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


//检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围  
TEST(Sorting, is_sorted_until)
{
    int digits[] = {3, 1, 4, 1, 5};
    auto iter = std::is_sorted_until(std::begin(digits), std::end(digits));
    int64_t sortedSize = std::distance(std::begin(digits), iter);
    
    MK_PRINT_MSG("sortedSize = %d", sortedSize);
}

TEST(Sorting, is_sorted_until_2)
{
    auto cmp = [](int n1, int n2){return n1>n2;};
    
    int digits[] = {3, 1, 4, 1, 5};
    auto iter = std::is_sorted_until(std::begin(digits), std::end(digits), cmp);
    int64_t sortedSize = std::distance(std::begin(digits), iter);
    
    MK_PRINT_MSG("sortedSize = %d", sortedSize);
}






