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

class SearchUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

//二重循环
bool imp_repeat1(vector<int> &v) 
{
	for (const auto& i : v) {
		for (const auto& j : v) {
			if (v[j] == v[i]) 
				return true;
		}
	}
	return false;
}


//二重循环
bool imp_repeat2(vector<int> &v) 
{
	int n = 100;
	std::bitset<1000> bcount;
	
	for (const auto& elem : v) {
		if(bcount[elem]) {
			return true;
		}
		bcount.set(elem);
	}
	
	return false;
}


//查找是否存在重复值
bool imp_Repeat3(vector<int>& v)
{
	for (const auto& i : v) {
		while (v[i] != i){
			int temp = v[i];
			
			if (v[i] == v[temp]) {
				return true;
			}
			else {
				int t = v[i];
				v[i] = v[temp];
				v[temp] = t;
			}
		}
	}
	return false;
}

TEST_F(SearchUT, SearchRepeat)
{
	vector<int> v = {1,2,54,6,87,5,4,2,45,677,434};
	bool result = imp_repeat2(v);
	cout << "result = "<<boolalpha <<result<<endl;
}

