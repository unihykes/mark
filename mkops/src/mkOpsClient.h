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

#ifndef __mkOpsClient
#define __mkOpsClient

#include "mkIOpsClient.h"
#include "mkRpcChannel.h"

namespace  mkops {
    class mkIOpsRpc_Stub;
}

class mkOpsStateClient : public mkIOpsStateClient
{
public:
    mkOpsStateClient(const std::string& guid, 
                    std::shared_ptr<mkRpcChannel> pChannel,
                    std::shared_ptr<mkops::mkIOpsRpc_Stub> pStub);
    virtual ~mkOpsStateClient();
    
    virtual void Put(const std::string& key, const std::string& value);
    virtual bool Get(const std::string& key, std::string& value);
    virtual void Delete(const std::string& key);
    virtual void List(const std::string& key, vector<std::string>& values);
    
private:
    std::string _guid;
    std::shared_ptr<mkRpcChannel> _pChannel;
    std::shared_ptr<mkops::mkIOpsRpc_Stub> _pStub;
};

class mkOpsClient : public mkIOpsClient
{
public:
    mkOpsClient();
    virtual ~mkOpsClient();
    
    virtual void ListState(vector<mkIOpsStateClient::Config>& vStates);
    virtual std::shared_ptr<mkIOpsStateClient> State(const std::string& guid);
    
private:
    std::shared_ptr<mkRpcChannel> _pChannel;
    std::shared_ptr<mkops::mkIOpsRpc_Stub> _pStub;
    
};




#endif