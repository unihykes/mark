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

#include<mkheaders.h>
#include"mkTimer.h"


mkTimer::mkTimer()
    : _begin(std::chrono::high_resolution_clock::now())
{
}

mkTimer::~mkTimer()
{
}

void 
mkTimer::Reset()
{
    _begin = std::chrono::high_resolution_clock::now();
}

int64 
mkTimer::Duration_ns() const
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _begin).count();
}

int64 
mkTimer::Duration_us() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _begin).count();
}

int64 
mkTimer::Duration_ms() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _begin).count();
}

int64 
mkTimer::Duration_sec() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - _begin).count();
}

int64 
mkTimer::Duration_min() const
{
    return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - _begin).count();
}

int64 
mkTimer::Duration_hr() const
{
    return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - _begin).count();
}
