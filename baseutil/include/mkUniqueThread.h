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

Time:2018-2

info:
    一个轻量线程代理,具有如下特点:
    1.可将全局函数作为线程执行体,支持变长参数
    2.可将类的成员函数作为线程执行体,支持变长参数
    3.出了ncAutoThread对象所在作用域后自动结束线程;
    4.线程结束后调用Get()接口, 可以获取线程执行结果和异常,线程未结束时,调用Get()会阻塞直到线程结束;
***************************************************************************************************/

#ifndef __mkUniqueThread
#define __mkUniqueThread

#include <thread>
#include <future>

class mkUniqueThread
{
public:
    //绑定全局函数
    //到该函数的参数只能move或者按值复制,若需要传递引用参数,在上层调用时必须包装之(可用std::ref或者std::cref等)
    template<typename Func, typename... Args>
    mkUniqueThread(Func&& procRunFunc, Args&&... args)
        : _needAbort(false)
        , _hasFinished(false)
    {
        std::packaged_task<void(mkUniqueThread*, Args...)> task(std::forward<Func>(procRunFunc));
        _future = task.get_future();
        std::thread temp(std::move(task), this, std::forward<Args>(args)...);
        _thread = std::move(temp);
    }
    
    //绑定类的成员函数
    //到该函数的参数只能move或者按值复制,若需要传递引用参数,在上层调用时必须包装之(可用std::ref或者std::cref等)
    template<typename T, typename Func, typename... Args>
    mkUniqueThread(Func&& procRunFunc, T* procInstance, Args&&... args)
        : _needAbort(false)
        , _hasFinished(false)
    {
        std::packaged_task<void(T*, mkUniqueThread*, Args...)> task(std::forward<Func>(procRunFunc));
        _future = task.get_future();
        std::thread temp(std::move(task), procInstance, this, std::forward<Args>(args)...);
        _thread = std::move(temp);
    }
    
    
    ~mkUniqueThread()
    {
        _needAbort = true;
        if(_thread.joinable()) {
            _thread.join();
        }
    }
    
    //外界获取线程的执行结果或异常
    void Get()
    {
        return _future.get();
    }
    
    //外界决定停止该线程,设置标志
    void SetAbort()
    {
        _needAbort = true;
    }
    
    //外界查询线程是否已经执行完成
    bool HasFinished()
    {
        return _hasFinished;
    }
    
    //线程执行体中,用来判断线程是否需要停止
    bool NeedAbrot()
    {
        return _needAbort;
    }
    
    //线程执行体中,当任务执行完成后,设置此标志
    void SetFinished()
    {
        _hasFinished = true;
    }
    
    
private:
    std::thread                 _thread;
    std::future<void>           _future;
    bool                        _needAbort;
    bool                        _hasFinished;
};

#endif //__mkUniqueThread
