/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#ifndef __mkUniqueThread
#define __mkUniqueThread

#include <thread>
#include <future>


class mkUniqueThread
{
public:
    mkUniqueThread()
        : _needStop(false)
    {
        MK_PRINT("");
    }
    
    ~mkUniqueThread()
    {
        MK_PRINT("");
        _needStop = true;
        if(_checkThread.joinable()) {
            MK_PRINT("");
            _checkThread.join();
            MK_PRINT("");
        }
        MK_PRINT("");
    }
    
    template<typename T, typename Func = void(T::*)(mkUniqueThread*)>
    void RunWithCallback(Func procRunFunc, T* procInstance)
    {
        MK_PRINT("");
        std::packaged_task<void(T*, mkUniqueThread*)> task(procRunFunc);
        _future = task.get_future();
        std::thread temp(std::move(task), procInstance, this);
        _checkThread = std::move(temp);
        MK_PRINT("");
        /*
        std::thread temp(procRunFunc, procInstance, this);
        _checkThread = std::move(temp);
        */
    }
    
    void SetStop()
    {
        MK_PRINT("");
        _needStop = true;
    }
    
    bool NeedStop()
    {
        MK_PRINT("_needStop = %d", int(_needStop));
        return _needStop;
    }
    
    void Get()
    {
        try {
            MK_PRINT("");
            return _future.get();
        }
        catch(...) {
            MK_PRINT("");
            throw;
        }
    }
    
private:
    bool                        _needStop;
    std::thread                 _checkThread;
    std::future<void>           _future;
};

#endif //__mkUniqueThread
