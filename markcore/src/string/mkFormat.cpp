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

string 
mkBytesFormat::str(const int64& bytes, int acc)
{
    string ret;
    if(bytes < 0) {
        //todo:不允许负数
        ret = mkFormat::str(_T("-"));
    }

    else if (bytes == 0) {
    	ret = mkFormat::str(_T("0.00 B"));
    }
    else {
    	int bits = 0;
    	int64 temp = bytes;
    	for (; temp > 0; bits++) {
    		temp >>= 10;
        }
        
    	switch (bits) {
    	case 1:
            if(acc == 0) {
                ret = mkFormat::str(_T("%lld B"), bytes);
            }
    		else {
                ret = mkFormat::str(_T("%.2f B"), (double)bytes);
            }
    		break;

    	case 2:
            if(acc == 0) {
                ret = mkFormat::str(_T("%lld KB"), bytes>>10);
            }
    		else {
    		    ret = mkFormat::str(_T("%.2f KB"), (double)bytes/1024.0);
            }
    		break;

    	case 3:
    		if(acc == 0) {
                ret = mkFormat::str(_T("%lld MB"), bytes>>20);
            }
    		else {
                ret = mkFormat::str(_T("%.2f MB"), (double)bytes/1048576.0);
            }
    		break;

    	case 4:
            if(acc == 0) {
                ret = mkFormat::str(_T("%lld GB"), bytes>>30);
            }
    		else {
    		    ret = mkFormat::str(_T("%.2f GB"), (double)bytes/1073741824.0);
            }
    		break;

    	case 5:
    		if(acc == 0) {
                ret = mkFormat::str(_T("%lld TB"), bytes>>40);
            }
    		else {
                ret = mkFormat::str(_T("%.2f TB"), (double)bytes/1099511627776.0);
            }
    		break;

    	default:
            if(acc == 0) {
                ret = mkFormat::str(_T("%lld PB"), bytes>>50);
            }
            else {
    		     ret = mkFormat::str(_T("%.2f PB"), (double)bytes/1125899906842624.0);
            }
    		break;
    	}
    }
    return ret;
}
