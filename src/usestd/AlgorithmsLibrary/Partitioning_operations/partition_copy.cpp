/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
    
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//将区间内的元素分为两组复制到不同位置 
TEST(Partitioning, partition_copy)
{
    int arr [10] = {1,2,3,4,5,6,7,8,9,10};
    int true_arr [5] = {0};
    int false_arr [5] = {0};
    
    std::partition_copy(std::begin(arr), std::end(arr), std::begin(true_arr), std::begin(false_arr),
        [] (int i) {return i > 5;}
    );
    for(auto& elem : true_arr) {
        MK_PRINT_MSG("%d", elem);
    }
    for(auto& elem : false_arr) {
        MK_PRINT_MSG("%d", elem);
    }
}