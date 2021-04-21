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
#include "mkConversion.h"

#ifdef __WINDOWS__
    #include "win-iconv/iconv.h"
#else
    #include <iconv.h>
#endif

enum class mkEnctype
{
	ASCII,
	UTF8,
	UTF16LE,
	UTF16BE,
	UTF32LE,
	UTF32BE,	
};

unique_ptr<wchar_t[]>
mkUTF16LE::wstr(const char* ptr)
{
    return wstr(ptr, 0, strlen(ptr));
}

unique_ptr<wchar_t[]>
mkUTF16LE::wstr(const char* ptr, size_t size)
{
    return wstr(ptr, 0, size);
}

#ifdef __WINDOWS__
unique_ptr<wchar_t[]> 
mkUTF16LE::wstr(const char* ptr, size_t offset, size_t size)
{
    const char* in = ptr + offset;
    if(!in) {
        MK_THROW(1024, "nullptr");
    }
    
    mkEnctype type = mkEnctype::ASCII;//todo
    
    if(type == mkEnctype::ASCII) {
        iconv_t c = iconv_open ("UTF-16LE", "GB18030");
        if (c == (iconv_t)(-1)) {
            MK_THROW(1024, "iconv_open error");
        }
        
        size_t inleftSize = size;
        size_t outleftSize = inleftSize*2 + 2;
        unique_ptr<wchar_t[]> buf(new wchar_t[inleftSize+1]);
        buf[inleftSize]=_T('\0');
        
        wchar_t* outbufW = static_cast<wchar_t*>(buf.get());
        char* outbuf = (char*)(outbufW);
        
        size_t ret = iconv(c, &in, &inleftSize, &outbuf, &outleftSize);
        if (ret == -1) {
            MK_THROW(1024, "iconv error");
        }
        iconv_close(c);
        return buf;
    }
    return nullptr;
}
#else
unique_ptr<wchar_t[]>  
mkUTF16LE::wstr(const char* ptr, size_t offset, size_t size)
{
    MK_THROW(1024, "todo");
}
#endif