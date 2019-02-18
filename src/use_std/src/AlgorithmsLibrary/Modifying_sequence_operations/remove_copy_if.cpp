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
#include <cctype>//for std::isspace

//复制一个范围内不满足特定条件的元素 
TEST(MSQ, remove_copy_if)
{
    std::string str = "Text with some   spaces";
    std::string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret), [](unsigned char x){return std::isspace(x);});
    MK_PRINT_MSG("ret = %s", ret.c_str());
}