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

Time:2021-3

info:

***************************************************************************************************/
#include <markcore.h>
#include "mkBlueQueue.h"

std::shared_ptr<mkLIRSValue> 
mkBlueQueue::Front()
{
    return _values[0];
}

std::shared_ptr<mkLIRSValue> 
mkBlueQueue::Remove(const int key)
{
    std::shared_ptr<mkLIRSValue> result;
    
    auto iter = find_if(_values.begin(), _values.end(), 
        [&](const std::shared_ptr<mkLIRSValue>& dest) {
            return (dest->_key == key);
        }
    );
    
    if(iter != _values.end()) {
        result = *iter;
        _values.erase(iter);
    }
    
    return result;
}

int64 
mkBlueQueue::Size() const
{
    return _values.size();
}

vector<std::shared_ptr<mkLIRSValue>> 
mkBlueQueue::List() const
{
    return _values;
}

void 
mkBlueQueue::Push_back(std::shared_ptr<mkLIRSValue> item)
{
    _values.push_back(item);
}

void 
mkBlueQueue::Pop_front()
{
    _values.erase(_values.begin());
}


