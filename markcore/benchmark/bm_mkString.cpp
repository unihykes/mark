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

MK_BM_BEGIN(mkString, empty)
{
    for (auto _ : __state__) {
        mkString src;
    }
}
MK_BM_END(mkString, empty);


MK_BM_BEGIN(mkString, constructor)
{
    for (auto _ : __state__) {
        mkString src(T_CHAR_STR);
    }
}
MK_BM_END(mkString, constructor);


MK_BM_BEGIN(mkString, copy_constructor)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        mkString copy(src);
    }
}
MK_BM_END(mkString, copy_constructor);


MK_BM_BEGIN(mkString, copy_constructor_RR1)
{
    auto Create = []() -> mkString{
        return mkString(T_CHAR_STR);
    };
    for (auto _ : __state__) {
        mkString dest(Create());
    }
}
MK_BM_END(mkString, copy_constructor_RR1);



MK_BM_BEGIN(mkString, copy_constructor_RR2)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        mkString dest(std::move(src));
    }
}
MK_BM_END(mkString, copy_constructor_RR2);

MK_BM_BEGIN(mkString, assign)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(src);
    }
}
MK_BM_END(mkString, assign);


MK_BM_BEGIN(mkString, assign_RR)
{
    mkString src(T_CHAR_STR);
    mkString dest;
    for (auto _ : __state__) {
        dest.assign(std::move(src));
    }
}
MK_BM_END(mkString, assign_RR);

MK_BM_BEGIN(mkString, append_RR)
{
    mkString dest;
    for (auto _ : __state__) {
        dest.append(mkString(T_CHAR_STR));
    }
}
MK_BM_END(mkString, append_RR);

MK_BM_BEGIN(mkString, length)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto ret = src.length();
    }
    MK_PRINT("length = %lld", src.length());
}
MK_BM_END(mkString, length)->Iterations(1<<30);

MK_BM_BEGIN(mkString, capacity)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        auto ret = src.capacity();
    }
}
MK_BM_END(mkString, capacity);


MK_BM_BEGIN(mkString, at)
{
    mkString src(T_CHAR_STR);
    int64 offset = src.size();
    for (auto _ : __state__) {
        while(--offset >= 0) {
            auto ret = src.at(offset);
        }
    }
}
MK_BM_END(mkString, at);





MK_BM_BEGIN(mkString, remove_erase)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        src.erase(0);
    }
}
MK_BM_END(mkString, remove_erase);




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
    mkString dest;
    for (auto _ : __state__) {
        dest.swap(src);
    }
}
MK_BM_END(mkString, swap);



MK_BM_BEGIN(mkString, reserve)
{
    mkString src(T_CHAR_STR);
    for (auto _ : __state__) {
        src.reserve(1<<20);
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

