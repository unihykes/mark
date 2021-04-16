/***************************************************************************************************
Author:liu.hao

Time:2021-3

info:
    
***************************************************************************************************/

#include <markcore.h>
#include "benchmark_helpers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//benchmark


MK_BM_BEGIN(mkheaders, call_once1)
{
    static int64 i = 100;
    for (auto _ : __state__) {
        MK_CALL_ONCE_BEGIN
        ++i;
        MK_CALL_ONCE_END
    }
}
MK_BM_END(mkheaders, call_once1);

std::once_flag flag1;

MK_BM_BEGIN(mkheaders, call_once2)
{
    static int64 i = 100;
    for (auto _ : __state__) {
        std::call_once(flag1, [](){++i;});
    }
}
MK_BM_END(mkheaders, call_once2);