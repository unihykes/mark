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
#ifdef __LINUX__
    #include <sys/time.h>
#else
    #include <windows.h>
#endif
#include <mkheaders.h>
#include <iostream>
#include "mkPerf.h"
#include "markcore.h"

class mkPerfFuncInfo
{
public:
    mkPerfFuncInfo(const char* func, int line) 
        : _func(func)
        , _line(line) 
    {
    }
    
    inline bool operator < (const mkPerfFuncInfo& target) const
    {
        if (_func < target._func)
            return true;
        else if(_func == target._func)
            return _line < target._line;
        else
            return false;
    }
    
    string _func;
    int _line;
};

class mkPerfTimeInfo : public std::enable_shared_from_this<mkPerfTimeInfo>
{
public:
    mkPerfTimeInfo()
        : _useTime(0)
        , _callNum(0)
    {
    }
    
    std::shared_ptr<mkPerfTimeInfo> CallSub(const mkPerfFuncInfo& funcInfo)
    {
        std::shared_ptr<mkPerfTimeInfo> subInfo;
        
        auto iter = _subInfos.find(funcInfo);
        if(iter == _subInfos.end()) {
            subInfo = std::make_shared<mkPerfTimeInfo>();
            subInfo->_parentInfo = shared_from_this();
            _subInfos.insert(make_pair(funcInfo, subInfo));
        }
        else {
            subInfo = iter->second;
        }
        
        subInfo->_callNum++;
        return subInfo;
    }
    
    std::shared_ptr<mkPerfTimeInfo> CallParent(const int64& time)
    {
        _useTime += time;
        return _parentInfo;
    }
public:
    int64 _useTime;
    int64 _callNum;
    std::shared_ptr<mkPerfTimeInfo> _parentInfo;
    std::map<mkPerfFuncInfo, std::shared_ptr<mkPerfTimeInfo>> _subInfos;
};

class mkPerfThreadInfo
{
public:
    mkPerfThreadInfo() 
        : _rootInfo(std::make_shared<mkPerfTimeInfo>())
        , _backInfo (_rootInfo)
    {
        _backInfo = _rootInfo;
    }
    
    void Push(const mkPerfFuncInfo& funcInfo)
    {
        _backInfo = _backInfo->CallSub(funcInfo);
    }
    void Pop(const int64& time)
    {
        _backInfo = _backInfo->CallParent(time);
    }
    std::shared_ptr<mkPerfTimeInfo> Top()
    {
        return _backInfo;
    }
    
    std::shared_ptr<mkPerfTimeInfo>     _rootInfo;
    std::shared_ptr<mkPerfTimeInfo>     _backInfo;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
mkPerf::Point::Point(std::shared_ptr<mkPerf> perf, const char* func, int line)
    : _perf(perf)
{
    if(_perf) {
        mkPerfFuncInfo funcInfo(func,line);
        std::shared_ptr<mkPerfThreadInfo> thInfo = _perf->GetThreadInfo();
        thInfo->Push(funcInfo);
    }
    //入栈时间
    #ifdef __WINDOWS__
        QueryPerformanceCounter((LARGE_INTEGER*)&_beginTime);
    #else
        struct timeval curr;
        gettimeofday(&curr, nullptr);
        _beginTime = curr.tv_sec + curr.tv_usec;
    #endif
}

mkPerf::Point::~Point()
{
    //出栈时间
    int64 curtime(0);
    #ifdef __WINDOWS__
        QueryPerformanceCounter((LARGE_INTEGER*)&curtime);
    #else
        struct timeval curr;
        gettimeofday(&curr, nullptr);
        curtime = curr.tv_sec + curr.tv_usec;
    #endif
    
    if(_perf) {
        std::shared_ptr<mkPerfThreadInfo> thInfo = _perf->GetThreadInfo();
        thInfo->Pop(curtime - _beginTime);
    }
}


mkPerf::mkPerf(const string& moduleName)
    : _moduleName(moduleName)
{
}

mkPerf::~mkPerf()
{
    Output();
}

void 
mkPerf::Output()
{
    printf("perf info: %s\n", _moduleName.c_str());
    
    for(auto& elem : _threadInfos) {
        std::cout<<"Thread:"<<elem.first<<endl;
        Output(elem.second->_rootInfo, "");
    }
    _threadInfos.clear();
}

void 
mkPerf::Output(std::shared_ptr<mkPerfTimeInfo> info, const string& blank)
{
    static int64_t frequency  = 0;//计数器频率
    if(frequency == 0) {
        #ifdef __WINDOWS__
            QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
        #else
            frequency = 1000000;
        #endif
    }
    
    for(const auto& elem : info->_subInfos) {
        printf("\t%s%s(), line=%d, time=%0.8f, callnum=%lld\n",
            blank.c_str(), 
            elem.first._func.c_str(), 
            elem.first._line, 
            (double)elem.second->_useTime/(double)frequency, 
            elem.second->_callNum
        );
        //递归
        Output(elem.second, blank + "\t");
    }
}

std::shared_ptr<mkPerfThreadInfo>
mkPerf::GetThreadInfo()
{
    std::thread::id threadId = this_thread::get_id();
    auto iter = _threadInfos.find(threadId);
    if(iter == _threadInfos.end()) {
        std::shared_ptr<mkPerfThreadInfo> thInfo = std::make_shared<mkPerfThreadInfo>();
        _threadInfos.insert(make_pair(threadId, thInfo));
        return thInfo;
    }
    else {
        return iter->second;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

mkPerfPoint::mkPerfPoint(double& usedSecond)
    : _usedSecond(usedSecond)
{
    #ifdef __WINDOWS__
        QueryPerformanceCounter((LARGE_INTEGER*)&_beginTime);//单位微秒
    #else
        gettimeofday(&_beginTime, NULL);
    #endif
}

mkPerfPoint::~mkPerfPoint()
{
    static int64_t frequency  = 0;
    if(frequency == 0) {
        #ifdef __WINDOWS__
            QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
        #else
            frequency = 1000000;
        #endif
    }
    
    #ifdef __WINDOWS__
        int64_t curtime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&curtime);
        _usedSecond = double(curtime - _beginTime)/double(frequency);
    #else
        struct timeval curtime;
        gettimeofday(&curtime, NULL);
        _usedSecond = double(curtime.tv_sec + curtime.tv_usec - _beginTime.tv_sec - tv_usec)/1000000;
    #endif
}


















