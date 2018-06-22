/***************************************************************************************************
Author:liu.hao

Time:2017-8

info:

***************************************************************************************************/

#include<mkheaders.h>

#ifdef __WINDOWS__
    void* hModule = 0;
    
    static void NoMemory ()
    {
        assert (false);
        throw std::exception("Failed to allocate memory!\n");
    }
    
    extern "C" 
    int APIENTRY DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
        if (dwReason == DLL_PROCESS_ATTACH) {
            hModule = hInstance;
            
            //set_new_handler函数的作用是设置
            //new_p指向的函数为new操作或new[]操作失败时调用的处理函数。
            std::set_new_handler (NoMemory);
        }
        
        return 1;
    }
#endif