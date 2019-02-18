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


//返回范围 [first, last) 中含有所有等价于 value 的元素的范围。  
TEST(BinarySearch, equal_range)
{
    std::vector<int> v{1,2,3,3,3,4,5};
    auto ret = std::equal_range(v.begin(), v.end(), 3);
    for(auto iter = ret.first; iter != ret.second; ++iter) {
        MK_PRINT_MSG("%d", *iter);
    }
}

