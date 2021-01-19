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

#ifndef __mkPerf
#define __mkPerf

#include <thread>

class mkPerfTimeInfo;
class mkPerfThreadInfo;

class MK_DLL_EXPORT mkPerf
{
public:
    mkPerf(const string& moduleName);
    ~mkPerf();
    void Output();
    std::shared_ptr<mkPerfThreadInfo> GetThreadInfo();
    
    class MK_DLL_EXPORT Point
    {
    public:
        Point(std::shared_ptr<mkPerf> perf, const char* func, int functionLine);
        ~Point();
        
    private:
        int64 _beginTime;
        std::shared_ptr<mkPerf> _perf;
    };
private:
    void Output(std::shared_ptr<mkPerfTimeInfo> info, const string& blank);
    
private:
    string                         _moduleName;         //模块名
    map<std::thread::id, std::shared_ptr<mkPerfThreadInfo>>  _threadInfos;  //线程映射表
};

class MK_DLL_EXPORT mkPerfPoint
{
public:
    mkPerfPoint(double& usedSecond);
    ~mkPerfPoint();

private:
    #ifdef __WINDOWS__
        int64_t             _beginTime;
    #else
        struct timeval      _beginTime;
    #endif
    
    double&             _usedSecond;
};

#endif