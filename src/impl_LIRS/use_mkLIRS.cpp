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
#include "mkLIRSCache.h"


void Print(const int& key, std::shared_ptr<mkBlock> block, const mkLIRSCache& market)
{
    static const char* stateName[] = {"LIR", "resident HIR","non-resident HIR","Invalid"};
    
    MK_PRINT("key = %d, block = {%d, %s}", key, block ? block->_key : -1, block ? stateName[block->_state] : stateName[3]);
    
    auto vBlockS = market.ListRedQ();
    string itemS;
    for(const auto& item : vBlockS) {
        string str = mkSharedFormat{}("%d[%s], ", item->_key, stateName[item->_state]);
        itemS += str;
    }
    MK_PRINT("redQ =  %s", itemS.c_str());
    
    auto vBlockQ = market.ListBlueQ();
    string itemQ;
    for(const auto& item : vBlockQ) {
        string str = mkSharedFormat{}("%d[%s], ", item->_key, stateName[item->_state]);
        itemQ += str;
    }
    MK_PRINT("blueQ =  %s\n", itemQ.c_str());
}


TEST(mkLIRSCache, run)
{
    mkLIRSCache market(3 , 2);
    int a[] = {1 , 2 , 3 , 4 , 5  , 1 , 2 , 3 , 4};
    for(int i = 0 ; i != 1 ; ++i)
    {
        for(int j = 0 ; j != sizeof(a)/sizeof(int) ; ++j)
        {
            int key = a[j];
            auto result = market.Get(key);
            Print(key, result, market);
        }
    }
    std::cout << market.GetHitCounts() << "\n";
}

