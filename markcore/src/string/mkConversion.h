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

#ifndef __mkConversion
#define __mkConversion


class MK_DLL_EXPORT mkUTF16LE
{
public:
    static unique_ptr<wchar_t[]> wstr(const char* ptr);
    static unique_ptr<wchar_t[]> wstr(const char* ptr, size_t size);
    static unique_ptr<wchar_t[]> wstr(const char* ptr, size_t offset, size_t size);
};


#endif //__mkConversion
