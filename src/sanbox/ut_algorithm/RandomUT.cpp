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

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <bitset>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class RandomUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

TEST_F(RandomUT, GetRandom)
{
	vector<int> vResult;
	set<int> setCheck;
	
	//设置随机数种子
	srand((unsigned int)time(nullptr));
	
	int count = 0;
	while(true) {
		count++;
		int a = rand()%100;//获取一个0-100之间的随机数
		//有重复值
		if(setCheck.count(a)) {
			continue;
		}
		//无重复值
		else {
			vResult.push_back(a);
			setCheck.insert(a);
		}
		if(vResult.size() == 100) {
			break;
		}
	}
	
	for(auto& elem : vResult) {
		cout << "elem = " << elem << "count = " <<count << endl;
	}
}

