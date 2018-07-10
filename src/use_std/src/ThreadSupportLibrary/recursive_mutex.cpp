/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    对于一个std::mutex对象，如果你已经锁定它了，那么在unock()之前你就不可以再次对他执行lock()函数。
    一种常见的情况是，一个类需要保护共享数据，所有的公有函数都锁定一个mutex。但有时候一个公有函数需要调用另一个公有函数，
    这样，另一个公有函数也需要去锁定mutex，这会导致重复锁定同一个mutex，产生未定义行为。(死锁)
    一种投机取巧的办法是将mutex换成std::recursive_mutex，使得另一个函数可以毫无顾忌的执行锁定操作。
    但是，这种做法是不提倡的。因为这是一种草率的做法、不成熟的设计。
    保持一个锁状态去意味着类的稳定性被破坏了，也就是说第二个公有函数是在类的稳定性被破坏的前提下被调用的。
    更好的做法是，提取出一个被两个个公有函数调用的私有函数，这个私有函数无需锁定mutex。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <mutex>

//递归锁
TEST(recursive_mutex, deadlock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            _mutex.lock();
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            impFunc(param);//导致死锁
            _mutex.unlock();
        }
        
        void impFunc(int param)
        {
            _mutex.lock();
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            _mutex.unlock();
        }
        
    private:
        std::mutex                  _mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    proc.func(100);//死锁
}

TEST(recursive_mutex, lock_unlock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            _recursive_mutex.lock();
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            impFunc(param);//递归锁不会死锁
            _recursive_mutex.unlock();
        }
        
        void impFunc(int param)
        {
            _recursive_mutex.lock();
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            _recursive_mutex.unlock();
        }
        
    private:
        std::recursive_mutex         _recursive_mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}

TEST(recursive_mutex, try_lock)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            //尝试锁定
            while(true){
                if(_recursive_mutex.try_lock()) {
                    break;
                }
                else {
                    MK_PRINT_MSG("threadId = %d, failed to lock...\n\n", this_thread::get_id());
                    this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
            
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            impFunc(param);//递归锁不会死锁
            _recursive_mutex.unlock();
        }
        
        void impFunc(int param)
        {
            //尝试锁定
            while(true){
                if(_recursive_mutex.try_lock()) {
                    break;
                }
                else {
                    MK_PRINT_MSG("threadId = %d, failed to lock...\n\n", this_thread::get_id());
                    this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
            
            MK_PRINT_MSG("threadId = %d, param = %d", this_thread::get_id(), param);
            _recursive_mutex.unlock();
        }
        
    private:
        std::recursive_mutex         _recursive_mutex;
        std::map<int,int>           _mapNum;
    };
    
    ncSomeProc proc;
    std::thread t1(&ncSomeProc::func, &proc,  0);
    std::thread t2(&ncSomeProc::func, &proc,  100);
    t1.join();
    t2.join();
}