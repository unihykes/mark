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
    mkBlueQueue 
    负责冷数据(HIR)汰换
    FIFO队列,尾端插入,头端删除
    存储resident-HIR
***************************************************************************************************/

#ifndef __mkBlueQueue
#define __mkBlueQueue

#include "mkILIRSReplacement.h"

class mkBlueQueue
{
public:
    std::shared_ptr<mkLIRSValue> Front();//获取头部数据详情
    std::shared_ptr<mkLIRSValue> Remove(const int key);//删除并返回删除的对象
    
    int64 Size() const;//获取队列size
    vector<std::shared_ptr<mkLIRSValue>> List() const;//枚举对象
    
    void Push_back(std::shared_ptr<mkLIRSValue> item);//从尾端插入一个元素
    void Pop_front();//删除头端元素
    
private:
    std::vector<std::shared_ptr<mkLIRSValue>> _values;
};

#endif