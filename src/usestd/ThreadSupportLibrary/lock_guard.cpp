/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <thread>
#include <mutex>

//加锁
TEST(lock_guard, construct)
{
    class ncSomeProc
    {
    public:
        void func(int param)
        {
            for(int i = 0; i != 5; ++i){
                std::lock_guard<std::mutex> lock(_mutex);
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