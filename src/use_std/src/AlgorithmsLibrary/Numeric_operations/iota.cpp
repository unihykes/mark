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

//用从起始值开始连续递增的值填充区间  
TEST(Numeric, iota)
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
    for_each(l.begin(),l.end(),[](const int& elem){MK_PRINT_MSG("%d", elem);});
}

TEST(Numeric, iota_2)
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
    
    std::vector<std::list<int>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());
    for_each(v.begin(),v.end(),[](auto& elem){MK_PRINT_MSG("%d", *elem);});
}

