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



//按从后往前的顺序移动某一范围的元素到新的位置 
TEST(MSQ, move_backward)
{
    vector<string> vObj1{"aa", "bb", "cc"};
    vector<string> vObj2{"dd", "ee", "ff"};
    std::move_backward(vObj1.begin(), vObj1.end(), end(vObj2));
    
    for(auto& elem : vObj1){
        MK_PRINT_MSG("vObj1----elem = %s", elem.c_str());
    }
    for(auto& elem : vObj2){
        MK_PRINT_MSG("vObj2----elem = %s", elem.c_str());
    }
}