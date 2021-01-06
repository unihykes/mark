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

Time:2021-1

info:

***************************************************************************************************/

#ifndef __mkModuleInstance
#define __mkModuleInstance



class MK_DLL_EXPORT mkModuleInstance final
{
public:
    mkModuleInstance(const std::string& moduleName, const std::string& resName);
    ~mkModuleInstance();
};



//声明全局变量
MK_VISIBILITY_HIDDEN extern std::shared_ptr<mkModuleInstance> g_moduleInstance;

//定义全局变量
#define MK_DEFINE_MODULE_INSTANCE(moduleName, resName)                                          \
    MK_VISIBILITY_HIDDEN std::shared_ptr<mkModuleInstance> g_moduleInstance(make_shared<mkModuleInstance>(#moduleName, #resName));              \


#endif