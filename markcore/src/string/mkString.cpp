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
#include "mkModuleInstance.h"
#include "utility/mkException.h"
#include "utility/mkLog.h"
#include "mkString.h"

const mkString mkStringHelper::EMPTY;

size_t 
mkStringHelper::findAny(const mkString& src, size_t offset, const mkString& dest)
{
    if (offset > src.size()) {
        MK_THROW(1024, _T("IDS_OFFSET_OFR"));
    }
    
    size_t pos = 0;
    for(const auto& elem : src) {
        if(pos >= offset) {
            for(const auto& item : dest) {
                if(elem == item) {
                    return pos;
                }
            }
        }
        ++pos;
    }
    return mkString::npos;
}

size_t 
mkStringHelper::findAny(const mkString& src, const mkString& dest)
{
    return findAny (src, 0, dest);
}

size_t 
mkStringHelper::findLastOfAny(const mkString& src, size_t offset, const mkString& dest)
{
    if (offset >= src.size()) {
        MK_THROW(1024, _T("IDS_OFFSET_OFR"));
    }
    
    size_t destSize = dest.size();
    
    for (size_t pos = offset; pos != mkString::npos; --pos) {
        for (size_t loop = 0; loop != destSize; loop++)
            if (src[pos] == dest[loop])
                return pos;
    }

    return mkString::npos;
    
}

size_t 
mkStringHelper::findLastOfAny(const mkString& src, const mkString& dest)
{
    return findLastOfAny (src, src.size()-1, dest);
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, const mkString& dest)
{
    return compareIgnoreCase (src, 0, src.size(),  dest.c_str(), dest.size());
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkString& dest)
{   
    return compareIgnoreCase (src, offset, number, dest.c_str(), dest.size());
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkString& dest, size_t roffset, size_t count)
{
    return compareIgnoreCase (src, offset, number, dest.c_str() + roffset, count);
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, const mkChar *ptr)
{
    #ifdef __WINDOWS__
        return compareIgnoreCase (src, 0, src.size(), ptr, wcslen(ptr));
    #else
        return compareIgnoreCase (src, 0, src.size(), ptr, strlen(ptr));
    #endif
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkChar *ptr)
{
    #ifdef __WINDOWS__
        return compareIgnoreCase (src, offset, number, ptr, wcslen(ptr));
    #else
        return compareIgnoreCase (src, offset, number, ptr, strlen(ptr));
    #endif
}

int 
mkStringHelper::compareIgnoreCase(const mkString& src, size_t offset, size_t number, const mkChar* ptr, size_t count )
{
    size_t size = src.size();    
    
    if (size < offset) {
        MK_THROW(1024, _T("IDS_OFFSET_OFR"));
    }
    
    if (size - offset < number) {
        number = size - offset;
    }
    
    size_t answer = 0;
    if (number != 0) {
        size_t tmp = number < count ? number : count;
        const mkChar* first1 = src.c_str() + offset;
        const mkChar* first2 = ptr;
         
        for (; 0 < tmp; --tmp, ++first1, ++first2) {
            if (*first1 != *first2) {
                mkChar u1 = ::toupper (*first1);
                mkChar u2 = ::toupper (*first2);
                if (u1 != u2) {
                    u1 = ::tolower (u1); 
                    u2 = ::tolower (u2); 
                    
                     if (u1 != u2) {
                        answer = (u1 < u2) ? -1 : 1;
                        break;
                    }
                }
            }
        }
    }
    return (answer != 0 ? (int)answer : number < count ? -1    : number == count ? 0 : +1);
}

mkString& 
mkStringHelper::replace(mkString& src, mkChar oldValue, mkChar newValue, bool replaceAll)
{
    if (oldValue != newValue) {
        for(auto& elem : src) {
            if(elem == oldValue) {
                elem = newValue;
                if(!replaceAll) {
                    break;
                }
            }
        }
    }
    return src;
}

void 
mkStringHelper::toUpper(mkString& src)
{
    for(auto& elem : src) {
        elem = ::toupper(elem);
    }
}

void 
mkStringHelper::toLower(mkString& src)
{
    for(auto& elem : src) {
        elem = ::tolower(elem);
    }
}

mkString 
mkStringHelper::trim(const mkString& src)
{
    return trim(src, _T(' '));
}

mkString 
mkStringHelper::trim(const mkString& src, mkChar ch)
{
    if (src.empty()) {
        return src;
    }
    
    const mkChar* ptr = src.c_str();
    const size_t size = src.size();
    size_t preLen = 0;
    
    // traverse from the begining
    while (*ptr == ch && preLen < size) {
        ++preLen, ++ptr;
    }

    // traverse from the end
    size_t postLen = size;
    ptr = src.c_str() + size - 1;
    while (*ptr == ch && (postLen > preLen)) {
        --postLen, --ptr;
    }
    
    return mkString(src.c_str() + preLen, postLen - preLen);
}

mkString 
mkStringHelper::trim_left(const mkString& src)
{
    mkString temp(src);
    auto it = temp.begin();
    for (; it != temp.end(); it++) {
        if (!isspace(*it)) {
            break;
        }
    }
    if (it == temp.end()) {
        temp.clear();
    } 
    else {
        temp.erase(temp.begin(), it);
    }
    return temp;
}

mkString 
mkStringHelper::trim_right(const mkString& src)
{
    mkString temp(src);
    for (auto it = temp.end() - 1; ;it--) {
        if (!isspace(*it)) {
            temp.erase(it + 1, temp.end());
            break;
        }
        if (it == temp.begin()) {
            temp.clear();
            break;
        }
    }
    return temp;
}

mkString 
mkStringHelper::leftString(const mkString& src, size_t count)
{
    if (count > src.size()) {
        MK_THROW(1024, _T("the count(%lld) is too long."), count);
    }
    return mkString(src, 0, count);
}

mkString 
mkStringHelper::rightString (const mkString& src, size_t count)
{
    if (count > src.size()) {
        MK_THROW(1024, _T("the count(%lld) is too long."), count);
    }
    return mkString(src, src.size() - count, src.size());
}

mkString 
mkStringHelper::beforeFirst (const mkString& src, mkChar ch)
{
    size_t offset = src.find_first_of (ch);
    return offset == mkString::npos ? src : mkString(src, 0, offset);
}

mkString 
mkStringHelper::beforeLast (const mkString& src, mkChar ch)
{
    size_t offset = src.find_last_of (ch);
    return offset == mkString::npos ? mkString() : mkString(src, 0, offset);
}

mkString 
mkStringHelper::afterFirst (const mkString& src, mkChar ch)
{
    size_t offset = src.find_first_of(ch);
    return offset == mkString::npos ? mkString() : mkString(src.c_str() + offset + 1, src.size() - offset - 1);
}

mkString 
mkStringHelper::afterLast(const mkString& src, mkChar ch)
{
    size_t offset = src.find_last_of(ch);
    return offset == mkString::npos ? src : mkString(src.c_str() + offset + 1, src.size() - offset - 1);
}

bool 
mkStringHelper::startsWith(const mkString & src, const mkString& prefix)
{
    if (prefix.size() > src.size()) 
        return false;
    return std::equal(prefix.begin(), prefix.end(), src.begin());
}

bool 
mkStringHelper::startsWith(const mkString & src, const mkChar* prefix)
{
    const auto* ptr = src.c_str();     
    
    while (*prefix ) {
        if (*prefix++ != *ptr++) {
            return false;
        }
    }
    return true;
}

bool 
mkStringHelper::endsWith(const mkString & src, const mkString& suffix)
{
    if (suffix.size() > src.size()) 
        return false;
    return std::equal(suffix.rbegin(), suffix.rend(), src.rbegin());
}

int 
mkStringHelper::freq(const mkString & src, mkChar ch)
{
    int count = 0;
    for(const auto& elem : src) {
        if(elem == ch) {
            ++count;
        }
    }
    return count;
}

void 
mkStringHelper::split(const mkString& src, const mkString& separators, std::vector<mkString>& substrs)
{
    struct tokenizer
    {
        tokenizer(mkString const& src)
            : _src(src)
            , _offset(0)
        {
        }
        
        bool next_token(mkString const& separators)
        {
            size_t i = _src.find_first_not_of(separators, _offset);
            if (i == mkString::npos) {
                _offset = _src.length();
                return false;
            }
            size_t j = _src.find_first_of(separators, i);
            if (j == mkString::npos) {
                _token = _src.substr(i);
                _offset = _src.length();
                return true;
            }
            _token = _src.substr(i, j - i);
            _offset = j;
            return true;
        }

        const mkString get_token() const
        {
            return _token;
        }
        
        const mkString& _src;
        size_t _offset;
        mkString _token;
    };
    
    
    tokenizer token(src);
    while (token.next_token(separators)) {
        substrs.push_back(token.get_token());
    }
}

void 
mkStringHelper::split (const mkString& src, mkChar separator, std::vector<mkString>& substrs)
{
    split(src, mkString(1, separator), substrs);
}

void 
mkStringHelper::splitAny(const mkString& src, const mkString& separators, std::vector<mkString>& substrs)
{
    if (src.empty())
        return;
    
    if (separators.empty ()) {
        substrs.push_back (src);
        return;
    }
    
    size_t off = 0;
    size_t index = findAny (src, off, separators);
    size_t sepslength = separators.size (); 
    while (true) {
        if (index == mkString::npos) {
            substrs.push_back (src.substr(off));
            break;
        }
        else {
            substrs.push_back(src.substr(off, index - off));
        }

        off = index + 1;
        if (off >= src.size()) {
            // last is a seperator
            substrs.push_back(mkStringHelper::EMPTY);
            break;
        }
        
        index = findAny (src, off, separators);
    }
}

mkString 
mkStringHelper::toString(const bool& val)
{
    if (val) {
        return mkString(_T("True"));
    }
    else {
        return mkString(_T("False"));
    }
}

mkString 
mkStringHelper::toString(const short val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const unsigned short val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const int val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const unsigned int val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const int64_t val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const uint64_t val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const float val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

mkString 
mkStringHelper::toString(const double val)
{
    #ifdef __WINDOWS__
        return std::to_wstring(val);
    #else
        return std::to_string(val);
    #endif
}

#ifdef __WINDOWS__
bool 
mkStringHelper::startsWith(const std::string & src, const char* prefix)
{
    const auto* ptr = src.c_str();     
    
    while (*prefix ) {
        if (*prefix++ != *ptr++) {
            return false;
        }
    }
    return true;
}

unique_ptr<wchar_t[]> 
mkStringHelper::conv(const char* ptr)
{
    return mkUTF16LE::wstr(ptr);
}

unique_ptr<wchar_t[]> 
mkStringHelper::conv(const char* ptr, size_t size)
{
    return mkUTF16LE::wstr(ptr, size);
}

unique_ptr<wchar_t[]>
mkStringHelper::conv(const char* ptr, size_t offset, size_t size)
{
    return mkUTF16LE::wstr(ptr, offset, size);
}

#endif
