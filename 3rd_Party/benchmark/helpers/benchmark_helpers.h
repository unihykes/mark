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

1.BENCHMARK 宏解析:

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

可简化为:
static auto BENCHMARK_PRIVATE_NAME(n) = ::benchmark::RegisterBenchmark(#n, n);


2.BENCHMARK_DEFINE_F 宏解析

#define BENCHMARK_PRIVATE_DECLARE_F(BaseClass, Method)        \
  class BaseClass##_##Method##_Benchmark : public BaseClass { \
   public:                                                    \
    BaseClass##_##Method##_Benchmark() : BaseClass() {        \
      this->SetName(#BaseClass "/" #Method);                  \
    }                                                         \
                                                              \
   protected:                                                 \
    virtual void BenchmarkCase(::benchmark::State&);          \
  };
  
#define BENCHMARK_PRIVATE_CONCAT_NAME(BaseClass, Method) \
    BaseClass##_##Method##_Benchmark

#define BENCHMARK_DEFINE_F(BaseClass, Method)    \
  BENCHMARK_PRIVATE_DECLARE_F(BaseClass, Method) \
  void BENCHMARK_PRIVATE_CONCAT_NAME(BaseClass, Method)::BenchmarkCase

***************************************************************************************************/
#ifndef __benchmark_helpers
#define __benchmark_helpers

#include <benchmark/benchmark.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
//方式1:单独使用benchmark, 上层定义全局函数,直接注册
#define MK_BM_REGISTER_FUNC(Fun) \
    static auto BENCHMARK_PRIVATE_NAME(Fun) = ::benchmark::RegisterBenchmark(#Fun, Fun)
    

////////////////////////////////////////////////////////////////////////////////////////////////////
//方式2:单独使用benchmark, 样式类似全局函数, 上层无需定义 BM_CLASS

#define MK_BM_BEGIN(BM_CLASS, Method)                                                                   \
    class BM_CLASS##_##Method##_Benchmark : public benchmark::Fixture                                   \
    {                                                                                                   \
    public:                                                                                             \
        BM_CLASS##_##Method##_Benchmark()                                                               \
        {                                                                                               \
            this->SetName(#BM_CLASS "/" #Method);                                                       \
        }                                                                                               \
        virtual void BenchmarkCase(::benchmark::State& __state__);                                      \
    };                                                                                                  \
    void BM_CLASS##_##Method##_Benchmark::BenchmarkCase(::benchmark::State& __state__)
    

#define MK_BM_END(BM_CLASS, Method) BENCHMARK_REGISTER_F(BM_CLASS, Method)


////////////////////////////////////////////////////////////////////////////////////////////////////
//方式3:单独使用benchmark, 样式类似成员函数, 上层需要定义类 BM_CLASS, 
#define MK_BM_F_BEGIN(BM_CLASS, Method) BENCHMARK_DEFINE_F(BM_CLASS, Method)(::benchmark::State& __state__)

#define MK_BM_F_END(BM_CLASS, Method)   BENCHMARK_REGISTER_F(BM_CLASS, Method)



////////////////////////////////////////////////////////////////////////////////////////////////////
//方式4: 与gtest的TEST_F()搭配使用
template<class GTEST_CLASS>
class mkTestToBenchmark : public benchmark::Fixture, public GTEST_CLASS
{
public:
    using GTEST_CLASS::SetUp;
    virtual void SetUp(benchmark::State& st)
    {
        GTEST_CLASS::SetUp();
    }
    
    using GTEST_CLASS::TearDown;
    virtual void TearDown(benchmark::State& st)
    {
        GTEST_CLASS::TearDown();
    }
private:
    virtual void TestBody()
    {
        //使该派生类可以实例化
    }
};

#define MK_BM_TEST_F_BEGIN(GTEST_CLASS, Method)                                                    \
    class GTEST_CLASS##_##Method##_Benchmark : public mkTestToBenchmark<GTEST_CLASS>                    \
    {                                                                                                   \
    public:                                                                                             \
        GTEST_CLASS##_##Method##_Benchmark()                                                            \
        {                                                                                               \
            this->SetName(#GTEST_CLASS "/" #Method); /*must have a name, or cannot register*/           \
        }                                                                                               \
        virtual void BenchmarkCase(::benchmark::State& __state__);                                      \
    };                                                                                                  \
    void GTEST_CLASS##_##Method##_Benchmark::BenchmarkCase(::benchmark::State& __state__)
    
#define MK_BM_TEST_F_END(GTEST_CLASS, Method)                                                      \
    static auto BENCHMARK_PRIVATE_NAME(GTEST_CLASS##_##Method##_Benchmark)                              \
        = ::benchmark::internal::RegisterBenchmarkInternal(new GTEST_CLASS##_##Method##_Benchmark())






#endif