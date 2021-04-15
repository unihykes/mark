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

Time:2021-4

info:

***************************************************************************************************/

#include <markcore.h>
#include "mkLIRSReplacement.h"

MK_DEFINE_MODULE_INSTANCE_VERSION(1, 0, 0);


class mkLIRSReplacementOption : public mkIOption
{
public:
    virtual bool OnSetValue(const string& key, const string& value)
    {
        if("--lir_size" == key) {
            lir_size = std::stoi(value);
            return true;
        }
        if("--hir_Size" == key) {
            hir_Size = std::stoi(value);
            return true;
        }
        return false;
    }
    virtual void OnApply()
    {
    }
    
public:
    int lir_size = 100;
    int hir_Size = 100;
};



void 
mkIReplacementBuilder::PushOptions(const string& key, const string& value)
{
    MK_CALL_ONCE_BEGIN
        g_moduleInstance->_switch->ClearOption<mkLIRSReplacementOption>();
    MK_CALL_ONCE_END
    
    g_moduleInstance->_switch->SetOptions(key, value, false);
}

std::shared_ptr<mkIReplacement> 
mkIReplacementBuilder::LIRS(shared_ptr<mkIReplaceValueBuilder> pBuilder)
{
    const auto& lir_size = g_moduleInstance->_switch->GetOption<mkLIRSReplacementOption>()->lir_size;
    const auto& hir_Size = g_moduleInstance->_switch->GetOption<mkLIRSReplacementOption>()->hir_Size;
    
    return make_shared<mkLIRSReplacement>(lir_size, hir_Size, pBuilder);
}
