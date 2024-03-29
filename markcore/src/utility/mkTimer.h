﻿/***************************************************************************************************
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

#ifndef __mkTimer
#define __mkTimer

#include <chrono>

class MK_DLL_EXPORT mkTimer
{
public:
    mkTimer();
    ~mkTimer();
    void Reset();
    int64 Duration_ns() const;
    int64 Duration_us() const;
    int64 Duration_ms() const;
    int64 Duration_sec() const;
    int64 Duration_min() const;
    int64 Duration_hr() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _begin;
};

#endif