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
#include "mkLIRSCache.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

mkLIRSCache::mkLIRSCache(int LIRSize , int HIRSize)
    :_hitCounts(0)
    ,_mishitCounts(0)
    ,_limitLIR(LIRSize)
    ,_limitHIR(HIRSize)
{
}

std::shared_ptr<mkBlock> 
mkLIRSCache::Get(const int& key)
{
    auto iter = _cacheMap.find(key);
    
    //未命中(key不在缓存中)
    if( iter == _cacheMap.end()) {
        //redQ未满,则将该新key当作LIR块,插入到redQ的尾端
        if(_limitLIR > 0){
            return InitLIR(key);
        }
        
        //redQ已满,而blueQ未满,则将该新key当作resident-HIR块,插入到redQ尾端,同时插入blueQ的尾端
        if(_limitHIR > 0) {
            return InitResidentHIR(key);
        }
        
        //都满了,判断是否命中了redQ中的non-residentHIR
        auto itemRed = _redQ.Remove(key);
        if(itemRed) {
            return HitNonResidentHIR(itemRed);
        }
        
        //未命中(一个纯粹的新key)
        return HitNothing(key);
    }
    //命中(key在缓存中)
    else {
        const mkBlockState& state = iter->second->_state;
        
        //命中LIR
        if(state == STATE_LIR) {
            HitLIR(key);
            return iter->second;;
        }
        
        //命中 residentHIR
        if(state == STATE_HIR_resident) {
            HitResidentHIR(key);
            return iter->second;;
        }
        
        MK_THROW(1024, "error, something is wrong, state = %d", int(state));
    }
    return nullptr;
}

int64 
mkLIRSCache::GetHitCounts()
{
    return _hitCounts;
}
vector<std::shared_ptr<mkBlock>> 
mkLIRSCache::ListRedQ() const
{
    return _redQ.List();
}

vector<std::shared_ptr<mkBlock>> 
mkLIRSCache::ListBlueQ() const
{
    return _blueQ.List();
}

//private
std::shared_ptr<mkBlock> 
mkLIRSCache::InitLIR(const int& key)
{
    std::shared_ptr<mkBlock> newBlock(new mkBlock(key , STATE_LIR));
    _cacheMap.insert({key, newBlock});
    _redQ.Push_back(newBlock);
    --_limitLIR;
    ++_mishitCounts;
    return newBlock;
}

std::shared_ptr<mkBlock> 
mkLIRSCache::InitResidentHIR(const int& key)
{
    std::shared_ptr<mkBlock> newBlock(new mkBlock(key , STATE_HIR_resident));
    _cacheMap.insert({key, newBlock});
    _redQ.Push_back(newBlock);
    _blueQ.Push_back(newBlock);
    --_limitHIR;
    ++_mishitCounts;
    return newBlock;
}

std::shared_ptr<mkBlock> 
mkLIRSCache::HitNonResidentHIR(std::shared_ptr<mkBlock> itemRed)
{
    const mkBlockState& state = itemRed->_state;
    if(state != STATE_HIR_nonResident) {
        MK_THROW(1024, "error, something is wrong!");
    }

    //移除blueQ头端的residentHIR,
    std::shared_ptr<mkBlock> discard = _blueQ.Front();
    _blueQ.Pop_front();
    
    //在redQ中将这个被移除的数据块修改为non-resident(如果存在的话)
    auto discardRed = _redQ.Find(discard->_key);
    if(discardRed) {
        discardRed->_state = STATE_HIR_nonResident;
        ClearBlock(discardRed);//释放资源
    }
    
    //将这个被移除的HIR从缓存中删除(注意:在缓存中被删除的数据块,在redQ中可能仍然以non-resident状态保留)
    auto eraseCount = _cacheMap.erase(discard->_key);
    if(0 == eraseCount) {
        //发生错误:数据丢失
        MK_THROW(1024, "error, data loss!");
    }
    
    //将新key添加进缓存
    std::shared_ptr<mkBlock> newBlock(new mkBlock(itemRed->_key, STATE_LIR));
    BuildBlock(newBlock);
    
    _cacheMap.insert({newBlock->_key, newBlock});
    
    //将该数据块移动到redQ尾端,并设置为LIR
    _redQ.Push_back(newBlock);
    
    //将redQ头端的LIR数据块转变为resident-HIR并移动到blueQ尾部
    auto discardBlock = _redQ.Front();
    _redQ.Pop_front();
    _redQ.Pruning();//对redQ进行剪枝,保证头端一定为LIR
    
    discardBlock->_state = STATE_HIR_resident;
    _blueQ.Push_back(discardBlock);
    
    ++_mishitCounts;
    return newBlock;
}

std::shared_ptr<mkBlock> 
mkLIRSCache::HitNothing(const int& key)
{
    //移除blueQ头端的residentHIR,同时在S中将这个HIR修改为non-resident(如果存在的话)
    std::shared_ptr<mkBlock> discard = _blueQ.Front();
    _blueQ.Pop_front();
    
    //在redQ中将这个被移除的数据块修改为non-resident(如果存在的话)
    auto discardRed = _redQ.Find(discard->_key);
    if(discardRed) {
        discardRed->_state = STATE_HIR_nonResident;
        ClearBlock(discardRed);//释放资源
    }
    
    //将这个被移除的HIR从缓存中删除(注意:在缓存中被删除的数据块,在redQ中可能仍然以non-resident状态保留)
    auto eraseCount = _cacheMap.erase(discard->_key);
    if(0 == eraseCount) {
        //发生错误:数据丢失
        MK_THROW(1024, "error, data loss!");
    }
    
    //将新key添加进缓存
    std::shared_ptr<mkBlock> newBlock(new mkBlock(key , STATE_HIR_resident));
    _cacheMap.insert({key, newBlock});
    
    //添加新添加的数据块的索引
    _redQ.Push_back(newBlock);
    _blueQ.Push_back(newBlock);
    
    return newBlock;
}

void
mkLIRSCache::HitLIR(const int& key)
{
    //访问redQ中的LIR,将其移动到尾部(更新R)
    std::shared_ptr<mkBlock> item = _redQ.Remove(key);
    if(item) {
        _redQ.Pruning();//如果命中的数据块之前在队列头端,需要进行剪枝操作
        _redQ.Push_back(item);
        _hitCounts++;
    }
    else {
        MK_THROW(1024, "error, something is wrong!");
    }
}

void 
mkLIRSCache::HitResidentHIR(const int& key)
{
    std::shared_ptr<mkBlock> itemRed = _redQ.Remove(key);
    
     // residentHIR 在redQ中
    if(itemRed) {
        //将该HIR数据块移动到尾端,并修改为LIR
        itemRed->_state = STATE_LIR;
        _redQ.Push_back(itemRed);
        //blueQ中如果也存在这个数据块,则淘汰之(因为此时数据块已经变成了LIR,而blueQ中仅保留HIR)
        _blueQ.Remove(key);
        
        //将redQ头端的LIR数据块淘汰(转变为resident-HIR并移动到blueQ尾部)
        auto discardBlock = _redQ.Front();
        _redQ.Pop_front();
        _redQ.Pruning();//对redQ进行剪枝,保证头端一定为LIR
        discardBlock->_state = STATE_HIR_resident;
        _blueQ.Push_back(discardBlock);
    }
    
     // residentHIR 不在redQ中
    else {
        std::shared_ptr<mkBlock> itemBlue = _blueQ.Remove(key);
        if(!itemBlue) {
            MK_THROW(1024, "error, data loss!");//索引与数据不一致
        }
        
        //访问blueQ中的resident-HIR (blueQ中的一定是 resident-HIR)
        //将该HIR复制到redQ的尾端(状态仍保持为resident-HIR)
        _redQ.Push_back(itemBlue);
        
        //将该HIR在blueQ队列中移动到尾端
        _blueQ.Push_back(itemBlue);
    }
    _hitCounts++;
}

void 
mkLIRSCache::BuildBlock(std::shared_ptr<mkBlock> newBlock)
{
    newBlock->_pBuf = std::make_shared<mkBlockBuffer>();
    //todo
}

void 
mkLIRSCache::ClearBlock(std::shared_ptr<mkBlock> newBlock)
{
    newBlock->_pBuf = nullptr;
    //todo
}