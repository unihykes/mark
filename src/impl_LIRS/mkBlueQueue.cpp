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

std::shared_ptr<mkBlock> 
mkBlueQueue::Front()
{
    return _vBlocks[0];
}

vector<std::shared_ptr<mkBlock>> 
mkBlueQueue::List() const
{
    return _vBlocks;
}

int64 
mkBlueQueue::Size()
{
    return _vBlocks.size();
}

void 
mkBlueQueue::Push_back(std::shared_ptr<mkBlock> item)
{
    _vBlocks.push_back(item);
}

void 
mkBlueQueue::Pop_front()
{
    _vBlocks.erase(_vBlocks.begin());
}

std::shared_ptr<mkBlock> 
mkBlueQueue::Remove(const int key)
{
    std::shared_ptr<mkBlock> result;
    
    auto iter = find_if(_vBlocks.begin(), _vBlocks.end(), 
        [&](const std::shared_ptr<mkBlock>& dest) {
            return (dest->_key == key);
        }
    );
    
    if(iter != _vBlocks.end()) {
        result = *iter;
        _vBlocks.erase(iter);
    }
    
    return result;
}

int 
mkBlueQueue::Find(int key)
{
    int location = -1;
    int step = 0;
    for(auto it : _vBlocks) {
        if(it->_key == key) {
            location = step;
            break;
        }
        else {
            ++step;
        }
    }
    return location;
}

void mkBlueQueue::eraseByBlockId(int key)
{
    int location = Find(key);
    if(location != -1) {
        _vBlocks.erase(_vBlocks.begin() + location);
    }
}

