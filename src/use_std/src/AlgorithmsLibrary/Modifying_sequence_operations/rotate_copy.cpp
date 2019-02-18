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

//将区间内的元素旋转并复制 
TEST(MSQ, rotate_copy)
{
    std::vector<int> src = {1, 2, 3, 4, 5}; 
    std::vector<int> dest(src.size()); 
    
    auto pivot = std::find(src.begin(), src.end(), 3); 
    std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());
    for (auto elem : dest) {
        MK_PRINT_MSG("n = %d", elem);
    }
}