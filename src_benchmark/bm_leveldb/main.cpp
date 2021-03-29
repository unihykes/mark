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

***************************************************************************************************/

#include <markcore.h>
#include <benchmark/benchmark.h>

MK_DEFINE_MODULE_INSTANCE(bm_leveldb, bm_leveldb, 1, 1, 1);

/*
int main(int argc, char** argv) 
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    
    ::benchmark::RunSpecifiedBenchmarks();
}
*/