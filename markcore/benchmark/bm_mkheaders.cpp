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


MK_BM_BEGIN(mkheaders, memcpy)
{
    auto size = __state__.range(0);
    
    std::unique_ptr<char[]> src(new char[size]);
    std::unique_ptr<char[]> dest(new char[size]);
    
    for (auto _ : __state__) {
        memcpy(dest.get(), src.get(), size);
        memcpy(src.get(), dest.get(), size);
    }
    
    __state__.SetItemsProcessed(__state__.iterations());
    __state__.SetBytesProcessed(__state__.iterations() * size*2);
    __state__.SetLabel(mkFormat::str("per_size : %s", mkBytesFormat::str(size).c_str()));
}
MK_BM_END(mkheaders, memcpy)->UseRealTime()->Range(1, 1<<22);

