/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:

***************************************************************************************************/

#include <mkheaders.h>

#include <mkAddTimeoutForFunc.h>
#include <gtest/gtest.h>
////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//
//模拟第三方API
string thirdPartyApi(const string& param)
{
    string result;
     
    //模拟抛异常
    if(param == "throw") {
        string errorMsg = string("failed, param = ") + param; 
        throw string(errorMsg);
    }
     
    //模拟卡死
    if(param == "endless") {
        while(true) {
            static int n = 0;
            MK_PRINT("n = %d", n++);
            Sleep(2000);
        }
    }
     
    //模拟正常结束
    result = string("success, param = ") + param; 
    return result;
}


TEST(ncMyProc, funcSync)
{
    //模拟自己负责的业务逻辑
    class ncMyProc
    {
    public:
        //同步调用, 同步等待,无超时
        string funcSync(const string& param)
        {
            string result = thirdPartyApi(param);
            //do something else
            return result;
        }
    };
    
    const std::array<string, 3> params = {"hello world", "throw", "endless"};
     
    for(const auto& elem :params) {
        try {
            string result = ncMyProc().funcSync(elem);
            MK_PRINT(result.c_str());
        }
        catch(string& e) {
            MK_PRINT(e.c_str());
        }
    }
}


TEST(ncMyProc, funcAsync)
{
    //模拟自己负责的业务逻辑
    class ncMyProcNew
    {
    public:
        //异步调用, 同步等待, 超时抛异常
        string funcAsync(const string& param)
        {
            ADD_TIMEOUT_BEGIN(string);//宏参数是当前函数的返回值类型
             
            string result = thirdPartyApi(param);
            //do something else
            return result;
             
            ADD_TIMEOUT_END(5, 0x0001);//5秒超时,超时时的异常ID为0x0001;
        }
    };
    const std::array<string, 3> params = {"hello world", "throw", "endless"};
     
    for(const auto& elem :params) {
        try {
            string result = ncMyProcNew().funcAsync(elem);
            MK_PRINT(result.c_str());
        }
        catch(string& e) {
            MK_PRINT(e.c_str());
        }
    }
}