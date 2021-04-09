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

#ifndef __mkBlueQueue
#define __mkBlueQueue

#include "mkBlock.h"

//FIFO队列,从尾端插入,头端删除, 头端编号为0,
//队列Q存储所有冷数据:resident-HIR
class mkBlueQueue
{
public:
    //获取头部数据详情
    std::shared_ptr<mkBlock> Front();
    
    //枚举对象
    vector<std::shared_ptr<mkBlock>> List() const;
    
    //获取队列size
    int64 Size();
    
    //从尾端插入一个元素
    void Push_back(std::shared_ptr<mkBlock> item);
    
    //删除头端元素
    void Pop_front();

    //删除并返回删除的对象
    std::shared_ptr<mkBlock> Remove(const int key);
    
    //查找指定元素的在队列中的位置
    int Find(int key);
    
    ////删除指定元素
    void eraseByBlockId(int key);
private:
    std::vector<std::shared_ptr<mkBlock>> _vBlocks;
};

#endif