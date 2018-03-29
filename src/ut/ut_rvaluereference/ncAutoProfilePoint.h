/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/

//性能工具
class ncAutoProfilePoint
{
public:
    ncAutoProfilePoint(double& usedSecond)
        : _beginTime(0)
        , _usedSecond(usedSecond)
    {
        #ifdef __WINDOWS__
            QueryPerformanceCounter((LARGE_INTEGER*)&_beginTime);
        #else
            _beginTime = Date::getCurrentTime();
        #endif
    }
    
    ~ncAutoProfilePoint()
    {
        int64_t curtime = 0;
        #ifdef __WINDOWS__
            QueryPerformanceCounter((LARGE_INTEGER*)&curtime);
        #else
            curtime = Date::getCurrentTime();
        #endif
        
        //使用时间
        static int64 frequency = 0;
        if(frequency == 0) {
            #ifdef __WINDOWS__
                QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
            #else
                frequency = Date::ticksPerSecond;
            #endif
        }
        
        _usedSecond = double(curtime - _beginTime)/double(frequency);
    }
private:
    int64_t     _beginTime;
    double&    _usedSecond;
};

//定义一次字符串供测试用
#define SOME_STRING                                                         \
   "890123456789012345678901234567890123456789012345678901234567890123456789\
    890123456789012345678901234567890123456789012345678901234567890123456789\
    890123456789012345678901234567890123456789012345678901234567890123456789\
    890123456789012345678901234567890123456789012345678901234567890123456789\
    890123456789012345678901234567890123456789012345678901234567890123456789\
    890123456789012345678901234567890123456789012345678901234567890123456789\0"