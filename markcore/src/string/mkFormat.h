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

Time:2019-4

info:

***************************************************************************************************/

#ifndef __mkFormat
#define __mkFormat

//#include <memory>//for xx
#include "utility/mkTypeCast.h"

class mkSharedFormat
{
public:
    template<typename ... TArgs>
    static shared_ptr<char> fmt(const char* format, TArgs... args)
    {
        //计算缓冲区size
        int size = std::snprintf(nullptr, 0, format, args...);
        shared_ptr<char> buf = shared_ptr<char>(new char[size+1], std::default_delete<char[]>());
        std::snprintf(buf.get(), size+1, format, args...);
        return buf;
    }
    
    template<typename ... TArgs>
    static shared_ptr<wchar_t> fmt(const wchar_t* format, TArgs... args)
    {
        //计算缓冲区size
        int size = std::swprintf(nullptr, 0, format, args...);
        shared_ptr<wchar_t> buf = shared_ptr<wchar_t>(new wchar_t[size+1], std::default_delete<wchar_t[]>());
        std::swprintf(buf.get(), size+1, format, args...);
        return buf;
    }
    
    template<typename ... TArgs>
    string operator()(const char* format, TArgs... args)
    {
        shared_ptr<char> buf = fmt(format, args...);
        return string(buf.get());
    }
    
    template<typename ... TArgs>
    string operator()(const wchar_t* format, TArgs... args)
    {
        shared_ptr<wchar_t> bufW = mkSharedFormat::fmt(format, args...);
        shared_ptr<char> buf = WcharToChar(bufW.get());
        return string(buf.get());
    }
    
private:
    //wchar -> char
    static shared_ptr<char> WcharToChar(const wchar_t* wp) 
    {
        #ifdef __WINDOWS__ 
            const unsigned int m_encode = CP_ACP;//默认
            int len = WideCharToMultiByte(m_encode, 0, wp, (int)wcslen(wp), NULL, 0, NULL, NULL);
            
            shared_ptr<char> buf = shared_ptr<char>(new char[len+1], std::default_delete<char[]>());
            WideCharToMultiByte(m_encode, 0, wp, (int)wcslen(wp), buf.get(), len, NULL, NULL);
            buf.get()[len] = '\0';
            return buf;
        #else
            return nullptr;
        #endif
    }

    //char -> wchar
    static shared_ptr<wchar_t> CharToWchar(const char* wp) 
    {
        #ifdef __WINDOWS__ 
            return nullptr;
        #else
            return nullptr;
        #endif
    }
};

class mkUniqueFormat
{
public:
    template<typename ... TArgs>
    static unique_ptr<char[]> fmt(const char* format, TArgs... args)
    {
        //计算缓冲区size
        int size = std::snprintf(nullptr, 0, format, args...);
        unique_ptr<char[]> buf (new char[size+1]);
        std::snprintf(buf.get(), size+1, format, args...);
        return buf;
    }
    
    template<typename ... TArgs>
    static unique_ptr<wchar_t[]> fmt(const wchar_t* format, TArgs... args)
    {
        //计算缓冲区size
        int size = std::swprintf(nullptr, 0, format, args...);
        unique_ptr<wchar_t[]> buf(new wchar_t[size+1]);
        std::swprintf(buf.get(), size+1, format, args...);
        return buf;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template<int N>
class mkFixedFormat
{
public:
    ~mkFixedFormat()
    {
        _buf[0] = '\0';
    }
    
    //使用时需要确保对象不被析构,否则返回值是野指针
    template<typename ... TArgs>
    const char* operator()(const char* format, TArgs... args)
    {
        std::snprintf(_buf, N, format, args...);
        return _buf;
    }
    
private:
    char _buf[N];//使用时需要确保对象不被析构,否则出现野指针
};
template<> class mkFixedFormat<0>;//禁用偏特化:<0>


template<int N>
class mkFixedFormatW
{
public:
    ~mkFixedFormatW()
    {
        _buf[0] = '\0';
    }
    
    //使用时需要确保对象不被析构,否则返回值是野指针
    template<typename ... TArgs>
    const wchar_t* operator()(const wchar_t* format, TArgs... args)
    {
        std::swprintf(_buf, N, format, args...);
        return _buf;
    }
    
private:
    wchar_t _buf[N];
};
template<> class mkFixedFormatW<0>;//禁用偏特化:<0>

using Format8 = mkFixedFormat<8>;
using Format16 = mkFixedFormat<16>;
using Format32 = mkFixedFormat<32>;
using Format64 = mkFixedFormat<64>;
using Format128 = mkFixedFormat<128>;
using Format256 = mkFixedFormat<256>;
using Format512 = mkFixedFormat<512>;
using Format1024 = mkFixedFormat<1024>;
using Format4096 = mkFixedFormat<4096>;

using Format8W = mkFixedFormatW<8>;
using Format16W = mkFixedFormatW<16>;
using Format32W = mkFixedFormatW<32>;
using Format64W = mkFixedFormatW<64>;
using Format128W = mkFixedFormatW<128>;
using Format256W = mkFixedFormatW<256>;
using Format512W = mkFixedFormatW<512>;
using Format1024W = mkFixedFormatW<1024>;
using Format4096W = mkFixedFormatW<4096>;

#endif //__mkFormat
