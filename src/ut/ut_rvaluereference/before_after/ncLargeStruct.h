/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#ifndef __ncLargeStruct
#define __ncLargeStruct

#ifndef __ENABLE_CXX11__
    #define nullptr    NULL
#endif

#ifdef __WINDOWS__
    #define usleep   Sleep
    //copy对象时间损耗:单位毫秒
    #define LOSS_TIME  10
#else
    //copy对象时间损耗:单位微秒
    #define LOSS_TIME  10000
#endif

//模拟一个copy性能不太好的struct
class ncLargeStruct
{
public:
    ncLargeStruct()
        :_str(nullptr)
    {
        //默认1k字节
        _str = new char[1024];
        memset(_str, 'a', 1024);
        usleep (1000);//模拟其他数据成员的初始化操作
    }
    
    ncLargeStruct(const char* source)
        :_str(nullptr)
    {
        _str = new char[strlen(source)+1];
        strcpy(_str, source);
        usleep (LOSS_TIME);//模拟其他数据成员的copy操作
    }
    
    ncLargeStruct(const ncLargeStruct& source)
    {
        _str = new char[strlen(source._str) + 1];
        strcpy(_str, source._str);
        usleep (LOSS_TIME);//模拟其他数据成员的copy操作
    }
    
    ncLargeStruct& operator = (const ncLargeStruct& source)
    {
        if (this != &source){
            char *tmp = new char[strlen(source._str) + 1];
            strcpy(tmp, source._str);
            usleep (LOSS_TIME);//模拟其他数据成员的copy操作
            delete []_str;
            _str = tmp;
        }
        return *this;
    }
    
    #ifdef __ENABLE_CXX11__
    ncLargeStruct(ncLargeStruct&& source)
    {
        _str = source._str;
        source._str = nullptr;
    }
    
    ncLargeStruct& operator = (ncLargeStruct&& source)
    {
        _str = source._str;
        source._str = nullptr;
        return *this;
    }
    #endif
    
   //析构函数
    ~ncLargeStruct()
    {
        if (_str) {
            delete[] _str;
            _str = nullptr;
        }
    }
private:
    char*       _str;
};

#endif