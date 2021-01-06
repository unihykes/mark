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

#ifndef __mkSourceLocation
#define __mkSourceLocation

class mkSourceLocation
{
public:
    static mkSourceLocation current(const char* file = __FILE__, const char* func = nullptr, const uint32_t line = __LINE__)
    {
        mkSourceLocation result;
        result._file = file;
        result._func = func;
        result._line = line;
        return result;
    }
    
    //获取文件名
    static const char* file_name(const char* file)
    {
        #ifdef __WINDOWS__ 
            const char identify = '\\';
        #else 
            const char identify = '/';
        #endif
        const char* fileName = strrchr(file, identify) ? strrchr(file, identify) + 1 : file;
        return fileName;
    }
    
    const char* file_name() const noexcept
    {
        return _file.c_str();
    }
    
    const char* function_name() const noexcept
    {
        return _func.c_str();
    }
    const uint32_t& line() const noexcept
    {
        return _line;
    }

private:
    std::string _file;
    std::string _func;
    uint32_t _line;
};

#endif