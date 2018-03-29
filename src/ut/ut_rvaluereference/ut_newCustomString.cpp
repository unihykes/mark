/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"


static int loopCount = 6000000;//用来定义循环次数,200万次
static double usedSecond = 0;  //用来保存指定作用域所消耗时间
////////////////////////////////////////////////////////////////////////////////////////////////////

class newCustomString
{
public:
    newCustomString()
        :_str(nullptr)
    {
    }
    newCustomString(const char* source)
        :_str(nullptr)
    {
        _str = new char[strlen(source)+1];
        strcpy(_str, source);
    }
    
    newCustomString(const newCustomString& source)
    {
        _str = new char[strlen(source._str) + 1];
        strcpy(_str, source._str);
    }
    
    newCustomString& operator = (const newCustomString& source)
    {
        if (this != &source){
            char *tmp = new char[strlen(source._str) + 1];
            strcpy(tmp, source._str);
            delete []_str;
            _str = tmp;
        }
        return *this;
    }
    
    newCustomString(newCustomString&& source)
    {
        _str = source._str;
        source._str = nullptr;
    }
    
    newCustomString& operator = (newCustomString&& source)
    {
        _str = source._str;
        source._str = nullptr;
        return *this;
    }
    
   //析构函数
    ~newCustomString()
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

void fun_newCustomString1()
{
    int temploopCount = loopCount;
    for(int i = 0; i != temploopCount; ++i) {
        newCustomString s;
        newCustomString s1 = SOME_STRING;
        s = s1;
    }
}

void fun_newCustomString2()
{
    int temploopCount = loopCount;
    for(int i = 0; i != temploopCount; ++i) {
        newCustomString s;
        s = newCustomString(SOME_STRING);
    }
}


TEST(ut_newCustomString, newCustomString1)
{
    {
        ncAutoProfilePoint point(usedSecond);
        fun_newCustomString1();
    }
    MK_PRINT_MSG("fun_newCustomString1() usedSecond = %.2f", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        fun_newCustomString2();
    }
    MK_PRINT_MSG("fun_newCustomString2() usedSecond = %.2f", usedSecond);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void fun_newCustomString3(newCustomString& str)
{
    str = SOME_STRING;
}

newCustomString fun_newCustomString4()
{
    newCustomString str = SOME_STRING;
    return str;
}

TEST(ut_newCustomString, newCustomString2)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            newCustomString str;
            fun_newCustomString3(str);
        }
    }
    MK_PRINT_MSG("fun_newCustomString3() usedSecond = %.2f", usedSecond);
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        for(int i = 0; i != loopCount; ++i) {
            newCustomString str;
            str = fun_newCustomString4();
        }
    }
    MK_PRINT_MSG("fun_newCustomString4() usedSecond = %.2f", usedSecond);
}

