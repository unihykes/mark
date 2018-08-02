/***************************************************************************************************
Author:liu.hao(33852613@163.com)

Time:2018-6
    为一个同步运行的函数(全局函数或者成员函数)添加超时机制,超时会抛异常
info:

***************************************************************************************************/
#ifndef __mkAddTimeoutForFunc
#define __mkAddTimeoutForFunc

#include <thread>
#include <future>
#include <exception>

//returntype = 当前函数返回值类型
#define ADD_TIMEOUT_BEGIN(returntype)                                                              \
    return mkAddTimeoutForFunc<returntype>()([&]()->returntype{

//timeout = 超时时限(单位:秒), errorId = 超时时抛出的异常id
#define ADD_TIMEOUT_END(timeout,errorId)                                                           \
    }, std::chrono::seconds(timeout), __FILE__, __LINE__, __func__, errorId);
    
//timeout = 超时时限(单位:秒), errorId = 超时时抛出的异常id, errorMsg= 超时时抛出的异常信息
#define ADD_TIMEOUT_END_WITH_ERRMSG(timeout,errorId, errorMsg)                                     \
    }, std::chrono::seconds(timeout), __FILE__, __LINE__, __func__, errorId, errorMsg);
    
    
template<typename ReturnType>
class mkAddTimeoutForFunc
{
public:
    mkAddTimeoutForFunc(){}
    mkAddTimeoutForFunc(const mkAddTimeoutForFunc&) = delete;
    mkAddTimeoutForFunc& operator=(const mkAddTimeoutForFunc&) = delete;
    
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
            ThrowTimeoutException(file, line, funcName, errorId, defaultErrorMsg);
        }
        
        try {
            return future.get();
        }
        catch(std::exception& e) {
            MK_PRINT("error = %s", e.what());
            throw e;
        }
    }
    
private:
    void ThrowTimeoutException(const char* file, int line, const char* funcName, 
                               const int& errorId, const string& defaultErrorMsg = "")
    {
        #ifdef __WINDOWS__ 
            constexpr const char identify = '\\';
        #else 
            constexpr const char identify = '/';
        #endif
        const char* fileName = strrchr(file, identify) ? strrchr(file, identify) + 1 : file;
        
        string errorMsg;
        if(defaultErrorMsg.empty()) {
            stringstream stream;
            stream<<"Timeout when method(" << funcName << ") is called.";
            stream>>errorMsg;
        }
        else {
            errorMsg = defaultErrorMsg;
        }
        
        stringstream stream;
        stream<<"("<<fileName<<":"<<line<<"): "<<errorMsg;
        
        string fullErrorMsg;
        stream>>fullErrorMsg;
        
        MK_PRINT ("error = %s",fullErrorMsg.c_str());
        
        //todo:throw
        //throw mkException (errorMsg, errorId);
    }
};


#endif //__mkAddTimeoutForFunc