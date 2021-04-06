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

Time:2018-2

info:

***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
#include "benchmark_helpers.h"

MK_DEFINE_EXEC_INSTANCE_VERSION(1, 0, 0);

int main(int argc, char** argv) 
{
    MK_PRINT("version = 0x%09x", g_moduleInstance->_version->Get());
    auto gbEnv = g_moduleInstance->_switch->InitEnv(argc, argv);
    
    int result = 0;
    
    //run gtest
    if(std::get<0>(gbEnv) > 1) {
        testing::InitGoogleTest(&std::get<0>(gbEnv), std::get<1>(gbEnv));
        if(RUN_ALL_TESTS () >= 0) {//Just to eliminate the warning
            ++result;
        }
    }
    
    //run benchmark
    if(std::get<2>(gbEnv) > 1) {
        ::benchmark::Initialize(&std::get<2>(gbEnv) , std::get<3>(gbEnv) );
        if (!benchmark::ReportUnrecognizedArguments(std::get<2>(gbEnv), std::get<3>(gbEnv))) {
            ::benchmark::RunSpecifiedBenchmarks();
            ++result;
        }
    }
    
    //run nothing
    if(!result) {
        testing::GTEST_FLAG(list_tests) = true;
        return RUN_ALL_TESTS ();
    }
    
    return result;
}