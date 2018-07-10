/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    std::condition_variable 只可与 std::unique_lock<std::mutex> 一同使用
    wait：当前线程调用wait()后将被阻塞，直到另外某个线程调用notify_*唤醒当前线程；
    当线程被阻塞时，该函数会自动调用std::mutex的unlock()释放锁，使得其它被阻塞在锁竞争上的线程得以继续执行。
    一旦当前线程获得通知(notify，通常是另外某个线程调用notify_*唤醒了当前线程)，wait()函数也是自动调用std::mutex的lock()。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <mutex>
#include <condition_variable>


//
TEST(Condition_variables, notify_all)
{
    class ncABC
    {
    public:
        void waits()
        {
            std::unique_lock<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), wating...", this_thread::get_id());
            _cv.wait(lk);//当wait()时，该函数会自动调用std::mutex的unlock(),一旦获得notif, wait()函数自动调用std::mutex的lock()。
            MK_PRINT_MSG("thread(%d), finished", this_thread::get_id());
        }
        
        void signal()
        {
            this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), notifying...", this_thread::get_id());
            _cv.notify_all();
        }
    private:
        std::mutex                  _mutex;//线程锁
        std::condition_variable     _cv;//条件变量
    };
    
    ncABC abc;
    std::thread t1(&ncABC::waits, &abc);
    std::thread t2(&ncABC::waits, &abc);
    std::thread t3(&ncABC::waits, &abc);
    std::thread t4(&ncABC::signal, &abc);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

//
TEST(Condition_variables, notify_one)
{
    class ncABC
    {
    public:
        void waits()
        {
            std::unique_lock<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), wating...", this_thread::get_id());
            _cv.wait(lk);
            MK_PRINT_MSG("thread(%d), finished", this_thread::get_id());
        }
        
        void signal()
        {
            this_thread::sleep_for(std::chrono::seconds(1));
            std::unique_lock<std::mutex> lk(_mutex2);
            MK_PRINT_MSG("thread(%d), notifying...", this_thread::get_id());
            _cv.notify_one();
            this_thread::sleep_for(std::chrono::seconds(3));//需要等待当前函数体的lk析构(unlock)后,_cv.wait(lk)才会解除阻塞
        }
    private:
        std::mutex                  _mutex;//线程锁
        std::mutex                  _mutex2;//线程锁
        std::condition_variable     _cv;//条件变量
    };
    
    ncABC abc;
    std::thread t1(&ncABC::waits, &abc);
    std::thread t2(&ncABC::waits, &abc);
    std::thread t3(&ncABC::waits, &abc);
    std::thread t4(&ncABC::signal, &abc);
    std::thread t5(&ncABC::signal, &abc);
    std::thread t6(&ncABC::signal, &abc);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}



//线程将在执行 notify_all() 或 notify_one() 时，或度过相对时限 rel_time 时被解除阻塞
TEST(Condition_variables, wait_for)
{
    class ncABC
    {
    public:
        void waits()
        {
            std::unique_lock<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), wating...", this_thread::get_id());
            std::cv_status status = _cv.wait_for(lk, std::chrono::seconds(3));
            if(status == cv_status::timeout) {
                MK_PRINT_MSG("thread(%d), timeout.", this_thread::get_id());
            }
            else {
                MK_PRINT_MSG("thread(%d), finished", this_thread::get_id());
            }
        }
        
        void signal()
        {
            this_thread::sleep_for(std::chrono::seconds(6));
            //std::lock_guard<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), notifying...", this_thread::get_id());
            _cv.notify_all();
        }
    private:
        std::mutex                  _mutex;//线程锁
        std::condition_variable     _cv;//条件变量
    };
    
    ncABC abc;
    std::thread t1(&ncABC::waits, &abc);
    std::thread t2(&ncABC::waits, &abc);
    std::thread t3(&ncABC::waits, &abc);
    std::thread t4(&ncABC::signal, &abc);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

//condition_variable_any能在任何满足基础可锁 (BasicLockable) 要求的锁上工作。 
//若锁是 std::unique_lock ，则 std::condition_variable 可能提供更好的性能。 
TEST(Condition_variables, condition_variable_any)
{
    class ncABC
    {
    public:
        void waits()
        {
            std::unique_lock<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), wating...", this_thread::get_id());
            _cv.wait(lk);
            MK_PRINT_MSG("thread(%d), finished", this_thread::get_id());
        }
        
        void signal()
        {
            this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lk(_mutex);
            MK_PRINT_MSG("thread(%d), notifying...", this_thread::get_id());
            _cv.notify_all();
        }
    private:
        std::mutex                       _mutex;//线程锁
        std::condition_variable_any     _cv;
    };
    
    ncABC abc;
    std::thread t1(&ncABC::waits, &abc);
    std::thread t2(&ncABC::waits, &abc);
    std::thread t3(&ncABC::waits, &abc);
    std::thread t4(&ncABC::signal, &abc);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

/**
notify_all_at_thread_exit 提供机制，通知其他线程给定的线程已完全完成，包括销毁所有 thread_local 对象。
将先前获得的锁 lk 的所有权转移到内部存储。 
修改执行环境，以令当前线程退出时，如同以下列方式通知 condition_variable cond ： 
lk.unlock();
cond.notify_all(); 
典型使用情况中，此函数是被detach()线程所做的最后行动。 
*/
TEST(Condition_variables, notify_all_at_thread_exit)
{
    std::mutex                          g_mutex;//线程锁
    std::mutex                          g_mutex2;//线程锁
    std::condition_variable             g_cv;
    
    auto lambda = [&]()
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        MK_PRINT_MSG("thread(%d), wating...", this_thread::get_id());
        for(int i = 0; i != 5;  ++i) {
            this_thread::sleep_for(std::chrono::seconds(1));
            MK_PRINT_MSG("thread(%d), sleep...", this_thread::get_id());
        }
        MK_PRINT_MSG("thread(%d), finished", this_thread::get_id());
        
        std::notify_all_at_thread_exit(g_cv, std::move(lk));
    };//线程结束后,销毁线程内局部对象,解锁mutex,调用_cv的notify()
        

    
    //ncABC abc;
    std::thread t1(lambda);
    t1.detach();
    
    //do something
    
    //等待detach()的线程正常结束
    std::unique_lock<std::mutex> lk(g_mutex2);
    MK_PRINT_MSG("thread(%d), wait()--begin", this_thread::get_id());
    g_cv.wait(lk);
    MK_PRINT_MSG("thread(%d), wait()--end", this_thread::get_id());
}