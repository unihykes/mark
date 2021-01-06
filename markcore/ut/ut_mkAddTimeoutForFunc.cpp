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

info:

***************************************************************************************************/

#include <markcore.h>
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
            //::Sleep(2000);
			std::this_thread::sleep_for(std::chrono::seconds(1));
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