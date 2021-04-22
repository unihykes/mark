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

#include "mkFormat.h"
#include "mkConversion.h"

using mkCharTraits = std::char_traits<mkChar>;
using mkCharAlloc = std::allocator<mkChar>;
using mkString = std::basic_string<mkChar, mkCharTraits, mkCharAlloc>;

class MK_DLL_EXPORT mkStringHelper
{
public:
    static size_t findAny(const mkString& src, size_t offset, const mkString& dest);
    static size_t findAny(const mkString& src, const mkString& dest);
    static size_t findLastOfAny(const mkString& src, size_t offset, const mkString& dest);
    static size_t findLastOfAny(const mkString& src, const mkString& dest);
    
    static int compareIgnoreCase(const mkString& src, const mkString& dest);
    static int compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkString& dest);
    static int compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkString& dest, size_t roffset, size_t count);
    static int compareIgnoreCase(const mkString& src, const mkChar *ptr);
    static int compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkChar *ptr);
    static int compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkChar* ptr, size_t count );
    
    static mkString& replace(mkString& src, mkChar oldValue, mkChar newValue, bool replaceAll = false);
    
    static void toUpper(mkString& src);
    static void toLower(mkString& src);
    
    static mkString trim(const mkString& src);
    static mkString trim(const mkString& src, mkChar ch);
    static mkString trim_left(const mkString& src);
    static mkString trim_right(const mkString& src);
    
    static mkString leftString(const mkString& src, size_t count);
    static mkString rightString(const mkString& src, size_t count);
    static mkString beforeFirst(const mkString& src, mkChar ch);
    static mkString beforeLast(const mkString& src, mkChar ch);
    static mkString afterFirst(const mkString& src, mkChar ch);
    static mkString afterLast(const mkString& src, mkChar ch);
    
    static bool startsWith(const mkString & src, const mkString& prefix);
    static bool startsWith(const mkString & src, const mkChar* prefix);
    static bool endsWith(const mkString & src, const mkString& suffix);
    
    static int freq(const mkString & src, mkChar ch);
    
    static void split(const mkString& src, const mkString& separators, std::vector<mkString>& substrs);
    static void split(const mkString& src, mkChar separator, std::vector<mkString>& substrs);
    static void splitAny(const mkString& src, const mkString& separators, std::vector<mkString>& substrs);
    
    static mkString toString(const bool& val);
    static mkString toString(const short val);
    static mkString toString(const unsigned short val);
    static mkString toString(const int val);
    static mkString toString(const unsigned int val);
    static mkString toString(const int64_t val);
    static mkString toString(const uint64_t val);
    static mkString toString(const float val);
    static mkString toString(const double val);
    
    template<typename ... TArgs>
    static mkString format(const mkChar* fmt, TArgs... args)
    {
        #ifdef __WINDOWS__
            auto buf = mkFormat::uniqueW(fmt, args...);
            return mkString(buf.get());
        #else
            auto buf = mkFormat::unique(fmt, args...);
            return mkString(buf.get());
        #endif
    }

//windows下特定方法
#ifdef __WINDOWS__
    template<typename ... TArgs>
    static mkString format(const char* fmt, TArgs... args)
    {
        auto buf = mkFormat::unique(fmt, args...);
        return mkString(mkUTF16LE::wstr(buf.get()).get());
    }
    
    static bool startsWith(const std::string& src, const char* prefix);
    static unique_ptr<wchar_t[]> conv(const char* ptr);
    static unique_ptr<wchar_t[]> conv(const char* ptr, size_t size);
    static unique_ptr<wchar_t[]> conv(const char* ptr, size_t offset, size_t size);
#endif
    
public:
    static const mkString EMPTY;
};

#endif //__mkString
