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

Time:2021-4

info:

***************************************************************************************************/

#ifndef __mkILIRSReplacement
#define __mkILIRSReplacement

#include "mkIReplacement.h"


//对象状态
enum mkLIRSState
{
    STATE_LIR               = 0,//热对象，已经被访问两次的对象
    STATE_HIR_resident      = 1,//冷对象，还仅仅只被访问一次的对象,有缓存 
    STATE_HIR_nonResident   = 2,//冷对象，还仅仅只被访问一次的对象,无缓存
    STATE_Invalid           = 3 //无效对象
};

//对象
struct mkLIRSValue
{
    mkLIRSValue(const int& key, const mkLIRSState& state)
        :_key(key) 
        ,_state(state)
    {
    }
    
    int             _key;
    mkLIRSState    _state;
    std::shared_ptr<mkIReplaceValue>  _value;
};

//基于LIRS算法的缓存器
class MK_DLL_EXPORT mkILIRSReplacement : public mkIReplacement
{
public:
    virtual ~mkILIRSReplacement(){}
    
    virtual std::shared_ptr<mkLIRSValue> GetValue(const int& key) = 0;
    virtual int64 GetHitCounts() const = 0;
    virtual int64 GetMissCounts() const = 0;
    virtual vector<std::shared_ptr<mkLIRSValue>> ListRedQ() const = 0;
    virtual vector<std::shared_ptr<mkLIRSValue>> ListBlueQ() const = 0;
};




#endif