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

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        //MK_PRINT_MSG("thread id = %d, n = %d, i = %d\n", this_thread::get_id(), n, i);
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        //MK_PRINT_MSG("thread id = %d, n = %d, i = %d\n", this_thread::get_id(), n, i);
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// 非线程
TEST(thread, construct1)
{
    std::thread t1;
}

//按值传递参数
TEST(thread, construct2)
{
    int n = 0;
    std::thread t1(f1, n + 1);
    
    MK_PRINT_MSG("n = %d\n", n);
    t1.join();
    MK_PRINT_MSG("n = %d\n", n);
}

//move
//只能move给joinable为false的线程对象，否则调用 std::terminate() 
TEST(thread, construct3)
{
    int n = 0;
    std::thread t1(f1, n + 1);
    MK_PRINT_MSG("~~~~thread id = %d\n", t1.get_id());
    
    std::thread t2(std::move(t1)); // t2 现在运行 f1() 。 t1 不再是线程
    MK_PRINT_MSG("~~~~thread id = %d\n", t1.get_id());
    MK_PRINT_MSG("~~~~thread id = %d\n", t2.get_id());
    
    std::thread t3;
    t3 = std::move(t2);
    MK_PRINT_MSG("~~~~thread id = %d\n", t1.get_id());
    MK_PRINT_MSG("~~~~thread id = %d\n", t2.get_id());
    MK_PRINT_MSG("~~~~thread id = %d\n", t3.get_id());
    
    t3.join();
    MK_PRINT_MSG("n = %d\n", n);
}

TEST(thread, construct4)
{
    int n = 0;
    std::thread t1(f1, std::ref(n)); // 按引用传递参数
    std::thread t2(f2, std::ref(n)); // 按引用传递参数
    
    t1.join();
    t2.join();
}

TEST(thread, destruct)
{
    std::thread t2(f1, 100);
    
    //线程在joinable为true状态时析构不安全;
    //若 *this 拥有关联线程（ joinable() == true ），则调用 std::terminate() 。 
    if(t2.joinable()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        MK_PRINT_MSG("id = %d", t2.get_id());
    }
    
    t2.join();
}

TEST(thread, joinable)
{
    //执行前
    std::thread t1;
    MK_PRINT_MSG("id = %d, joinable = %d", t1.get_id(), t1.joinable());
    
    //执行后
    std::thread t2(f1, 100);
    MK_PRINT_MSG("id = %d, joinable = %d", t2.get_id(), t2.joinable());
    
    //join后
    t2.join();
    MK_PRINT_MSG("id = %d, joinable = %d", t2.get_id(), t2.joinable());
}

TEST(thread, get_id)
{
    //无关联的线程,id = 0
    std::thread t0;
    MK_PRINT_MSG("id = %d", t0.get_id());
    
    //获取有状态的
    int n = 0;
    std::thread t1(f1, n + 1);
    MK_PRINT_MSG("type = %s, n = %d\n", typeid(t1.get_id()).name(), n);
    MK_PRINT_MSG("id = %d, n = %d\n", t1.get_id(), n);
    t1.join();
}
TEST(thread, this_thread_get_id)
{
    MK_PRINT_MSG("this_thread::get_id() = %d", this_thread::get_id());
}

//返回实现所支持的并发线程数
TEST(thread, hardware_concurrency)
{
    MK_PRINT_MSG("hardware_concurrency = %d", thread::hardware_concurrency());
}

//阻塞当前线程，直至 *this 所标识的线程完成其执行
TEST(thread, join)
{
    try {
        std::thread t1;
        t1.join();
    }
    catch(std::exception& e) {
        MK_PRINT_MSG("e = %s", e.what());
    }
    
    std::thread t2(f1, 100);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t2.join();
}

//容许线程从线程句柄独立开来执行 
TEST(thread, detach)
{
    std::thread t2(f1, 100);
    t2.detach();
}

//交换二个 thread 对象 
TEST(thread, swap)
{
    std::thread t1(f1, 100);
    std::thread t2(f1, 200);
    
    MK_PRINT_MSG("t1  id = %d", t1.get_id());
    MK_PRINT_MSG("t2  id = %d", t2.get_id());
    
    t1.swap(t2);
    MK_PRINT_MSG("t1  id = %d", t1.get_id());
    MK_PRINT_MSG("t2  id = %d", t2.get_id());
}
