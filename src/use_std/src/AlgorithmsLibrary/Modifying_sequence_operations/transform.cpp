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
#include <cctype>//for std::toupper

//将一个函数应用于某一范围的元素 
TEST(MSQ, transform)
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
    for (auto elem : s) {
        MK_PRINT_MSG("n = %c", elem);
    }
    
    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
    for (auto elem : ordinals) {
        MK_PRINT_MSG("n = %d", elem);
    }
    
    std::vector<int> vRet;
    std::transform(s.begin(), s.end(), ordinals.begin(), std::back_inserter(vRet),[](unsigned char c, size_t n) {
            return c + int(n);
        }
    );
    for (auto elem : vRet) {
        MK_PRINT_MSG("n = %d", elem);
    }
}
