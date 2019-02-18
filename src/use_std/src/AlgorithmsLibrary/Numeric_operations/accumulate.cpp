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
#include <numeric>


//计算给定值 init 与给定范围 [first, last) 中元素的和 
TEST(Numeric, accumulate)
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    MK_PRINT_MSG("sum = %d", sum);
    
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());//乘法
    MK_PRINT_MSG("product = %d", product);
    
    std::string s = std::accumulate(std::next(v.begin()), v.end(),std::to_string(v[0]), // 以首元素开始
        [](std::string a, int b) {
            return a + '-' + std::to_string(b);
        }
    );
    MK_PRINT_MSG("s = %s", s.c_str());
}