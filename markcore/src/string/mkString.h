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
    //string to xx
    template<class Str> static int stoi(const Str& str, size_t* idx = 0, int base = 10);
    
    template<class Str> static long stol(const Str& str, size_t* idx = 0, int base = 10);
    
    template<class Str> static unsigned long stoul(const Str& str, size_t* idx = 0, int base = 10);
    
    template<class Str> static long long stoll(const Str& str, size_t* idx = 0, int base = 10);
    
    template<class Str> static unsigned long long stoull(const Str& str, size_t* idx = 0, int base = 10);
    
    template<class Str> static float stof(const Str& str, size_t* idx = 0);
    
    template<class Str> static double stod(const Str& str, size_t* idx = 0);
    
    template<class Str> static long double stold(const Str& str, size_t* idx = 0);
    
    template<class Str> static int hexstoi(const Str& str)
    {
        int obj;
        std::basic_istringstream<typename Str::value_type> temp(str);
        temp >> std::hex >> obj;
        return obj;
    }
    
    //xx to string
    template<class Str> static Str to_string(int val);
    
    template<class Str> static Str to_string(unsigned val);
    
    template<class Str> static Str to_string(long val);
    
    template<class Str> static Str to_string(unsigned long val);
    
    template<class Str> static Str to_string(long long val);
    
    template<class Str> static Str to_string(unsigned long long val);
    
    template<class Str> static Str to_string(float val);
    
    template<class Str> static Str to_string(double val);
    
    template<class Str> static Str to_string(long double val);
    
    template<class Str> static Str hex_to_string(const int& var, int width)
    {
        std::basic_ostringstream<typename Str::value_type> temp;
        temp << std::hex;
        if(width > 0)
        {
            temp << std::setw(width) << std::setfill<typename Str::value_type>('0');
        }
        temp << var;
        return temp.str();
    }
    
    //
    template<class Str> static void swap(Str& lhs, Str& rhs) noexcept;
    //
    template<class Str> static Str to_upper(const Str& str)
    {
        Str temp(str);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        return temp;
    }
    
    template<class Str> static Str to_lower(const Str& str)
    {
        Str temp(str);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }
    
    template<class Str> static Str trim_left(const Str& str)
    {
        Str temp(str);
        auto it = temp.begin();
        for (it = temp.begin(); it != temp.end(); it++) {
            if (!isspace(*it)) {
                break;
            }
        }
        if (it == temp.end()) {
            temp.clear();
        } else {
            temp.erase(temp.begin(), it);
        }
        return temp;
    }

    template<class Str> static Str trim_right(const Str& str)
    {
        Str temp(str);
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
    
    template<class Str> static Str trim(const Str& str)
    {
        Str temp = trim_left(str);
        return trim_right(temp);
    }
    

    template<class Str> static bool starts_with(Str const & value, Str const & starting)
    {
        if (starting.size() > value.size()) return false;
        return std::equal(starting.begin(), starting.end(), value.begin());
    }

    template<class Str> static bool ends_with(Str const & value, Str const & ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    template<class Str> static bool equals_ignore_case(const Str& str1, const Str& str2)
    {
        return to_lower(str1) == to_lower(str2);
    }

    template<class Str> static bool starts_with_ignore_case(Str const & value, Str const & starting)
    {
        if (starting.size() > value.size()) return false;
        Str temp = value.substr(0, starting.size());
        return equals_ignore_case(starting, temp);
    }

    template<class Str> static bool ends_with_ignore_case(Str const & value, Str const & ending)
    {
        if (ending.size() > value.size()) return false;
        Str temp = value.substr(value.size() - ending.size(), ending.size());
        return equals_ignore_case(ending, temp);
    }


    template<class Str> static std::vector<Str> split(Str const& str, Str const& delimiters)
    {
        struct tokenizer
        {
            tokenizer(Str const& str)
                : _string(str)
                , _offset(0)
            {
            }
            
            bool next_token(Str const& delimiters)
            {
                size_t i = _string.find_first_not_of(delimiters, _offset);
                if (i == Str::npos) {
                    _offset = _string.length();
                    return false;
                }
                size_t j = _string.find_first_of(delimiters, i);
                if (j == Str::npos) {
                    _token = _string.substr(i);
                    _offset = _string.length();
                    return true;
                }
                _token = _string.substr(i, j - i);
                _offset = j;
                return true;
            }

            const Str get_token() const
            {
                return _token;
            }
            size_t _offset;
            const Str _string;
            Str _token;
        };
        
        std::vector<Str> result;
        tokenizer token(str);
        while (token.next_token(delimiters)) {
            result.push_back(token.get_token());
        }
        return result;
    }
    
    //hash
    //todo
};


template<class Str> 
void mkStringHelper::swap(Str& lhs, Str& rhs) noexcept
{
}











#endif //__mkString
