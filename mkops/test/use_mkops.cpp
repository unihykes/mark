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
#include "mkIOpsClient.h"
#include "mkIOpsRegister.h"

class use_mkops : public testing::Test
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
        _builder = std::make_shared<mkIOpsClientBuilder>();
        _builder->PushOptions("--timeout_ms", "2000");
        _builder->PushOptions("--load_balancer", "");
        _builder->PushOptions("--protocol", "baidu_std");
        _builder->PushOptions("--connection_type", "");
        _builder->PushOptions("--max_retry", "3");
        _builder->PushOptions("--ip_port", "192.168.88.128:9999");
        _builder->PushOptions("--dummy_port", "-1");
    }
    
    virtual void TearDown()
    {
        _builder = nullptr;
    }
    
protected:
    std::shared_ptr<mkIOpsClientBuilder> _builder;
};


TEST_F(use_mkops, service)
{
    class mkOpsState : public mkIOpsState
    {
    public:
        mkOpsState()
        {
            MK_PRINT("");
        }
        
        virtual ~mkOpsState()
        {
            MK_PRINT("");
        }
        
        virtual mkIOpsState::Config GetConfig() const 
        {
            return {"1234", "mkOpsState"};
        }
        
        virtual void Put(const std::string& key, const std::string& value)
        {
            MK_PRINT("");
        }
        
        virtual bool Get(const std::string& key, std::string& value)
        {
            MK_PRINT("");
        }
        
        virtual void Delete(const std::string& key)
        {
            MK_PRINT("");
        }
        
        virtual void List(const std::string& key, vector<std::string>& values)
        {
            MK_PRINT("");
        }
    };
    auto state = std::make_shared<mkOpsState>();
    mkIOpsRegister::Register(state);
    
    while(true) {
        sleep(1);
    }
}

TEST_F(use_mkops, ListState)
{
    auto client = _builder->Build();
    
    vector<mkIOpsStateClient::Config> vStates;
    client->ListState(vStates);
    
    for(const auto& elem : vStates) {
        MK_PRINT("guid = %s, name = %s", elem.guid.c_str(), elem.name.c_str());
    }
}

TEST_F(use_mkops, Put)
{
    auto client = _builder->Build();
    
    vector<mkIOpsStateClient::Config> vStates;
    client->ListState(vStates);
    
    for(const auto& elem : vStates) {
        auto stateClient = client->State(elem.guid);
        
        string key;//todo
        string value;//todo
        stateClient->Put(key,value);
        MK_PRINT("guid = %s, name = %s", elem.guid.c_str(), elem.name.c_str());
    }
}

TEST_F(use_mkops, Get)
{
    auto client = _builder->Build();
    
    vector<mkIOpsStateClient::Config> vStates;
    client->ListState(vStates);
    
    for(const auto& elem : vStates) {
        auto stateClient = client->State(elem.guid);
        string key;//todo
        string value;
        stateClient->Get(key,value);
        MK_PRINT("guid = %s, name = %s", elem.guid.c_str(), elem.name.c_str());
    }
}

TEST_F(use_mkops, Delete)
{
    auto client = _builder->Build();
    
    vector<mkIOpsStateClient::Config> vStates;
    client->ListState(vStates);
    
    for(const auto& elem : vStates) {
        auto stateClient = client->State(elem.guid);
        
        string key;//todo
        stateClient->Delete(key);
        MK_PRINT("guid = %s, name = %s", elem.guid.c_str(), elem.name.c_str());
    }
}

TEST_F(use_mkops, List)
{
    auto client = _builder->Build();
    
    vector<mkIOpsStateClient::Config> vStates;
    client->ListState(vStates);
    
    for(const auto& elem : vStates) {
        auto stateClient = client->State(elem.guid);
        string key;//todo
        vector<std::string> values;
        stateClient->List(key,values);
    }
}