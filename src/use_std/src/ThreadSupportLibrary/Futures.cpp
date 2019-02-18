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

//同步变成异步
TEST(Futures, async)
{
    class ncABC
    {
    public:
        void func(const int& i)
        {
            int n = i;
            //线程执行体
            auto imp = [&](){
                while(true) {
                    MK_PRINT_MSG("n = %d", n++);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            };
            
            
            //等待线程执行完成或者超时
            auto ret = std::async(std::launch::async, imp);
            auto status = ret.wait_for(std::chrono::seconds(5));
            if (status == std::future_status::timeout) {
                MK_PRINT_MSG("timeout");
            }
            MK_PRINT_MSG("wait_for()---end");
        }
        
    private:
        
    };
    
    ncABC abc;
    abc.func(100);
    MK_PRINT_MSG("---end");
}
