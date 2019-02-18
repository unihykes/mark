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



//计算范围 [first, last) 的子范围中元素的部分和 
TEST(Numeric, partial_sum)
{
    std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 或 std::vector<int>v(10, 2);
    std::vector<int> ret;
    std::partial_sum(v.begin(), v.end(), back_inserter(ret));
    for_each(ret.begin(),ret.end(),[](auto& elem){MK_PRINT_MSG("%d", elem);});
    cout<<endl;
    
    std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
    for_each(v.begin(),v.end(),[](auto& elem){MK_PRINT_MSG("%d", elem);});
}

