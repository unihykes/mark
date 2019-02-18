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

//合并两个已排序的区间 
TEST(SetOperations, merge)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2{1,2,3,4,5,6,7,8,9};
    
    //归并
    std::vector<int> dest;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest));
    std::copy(dest.begin(),dest.end(),std::ostream_iterator<int>(std::cout, ""));
}

//合并两个已排序的区间 
TEST(SetOperations, merge_2)
{
    std::vector<int> v1{1,2,3,4,5,6,7,8,9,10};
    std::vector<int> v2{1,2,3,4,5,6,7,8,9};
    
    //归并
    std::vector<int> dest;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),std::greater<int>());
    std::copy(dest.begin(),dest.end(),std::ostream_iterator<int>(std::cout, ""));
}




