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
#include <numeric>

//计算内积（即积之和）或在范围 [first1, last1) 和始于 first2 的范围上进行有序映射/规约操作。  
TEST(Numeric, inner_product)
{
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
    
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);//0*5 + 1*4 +2*2 + 3*3 + 4*1
    MK_PRINT_MSG("r1 = %d", r1);
    
    //op1 被使用的二元函数对象。此“和”函数接收 op2 所返回的值和当前积累器的值，并产生存储于积累器的新值
    //op2 被使用的二元函数对象。此“积”函数从每个范围接收一个值并产生新值。
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,std::plus<>(), std::equal_to<>());
    MK_PRINT_MSG("r2 = %d", r2);
}
