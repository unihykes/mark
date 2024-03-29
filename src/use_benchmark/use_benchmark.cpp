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
#include <markcore.h>
#include <benchmark/benchmark.h>

static void run1(benchmark::State& state) 
{
    int i = 0;
    for (auto _ : state) {
        string x = mkFormat::str("%s, %d", "run1", i++);
    }
}

auto run2 = [](benchmark::State& state){
    int i = 0;
    for (auto _ : state) {
        shared_ptr<char> p = mkFormat::shared("%s, %d", "run2", i++);
    }
};

BENCHMARK(run2)->RangeMultiplier(10)->Range(10, 1000);
static ::benchmark::internal::Benchmark* prun2 = ::benchmark::RegisterBenchmark("run2", run2);