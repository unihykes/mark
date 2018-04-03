/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"

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
    
static int loopCount = 6000000;//用来定义循环次数,200万次
static double usedSecond = 0;  //用来保存指定作用域所消耗时间
////////////////////////////////////////////////////////////////////////////////////////////////////

class oldCustomString
{
public:
    oldCustomString()
        :_str(nullptr)
    {
    }
    oldCustomString(const char* source)
        :_str(nullptr)
    {
        _str = new char[strlen(source)+1];
        strcpy(_str, source);
    }
    
    oldCustomString(const oldCustomString& source)
    {
        _str = new char[strlen(source._str) + 1];
        strcpy(_str, source._str);
    }
    
    oldCustomString& operator = (const oldCustomString& source)
    {
        if (this != &source){
            char *tmp = new char[strlen(source._str) + 1];
            strcpy(tmp, source._str);
            delete []_str;
            _str = tmp;
        }
        return *this;
    }
    
   //析构函数
    ~oldCustomString()
    {
        if (_str) {
            delete[] _str;
            _str = nullptr;
        }
    }
private:
    char*       _str;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
void fun_oldCustomString1()
{
    for(int i = 0; i != loopCount; ++i) {
        oldCustomString s;
        oldCustomString s1 = SOME_STRING;
        s = s1;
    }
}

void fun_oldCustomString2()
{
    for(int i = 0; i != loopCount; ++i) {
        oldCustomString s;
        s = oldCustomString(SOME_STRING);
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
void fun_oldCustomString3(oldCustomString& str)
{
    str = SOME_STRING;
}

oldCustomString fun_oldCustomString4()
{
    oldCustomString str = SOME_STRING;
    return str;
}

TEST(ut_oldCustomString, oldCustomString2)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            oldCustomString str;
            fun_oldCustomString3(str);
        }
    }
    MK_PRINT_MSG("fun_oldCustomString3() usedSecond = %.2f", usedSecond);
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            oldCustomString str;
            str = fun_oldCustomString4();
        }
    }
    MK_PRINT_MSG("fun_oldCustomString4() usedSecond = %.2f", usedSecond);
}

