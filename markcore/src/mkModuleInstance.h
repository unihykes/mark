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

class mkTrace;
class mkLog;
class mkPrint;
class mkOptionSwitch;
class mkVersion;
class mkPerf;

class MK_DLL_EXPORT mkModuleInstance final
{
public:
    mkModuleInstance(const std::string& moduleName, const std::string& resName, 
                    unsigned int major, unsigned int minor, unsigned int patch, bool isExec);
    ~mkModuleInstance();
    
public:
    shared_ptr<mkTrace> _trace;
    shared_ptr<mkLog> _loger;
    shared_ptr<mkPrint> _print;
    shared_ptr<mkOptionSwitch> _switch;
    shared_ptr<mkVersion> _version;
    shared_ptr<mkPerf> _perf;
};

//声明全局变量: g_moduleInstance
MK_VISIBILITY_HIDDEN extern std::shared_ptr<mkModuleInstance> g_moduleInstance;

//定义全局变量: g_moduleInstance
#define MK_DEFINE_MODULE_INSTANCE_S(moduleName, resName, major, minor, patch)                   \
    MK_VISIBILITY_HIDDEN std::shared_ptr<mkModuleInstance> g_moduleInstance =                   \
        std::make_shared<mkModuleInstance>(moduleName, resName, major, minor, patch, false)
        
#define MK_DEFINE_MODULE_INSTANCE(moduleName, resName, major, minor, patch)                     \
    MK_DEFINE_MODULE_INSTANCE_S(#moduleName, #resName, major, minor, patch)

#define MK_DEFINE_MODULE_INSTANCE_VERSION(major, minor, patch)                                  \
    MK_DEFINE_MODULE_INSTANCE_S(__MK_MODULE_NAME__, __MK_MODULE_NAME__, major, minor, patch)
    
//定义全局变量: g_moduleInstance
#define MK_DEFINE_EXEC_INSTANCE_S(moduleName, resName, major, minor, patch)                     \
    MK_VISIBILITY_HIDDEN std::shared_ptr<mkModuleInstance> g_moduleInstance =                   \
        std::make_shared<mkModuleInstance>(moduleName, resName, major, minor, patch, true)
        
#define MK_DEFINE_EXEC_INSTANCE(moduleName, resName, major, minor, patch)                       \
    MK_DEFINE_EXEC_INSTANCE_S(#moduleName, #resName, major, minor, patch)

#define MK_DEFINE_EXEC_INSTANCE_VERSION(major, minor, patch)                                    \
    MK_DEFINE_EXEC_INSTANCE_S(__MK_MODULE_NAME__, __MK_MODULE_NAME__, major, minor, patch)

//定义全局变量
#define g_switch    g_moduleInstance->_switch


//全局宏:print
#define MK_PRINT(...)       (*g_moduleInstance->_print)(__FILE__, __LINE__, __func__, ##__VA_ARGS__)

//全局宏:trace
#define MK_TRACE(...)       (*g_moduleInstance->_trace)(__FILE__, __LINE__, __func__, ##__VA_ARGS__)

//全局宏:log
#define MK_LOG(...)         (*g_moduleInstance->_loger)(__FILE__, __LINE__, __func__, ##__VA_ARGS__)

//全局宏:throw
#define MK_THROW(errorid, ...)                                              \
    do {                                                                    \
        auto __errMsg__ = mkSharedFormat::fmt(__VA_ARGS__);                 \
        MK_LOG(__VA_ARGS__);                                                \
        mkException __e__(string(__errMsg__.get()), __FILE__, __LINE__, errorid);   \
        throw __e__;                                                        \
    } while(0)
    
//全局宏:perf (性能桩)
#ifdef __MK_PERF_ENABLE__
	#define MK_PERF() mkPerf::Point __mkPerf_Point_##__LINE__(g_moduleInstance->_perf, __func__, __LINE__);
#else
	#define MK_PERF()
#endif


    
    
#endif
