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

Time:2021-2

info:

***************************************************************************************************/

#include <markcore.h>
#include "benchmark_helpers.h"
#include "_STR_.h"

MK_BM_BEGIN(mkString, constructor0)
{
    for (auto _ : __state__) {
        mkString src;
    }
    __state__.SetBytesProcessed(0);
}
MK_BM_END(mkString, constructor0);


MK_BM_BEGIN(mkString, constructor1)
{
    auto size = __state__.range(0);
    mkString src(size, _T('X'));
    
    for (auto _ : __state__) {
        mkString dest(src);
    }
    
    __state__.SetItemsProcessed(__state__.iterations());
    __state__.SetBytesProcessed(__state__.iterations() * size);
    __state__.SetLabel(mkFormat::str("per_size : %s", mkBytesFormat::str(size).c_str()));
}
MK_BM_END(mkString, constructor1)
    ->Range(1, 1<<30);



MK_BM_BEGIN(mkString, constructor3)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        mkString dest(std::move(src));
    }
}
MK_BM_END(mkString, constructor3);


MK_BM_BEGIN(mkString, constructor5)
{
    for (auto _ : __state__) {
        mkString src(4096, _T('A'));
    }
}
MK_BM_END(mkString, constructor5);


MK_BM_BEGIN(mkString, constructor6)
{
    for (auto _ : __state__) {
        mkString src(T_CHAR_STR);
    }
}
MK_BM_END(mkString, constructor6);



MK_BM_BEGIN(mkString, assign0)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(src);
    }
}
MK_BM_END(mkString, assign0);


MK_BM_BEGIN(mkString, assign3)
{
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(T_CHAR_STR);
    }
}
MK_BM_END(mkString, assign3);

MK_BM_BEGIN(mkString, assign4)
{
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(4096, _T('A'));
    }
}
MK_BM_END(mkString, assign4);


MK_BM_BEGIN(mkString, assign5)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(std::move(src));
    }
}
MK_BM_END(mkString, assign5);



MK_BM_BEGIN(mkString, append0)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.append(src);
    }
}
MK_BM_END(mkString, append0);


MK_BM_BEGIN(mkString, append3)
{
    mkString dest;
    for (auto _ : __state__) {
        dest.append(T_CHAR_STR);
    }
}
MK_BM_END(mkString, append3);


MK_BM_BEGIN(mkString, append4)
{
    mkString dest;
    for (auto _ : __state__) {
        dest.append(4096, _T('A'));
    }
}
MK_BM_END(mkString, append4);



MK_BM_BEGIN(mkString, append9)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.append(std::move(src));
    }
}
MK_BM_END(mkString, append9);


MK_BM_BEGIN(mkString, getx)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto alloc = src.get_allocator();
        auto len = src.length();
        auto cap = src.capacity();
        auto maxSize = src.max_size();
        auto isEmpty = src.empty();
        auto p = src.c_str();
    }
}
MK_BM_END(mkString, getx);

MK_BM_BEGIN(mkString, at1)
{
    mkString src;
    src.resize(1024);
    size_t size = src.size();
    for (auto _ : __state__) {
        for(size_t pos = 0 ; pos != size; ++pos) {
            auto ret = src.at(pos);
        }
    }
}
MK_BM_END(mkString, at1);

MK_BM_BEGIN(mkString, at2)
{
    mkString src;
    src.resize(1024*1024);
    size_t size = src.size();
    for (auto _ : __state__) {
        for(size_t pos = 0 ; pos != size; ++pos) {
            auto ret = src.at(pos);
        }
    }
}
MK_BM_END(mkString, at2);





MK_BM_BEGIN(mkString, remove1)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        src.erase();
    }
}
MK_BM_END(mkString, remove1);


MK_BM_BEGIN(mkString, remove2)
{
    mkString src(T_CHAR_STR);
    size_t offset = src.size()/2;
    for (auto _ : __state__) {
        src.erase(offset, 1);
    }
}
MK_BM_END(mkString, remove2);

MK_BM_BEGIN(mkString, remove3)
{
    mkString src(T_CHAR_STR);
    size_t offset = src.size() - 1;
    for (auto _ : __state__) {
        src.erase(offset);
    }
}
MK_BM_END(mkString, remove3);


MK_BM_BEGIN(mkString, clear)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        src.clear();
    }
}
MK_BM_END(mkString, clear);


MK_BM_BEGIN(mkString, swap)
{
    mkString src(T_CHAR_STR);
    mkString dest(T_CHAR_STR);
    
    for (auto _ : __state__) {
        dest.swap(src);
    }
}
MK_BM_END(mkString, swap);



MK_BM_BEGIN(mkString, reserve)
{
    mkString src(T_CHAR_STR);
    size_t size = 4<<20;//1MB
    for (auto _ : __state__) {
        src.reserve(size);
    }
}
MK_BM_END(mkString, reserve);


MK_BM_BEGIN(std_string, find_non_exist)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto pos = src.find(';');
    }
}
MK_BM_END(std_string, find_non_exist);

MK_BM_BEGIN(std_string, find_exist_middle)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto pos = src.find('$');
    }
}
MK_BM_END(std_string, find_exist_middle);

MK_BM_BEGIN(std_string, find_exist_tail)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto pos = src.find('#');
    }
}
MK_BM_END(std_string, find_exist_tail);


MK_BM_BEGIN(mkString, to_upper_without)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        for(auto& elem : src) {
            elem = ::toupper(elem);
        }
    }
}
MK_BM_END(mkString, to_upper_without);

