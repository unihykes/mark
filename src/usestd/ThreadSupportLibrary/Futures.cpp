/***************************************************************************************************
Author:liu.hao

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
