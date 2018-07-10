/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

class ut_LanguageSupport : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// 附加性基本类型及宏
//

TEST_F(ut_LanguageSupport, size_t)
{
    //todo
}

TEST_F(ut_LanguageSupport, ptrdiff_t)
{
    //todo
}

//C++11)
TEST_F(ut_LanguageSupport, nullptr_t)
{
    //todo
}

TEST_F(ut_LanguageSupport, NULL)
{
    //todo
}

TEST_F(ut_LanguageSupport, max_align_t)
{
    //todo
}

//标准布局类型的成员相对类型起始地址的字符偏移量 
TEST_F(ut_LanguageSupport, offsetof)
{
    struct S 
    {
        char c;//0-3
        int d;//4-7
        short e;//8-11
        short f;//8-11
    };
    MK_PRINT_MSG("sizeof(S) = %d", sizeof(S));
    MK_PRINT_MSG("offsetof(S.c) = %d", offsetof(S, c));
    MK_PRINT_MSG("offsetof(S.d) = %d", offsetof(S, d));
    MK_PRINT_MSG("offsetof(S.e) = %d", offsetof(S, e));
    MK_PRINT_MSG("offsetof(S.f) = %d", offsetof(S, f));
    struct alignas(8) S2 
    {
        char c;//0-7
        int d;//0-7
        short e;//8-15
        short f;//8-15
    };
    MK_PRINT_MSG("sizeof(S2) = %d", sizeof(S2));
    MK_PRINT_MSG("offsetof(S2.c) = %d", offsetof(S2, c));
    MK_PRINT_MSG("offsetof(S2.d) = %d", offsetof(S2, d));
    MK_PRINT_MSG("offsetof(S2.e) = %d", offsetof(S2, e));
    MK_PRINT_MSG("offsetof(S.f) = %d", offsetof(S, f));
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// 定宽整数(C++11 起)
//
#include <cinttypes>
TEST_F(ut_LanguageSupport, Fixed_width_integer)
{
    /**
    int8_t
    int16_t
    int32_t
    int64_t
    */
    std::printf("%zu\n", sizeof(std::int64_t));
    std::printf("%s\n", PRId64);
    std::printf("%+" PRId64 "\n", INT64_MIN);
    std::printf("%+" PRId64 "\n", INT64_MAX);
 
    std::int64_t n = 7;
    std::printf("%+" PRId64 "\n", n);
    std::printf("%+" "lld" "\n", n);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// std::numeric_limits
//


////////////////////////////////////////////////////////////////////////////////////////////////////
// C 数值极限接口
//


////////////////////////////////////////////////////////////////////////////////////////////////////
// 类型特性(C++11 起)
//

