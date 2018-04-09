/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/
#include <vector>
using namespace std;

#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"
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
        ncAutoProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr;
        fun_vector1(vStr);
    }
    printf("fun_vector1() usedSecond = %.2fs\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr2;
        vStr2 = fun_vector2();
    }
    
    printf("fun_vector2() usedSecond = %.2fs\n", usedSecond);
}
