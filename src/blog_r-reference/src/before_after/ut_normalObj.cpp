/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/
#include <string>
using namespace std;

#include <gtest/gtest.h>
#include "mkUniqueProfilePoint.h"
#include "ncLargeStruct.h"

static int loopCount = 500;//用来定义循环次数
static double usedSecond = 0;  //用来保存指定作用域所消耗时间

#ifndef __ENABLE_CXX11__
    #define move(data)   data
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////

class normalObj1
{
public:
    normalObj1(const ncLargeStruct& data)
        : _data(data)
    {
    }
    void fun(){}
private:
    ncLargeStruct _data;
};

/////////////////////////////////////////////
class normalObj2
{
public:
    normalObj2(ncLargeStruct data)
        : _data(move(data))
    {
    }
    void fun(){}
private:
    ncLargeStruct _data;
};

TEST(ut_normalObj, Construction1)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj1 obj(str);
            obj.fun();
        }
    }
    printf("normalObj1() usedSecond = %.2fs\n", usedSecond);
    
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj2 obj(str);
            obj.fun();
        }
    }
    printf("normalObj2() usedSecond = %.2fs\n", usedSecond);
}


TEST(ut_normalObj, Construction2)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj1 obj(move(str));
            obj.fun();
        }
    }
    printf("normalObj1() usedSecond = %.2fs\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj2 obj(move(str));
            obj.fun();
        }
    }
    printf("normalObj2() usedSecond = %.2fs\n", usedSecond);
}