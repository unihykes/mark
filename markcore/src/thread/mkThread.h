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

Time:2020-6

info:
    线程管理
***************************************************************************************************/

#ifndef __mkThread
#define __mkThread

#include <thread>

////////////////////////////////////////////////////////////////////////////////////////////////////
//

class mkThread
{
public:
    static string GetThreadId()
    {
        std::stringstream stream;
        stream<<std::this_thread::get_id();
        return stream.str();
    }
    
    static void Sleep(const int64& ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
};

#endif 