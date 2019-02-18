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

Time:2017-6

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkString.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// ncEnvironment
//
//全局事件：此处定义的变量，可以全局使用
class ncEnvironment : public testing::Environment
{
public:
	virtual void SetUp()
	{
	}
	virtual void TearDown()
	{
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// main
//
int main(int argc, char** argv)
{
	// 获取输入参数
	if(argc == 1) {
		wprintf(_T(" Error:Invalid arguments! 									\
						\n Please use the following way: 								\
						\n    ./test --gtest_filter=aaaUT.*								\
						\n or:./test --gtest_filter=aaaUT.*:bbbUT.*						\
						"));
		return 0;
	}
	
	try {
		testing::AddGlobalTestEnvironment(new ncEnvironment());
		testing::InitGoogleTest(&argc, argv); 
		
		int ret = RUN_ALL_TESTS ();
		return ret;
	}
	catch (...) {
		wprintf (_T("Test Error: Unknown."));
		return 1;
	}
	
	return 0;
}