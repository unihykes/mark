/***************************************************************************************************
Author:liu.hao

Time:2017-6

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

class ncEnvironment : public testing::Environment
{
public:
//	virtual void SetUp(){}
//	virtual void TearDown(){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// main
//
int main(int argc, char** argv)
{
	// 获取输入参数
	if(argc == 1) {
		wprintf(_T("-gtest_filter=aaaUT.*:bbbUT.*"));
		return -1;
	}
	
	try {
		testing::AddGlobalTestEnvironment(new ncEnvironment());
		testing::InitGoogleTest(&argc, argv); 
		
		int ret = RUN_ALL_TESTS ();
		return ret;
	}
	catch (...) {
		wprintf (_T("Test Error: Unknown."));
		return -1;
	}
	
	return 0;
}