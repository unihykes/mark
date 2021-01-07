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

class mkString
{
public:
    static bool startsWith(const std::string src, const char* dest)
    {
        const char* pSrc = src.c_str();  
        while (*dest) {
            if (*dest++ != *pSrc++) {
                return false;
            }
        }
        return true;
    }
    
public:
    operator std::basic_string<auto_char>()
    {
        return _imp;
    }
    
    mkString()
    {
    }
    
    mkString(auto_char ch)
    {
        
    }
    
    mkString(auto_char* ptr)
    {
        
    }
    
    

private:
    std::basic_string<auto_char>    _imp;
};

namespace std {
struct tchar_less : public binary_function<const auto_char*, const auto_char*, bool>
{
	bool operator()(const auto_char* const _Left, const auto_char* const _Right) const
	{
#ifdef __WINDOWS__
		return (::wcscmp (_Left, _Right) < 0);
#else
		return (strcmp (_Left, _Right) < 0);
#endif
	}
};

struct tchar_less_nocase : public binary_function<const auto_char*, const auto_char*, bool>
{
	bool operator()(const auto_char* const _Left, const auto_char* const _Right) const
	{
#ifdef __WINDOWS__
	return (::_wcsicmp (_Left, _Right) < 0);
#else
	return (::strcasecmp (_Left, _Right) < 0);
#endif

	}
};

class tchars_equal : public std::binary_function<const auto_char*, const auto_char*, bool>
{
public:
	bool operator() (const auto_char* left, const auto_char* right) const
	{
#ifdef __WINDOWS__
		if (::wcscmp (left, right) == 0)
#else
		if (::strcmp (left, right) == 0)
#endif
			return true;
		else
			return false;
	}
};
}// namespace std


#endif //__mkString
