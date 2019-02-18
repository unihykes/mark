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
#include <chrono>

/*
std::this_thread::yield() 的目的是避免一个线程频繁与其他线程争抢CPU时间片, 从而导致多线程处理性能下降.
std::this_thread::yield() 是让当前线程让渡出自己的CPU时间片(给其他线程使用),此时”当前线程”不参与争抢).
*/
TEST(this_thread, yield)
{
    class ncABC
    {
    public:
        void fun1()
        {
            int i = 10;
            while(i--) {
                MK_PRINT_MSG("i = %d", i);
            }
        }
        
        void fun2()
        {
            int i = 10;
            while(i--) {
                std::this_thread::yield();
                MK_PRINT_MSG("i = %d", i);
            }
        }
    };
    
    ncABC abc;
    std::thread t1(&ncABC::fun1, &abc);
    std::thread t2(&ncABC::fun2, &abc);
    t1.join();
    t2.join();
}

TEST(this_thread, yield2)
{
    int i = 65525;
    while(i--) {
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }
}

TEST(this_thread, yield3)
{
    int i = 65535;
    while(i--) {
        std::this_thread::yield();
    }
}

//返回当前线程的线程 id 
TEST(this_thread, get_id)
{
    MK_PRINT_MSG("this thread id = %d", std::this_thread::get_id());
}

//std::this_thread::sleep_for() 是让当前休眠”指定的一段”时间.
TEST(this_thread, sleep_for)
{
    std::this_thread::sleep_for(std::chrono::duration<int, std::ratio<1>>(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//暂停当前线程的执行直到特定的时间点 
TEST(this_thread, sleep_until)
{
    /*
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    struct std::tm *ptm = std::localtime(&tt);
    ptm->tm_min++; 
    ptm->tm_sec = 0;
    std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
    MK_PRINT_MSG("");
    */
    
    auto now = std::chrono::steady_clock::now();
    std::this_thread::sleep_until(now + std::chrono::seconds(3));
    MK_PRINT_MSG("");
}