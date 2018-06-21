/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <condition_variable>


//同步变成异步
TEST(Condition_variables, threadInLambda)
{
    class ncABC
    {
    public:
        void func(const int& i)
        {
            int n = i;
            //线程执行体
            auto imp = [&](){
                cout<<i<<endl;
                while(true) {
                    MK_PRINT_MSG("n = %d", n++);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                _cv.notify_all();
            };
            
            
            //等待线程执行完成或者超时
            std::thread t1(imp);
            std::unique_lock<std::mutex> lk(_cv_m);
            auto ret = _cv.wait_for(lk, std::chrono::seconds(5));
            if(ret == cv_status::timeout) {
                t1.detach();
                MK_PRINT_MSG("timeout");
            }
            else {
                t1.join();
                MK_PRINT_MSG("no_timeout");
            }
        }
        
    private:
        std::mutex                  _cv_m;//线程锁
        std::condition_variable     _cv;//条件变量
    };
    
    ncABC abc;
    abc.func(100);
}