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

#ifndef __mkStringUtil
#define __mkStringUtil

#include "string/mkString.h"

class MK_DLL_EXPORT mk_char_string_util
{
public:
    void swap(mk_char_string& lhs, mk_char_string& rhs) noexcept;
    
    int stoi(const mk_char_string& str, size_t* idx = 0, int base = 10);
    long stol(const mk_char_string& str, size_t* idx = 0, int base = 10);
    unsigned long stoul(const mk_char_string& str, size_t* idx = 0, int base = 10);
    long long stoll(const mk_char_string& str, size_t* idx = 0, int base = 10);
    unsigned long long stoull(const mk_char_string& str, size_t* idx = 0, int base = 10);
    float stof(const mk_char_string& str, size_t* idx = 0);
    double stod(const mk_char_string& str, size_t* idx = 0);
    long double stold(const mk_char_string& str, size_t* idx = 0);
    mk_char_string to_string(int val);
    mk_char_string to_string(unsigned val);
    mk_char_string to_string(long val);
    mk_char_string to_string(unsigned long val);
    mk_char_string to_string(long long val);
    mk_char_string to_string(unsigned long long val);
    mk_char_string to_string(float val);
    mk_char_string to_string(double val);
    mk_char_string to_string(long double val);
    //hash
};

class MK_DLL_EXPORT mkStringUtil
{
public:
    
    
    
    
    
    
    
};

#endif //__mkStringUtil
