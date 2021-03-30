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

std::once_flag flag1, flag2;

void simple_do_once()
{
    std::call_once(flag1, [](){ std::cout << "Simple example: called once\n"; });
}

TEST(call_once, simple_do_once)
{
    std::thread st1(simple_do_once);
    std::thread st2(simple_do_once);
    std::thread st3(simple_do_once);
    std::thread st4(simple_do_once);
    st1.join();
    st2.join();
    st3.join();
    st4.join();
}

void may_throw_function(bool do_throw)
{
  if (do_throw) {
    std::cout << "throw: call_once will retry\n"; // 这会出现多于一次
    //If that invocation throws an exception, 
    //it is propagated to the caller of call_once, 
    //and the flag is not flipped so that another call will be attempted 
    //(such call to call_once is known as exceptional). 
    throw std::exception();
  }
  std::cout << "Didn't throw, call_once will not attempt again\n"; // 保证一次
}

void do_once(bool do_throw)
{
  try {
    ////如果发生了异常, 则传播异常给 call_once 的调用方，，并且不更改flag, 以令其他调用将得到尝试
    std::call_once(flag2, may_throw_function, do_throw);
  }
  catch (...) {
  }
}

TEST(call_once, may_throw_function)
{
    std::thread t1(do_once, true);
    std::thread t2(do_once, true);
    std::thread t3(do_once, false);
    std::thread t4(do_once, true);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}