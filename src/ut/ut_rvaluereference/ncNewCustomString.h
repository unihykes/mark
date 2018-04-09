/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#ifndef __ncNewCustomString
#define __ncNewCustomString

#ifdef __WINDOWS__
    #define usleep   Sleep
    //copy对象时间损耗:单位毫秒
    #define LOSS_TIME  100
#else
    //copy对象时间损耗:单位微秒
    #define LOSS_TIME  100000
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////

class ncNewCustomString
{
public:
    ncNewCustomString()
        :_str(nullptr)
    {
    }
    
    ncNewCustomString(const char* source)
        :_str(nullptr)
    {
        MK_PRINT_MSG("--(const char* source)");
        
        _str = new char[strlen(source)+1];
        strcpy(_str, source);
        usleep (LOSS_TIME * strlen(source) );//模拟其他数据成员的memcopy
    }
    
    ncNewCustomString(const ncNewCustomString& source)
    {
        MK_PRINT_MSG("--(const ncNewCustomString& source)");
        
        _str = new char[strlen(source._str) + 1];
        strcpy(_str, source._str);
        usleep (LOSS_TIME * strlen(source._str) );//模拟其他数据成员的memcopy
    }
    
    ncNewCustomString& operator = (const ncNewCustomString& source)
    {
        MK_PRINT_MSG("--operator = (const ncNewCustomString& source)");
        
        if (this != &source){
            char *tmp = new char[strlen(source._str) + 1];
            strcpy(tmp, source._str);
            usleep (LOSS_TIME * strlen(source._str) );//模拟其他数据成员的memcopy
            delete []_str;
            _str = tmp;
        }
        return *this;
    }
    
    ncNewCustomString(ncNewCustomString&& source)
    {
        MK_PRINT_MSG("--(ncNewCustomString&& source)");
        
        _str = source._str;
        source._str = nullptr;
    }
    
    ncNewCustomString& operator = (ncNewCustomString&& source)
    {
        MK_PRINT_MSG("--operator = (ncNewCustomString&& source)");
        
        _str = source._str;
        source._str = nullptr;
        return *this;
    }
    
   //析构函数
    ~ncNewCustomString()
    {
        if (_str) {
            delete[] _str;
            _str = nullptr;
        }
    }
private:
    char*       _str;
};



#endif //__ncNewCustomString