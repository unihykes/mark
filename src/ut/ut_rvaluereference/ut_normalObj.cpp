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
class normalObj1
{
public:
    normalObj1(const string& name)
        : _name(name)
    {
    }
private:
    string _name;
};

class normalObj2
{
public:
    normalObj2(string name)
        : _name(static_cast<string&&>(name))
    {
    }
    
private:
    string _name;
};



void fun_normalObj1()
{
    for(int i = 0; i != loopCount; ++i) {
        normalObj1 obj(SOME_STRING);
    }
}

void fun_normalObj2()
{
    for(int i = 0; i != loopCount; ++i) {
        normalObj2 obj(SOME_STRING);
    }
}

TEST(ut_normalObj, ncTestObj)
{
    {
        ncAutoProfilePoint point(usedSecond);
        fun_normalObj1();
    }
    MK_PRINT_MSG("fun_normalObj1() usedSecond = %.2f", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        fun_normalObj2();
    }
    MK_PRINT_MSG("fun_normalObj2() usedSecond = %.2f", usedSecond);
}


