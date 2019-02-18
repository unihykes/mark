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
    返回范围 [first, last) 中满足特定判别标准的首个元素： 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, find_if)
{
    vector<int> v = {2,4,6,8,10};
    auto ret = std::find_if(v.begin(), v.end(), [](int i){return i % 2 == 0;} );
    if(ret != v.end()) {
        MK_PRINT_MSG("ret = %d", *ret);
    }
    else {
        MK_PRINT_MSG("end of v");
    }
}