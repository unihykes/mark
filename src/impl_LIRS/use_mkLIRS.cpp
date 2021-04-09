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
#include <initializer_list>
#include <gtest/gtest.h>
#include "mkLIRSCache.h"


class mkLIRSCacheOption : public mkIOption
{
public:
    mkLIRSCacheOption()
        //: mkIOption()
    {
    }
    
    virtual bool OnSetValue(const string& key, const string& value)
    {
        if("--lirlimit" == key) {
            _lirlimit = std::stoi(value);
            return true;
        }
        if("--hirlimit" == key) {
            _hirlimit = std::stoi(value);
            return true;
        }
        
        return false;
    }
    virtual void OnApply()
    {
    }
    
public:
    int     _lirlimit = 100;
    int     _hirlimit = 100;
};

class use_mkLIRSCache : public testing::Test
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
        g_moduleInstance->_switch->ClearOption<mkLIRSCacheOption>();
        g_moduleInstance->_switch->ApplyOption<mkLIRSCacheOption>();
        
        int lirlimit = g_moduleInstance->_switch->GetOption<mkLIRSCacheOption>()->_lirlimit;
        int hirlimit = g_moduleInstance->_switch->GetOption<mkLIRSCacheOption>()->_hirlimit;
        _pMarket = std::make_shared<mkLIRSCache>(lirlimit, hirlimit);
    }
    
    virtual void TearDown()
    {
    }
    
    void Print(const int& key, std::shared_ptr<mkBlock> block)
    {
        static const char* stateName[] = {"LIR", "resident HIR","non-resident HIR","Invalid"};
        
        MK_PRINT("key = %d, block = {%d, %s}", key, block ? block->_key : -1, block ? stateName[block->_state] : stateName[3]);
        
        auto vBlockS = _pMarket->ListRedQ();
        string itemS;
        for(const auto& item : vBlockS) {
            string str = mkSharedFormat{}("%d[%s], ", item->_key, stateName[item->_state]);
            itemS += str;
        }
        MK_PRINT("redQ =  %s", itemS.c_str());
        
        auto vBlockQ = _pMarket->ListBlueQ();
        string itemQ;
        for(const auto& item : vBlockQ) {
            string str = mkSharedFormat{}("%d[%s], ", item->_key, stateName[item->_state]);
            itemQ += str;
        }
        MK_PRINT("blueQ =  %s\n", itemQ.c_str());
    }
protected:
    std::shared_ptr<mkLIRSCache> _pMarket;
};

//顺序扫描
TEST_F(use_mkLIRSCache, scan)
{
    for(int cnt = 0 ; cnt !=5; ++cnt) {
        for(int i = 0; i != 100; ++i) {
            auto result = _pMarket->Get(i);
            Print(i, result);
        }
        MK_PRINT("hit = %lld", _pMarket->GetHitCounts());
        MK_PRINT("miss = %lld", _pMarket->GetMissCounts());
    }
}

