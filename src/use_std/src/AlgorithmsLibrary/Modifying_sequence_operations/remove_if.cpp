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

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <cctype>//for std::isspace

//从范围 [first, last) 移除所有满足特定判别标准的元素，并返回范围新结尾的尾后迭代器。 
TEST(MSQ, remove_if)
{
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), str2.end(),
                [](unsigned char x){return std::isspace(x);}),str2.end());
    MK_PRINT_MSG("str2 = %s", str2.c_str());
}
