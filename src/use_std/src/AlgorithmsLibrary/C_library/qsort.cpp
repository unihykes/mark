/***************************************************************************************************
Author:liu.hao

Time:2018-6

info:
 
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


//排序类型未指定的元素的范围 
//定义于头文件 <cstdlib> 
TEST(C_library, qsort)
{
    //下列代码用 qsort() 排序整数数组。
    int a[] = {-2, 99, 0, -743, 2, INT_MIN, 4};
    constexpr std::size_t size = sizeof a / sizeof *a;
 
    std::qsort(a, size, sizeof *a, 
        [](const void* a, const void* b) {
            int arg1 = *static_cast<const int*>(a);
            int arg2 = *static_cast<const int*>(b);
            if(arg1 < arg2) 
                return -1;
            if(arg1 > arg2) 
                return 1;
            return 0;
        
            //  返回 (arg1 > arg2) - (arg1 < arg2); // 可行的缩写
            //  返回 arg1 - arg2; // 错误的缩写（若有 INT_MIN 则失败）
        }
    );
 
    for(int ai : a) {
        MK_PRINT_MSG("%d", ai);
    }
}

//在 ptr 所指向的数组中寻找等于 key 所指向的元素的元素 
TEST(C_library, bsearch)
{
    auto compare = [](const void *ap, const void *bp){
        auto a = static_cast<const int *>(ap);
        auto b = static_cast<const int *>(bp);
        if(*a < *b)
            return -1;
        else if(*a > *b)
            return 1;
        else
            return 0;
    };
    
    const int ARR_SIZE = 8;
    int arr[ARR_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8 };
 
    int key1 = 4;
    int *p1 = (int *) std::bsearch(&key1, arr, ARR_SIZE, sizeof(arr[0]), compare);
    if(p1) {
        std::cout << "value " << key1 << " found at position " << (p1 - arr) << '\n';
    }
    else {
        std::cout << "value " << key1 << " not found\n";
    }
     
    int key2 = 9;
    int *p2 = (int *) std::bsearch(&key2, arr, ARR_SIZE, sizeof(arr[0]), compare);
    if(p2) {
        std::cout << "value " << key2 << " found at position " << (p2 - arr) << '\n';
    }
    else {
       std::cout << "value " << key2 << " not found\n";
    }
}