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

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkString
#define __mkString

using mkCharTraits = std::char_traits<mkChar>;
using mkString = std::basic_string<mkChar>;
//using mstring_view = std::basic_string_view<mkChar>;



class MK_DLL_EXPORT mkStringHelper
{
public:
    void swap(mkString& lhs, mkString& rhs) noexcept;
    
    int stoi(const mkString& str, size_t* idx = 0, int base = 10);
    long stol(const mkString& str, size_t* idx = 0, int base = 10);
    unsigned long stoul(const mkString& str, size_t* idx = 0, int base = 10);
    long long stoll(const mkString& str, size_t* idx = 0, int base = 10);
    unsigned long long stoull(const mkString& str, size_t* idx = 0, int base = 10);
    float stof(const mkString& str, size_t* idx = 0);
    double stod(const mkString& str, size_t* idx = 0);
    long double stold(const mkString& str, size_t* idx = 0);
    mkString to_string(int val);
    mkString to_string(unsigned val);
    mkString to_string(long val);
    mkString to_string(unsigned long val);
    mkString to_string(long long val);
    mkString to_string(unsigned long long val);
    mkString to_string(float val);
    mkString to_string(double val);
    mkString to_string(long double val);
    //hash
};




















#endif //__mkString
