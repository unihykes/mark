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
最近连续访问同一个对象之间访问其他不同对象非重复个数称为这个对象的 IRR
当第一次被访问时IRR的值为无穷大

R(Recency):
一个对象从上一次访问到当前时间访问其他不同对象非重复个数称为这个对象的 recency
这个与LRU算法中的R含义相同

LIR（low IRR set）
具有较小 IRR 的对象集合，可以将这部分对象理解为热数据，
因为 IRR 低说明访问的频次高

HIR（high IRR set）
具有较高 IRR 的对象集合，可以将这部分对象理解为冷数据。
在 HIR 集合中有部分对象不在缓存中，但我们记录了它们的历史信息并标记为未驻留在缓存中，
我们称这部分对象为 nonresident-HIR，
另外一部分驻留在缓存中的对象称为 resident-HIR。

原则:
1.当发生缓存未命中需要置换缓存块时候，会选择优先淘汰置换 resident-HIR。
2.如果 HIR 集合的对象 IRR 经过更新比 LIR 集合中的小，那么 LIR 集合的一个对象就会被 HIR 集合中 IRR 小的对象挤出并转换为 HIR。

参考资料:
http://web.cse.ohio-state.edu/hpcs/WWW/HTML/publications/papers/TR-02-6.pdf
https://cloud.tencent.com/developer/article/1464670
***************************************************************************************************/

#ifndef __mkLIRSReplacement
#define __mkLIRSReplacement

#include "mkILIRSReplacement.h"
#include "mkRedQueue.h"
#include "mkBlueQueue.h"

//基于LIRS算法的缓存器
class mkLIRSReplacement : public mkILIRSReplacement
{
public:
    mkLIRSReplacement(int LIRSize, int HIRSize, std::shared_ptr<mkIReplaceValueBuilder> pValueBuilder);
    virtual std::shared_ptr<mkIReplaceValue> Get(const int& key);
    
    virtual std::shared_ptr<mkLIRSValue> GetValue(const int& key);
    virtual int64 GetHitCounts() const;
    virtual int64 GetMissCounts() const;
    virtual vector<std::shared_ptr<mkLIRSValue>> ListRedQ() const;
    virtual vector<std::shared_ptr<mkLIRSValue>> ListBlueQ() const;
    
private:
    //未命中
    std::shared_ptr<mkLIRSValue> InitLIR(const int& key);//初始化LIR
    std::shared_ptr<mkLIRSValue> InitResidentHIR(const int& key);//初始化residentHIR
    std::shared_ptr<mkLIRSValue> HitNonResidentHIR(std::shared_ptr<mkLIRSValue> itemRed);//命中non-residentHIR
    std::shared_ptr<mkLIRSValue> HitNothing(const int& key);//发生汰换
    
    //命中
    void HitLIR(const int& key);
    void HitResidentHIR(const int& key);
    
    void Build(std::shared_ptr<mkLIRSValue> newItem);//从底层服务获取到指定对象的具体信息
    void Clear(std::shared_ptr<mkLIRSValue> newItem);//释放对象的内存,仅保留索引
    
private:
    int64 _hitCounts; //命中次数
    int64 _missCounts;//未命中次数
    int _limitLIR;  //low IRR set:热数据
    int _limitHIR;  //high IRR set:冷数据
    
    std::unordered_map<int, std::shared_ptr<mkLIRSValue>> _cacheMap;//所有缓存对象的key集合,只保留LIR和resident-HIR, non-residentHIR不在缓存中
    mkRedQueue _redQ;//热数据(LIR)汰换
    mkBlueQueue _blueQ; //冷数据（HIR块）淘汰
    
    std::shared_ptr<mkIReplaceValueBuilder> _pValueBuilder;
};


#endif