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
#include <gtest/gtest.h>
#include "mkILIRSReplacement.h"


class mkLIRSReplacementOption : public mkIOption
{
public:
    virtual bool OnSetValue(const string& key, const string& value)
    {
        if("--lir_size" == key) {
            lir_size = std::stoi(value);
            return true;
        }
        if("--hir_Size" == key) {
            hir_Size = std::stoi(value);
            return true;
        }
        
        return false;
    }
    virtual void OnApply()
    {
    }
    
public:
    int     lir_size = 100;
    int     hir_Size = 100;
};

class mkReplaceValue : public mkIReplaceValue
{
public:
    mkReplaceValue(const int& key)
        : _key(key)
    {
    }
    
    virtual void Hit()
    {
        ++_hit;
    }
    
    virtual int64 GetHitCount() const
    {
        return _hit;
    }
    
    virtual void write(const string& in)
    {
        _buf = in;
    }
    
    virtual void read(string& out)
    {
        out.append(std::to_string(_key));
        out.append(_buf);
    }
    
private:
    int _key;
    string _buf;
    int64 _hit = -1;
};

class mkReplaceValueBuilder : public mkIReplaceValueBuilder
{
public:
    virtual std::shared_ptr<mkIReplaceValue> Create(const int& key)
    {
        std::shared_ptr<mkIReplaceValue> result = std::make_shared<mkReplaceValue>(key);
        return result;
    }
};

class use_mkILIRSReplacement : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
    }
    
    static void TearDownTestCase()
    {
    }
    
    virtual void SetUp()
    {
        //重置参数
        g_switch->ClearOption<mkLIRSReplacementOption>();
        g_switch->ApplyOption<mkLIRSReplacementOption>();
        
        std::shared_ptr<mkIReplaceValueBuilder> valueBuilder = std::make_shared<mkReplaceValueBuilder>();
        mkIReplacementBuilder builder;
        builder.PushOptions("--lir_size", std::to_string(g_switch->GetOption<mkLIRSReplacementOption>()->lir_size));
        builder.PushOptions("--hir_Size", std::to_string(g_switch->GetOption<mkLIRSReplacementOption>()->hir_Size));
        auto pPlacement = builder.LIRS(valueBuilder);
        _pPlacement = std::dynamic_pointer_cast<mkILIRSReplacement>(pPlacement);
        
    }
    
    virtual void TearDown()
    {
    }
    
    void Print(const int& key, std::shared_ptr<mkLIRSValue> item) 
    {
        static const char* stateName[] = {"LIR", "resident HIR","non-resident HIR","Invalid"};
        
        if(!item) {
            MK_THROW(1024, "key = %d, item = {%d, %s}", key, -1, stateName[3]);
        }
        
        MK_PRINT("key = %d, item = {%d, %s}", key, item->_key, stateName[item->_state]);
        if(item->_value) {
            string out;
            item->_value->read(out);
            MK_PRINT("value = %s", out.c_str());
        }
        
        auto vRedQ = _pPlacement->ListRedQ();
        string itemS;
        for(const auto& elem : vRedQ) {
            string str = mkSharedFormat{}("%d[%s], ", elem->_key, stateName[elem->_state]);
            itemS += str;
        }
        MK_PRINT("redQ =  %s", itemS.c_str());
        
        auto vBlueQ = _pPlacement->ListBlueQ();
        string itemQ;
        for(const auto& elem : vBlueQ) {
            string str = mkSharedFormat{}("%d[%s], ", elem->_key, stateName[elem->_state]);
            itemQ += str;
        }
        MK_PRINT("blueQ =  %s\n", itemQ.c_str());
    };
protected:
    std::shared_ptr<mkILIRSReplacement> _pPlacement;
};

//顺序扫描
TEST_F(use_mkILIRSReplacement, LIRS_scan)
{
    for(int cnt = 0 ; cnt !=5; ++cnt) {
        for(int i = 0; i != 100; ++i) {
            auto result = _pPlacement->GetValue(i);
            Print(i, result);
        }
        MK_PRINT("hit = %lld", _pPlacement->GetHitCounts());
        MK_PRINT("miss = %lld", _pPlacement->GetMissCounts());
    }
}

