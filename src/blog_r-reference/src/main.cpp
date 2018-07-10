/***************************************************************************************************
Author:liu.hao

Time:2018-3

info:

***************************************************************************************************/
#include <mkheaders.h>
#include <gtest/gtest.h>
#include "ncAutoProfilePoint.h"

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
    
    //初始化 ncAutoProfilePoint
    double usedSecond = 0;
    {
        ncAutoProfilePoint point(usedSecond);
    }
    
    //testing::AddGlobalTestEnvironment(new ncEnvironment());
    testing::InitGoogleTest(&argc, argv); 
    int ret = RUN_ALL_TESTS ();
    return ret;
}