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
#include "mkOpsStateFactory.h"

mkOpsStateFactory::mkOpsStateFactory()
{
}

mkOpsStateFactory::~mkOpsStateFactory()
{
}

void 
mkOpsStateFactory::Insert(std::shared_ptr<mkIOpsState> pState)
{
    if(pState) {
        std::lock_guard<std::mutex> lock(_allStatesMutex);
        MK_PRINT("guid = %s", pState->GetConfig()._guid.c_str());
        _allStates.insert(std::make_pair(pState->GetConfig()._guid, pState));
    }
}

void 
mkOpsStateFactory::Remove(std::shared_ptr<mkIOpsState> pState)
{
    if(pState) {
        std::lock_guard<std::mutex> lock(_allStatesMutex);
        _allStates.erase(pState->GetConfig()._guid);
    }
}

std::shared_ptr<mkIOpsState> 
mkOpsStateFactory::Find(const string& guid)
{
    std::lock_guard<std::mutex> lock(_allStatesMutex);
    auto iter = _allStates.find(guid);
    if(iter == _allStates.end()) {
        return nullptr;
    }
    else {
        return iter->second;
    }
}

void 
mkOpsStateFactory::List(vector<std::shared_ptr<mkIOpsState>>& states)
{
    std::lock_guard<std::mutex> lock(_allStatesMutex);
    for(auto& elem : _allStates) {
        states.push_back(elem.second);
    }
}