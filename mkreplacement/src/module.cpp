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

mkIReplacementBuilder::mkIReplacementBuilder()
{
}

mkIReplacementBuilder::~mkIReplacementBuilder()
{
}

void 
mkIReplacementBuilder::PushOptions(const string& key, const string& value)
{
}

std::shared_ptr<mkIReplacement> 
mkIReplacementBuilder::LIRS()
{
    //todo
    return make_shared<mkLIRSReplacement>(100,100);
}
