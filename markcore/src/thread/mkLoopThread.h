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

Time:2020-6

info:
    线程管理
***************************************************************************************************/

#ifndef __mkLoopThread
#define __mkLoopThread

#include<thread>
#include <mutex>
#include <condition_variable>
#include "thread/mkEvent.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//

class mkLoopThread
{
public:
    mkLoopThread()
        : _threadAbortFlag(false)
    {
        MK_TRACE (_T("this = 0x%p"), this);
    }
    
    virtual ~mkLoopThread()
    {
        MK_TRACE (_T("this = 0x%p"), this);
    }
    
    virtual void Start(const int count)
    {
        auto threadFunc = [&](std::shared_ptr<mkEvent> threadEvent){
            OnBegin();
            
            while(true) {
                if(_threadAbortFlag){
                    MK_LOG (_T("[this = 0x%p]"), this);
                    break;
                }
                
                try {
                    //适用于多线程抢占式消费同一个资源队列
                    OnProc();
                }
                catch(Exception& e) {
                    OnError(e);
                    MK_LOG(_T("error = %s"), e.toFullString().getCStr());
                }
                catch(...) {
                    ncModuleException e(__FILE__, __LINE__, String(_T("unknown error")), Exception::NO_MAPPED_ERROR_ID, g_moduleProvider);
                    OnError(e);
                    MK_LOG(_T("error = %s"), e.toFullString().getCStr());
                }
            }
            
            OnEnd();
            
            MK_LOG(_T("this = 0x%p, threadId = %d"), this, Thread::getCurThreadId());
            threadEvent->signal();
        };
        
        //预分配n个线程
        for(int i = 0 ; i != count; ++i) {
            std::shared_ptr<mkEvent> threadEvent = std::make_shared<mkEvent>(false);//false:忽略signal之后的一至多次wait
            std::shared_ptr<std::thread> threadProc(new std::thread(threadFunc, threadEvent));
            threadProc->detach();
            _vThreadEvents.push_back(threadEvent);
        }
    }
    
    virtual void Stop()
    {
        //停止所有线程
        _threadAbortFlag = true;
        OnStop();
        for(auto& threadEvent : _vThreadEvents) {
            threadEvent->wait();
        }
    }
    
    
protected:
    bool _threadAbortFlag;
    vector<std::shared_ptr<mkEvent>> _vThreadEvents;
    
private:
    virtual void OnBegin() = 0;
    virtual void OnProc() = 0;
    virtual void OnError(Exception& e) = 0;
    virtual void OnEnd() = 0;
    virtual void OnStop() = 0;//通知 OnProc 解除阻塞
};

#endif // __mkThread