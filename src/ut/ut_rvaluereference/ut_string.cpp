/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"

static int loopCount = 2000000;//用来定义循环次数,200万次
static double usedSecond = 0;  //用来保存指定作用域所消耗时间
////////////////////////////////////////////////////////////////////////////////////////////////////

void fun_string1()
{
    for(int i = 0; i != loopCount; ++i) {
        string s;
        string s1 = SOME_STRING;
        s = s1;
    }
}

void fun_string2()
{
    for(int i = 0; i != loopCount; ++i) {
        string s;
        s = string(SOME_STRING);
    }
}

TEST(ut_string, string1)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        fun_string1();
    }
    MK_PRINT_MSG("fun_string1() usedSecond = %.2f", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        fun_string2();
    }
    MK_PRINT_MSG("fun_string2() usedSecond = %.2f", usedSecond);
}



void fun_string3(string& str)
{
    str = SOME_STRING;
}

string fun_string4()
{
    string str = SOME_STRING;
    return str;
}

TEST(ut_string, string2)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            string str;
            fun_string3(str);
        }
    }
    MK_PRINT_MSG("fun_string3() usedSecond = %.2f", usedSecond);
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            string str;
            str = fun_string4();
        }
    }
    MK_PRINT_MSG("fun_string4() usedSecond = %.2f", usedSecond);
}

