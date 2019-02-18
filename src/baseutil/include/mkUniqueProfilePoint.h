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

Time:2018-3
    基于生命周期作用域的性能分析小工具
info:

***************************************************************************************************/
#ifndef __mkUniqueProfilePoint
#define __mkUniqueProfilePoint

#ifdef __LINUX__
    #include <sys/time.h>
#else
    #include <windows.h>
#endif

//性能工具
class mkUniqueProfilePoint
{
public:
    mkUniqueProfilePoint(double& usedSecond)
        : _usedSecond(usedSecond)
    {
        #ifdef __WINDOWS__
            QueryPerformanceFrequency((LARGE_INTEGER*)&_frequency);
            QueryPerformanceCounter((LARGE_INTEGER*)&_beginTime);//单位微秒
            
        #else
            _frequency = 1000000;
            gettimeofday(&_beginTime, NULL);
        #endif
    }
    
    ~mkUniqueProfilePoint()
    {
        
        #ifdef __WINDOWS__
            int64_t curtime = 0;
            QueryPerformanceCounter((LARGE_INTEGER*)&curtime);
            _usedSecond = double(curtime - _beginTime)/double(_frequency);
        #else
            struct timeval curtime;
            gettimeofday(&curtime, NULL);
            _usedSecond = double(curtime.tv_sec - _beginTime.tv_sec) + double(curtime.tv_usec - _beginTime.tv_usec)/1000000;
        #endif
    }
private:
#ifndef __WINDOWS__
    struct timeval      _beginTime;
#else
    int64_t             _beginTime;
#endif
    int64_t             _frequency;
    double&             _usedSecond;
};

#endif