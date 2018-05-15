/***************************************************************************************************
Author:liu.hao

Time:2017-8

info:

***************************************************************************************************/

#include<mkheaders.h>

#if defined(__MAKE_MONK_DLL__) && defined(__WINDOWS__)
    void* hModule = 0;
    
    static void oomHandler (void)
    {
        assert (false);
        //throw Exception(_T("Out Of Memory Exception"));
    }

    extern "C" int APIENTRY DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
        if (dwReason == DLL_PROCESS_ATTACH) {
            hModule = hInstance;
            
            // 设置内存不足时的处理器对象。
            set_new_handler (&oomHandler);
        }
        
        return 1;
    }
#endif