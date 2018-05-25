/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"
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
        ncAutoProfilePoint point(usedSecond);
        fun_oldCustomString1();
    }
    MK_PRINT_MSG("fun_oldCustomString1() usedSecond = %.2f", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
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
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncOldCustomString str;
            fun_oldCustomString3(str);
        }
    }
    MK_PRINT_MSG("fun_oldCustomString3() usedSecond = %.2f", usedSecond);
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            ncOldCustomString str;
            str = fun_oldCustomString4();
        }
    }
    MK_PRINT_MSG("fun_oldCustomString4() usedSecond = %.2f", usedSecond);
}

