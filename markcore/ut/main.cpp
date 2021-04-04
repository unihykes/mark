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

#ifndef __MK_MODULE_NAME__
    #error "error, need to define macro __MK_MODULE_NAME__ first"
#endif

//MK_DEFINE_EXEC_INSTANCE(use_markcore, use_markcore,1,1,1);
MK_VISIBILITY_HIDDEN std::shared_ptr<mkModuleInstance> g_moduleInstance 
    = std::make_shared<mkModuleInstance>(__MK_MODULE_NAME__, __MK_MODULE_NAME__, 1, 1, 1, true);

int main(int argc, char** argv) 
{
    MK_PRINT("version = 0x%09x", g_moduleInstance->_version->Get());
    auto gbEnv = g_moduleInstance->_switch->InitEnv(argc, argv);
    
    int result = 0;
    
    //run gtest
    if(std::get<0>(gbEnv) > 1) {
        testing::InitGoogleTest(&std::get<0>(gbEnv), std::get<1>(gbEnv));
        RUN_ALL_TESTS ();
         ++result;
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
        RUN_ALL_TESTS ();
        return result;
    }
    
    return result;
}