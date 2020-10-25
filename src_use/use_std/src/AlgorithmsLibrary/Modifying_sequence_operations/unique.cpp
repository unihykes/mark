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
#include <cctype>//for std::isspace

//删除区间内连续重复的元素 
//从来自范围 [first, last) 的相继等价元素组消除首元素外的元素，并返回范围的新逻辑结尾的尾后迭代器。 
TEST(MSQ, unique)
{
    // 移除重复元素（正常使用）
    std::vector<int> v{1,2,3,1,2,3,3,4,5,4,5,6,7};
    std::sort(v.begin(), v.end()); 
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end()); 
    for (auto elem : v) {
        MK_PRINT_MSG("n = %d", elem);
    }
    
    // 移除连续空格
    std::string s = "wanna go    to      space?";
    auto end = std::unique(s.begin(), s.end(), [](char l, char r){
            return std::isspace(l) && std::isspace(r) && l == r;
        }
    );
    
    MK_PRINT_MSG("s = %s", s.c_str());
}