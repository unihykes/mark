/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)

Time:2018-4

info:

***************************************************************************************************/
#ifndef __ncOldCustomString
#define __ncOldCustomString

#ifdef __WINDOWS__
    #define usleep   Sleep
    //copy对象时间损耗:单位毫秒
    #define LOSS_TIME  100
#else
    //copy对象时间损耗:单位微秒
    #define LOSS_TIME  100000
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////

class ncOldCustomString
{
public:
    ncOldCustomString()
        :_str(nullptr)
    {
    }
    
    ncOldCustomString(const char* source)
        :_str(nullptr)
    {
        MK_PRINT_MSG("--(const char* source)");
        
        _str = new char[strlen(source)+1];
        strcpy(_str, source);
        usleep (LOSS_TIME * (int)strlen(source) );//模拟其他数据成员的memcopy
    }
    
    ncOldCustomString(const ncOldCustomString& source)
    {
        MK_PRINT_MSG("--(const ncOldCustomString& source)");
        
        _str = new char[strlen(source._str) + 1];
        strcpy(_str, source._str);
        usleep (LOSS_TIME * (int)strlen(source._str) );//模拟其他数据成员的memcopy
    }
    
    ncOldCustomString& operator = (const ncOldCustomString& source)
    {
        MK_PRINT_MSG("--operator = (const ncOldCustomString& source)");
        
        if (this != &source){
            char *tmp = new char[strlen(source._str) + 1];
            strcpy(tmp, source._str);
            usleep (LOSS_TIME * (int)strlen(source._str) );//模拟其他数据成员的memcopy
            delete []_str;
            _str = tmp;
        }
        return *this;
    }
    
   //析构函数
    ~ncOldCustomString()
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