/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/

#ifndef __ncMetadataObj
#define __ncMetadataObj

#include "ncOldCustomString.h"
#include "ncNewCustomString.h"

#ifdef __WINDOWS__
    #define usleep   Sleep
    //copy对象时间损耗:单位毫秒
    #define LOSS_TIME  100
#else
    //copy对象时间损耗:单位微秒
    #define LOSS_TIME  100000
#endif



//模拟一个应用层的元数据对象
class ncMetadataObj
{
public:
    ncMetadataObj()
    {
    }
    
    ~ncMetadataObj()
    {
    }
    
    //构造函数-oldstring
    ncMetadataObj(const ncOldCustomString& str)
        : _oldCustomStr(str)
    {
        MK_PRINT_MSG("--(const ncOldCustomString& str)");
    }
    
    ncMetadataObj(ncOldCustomString&& str)
        : _oldCustomStr(std::move(str))
    {
        MK_PRINT_MSG("--(ncOldCustomString&& str)");
    }
    
    //构造函数-newstring
    ncMetadataObj(const ncNewCustomString& str)
        : _newCustomStr(str)
    {
        MK_PRINT_MSG("--(const ncNewCustomString& str)");
    }
    
    ncMetadataObj(ncNewCustomString&& str)
        : _newCustomStr(std::move(str))
    {
        MK_PRINT_MSG("--(ncNewCustomString&& str)");
    }
    
    //拷贝构造函数
    ncMetadataObj(const ncMetadataObj& source)
    {
        MK_PRINT_MSG("--(const ncMetadataObj& source)");
        
        _oldCustomStr = source._oldCustomStr;
        _newCustomStr = source._newCustomStr;
        
        //模拟指针对象深拷贝
        //memcopy(...);
        usleep (LOSS_TIME);//模拟其他数据成员的memcopy
    }
    
    ncMetadataObj& operator = (const ncMetadataObj& source)
    {
        MK_PRINT_MSG("--operator = (const ncMetadataObj& source)");
        
        if (this != &source){
            _oldCustomStr = source._oldCustomStr;
            _newCustomStr = source._newCustomStr;  
            usleep (LOSS_TIME);//模拟其他数据成员的memcopy
        }
        
        return *this;
    }
    
    ncMetadataObj(ncMetadataObj&& source)
    {
        MK_PRINT_MSG("--(ncMetadataObj&& source)");
        
        _oldCustomStr = std::move(source._oldCustomStr);
        _newCustomStr = std::move(source._newCustomStr);
    }
    
    ncMetadataObj& operator = (ncMetadataObj&& source)
    {
        MK_PRINT_MSG("--operator = (ncMetadataObj&& source)");
        
        _oldCustomStr = std::move(source._oldCustomStr);
        _newCustomStr = std::move(source._newCustomStr);
        
        return *this;
    }
    
    void fun()
    {
        MK_PRINT_MSG("");
    }
    
    void push_back(const ncNewCustomString& str)
    {
        _newCustomStr = str;
    }
    
    void push_back(ncNewCustomString&& str)
    {
        _newCustomStr = std::move(str);
    }
    
private:
    ncOldCustomString           _oldCustomStr;
    ncNewCustomString           _newCustomStr;
};

#endif //__ncMetadataObj