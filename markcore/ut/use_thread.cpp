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

***************************************************************************************************/

#include <markcore.h>
#include <gtest/gtest.h>
#include <gof/mkSingleton.h>


class use_mkUniqueThread : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
    class ncABC
    {
    public:
        void run(mkUniqueThread* thread)
        {
            MK_PRINT("");
            while(true) {
                MK_PRINT("");
                if(thread->NeedAbrot()) {
                    MK_PRINT("");
                    break;
                }
            }
            
            MK_PRINT("");
            if(0) {
                thread->SetFinished();
            }
            else {
                throw string("something is wrong!");
            }
        }
    private:
    };
};

TEST_F(use_mkUniqueThread, lambda)
{
    MK_PRINT("");
    
    auto lam = [](mkUniqueThread* thread, int& a) ->void{
        MK_PRINT("a=%d",a);
        while(true) {
            if(thread->NeedAbrot()) {
                break;
            }
        }
        a = 222;
        thread->SetFinished();
    };
    
    {
        MK_PRINT("");
        int a = 11;
        mkUniqueThread thread(lam, std::ref(a));
        thread.SetAbort();
        thread.Get();
        MK_PRINT("a=%d",a);
    }
    
    MK_PRINT("");
    cout<<endl;
}

TEST_F(use_mkUniqueThread, exception)
{
    MK_PRINT("");
    ncABC abc;
    {
        MK_PRINT("");
        mkUniqueThread thread(&ncABC::run, &abc);
        MK_PRINT("");
        try {
            MK_PRINT("");
            thread.SetAbort();
            thread.Get();
            MK_PRINT("");
        }
        catch(std::string& errmsg){
            MK_PRINT("%s", errmsg.c_str());
        }
    }
    MK_PRINT("");
    cout<<endl;
}

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
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(n >=15) {
                break;
            }
        }
    }
     
    //模拟正常结束
    result = string("success, param = ") + param; 
    return result;
}

TEST(mkTimerThread, funcSync)
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

TEST(mkTimerThread, funcAsync)
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


TEST(mkScopeLimiter, run)
{
    class ncABC
    {
    public:
        void run()
        {
            mkScopeLimiter<ncABC> limiter([](){return false;});
            {
                std::lock_guard<std::mutex> lock(mutex);
                MK_PRINT("%d", ++i);
            }
            
            int count = 5;
            while(--count>0) {
                this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    private:
        std::mutex mutex;
        int i = 0;
    };
    
    
    mkScopeLimiter<ncABC>::SetMax(10);
    vector<std::shared_ptr<std::thread>> vThreads;
    ncABC p;
    for(int i = 0; i != 100; ++i) {
        vThreads.push_back(std::make_shared<std::thread>(&ncABC::run, &p));
    }
    
    for(auto & elem : vThreads) {
        elem->join();
    }
}
