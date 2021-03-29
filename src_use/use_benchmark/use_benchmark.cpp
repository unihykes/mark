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

宏解析:

#if defined(__COUNTER__) && (__COUNTER__ + 1 == __COUNTER__ + 0)
#define BENCHMARK_PRIVATE_UNIQUE_ID __COUNTER__
#else
#define BENCHMARK_PRIVATE_UNIQUE_ID __LINE__
#endif

#define BENCHMARK_PRIVATE_CONCAT2(a, b, c) a##b##c

#define BENCHMARK_PRIVATE_CONCAT(a, b, c) BENCHMARK_PRIVATE_CONCAT2(a, b, c)

#define BENCHMARK_PRIVATE_NAME(n)  BENCHMARK_PRIVATE_CONCAT(_benchmark_, BENCHMARK_PRIVATE_UNIQUE_ID, n)

#if defined(__GNUC__)
#define BENCHMARK_UNUSED __attribute__((unused))
#endif

#define BENCHMARK_PRIVATE_DECLARE(n) static ::benchmark::internal::Benchmark* BENCHMARK_PRIVATE_NAME(n) BENCHMARK_UNUSED

#define BENCHMARK(n)  BENCHMARK_PRIVATE_DECLARE(n)=(::benchmark::internal::RegisterBenchmarkInternal(new ::benchmark::internal::FunctionBenchmark(#n, n)))


通过以上宏定义的原型,BENCHMARK(n)可解析成:
#define BENCHMARK(n) \
static ::benchmark::internal::Benchmark* _benchmark_##__COUNTER__##n  __attribute__((unused)) 
    = (::benchmark::internal::RegisterBenchmarkInternal(new ::benchmark::internal::FunctionBenchmark(#n, n)))


***************************************************************************************************/
#include <markcore.h>
#include <benchmark/benchmark.h>

static void run1(benchmark::State& state) 
{
    int i = 0;
    for (auto _ : state) {
        string x = mkSharedFormat{}("%s, %d", "run1", i++);
    }
}

auto run2 = [](benchmark::State& state){
    int i = 0;
    for (auto _ : state) {
        shared_ptr<char> p = mkSharedFormat::fmt("%s, %d", "run2", i++);
    }
};

BENCHMARK(run2)->RangeMultiplier(10)->Range(10, 1000);
static ::benchmark::internal::Benchmark* prun2 = ::benchmark::RegisterBenchmark("run2", run2);