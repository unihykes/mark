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

Time:2021-1

info:

***************************************************************************************************/

#ifndef __mkLog
#define __mkLog

#include "types/mkFormat.h"


class MK_DLL_EXPORT mkLog
{
public:
    mkLog(const std::string& moduleName);
    ~mkLog();
    
    bool Enable();
    
    template<typename ... TArgs>
    void operator()(const char* file, int line, const char* func, const char* format, TArgs... args)
    {
        shared_ptr<char> msg = mkSharedFormat::fmt(format, args...);
        Output(file, line, func, msg.get());
    }
    
    template<typename ... TArgs>
    void operator()(const char* file, int line, const char* func, const wchar_t* format, TArgs... args)
    {
        string msg = mkSharedFormat::fmtW(format, args...);
        Output(file, line, func, msg.c_str());
    }
    
private:
    void Output(const char* file, int line, const char* func, const char* msg);
    
private:
    std::string     _moduleName;
    std::string     _fileName;
};

#endif