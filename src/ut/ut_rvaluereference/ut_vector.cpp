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

void fun_vector1(vector<string>& vStr)
{
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(SOME_STRING);
    }
}

vector<string> fun_vector2()
{
    vector<string> vStr;
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(SOME_STRING);
    }
    return vStr;
}


TEST(ut_vector, vector)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        vector<string> vStr;
        fun_vector1(vStr);
    }
    MK_PRINT_MSG("fun_vector1() usedSecond = %.2f", usedSecond);
    
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        vector<string> vStr2;
        vStr2 = fun_vector2();
    }
    MK_PRINT_MSG("fun_vector2() usedSecond = %.2f", usedSecond);
}
