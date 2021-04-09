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

#ifndef __mkRedQueue
#define __mkRedQueue

#include "mkBlock.h"

//FIFO队列,从尾端插入,头端删除,头端编号为0,
//负责热数据(LIR)汰换, 
//存储 LIR 和 resident-HIR 以及 nonresident-HIR
//越靠近尾端,R越小
class mkRedQueue
{
public:
    //获取头部数据详情
    std::shared_ptr<mkBlock> Front();
    
    //获取尾部数据
    std::shared_ptr<mkBlock> Back();
    
    //获取指定位置元素的数据详情
    std::shared_ptr<mkBlock> At(int location);
    
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
    
    //剪枝, 保证头端为LIR，
    //这样访问一个resident-HIR时就知道这个resident-HIR的新IRR一定小于头端LIR的recency。
    void pruning();
    
private:
    std::vector<std::shared_ptr<mkBlock>> _vBlocks;
};

#endif