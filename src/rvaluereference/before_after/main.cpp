/***************************************************************************************************
Author:liu.hao

Time:2018-4

info:

***************************************************************************************************/
#include <gtest/gtest.h>

int main(int argc, char** argv) 
{
    #ifdef __WINDOWS__
        //切换编译器版本,以及关闭一些优化选项,只在linux下生效
        static_assert(false, "windows is not supported.");
    #endif
    
    
    // 获取输入参数
    if(argc == 1) {
        printf("eg: ./test --gtest_filter=aaaUT.*    or: ./test --gtest_filter=aaaUT.*:bbbUT.*\n");
        return 0;
    }
    
    testing::InitGoogleTest(&argc, argv); 
    int ret = RUN_ALL_TESTS ();
    return ret;
}