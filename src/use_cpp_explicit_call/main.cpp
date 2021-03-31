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

Time:2018-5

info:

***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
#include "benchmark_helpers.h"

MK_DEFINE_EXEC_INSTANCE(use_cpp_explicit_call, use_cpp_explicit_call, 1, 1, 1);

int main(int argc, char** argv) 
{
    auto gbEnv = g_moduleInstance->_switch->InitEnv(argc, argv);
    
    //run gtest
    if(std::get<0>(gbEnv) == 1) {
        testing::GTEST_FLAG(list_tests) = true;
    }
    testing::InitGoogleTest(&std::get<0>(gbEnv), std::get<1>(gbEnv));
    RUN_ALL_TESTS ();
    
    //run benchmark
    if(std::get<2>(gbEnv) > 1) {
        ::benchmark::Initialize(&std::get<2>(gbEnv) , std::get<3>(gbEnv) );
        if (::benchmark::ReportUnrecognizedArguments(std::get<2>(gbEnv), std::get<3>(gbEnv))) {
            MK_PRINT("error");
            return -1;
        }
        ::benchmark::RunSpecifiedBenchmarks();
    }
    
    return 0;
}