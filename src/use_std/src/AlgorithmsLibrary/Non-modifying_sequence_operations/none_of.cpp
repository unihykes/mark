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
    std::none_of
    检查一元谓词 p 是否不对范围 [first, last) 中任何元素返回 true 。
    返回值:若一元谓词不对范围中任何元素返回 true 则为 true ，否则为 false 。若范围为空则返回 true 。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, none_of)
{
    vector<int> v = {1,3,5,7,9};
    bool ret = std::none_of(v.begin(), v.end(), [](int i){return i%2==0;} );
    MK_PRINT_MSG("ret = %s", ret?"true":"false");
}