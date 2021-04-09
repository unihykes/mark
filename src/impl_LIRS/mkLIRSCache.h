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
IRR(Inter-Reference Recency): 
最近连续访问同一个数据块之间访问其他不同数据块非重复个数称为这个数据块的 IRR
当第一次被访问时IRR的值为无穷大

R(Recency):
一个数据块从上一次访问到当前时间访问其他不同数据块非重复个数称为这个数据块的 recency
这个与LRU算法中的R含义相同

LIR（low IRR block set）
具有较小 IRR 的数据块集合，可以将这部分数据块理解为热数据，
因为 IRR 低说明访问的频次高

HIR（high IRR block set）
具有较高 IRR 的数据块集合，可以将这部分数据块理解为冷数据。
在 HIR 集合中有部分数据块不在缓存中，但我们记录了它们的历史信息并标记为未驻留在缓存中，
我们称这部分数据块为 nonresident-HIR，
另外一部分驻留在缓存中的数据块称为 resident-HIR。

原则:
1.当发生缓存未命中需要置换缓存块时候，会选择优先淘汰置换 resident-HIR。
2.如果 HIR 集合的数据块 IRR 经过更新比 LIR 集合中的小，那么 LIR 集合的一个数据块就会被 HIR 集合中 IRR 小的数据块挤出并转换为 HIR。

参考资料:
http://web.cse.ohio-state.edu/hpcs/WWW/HTML/publications/papers/TR-02-6.pdf
https://cloud.tencent.com/developer/article/1464670
***************************************************************************************************/

#ifndef __mkLIRSCache
#define __mkLIRSCache

#include "mkRedQueue.h"
#include "mkBlueQueue.h"

//基于LIRS算法的缓存器
class mkLIRSCache
{
public:
    mkLIRSCache(int LIRSize, int HIRSize);
    
    std::shared_ptr<mkBlock> Get(const int& key);
    
    int64 GetHitCounts();
    vector<std::shared_ptr<mkBlock>> ListRedQ() const;
    vector<std::shared_ptr<mkBlock>> ListBlueQ() const;
    
private:
    //未命中
    std::shared_ptr<mkBlock> InitLIR(const int& key);//初始化LIR
    std::shared_ptr<mkBlock> InitResidentHIR(const int& key);//初始化residentHIR
    std::shared_ptr<mkBlock> HitNonResidentHIR(std::shared_ptr<mkBlock> itemRed);//命中non-residentHIR
    std::shared_ptr<mkBlock> HitNothing(const int& key);//发生汰换
    
    //命中
    void HitLIR(const int& key);
    void HitResidentHIR(const int& key);
    
private:
    int64 _hitCounts; //命中次数
    int64 _mishitCounts;//未命中次数
    int _limitLIR;  //low IRR block set:热数据
    int _limitHIR;  //high IRR block set:冷数据
    
    std::unordered_map<int, std::shared_ptr<mkBlock>> _cacheMap;//所有缓存数据块的key集合,只保留LIR和resident-HIR, non-residentHIR不在缓存中
    mkRedQueue _redQ;//热数据(LIR)汰换
    mkBlueQueue _blueQ; //冷数据（HIR块）淘汰
};
#endif