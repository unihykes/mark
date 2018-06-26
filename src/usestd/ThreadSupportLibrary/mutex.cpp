/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <mutex>

//不加锁
TEST(mutex, no_mutex)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 10; ++i){
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                
                this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    private:
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

//加锁
TEST(mutex, lock_unlock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 10; ++i){
                _mutex.lock();
                _mapNum[i] = param + i;
                MK_PRINT_MSG("threadId = %d, _mapNum[%d] = %d, param+i = %d, consistency = %s\n", 
                    this_thread::get_id(), i, _mapNum[i], param+i, (_mapNum[i] == param + i)?"true":"false");
                    
                this_thread::sleep_for(std::chrono::seconds(1));
                _mutex.unlock();
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
TEST(mutex, try_lock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                //尝试锁定
                while(true){
                    if(_mutex.try_lock()) {
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
                _mutex.unlock();
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