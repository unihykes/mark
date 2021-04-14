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

#ifndef __mkOpsStateFactory
#define __mkOpsStateFactory

#include "mkIOpsService.h"

class mkOpsStateFactory
{
public:
    mkOpsStateFactory();
    ~mkOpsStateFactory();
    
    void Insert(std::shared_ptr<mkIOpsState> pState);
    void Remove(std::shared_ptr<mkIOpsState> pState);
    
    void List(vector<std::shared_ptr<mkIOpsState>>& states);
    std::shared_ptr<mkIOpsState> Find(const string& guid);
    
    
private:
    std::map<std::string, std::shared_ptr<mkIOpsState>> _allStates;
    std::mutex _allStatesMutex;
};



#endif