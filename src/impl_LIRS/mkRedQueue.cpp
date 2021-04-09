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
#include "mkRedQueue.h"

std::shared_ptr<mkBlock> 
mkRedQueue::Front()
{
    return _vBlocks[0];
}

std::shared_ptr<mkBlock> 
mkRedQueue::Find(const int key)
{
    std::shared_ptr<mkBlock> result;
    
    //todo:可以添加一个non-residentHIR的 unorderedmap加速检索
    auto iter = find_if(_vBlocks.begin(), _vBlocks.end(), 
        [&](const std::shared_ptr<mkBlock>& dest) {
            return (dest->_key == key);
        }
    );
    
    if(iter != _vBlocks.end()) {
        result = *iter;
    }
    return result;
}

std::shared_ptr<mkBlock> 
mkRedQueue::Remove(const int key)
{
    std::shared_ptr<mkBlock> result;
    
    //todo:可以添加一个non-residentHIR的 unorderedmap加速检索
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

int64 
mkRedQueue::Size() const
{
    return _vBlocks.size();
}

vector<std::shared_ptr<mkBlock>> 
mkRedQueue::List() const
{
    return _vBlocks;
}

void 
mkRedQueue::Push_back(std::shared_ptr<mkBlock> item)
{
    _vBlocks.push_back(item);
}

void 
mkRedQueue::Pop_front()
{
    _vBlocks.erase(_vBlocks.begin());
}

void 
mkRedQueue::Pruning()
{
    while (true) {
        mkBlockState state = Front()->_state;
        //如果当前头部元素是HIR, 则丢弃之
        if(state == STATE_HIR_resident || state == STATE_HIR_nonResident) {
            Pop_front();
        }
        //如果当前头部元素是LIR,则结束
        else {
            break;
        }
    }
}