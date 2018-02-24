/***************************************************************************************************
Author:liu.hao

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

