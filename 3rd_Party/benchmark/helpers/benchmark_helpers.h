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

#define MK_BM_FUNC(Fun) \
    static auto BENCHMARK_PRIVATE_NAME(Fun) = ::benchmark::RegisterBenchmark(#Fun, Fun)
    
#define MK_BM_CLASS(Class) \
    static auto BENCHMARK_PRIVATE_NAME(Class) = ::benchmark::internal::RegisterBenchmarkInternal(new Class())


template<class GTEST_CLASS>
class mkTest2Benchmark : public benchmark::Fixture
{

public:
    virtual void SetUp(benchmark::State& st)
    {
        _pTest = std::make_shared<mk_GTEST_CLASS_public>();
        _pTest->SetUp();
    }
    
    virtual void TearDown(benchmark::State& st)
    {
        _pTest->TearDown();
        _pTest.reset();
    }
private:
    //将 SetUp 和 TearDown 从protected 转换为 public
    class mk_GTEST_CLASS_public : public GTEST_CLASS
    {
    public:
      virtual void SetUp()
      {
          return GTEST_CLASS::SetUp();
      }

      virtual void TearDown()
      {
          return GTEST_CLASS::TearDown();
      }
    };
private:
    std::shared_ptr<mk_GTEST_CLASS_public>    _pTest;
};

//在 TEST(...) 或者 TEST_F() 之后使用,借用 TEST(...) 或者 TEST_F() 的业务逻辑
#define MK_BM_FROM_TEST_BEGIN(GTEST_CLASS, Method)                                                      \
    class GTEST_CLASS##_##Method##_Benchmark : public mkTest2Benchmark<GTEST_CLASS##_##Method##_Test>   \
    {                                                                                                   \
    public:                                                                                             \
        GTEST_CLASS##_##Method##_Benchmark()                                                            \
        {                                                                                               \
            this->SetName(#GTEST_CLASS "/" #Method); /*must have a name, or cannot register*/           \
        }                                                                                               \
        virtual void BenchmarkCase(::benchmark::State& __state__);                                      \
    };                                                                                                  \
    void GTEST_CLASS##_##Method##_Benchmark::BenchmarkCase(::benchmark::State& __state__)
    
//紧随 MK_BM_FROM_TEST_BEGIN 之后使用,将该 benchmark 注册到待处理列表中
#define MK_BM_FROM_TEST_END(GTEST_CLASS, Method)                                                        \
    MK_BM_CLASS(GTEST_CLASS##_##Method##_Benchmark)


#endif