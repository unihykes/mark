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

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
// main
//

int main(int argc, char** argv) 
{
	// 获取输入参数
	if(argc == 1) {
		printf("eg: ./test --gtest_filter=aaaUT.*    or: ./test --gtest_filter=aaaUT.*:bbbUT.*");
		return 0;
	}
	
	//testing::AddGlobalTestEnvironment(new ncEnvironment());
	testing::InitGoogleTest(&argc, argv); 
	
	int ret = RUN_ALL_TESTS ();
	return ret;
}