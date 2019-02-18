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