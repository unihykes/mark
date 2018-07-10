/***************************************************************************************************
main.cpp:
	Copyright (c) Eisoo Software, Inc.(2018), All rights reserved.

Purpose:
	

Author:
	liu.hao@eisoo.com

Creating Time:
	2018-06-26
***************************************************************************************************/
 
#include <abprec.h>
#include <array>
#include <ncModuleUtEnv.h>
#include "ncSyncToAsync.h"

NC_DEFINE_UT_MODULE(ut_SyncToAsync);//for 初始化cfl资源

//模拟第三方API
String thirdPartyApi(const String& param)
{
    String result;
    
    //模拟抛异常
    if(param == _T("throw")) {
        String errorMsg;
        errorMsg.format(_T("failed, param = %s"), param.getCStr()); 
        throw Exception(errorMsg);
    }
    
    //模拟卡死
    if(param == _T("endless")) {
        while(true) {
            static int n = 0;
            printMessage2(_T("n = %d"), n++);
            Sleep(2000);
        }
    }
    
    //模拟正常结束
    result.format(_T("success, param = %s"), param.getCStr()); 
    return result;
}

//模拟自己负责的业务逻辑
class ncMyProc
{
public:
    //同步调用, 同步等待,无超时
    String funcSync(const String& param)
    {
        String result = thirdPartyApi(param);
        //do something else
        return result;
    }
};

TEST(ncMyProc, funcSync)
{
    const std::array<String, 3> params = {_T("hello world"), _T("throw"), _T("endless")};
    
    for(const auto& elem :params) {
        try {
            String result = ncMyProc().funcSync(elem);
            printMessage(result);
        }
        catch(Exception& e) {
            printMessage(e.toFullString());
        }
    }
}

//模拟自己负责的业务逻辑
class ncMyProcNew
{
public:
    //同步调用, 同步等待,无超时
    String funcSync(const String& param)
    {
        String result = thirdPartyApi(param);
        //do something else
        return result;
    }
    
    //异步调用, 同步等待, 超时抛异常
    String funcAsync(const String& param)
    {
        BEGIN_ASYNC_BY_RETURN(String);//宏参数是当前函数的返回值类型
        
        String result = thirdPartyApi(param);
        //do something else
        return result;
        
        END_ASYNC_BY_TIMEOUT(5, 1);//5秒超时,超时时的异常ID为0x0001;
    }
};

TEST(ncMyProcNew, funcAsync)
{
    const std::array<String, 3> params = {_T("hello world"), _T("throw"), _T("endless")};
    
    for(const auto& elem :params) {
        try {
            String result = ncMyProcNew().funcAsync(elem);
            printMessage(result);
        }
        catch(Exception& e) {
            printMessage(e.toFullString());
        }
    }
}



int main(int argc, char** argv) 
{
    testing::AddGlobalTestEnvironment(new ncEnvironment());
    testing::InitGoogleTest(&argc, argv); 

    int ret = RUN_ALL_TESTS ();
    return ret;
}