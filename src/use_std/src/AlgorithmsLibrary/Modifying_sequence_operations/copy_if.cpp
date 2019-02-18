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
    复制 [first, last) 所定义的范围中的元素到始于 d_first 的另一范围。 
    仅复制谓词 pred 对其返回 true 的元素。保持被复制元素的相对顺序。若源与目标范围重叠则行为未定义。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

TEST(MSQ, copy_if)
{
    vector<int> v = {1,2,3,4,5,6};
    vector<int> t(v.size());
    std::copy_if(v.begin(), v.end(), t.begin(), [](int n) {return n%2 ==0;});
    
    std::for_each(t.begin(), t.end(),[](int n){
        MK_PRINT_MSG("n = %d", n);}
    );
}

TEST(MSQ, copy_if_2)
{
    vector<int> v = {1,2,3,4,5,6};
    vector<int> t;
    std::copy_if(v.begin(), v.end(), std::back_inserter(t), [](int n) {return n%2 ==0;});
    for(const auto elem : t) {
        MK_PRINT_MSG("n = %d", elem);
    }
}




































