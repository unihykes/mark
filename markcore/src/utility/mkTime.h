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

Time:2021-1

info:

***************************************************************************************************/

#ifndef __mkTime
#define __mkTime

class MK_DLL_EXPORT mkTime
{
public:
    static int64 GetCurrentTime();
    static string GetCurrentTimeStr();
    
public:
    mkTime(const int64 time);
    ~mkTime();
    
    unsigned int GetYear() const;
    unsigned int GetMonth() const;
    unsigned int GetDay() const;
    unsigned int GetHours() const;
    unsigned int GetMinutes() const;
    unsigned int GetSeconds() const;
    string ToString() const;
};

#endif