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
#ifdef __WINDOWS__
#else
    #include <sys/time.h>
#endif

#include <ctime>
#include<mkheaders.h>
#include"mkTime.h"


int64
mkTime::GetCurrentTime()
{
    #ifdef __WINDOWS__
        SYSTEMTIME sysTime;
        ::GetSystemTime(&sysTime);
        
        FILETIME fileTime;
        ::SystemTimeToFileTime (&sysTime, &fileTime);
        
        int64 result = fileTime.dwHighDateTime;
        result = result << 32;
        result |= fileTime.dwLowDateTime;
        result /= 10;
        result -= 11644473600000000;//转为unix
        return result;
    #else
        struct timeval currTime;
        int64 result = 0;
        if (gettimeofday(&currTime, NULL) == 0) {
            result = ((int64)currTime.tv_sec * 1000000 + currTime.tv_usec);
        }
        return result;
    #endif
}

string 
mkTime::GetCurrentTimeStr()
{
    time_t rawtime;
    time(&rawtime); 
    string result = ctime(&rawtime);//todo:ctime()线程不安全,多线程会存在问题
    
    //移除末尾\n
    auto pos = result.find_last_of('\n');
    if(pos != string::npos) {
        result.erase(pos, 1);
    }
    
    return result;
}

mkTime::mkTime(const int64 time)
{
    
}

mkTime::~mkTime()
{
    
}