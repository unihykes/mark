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

#include <markcore.h>
#include <gtest/gtest.h>
#include "ncNewCustomString.h"

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

void fun_newCustomString1()
{
    int temploopCount = loopCount;
    for(int i = 0; i != temploopCount; ++i) {
        ncNewCustomString s;
        ncNewCustomString s1 = SOME_STRING;
        s = s1;
    }
}

void fun_newCustomString2()
{
    int temploopCount = loopCount;
    for(int i = 0; i != temploopCount; ++i) {
        ncNewCustomString s;
        s = ncNewCustomString(SOME_STRING);
    }
}


TEST(ut_newCustomString, newCustomString1)
{
    {
        mkPerfPoint point(usedSecond);
        fun_newCustomString1();
    }
    MK_PRINT("fun_newCustomString1() usedSecond = %.2f", usedSecond);
    
    {
        mkPerfPoint point(usedSecond);
        fun_newCustomString2();
    }
    MK_PRINT("fun_newCustomString2() usedSecond = %.2f", usedSecond);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void fun_newCustomString3(ncNewCustomString& str)
{
    str = SOME_STRING;
}

ncNewCustomString fun_newCustomString4()
{
    ncNewCustomString str = SOME_STRING;
    return str;
}

TEST(ut_newCustomString, newCustomString2)
{
    {
        mkPerfPoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncNewCustomString str;
            fun_newCustomString3(str);
        }
    }
    MK_PRINT("fun_newCustomString3() usedSecond = %.2f", usedSecond);
    
    
    {
        mkPerfPoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncNewCustomString str;
            str = fun_newCustomString4();
        }
    }
    MK_PRINT("fun_newCustomString4() usedSecond = %.2f", usedSecond);
}

