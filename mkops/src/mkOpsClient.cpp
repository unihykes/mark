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

#include <markcore.h>
#include "mkIOpsRpc.pb.h"
#include "mkOpsClient.h"


mkOpsStateClient::mkOpsStateClient(const std::string& guid,
                                std::shared_ptr<mkRpcChannel> pChannel,
                                std::shared_ptr<mkops::mkIOpsRpc_Stub> pStub)
    : _guid(guid)
    , _pChannel(pChannel)
    , _pStub(pStub)
{
}

mkOpsStateClient::~mkOpsStateClient()
{
}

void 
mkOpsStateClient::Put(const std::string& key, const std::string& value)
{
    //设置 cntl
    brpc::Controller cntl;
    
    //设置 request
    mkops::RequestPut request;
    request.set_guid(_guid);
    request.set_key(key);
    request.set_value(value);
    
    //设置 response
    mkops::ResponsePut response;
        
    //设置 done
    ::google::protobuf::Closure* done = nullptr;
    
    _pStub->Put(&cntl, &request, &response, done);
    
    if (cntl.Failed()) {//失败
        MK_THROW(123, "%s", cntl.ErrorText().c_str());
    }
    _pChannel->SetLatency(cntl);
}

bool 
mkOpsStateClient::Get(const std::string& key, std::string& value)
{
    //设置 cntl
    brpc::Controller cntl;
    
    //设置 request
    mkops::RequestGet request;
    request.set_guid(_guid);
    request.set_key(key);
    
    //设置 response
    mkops::ResponseGet response;
        
    //设置 done
    ::google::protobuf::Closure* done = nullptr;
    
    _pStub->Get(&cntl, &request, &response, done);
    
    if (cntl.Failed()) {//失败
        MK_THROW(123, "%s", cntl.ErrorText().c_str());
    }
    _pChannel->SetLatency(cntl);
    
    value = response.value();
}

void 
mkOpsStateClient::Delete(const std::string& key)
{
    //设置 cntl
    brpc::Controller cntl;
    
    //设置 request
    mkops::RequestDelete request;
    request.set_guid(_guid);
    request.set_key(key);
    
    //设置 response
    mkops::ResponseDelete response;
        
    //设置 done
    ::google::protobuf::Closure* done = nullptr;
    
    _pStub->Delete(&cntl, &request, &response, done);
    
    if (cntl.Failed()) {//失败
        MK_THROW(123, "%s", cntl.ErrorText().c_str());
    }
    _pChannel->SetLatency(cntl);
}

void 
mkOpsStateClient::List(const std::string& key, vector<std::string>& values)
{
    //设置 cntl
    brpc::Controller cntl;
    
    //设置 request
    mkops::RequestList request;
    request.set_guid(_guid);
    request.set_key(key);
    
    //设置 response
    mkops::ResponseList response;
        
    //设置 done
    ::google::protobuf::Closure* done = nullptr;
    
    _pStub->List(&cntl, &request, &response, done);
    
    if (cntl.Failed()) {//失败
        MK_THROW(123, "%s", cntl.ErrorText().c_str());
    }
    _pChannel->SetLatency(cntl);
    
    for(int i = 0; i != response.value_size(); ++i) {
        values.emplace_back(response.value(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

mkOpsClient::mkOpsClient()
{
    _pChannel = std::make_shared<mkRpcChannel>();
    _pChannel->Login();
    _pStub = _pChannel->CreateStub<mkops::mkIOpsRpc_Stub>();
}

mkOpsClient::~mkOpsClient()
{
}
void 
mkOpsClient::ListState(vector<mkIOpsStateClient::Config>& vStates)
{
    //设置 cntl
    brpc::Controller cntl;
    
    //设置 request
    mkops::RequestListState request;
    
    //设置 response
    mkops::ResponseListState response;
        
    //设置 done
    ::google::protobuf::Closure* done = nullptr;
    
    _pStub->ListState(&cntl, &request, &response, done);
    
    if (cntl.Failed()) {//失败
        MK_THROW(123, "%s", cntl.ErrorText().c_str());
    }
    _pChannel->SetLatency(cntl);
    
    for(int i = 0; i != response.guid_size(); ++i) {
        vStates.push_back({response.guid(i), response.name(i)});
    }
}

std::shared_ptr<mkIOpsStateClient> 
mkOpsClient::State(const std::string& guid)
{
    auto result = std::make_shared<mkOpsStateClient>(guid, _pChannel, _pStub);
    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void 
mkIOpsClientBuilder::PushOptions(const string& key, const string& value)
{
    MK_CALL_ONCE_BEGIN
        g_switch->ClearOption<mkRpcChannelOption>();
    MK_CALL_ONCE_END
    
    g_switch->SetOptions(key, value, false);
}

std::shared_ptr<mkIOpsClient> 
mkIOpsClientBuilder::Build()
{
    auto result = std::make_shared<mkOpsClient>();
    return result;
}
