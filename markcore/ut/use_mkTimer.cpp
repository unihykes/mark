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

Time:2018-2

info:

***************************************************************************************************/

#include <markcore.h>
#include <gtest/gtest.h>

TEST(mkTimer, run)
{
    mkTimer timer;
    this_thread::sleep_for(std::chrono::seconds(1));
    MK_PRINT("Duration_ns = %lld", timer.Duration_ns());
    MK_PRINT("Duration_us = %lld", timer.Duration_us());
    MK_PRINT("Duration_ms = %lld", timer.Duration_ms());
    MK_PRINT("Duration_sec = %lld", timer.Duration_sec());
    MK_PRINT("Duration_min = %lld", timer.Duration_min());
    MK_PRINT("Duration_hr = %lld", timer.Duration_hr());
}
