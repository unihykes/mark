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
#include <gtest/gtest.h>
#include <gflags/gflags.h>


MK_DEFINE_MODULE_INSTANCE(use_brpc_client, use_brpc_client, 1, 1, 1);

DEFINE_string(cmd, "default", "default");

int main(int argc, char** argv)
{
    // 解析参数
    auto gtestEnv = g_moduleInstance->_switch->InitEnv(argc, argv);
    
    // 获取输入参数
    if(gtestEnv.first == 1) {
        testing::GTEST_FLAG(list_tests) = true;
    }
    
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    testing::InitGoogleTest(&gtestEnv.first, gtestEnv.second);
    int ret = RUN_ALL_TESTS ();
    return ret;
}