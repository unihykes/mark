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

//从始于 first 的范围复制 count 个元素到始于 d_first 的未初始化内存区域 
TEST(Uninitialized_memory, uninitialized_copy_n)
{
    std::vector<std::string> v = {"This", "is", "an", "example"};
 
    std::string* p;
    std::size_t sz;
    std::tie(p, sz)  = std::get_temporary_buffer<std::string>(v.size());
    sz = (std::min)(sz, v.size());
 
    std::uninitialized_copy_n(v.begin(), sz, p);
 
    for (std::string* i = p; i != p+sz; ++i) {
        std::cout << *i << ' ';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}
