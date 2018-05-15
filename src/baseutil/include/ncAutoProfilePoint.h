/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/
#ifndef __ncAutoProfilePoint
#define __ncAutoProfilePoint

#ifdef __LINUX__
    #include <sys/time.h>
#else
    #include <windows.h>
#endif

//性能工具
class ncAutoProfilePoint
{
public:
    ncAutoProfilePoint(double& usedSecond)
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
    
    ~ncAutoProfilePoint()
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