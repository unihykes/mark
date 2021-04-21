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

#include <mkheaders.h>
#include"mkFormat.h"

//wchar -> char
shared_ptr<char> 
mkFormat::WcharToChar(const wchar_t* wp) 
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
shared_ptr<wchar_t> 
mkFormat::CharToWchar(const char* p) 
{
    #ifdef __WINDOWS__ 
        return nullptr;
    #else
        return nullptr;
    #endif
}