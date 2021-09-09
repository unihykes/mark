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
#include "mkLIRSReplacement.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

mkLIRSReplacement::mkLIRSReplacement(int LIRSize , int HIRSize, std::shared_ptr<mkIReplaceValueBuilder> pValueBuilder)
    :_hitCounts(0)
    ,_missCounts(0)
    ,_limitLIR(LIRSize)
    ,_limitHIR(HIRSize)
    ,_pValueBuilder(pValueBuilder)
{
    if(_limitLIR <=1) {
        MK_THROW(1024, "error, _limitLIR = %d", _limitLIR);
    }
    
    if(_limitHIR <=1) {
        MK_THROW(1024, "error, _limitHIR = %d", _limitHIR);
    }
    
    _pState = std::make_shared<mkLIRSReplacementState>(this);
    mkIOpsRegister::Register(_pState);
}

mkLIRSReplacement::~mkLIRSReplacement()
{
    mkIOpsRegister::UnRegister(_pState);
    _pState = nullptr;
}

std::shared_ptr<mkIReplaceValue> 
mkLIRSReplacement::Get(const int& key)
{
    auto pValue = GetValue(key);
    if(pValue->_value) {
        pValue->_value->Hit();
        return pValue->_value;
    }
    else {
        return nullptr;
    }
}

std::shared_ptr<mkLIRSValue> 
mkLIRSReplacement::GetValue(const int& key)
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
        const mkLIRSState& state = iter->second->_state;
        
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
mkLIRSReplacement::GetHitCounts() const
{
    return _hitCounts;
}

int64 
mkLIRSReplacement::GetMissCounts() const
{
    return _missCounts;
}

vector<std::shared_ptr<mkLIRSValue>> 
mkLIRSReplacement::ListRedQ() const
{
    return _redQ.List();
}

vector<std::shared_ptr<mkLIRSValue>> 
mkLIRSReplacement::ListBlueQ() const
{
    return _blueQ.List();
}

//private
std::shared_ptr<mkLIRSValue> 
mkLIRSReplacement::InitLIR(const int& key)
{
    std::shared_ptr<mkLIRSValue> newItem(new mkLIRSValue(key , STATE_LIR));
    Build(newItem);
    _cacheMap.insert({key, newItem});
    _redQ.Push_back(newItem);
    --_limitLIR;
    ++_missCounts;
    return newItem;
}

std::shared_ptr<mkLIRSValue> 
mkLIRSReplacement::InitResidentHIR(const int& key)
{
    std::shared_ptr<mkLIRSValue> newItem(new mkLIRSValue(key , STATE_HIR_resident));
    Build(newItem);
    _cacheMap.insert({key, newItem});
    _redQ.Push_back(newItem);
    _blueQ.Push_back(newItem);
    --_limitHIR;
    ++_missCounts;
    return newItem;
}

std::shared_ptr<mkLIRSValue> 
mkLIRSReplacement::HitNonResidentHIR(std::shared_ptr<mkLIRSValue> itemRed)
{
    const mkLIRSState& state = itemRed->_state;
    if(state != STATE_HIR_nonResident) {
        MK_THROW(1024, "error, something is wrong!");
    }

    //移除blueQ头端的residentHIR,
    std::shared_ptr<mkLIRSValue> discard = _blueQ.Front();
    _blueQ.Pop_front();
    
    //在redQ中将这个被移除的对象修改为non-resident(如果存在的话)
    auto discardRed = _redQ.Find(discard->_key);
    if(discardRed) {
        discardRed->_state = STATE_HIR_nonResident;
        Clear(discardRed);//释放资源
    }
    
    //将这个被移除的HIR从缓存中删除(注意:在缓存中被删除的对象,在redQ中可能仍然以non-resident状态保留)
    auto eraseCount = _cacheMap.erase(discard->_key);
    if(0 == eraseCount) {
        //发生错误:数据丢失
        MK_THROW(1024, "error, data loss!");
    }
    
    //将新key添加进缓存
    std::shared_ptr<mkLIRSValue> newItem(new mkLIRSValue(itemRed->_key, STATE_LIR));
    Build(newItem);
    
    _cacheMap.insert({newItem->_key, newItem});
    
    //将该对象移动到redQ尾端,并设置为LIR
    _redQ.Push_back(newItem);
    
    //将redQ头端的LIR对象转变为resident-HIR并移动到blueQ尾部
    auto discardItem = _redQ.Front();
    _redQ.Pop_front();
    _redQ.Pruning();//对redQ进行剪枝,保证头端一定为LIR
    
    discardItem->_state = STATE_HIR_resident;
    _blueQ.Push_back(discardItem);
    
    ++_missCounts;
    return newItem;
}

std::shared_ptr<mkLIRSValue> 
mkLIRSReplacement::HitNothing(const int& key)
{
    //移除blueQ头端的residentHIR,同时在S中将这个HIR修改为non-resident(如果存在的话)
    std::shared_ptr<mkLIRSValue> discard = _blueQ.Front();
    _blueQ.Pop_front();
    
    //在redQ中将这个被移除的对象修改为non-resident(如果存在的话)
    auto discardRed = _redQ.Find(discard->_key);
    if(discardRed) {
        discardRed->_state = STATE_HIR_nonResident;
        Clear(discardRed);//释放资源
    }
    
    //将这个被移除的HIR从缓存中删除(注意:在缓存中被删除的对象,在redQ中可能仍然以non-resident状态保留)
    auto eraseCount = _cacheMap.erase(discard->_key);
    if(0 == eraseCount) {
        //发生错误:数据丢失
        MK_THROW(1024, "error, data loss!");
    }
    
    //将新key添加进缓存
    std::shared_ptr<mkLIRSValue> newItem(new mkLIRSValue(key , STATE_HIR_resident));
    Build(newItem);
    _cacheMap.insert({key, newItem});
    
    //添加新添加的对象的索引
    _redQ.Push_back(newItem);
    _blueQ.Push_back(newItem);
    
    ++_missCounts;
    return newItem;
}

void
mkLIRSReplacement::HitLIR(const int& key)
{
    //访问redQ中的LIR,将其移动到尾部(更新R)
    std::shared_ptr<mkLIRSValue> item = _redQ.Remove(key);
    if(item) {
        _redQ.Pruning();//如果命中的对象之前在队列头端,需要进行剪枝操作
        _redQ.Push_back(item);
        _hitCounts++;
    }
    else {
        MK_THROW(1024, "error, something is wrong!");
    }
}

void 
mkLIRSReplacement::HitResidentHIR(const int& key)
{
    std::shared_ptr<mkLIRSValue> itemRed = _redQ.Remove(key);
    
     // residentHIR 在redQ中
    if(itemRed) {
        //将该HIR对象移动到尾端,并修改为LIR
        itemRed->_state = STATE_LIR;
        _redQ.Push_back(itemRed);
        //blueQ中如果也存在这个对象,则淘汰之(因为此时对象已经变成了LIR,而blueQ中仅保留HIR)
        _blueQ.Remove(key);
        
        //将redQ头端的LIR对象淘汰(转变为resident-HIR并移动到blueQ尾部)
        auto discardItem = _redQ.Front();
        _redQ.Pop_front();
        _redQ.Pruning();//对redQ进行剪枝,保证头端一定为LIR
        discardItem->_state = STATE_HIR_resident;
        _blueQ.Push_back(discardItem);
    }
    
     // residentHIR 不在redQ中
    else {
        std::shared_ptr<mkLIRSValue> itemBlue = _blueQ.Remove(key);
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
mkLIRSReplacement::Build(std::shared_ptr<mkLIRSValue> newItem)
{
    newItem->_value = _pValueBuilder->Create(newItem->_key);
    //todo
}

void 
mkLIRSReplacement::Clear(std::shared_ptr<mkLIRSValue> newItem)
{
    newItem->_value = nullptr;
    //todo
}

////////////////////////////////////////////////////////////////////////////////////////////////////

mkLIRSReplacementState::mkLIRSReplacementState(mkLIRSReplacement* pTarget)
    : _pTarget(pTarget)
{
    _guid = mkGuid::Generate();
    MK_PRINT("");
}

mkLIRSReplacementState::~mkLIRSReplacementState()
{
    MK_PRINT("");
    _pTarget = nullptr;
}

mkIOpsState::Config 
mkLIRSReplacementState::GetConfig() const 
{
    return {_guid, "mkLIRSReplacementState"};
}

void 
mkLIRSReplacementState::Put(const std::string& key, const std::string& value)
{
    MK_PRINT("");
}

bool 
mkLIRSReplacementState::Get(const std::string& key, std::string& value)
{
    MK_PRINT("");
    
    if(_pTarget) {
        MK_PRINT("_hitCounts = %lld", _pTarget->_hitCounts);
        MK_PRINT("_missCounts = %lld", _pTarget->_missCounts);
        MK_PRINT("_limitLIR = %lld", _pTarget->_limitLIR);
        MK_PRINT("_limitHIR = %lld", _pTarget->_limitHIR);
        MK_PRINT("_cacheMap.size = %lld", _pTarget->_cacheMap.size());
    }
    
    value = "todo";
}

void 
mkLIRSReplacementState::Delete(const std::string& key)
{
    MK_PRINT("");
}

void 
mkLIRSReplacementState::List(const std::string& key, vector<std::string>& values)
{
    MK_PRINT("");
}