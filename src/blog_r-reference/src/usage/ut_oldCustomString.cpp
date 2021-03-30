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

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkUniqueProfilePoint.h"
#include "ncOldCustomString.h"

#define SOME_STRING                                                                                  \
   "abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\
    abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz"
    
static int loopCount = 6000000;//用来定义循环次数
static double usedSecond = 0;  //用来保存指定作用域所消耗时间

////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_oldCustomString1()
{
    for(int i = 0; i != loopCount; ++i) {
        ncOldCustomString s;
        ncOldCustomString s1 = SOME_STRING;
        s = s1;
    }
}

void fun_oldCustomString2()
{
    for(int i = 0; i != loopCount; ++i) {
        ncOldCustomString s;
        s = ncOldCustomString(SOME_STRING);
    }
}


TEST(ut_oldCustomString, oldCustomString1)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        fun_oldCustomString1();
    }
    MK_PRINT_MSG("fun_oldCustomString1() usedSecond = %.2f", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        fun_oldCustomString2();
    }
    MK_PRINT_MSG("fun_oldCustomString2() usedSecond = %.2f", usedSecond);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_oldCustomString3(ncOldCustomString& str)
{
    str = SOME_STRING;
}

ncOldCustomString fun_oldCustomString4()
{
    ncOldCustomString str = SOME_STRING;
    return str;
}

TEST(ut_oldCustomString, oldCustomString2)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncOldCustomString str;
            fun_oldCustomString3(str);
        }
    }
    MK_PRINT_MSG("fun_oldCustomString3() usedSecond = %.2f", usedSecond);
    
    
    {
        mkUniqueProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncOldCustomString str;
            str = fun_oldCustomString4();
        }
    }
    MK_PRINT_MSG("fun_oldCustomString4() usedSecond = %.2f", usedSecond);
}

