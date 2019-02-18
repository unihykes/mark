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

Time:2018-3

info:

***************************************************************************************************/
#include <vector>
using namespace std;

#include <gtest/gtest.h>
#include "mkUniqueProfilePoint.h"
#include "ncLargeStruct.h"

static int loopCount = 200;//用来定义循环次数
static double usedSecond = 0;  //用来保存指定作用域所消耗时间
////////////////////////////////////////////////////////////////////////////////////////////////////

void fun_vector1(vector<ncLargeStruct>& vStr)
{
    vStr.clear();
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(ncLargeStruct());
    }
}

vector<ncLargeStruct> fun_vector2()
{
    vector<ncLargeStruct> vStr;
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(ncLargeStruct());
    }
    return vStr;
}


TEST(ut_vector, vector)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr;
        fun_vector1(vStr);
    }
    printf("fun_vector1() usedSecond = %.2fs\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr2;
        vStr2 = fun_vector2();
    }
    
    printf("fun_vector2() usedSecond = %.2fs\n", usedSecond);
}
