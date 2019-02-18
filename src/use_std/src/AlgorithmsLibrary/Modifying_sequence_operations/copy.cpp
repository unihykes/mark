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


TEST(MSQ, copy)
{
    vector<int> v = {2,4,6,8,10};
    vector<int> t(v.size());
    std::copy(v.begin(), v.end(), t.begin());
    std::for_each(t.begin(), t.end(),[](int n){
        MK_PRINT_MSG("n = %d", n);}
    );
}

TEST(MSQ, copy2)
{
    vector<int> v = {2,4,6,8,10};
    vector<int> t;
    std::copy(v.begin(), v.end(), std::back_inserter(t));
    for(const auto elem : t) {
        MK_PRINT_MSG("n = %d", elem);
    }
}