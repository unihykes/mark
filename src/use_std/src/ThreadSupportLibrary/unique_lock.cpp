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
#include <mutex>

//实现可移动的互斥锁有权包装器, 是通用互斥包装器，允许延迟锁定、锁定的有时限尝试、递归锁定、所有权转移和与条件变量一同使用。 
TEST(unique_lock, construct)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::unique_lock<std::mutex> lock(_mutex);
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                    
                this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    private:
        std::mutex                  _mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

TEST(unique_lock, lock_unlock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::unique_lock<std::mutex> lock(_mutex);
                _mapNum[i] = param + i;
                
                //模拟不需要锁的操作
                lock.unlock();
                this_thread::sleep_for(std::chrono::seconds(1));
                
                lock.lock();
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
            }
        }
    private:
        std::mutex                  _mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

//try_lock:尝试锁定互斥。立即返回。成功获得锁时返回 true ，否则返回 false 。 
TEST(unique_lock, try_lock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::unique_lock<std::mutex> lock(_mutex);
                //尝试锁定
                while(true){
                    if(lock.try_lock()) {
                        break;
                    }
                    else {
                        MK_PRINT_MSG("threadId = %d, i = %d, failed to lock...\n", this_thread::get_id(), i);
                        this_thread::sleep_for(std::chrono::milliseconds(50));
                    }
                }
                
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                    
                this_thread::sleep_for(std::chrono::milliseconds(50));
                lock.unlock();
                this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    private:
        std::mutex                  _mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

TEST(unique_lock, try_lock_for)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::unique_lock<std::timed_mutex> lock(_timed_mutex);
                //尝试锁定
                while(true){
                    if(lock.try_lock_for(chrono::milliseconds(50))) {
                        break;
                    }
                    else {
                        MK_PRINT_MSG("threadId = %d, i = %d, failed to lock...\n", this_thread::get_id(), i);
                    }
                }
                
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                    
                this_thread::sleep_for(std::chrono::milliseconds(50));
                lock.unlock();
                this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    private:
        std::timed_mutex            _timed_mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

//尝试所互斥。阻塞直至抵达指定的 timeout_time 或得到锁，
TEST(unique_lock, try_lock_until)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::unique_lock<std::timed_mutex> lock(_timed_mutex);
                //尝试锁定
                while(true){
                    auto now=std::chrono::steady_clock::now();
                    if(lock.try_lock_until(now + chrono::milliseconds(50))) {
                        break;
                    }
                    else {
                        MK_PRINT_MSG("threadId = %d, i = %d, failed to lock...\n", this_thread::get_id(), i);
                    }
                }
                
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                    
                this_thread::sleep_for(std::chrono::milliseconds(50));
                lock.unlock();
                this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    private:
        std::timed_mutex            _timed_mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}