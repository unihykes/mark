﻿/***************************************************************************************************
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

Time:2019-4

info:

***************************************************************************************************/

#ifndef __mkFormat
#define __mkFormat

//初等模板
template<typename T, int N> class mkFormat;

//偏特化:char
template<int N>
class mkFormat<char, N>
{
public:
    template<typename ... TArgs>
    const char* operator()(const char* format, TArgs... args)
    {
        std::snprintf(_buf, N, format, args...);
        return _buf;
    }
    
private:
    char _buf[N];
};

//偏特化:wchar_t
template<int N>
class mkFormat<wchar_t, N>
{
public:
    template<typename ... TArgs>
    const wchar_t* operator()(const wchar_t* format, TArgs... args)
    {
        std::swprintf(_buf, N, format, args...);
        return _buf;
    }
    
private:
    wchar_t _buf[N];
};


using Format16 =mkFormat<char,16>;
using Format32 =mkFormat<char,32>;
using Format64 =mkFormat<char,64>;
using Format128 =mkFormat<char,128>;
using Format256 =mkFormat<char,256>;
using Format512 =mkFormat<char,512>;
using Format1024 =mkFormat<char,1024>;
using Format4096 =mkFormat<char,4096>;

using Format16W =mkFormat<wchar_t,16>;
using Format32W =mkFormat<wchar_t,32>;
using Format64W =mkFormat<wchar_t,64>;
using Format128W =mkFormat<wchar_t,128>;
using Format256W =mkFormat<wchar_t,256>;
using Format512W =mkFormat<wchar_t,512>;
using Format1024W =mkFormat<wchar_t,1024>;
using Format4096W =mkFormat<wchar_t,4096>;

#endif //__mkFormat