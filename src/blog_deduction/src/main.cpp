/***************************************************************************************************
Author:liu.hao

Time:2018-5

info:

***************************************************************************************************/
#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////
// main
//

int main(int argc, char** argv) 
{
    if(argc == 1) {
        printf("eg: ./test --gtest_filter=aaaUT.*\
                or: ./test --gtest_filter=aaaUT.*:bbbUT.*");
        return 0;
    }
    
    //testing::AddGlobalTestEnvironment(new ncEnvironment());
    testing::InitGoogleTest(&argc, argv); 
    int ret = RUN_ALL_TESTS ();
    return ret;
}