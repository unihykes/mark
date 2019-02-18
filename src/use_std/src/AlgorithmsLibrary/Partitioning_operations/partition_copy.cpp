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


//将区间内的元素分为两组复制到不同位置 
TEST(Partitioning, partition_copy)
{
    int arr [10] = {1,2,3,4,5,6,7,8,9,10};
    int true_arr [5] = {0};
    int false_arr [5] = {0};
    
    std::partition_copy(std::begin(arr), std::end(arr), std::begin(true_arr), std::begin(false_arr),
        [] (int i) {return i > 5;}
    );
    for(auto& elem : true_arr) {
        MK_PRINT_MSG("%d", elem);
    }
    for(auto& elem : false_arr) {
        MK_PRINT_MSG("%d", elem);
    }
}