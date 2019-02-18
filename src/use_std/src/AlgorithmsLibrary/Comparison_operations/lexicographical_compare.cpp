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

//检查第一个范围 [first1, last1) 是否按字典序小于第二个范围 [first2, last2) 。  
TEST(Comparison, lexicographical_compare)
{
    std::vector<char> v1 {'a', 'b', 'c', 'd'};
    std::vector<char> v2 {'a', 'b', 'c', 'd'};
    
    bool ret1 = std::lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end());
    MK_PRINT_MSG("ret1 = %d", ret1);
    
    bool ret2 = std::lexicographical_compare(v1.begin(),v1.end(),v2.begin(),v2.end(),
        [](const char a, const char b){return a < b;});
    MK_PRINT_MSG("ret2 = %d", ret2);
}