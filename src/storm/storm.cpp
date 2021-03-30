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

Time:2021-3

info:

***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>

TEST(storm, conversion8)
{
    auto conversion = [](int N){
        //利用栈的基本运算，将一个非负的十进制整数转换为八进制数，并从高位到低位顺序打印出八进制数的每一位的值。
        std::stack<int> ss;
        while (N)
        {
            ss.push(N % 8);
            N = N / 8;
        }

        while (!ss.empty())
        {
            printf ("%d ", ss.top());
            ss.pop();
        }
    };
    
    conversion(30);
}

TEST(storm, find1Count)
{
    auto find1Count = [](int num) ->int {
        if (num==0) {
            return 0;
        }
        
        int count=1;
        while (num= num & (num-1)) {
            count++;
        }
        return count;
    };
    
    MK_PRINT("ret = %d", find1Count(3));
}