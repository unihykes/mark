/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <future>


TEST(promise, promise)
{
    class ncSomeProc
    {
    public:
        void run(int val, std::promise<int> promiseObj)
        {
            promiseObj.set_value(100);//提醒future
        }
    };
    
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future(); 
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::run, &proc,  0, std::move(promiseObj));
    futureObj.wait();//等待结果
    int ret = futureObj.get();//得到结果
    t1.join();
}