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

Time:2018-6
    为一个同步运行的函数(全局函数或者成员函数)添加超时机制,超时会抛异常
info:

***************************************************************************************************/
#ifndef __mkAddTimeoutForFunc
#define __mkAddTimeoutForFunc

#include <thread>
#include <future>
#include "utility/mkSourceLocation.h"
#include "string/mkFormat.h"
#include "utility/mkException.h"
#include "mkModuleInstance.h"

//returntype = 当前函数返回值类型
#define ADD_TIMEOUT_BEGIN(returntype)                                                              \
    return mkTimerThread<returntype>{}([&]()->returntype{

//timeout = 超时时限(单位:秒), errorId = 超时时抛出的异常id, errorMsg= 超时时抛出的异常信息
#define ADD_TIMEOUT_END_WITH_ERRMSG(timeout,errorId, errorMsg)                                     \
    }, std::chrono::seconds(timeout), __FILE__, __LINE__, __func__, errorId, errorMsg);
    
//timeout = 超时时限(单位:秒), errorId = 超时时抛出的异常id
#define ADD_TIMEOUT_END(timeout,errorId)                                                           \
    ADD_TIMEOUT_END_WITH_ERRMSG(timeout, errorId, "")
    
template<typename ReturnType>
class mkTimerThread
{
public:
    mkTimerThread(){}
    
    template<typename F, class Rep, class Period>
    ReturnType operator()(F&& f, const std::chrono::duration<Rep,Period>& dTimeout,
                            const char* file, int line, const char* funcName,
                            const int& errorId, const string& defaultErrorMsg = "")
    {
        std::packaged_task<ReturnType()> task(f);
        auto future = task.get_future();
        std::thread(std::move(task)).detach();
        auto status = future.wait_for(dTimeout);
        
        if(status == std::future_status::timeout) {
            const char* fileName = mkSourceLocation::file_name(file);
            if(defaultErrorMsg.empty()) {
                MK_THROW(errorId, "(%s:%d): Timeout when method(%s) is called.", fileName, line, funcName);
            }
            else {
                MK_THROW(errorId, "(%s:%d): %s.", fileName, line, defaultErrorMsg.c_str());
            }
        }
        
        try {
            return future.get();
        }
        catch(std::exception& e) {
            throw e;
        }
    }
private:
    mkTimerThread(const mkTimerThread&) = delete;
    mkTimerThread& operator=(const mkTimerThread&) = delete;
};


#endif //__mkAddTimeoutForFunc