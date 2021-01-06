/***************************************************************************************************
LICENSE:
    Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
Author:liu.hao(33852613@163.com)

Time:2017-8

info:

***************************************************************************************************/

#include<mkheaders.h>
#include "markcore.h"

MK_DEFINE_MODULE_INSTANCE(markcore, markcore);

#ifdef __WINDOWS__
    void* hModule = 0;
    
    static void NoMemory ()
    {
        assert (false);
        throw std::exception("Failed to allocate memory!\n");
    }
    
    extern "C" 
    int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
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