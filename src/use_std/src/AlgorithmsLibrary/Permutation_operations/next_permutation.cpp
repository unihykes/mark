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

//变换范围 [first, last) 为来自所有按相对于 operator< 或 comp 的字典序的下个排列。
TEST(Permutation, next_permutation)
{
    //下列代码打印字符串 "abc" 的全部三种排列 
    std::string s = "abc";
    
    std::sort(s.begin(), s.end());
    do {
        MK_PRINT_MSG("s = %s", s.c_str());
    } while(std::next_permutation(s.begin(), s.end()));
    cout<<endl;
    
    std::sort(s.begin(), s.end(),std::greater<char>());
    do {
        MK_PRINT_MSG("s = %s", s.c_str());
    } while(std::next_permutation(s.begin(), s.end(), std::greater<char>()));
}

