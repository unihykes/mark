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
#include <brpc/server.h>
#include "mkIOpsRpc.pb.h"
#include "mkOpsHandler.h"

mkOpsHandler::mkOpsHandler(std::shared_ptr<mkOpsStateFactory> pStateFactory)
    : _pStateFactory(pStateFactory)
{
}

mkOpsHandler::~mkOpsHandler()
{
}

void 
mkOpsHandler::ListState(::google::protobuf::RpcController* controller,
                   const ::mkops::RequestListState* request,
                   ::mkops::ResponseListState* response,
                   ::google::protobuf::Closure* done)
{
    MK_PRINT("");
    brpc::ClosureGuard done_guard(done);//note:没有这句,客户端会收不到回执
    
   vector<std::shared_ptr<mkIOpsState>> states;
   _pStateFactory->List(states);
   
    for(const auto& state : states) {
        response->add_guid(state->GetConfig()._guid);
        response->add_name(state->GetConfig()._name);
    }
}

void 
mkOpsHandler::Put(::google::protobuf::RpcController* controller,
                   const ::mkops::RequestPut* request,
                   ::mkops::ResponsePut* response,
                   ::google::protobuf::Closure* done)
{
    MK_PRINT("guid = %s, key = %s", request->guid().c_str(), request->key().c_str());
    brpc::ClosureGuard done_guard(done);
    
    std::shared_ptr<mkIOpsState> pState = _pStateFactory->Find(request->guid());
    if(pState) {
        pState->Put(request->key(), request->value());
    }
}

void 
mkOpsHandler::Get(::google::protobuf::RpcController* controller,
                   const ::mkops::RequestGet* request,
                   ::mkops::ResponseGet* response,
                   ::google::protobuf::Closure* done)
{
    MK_PRINT("guid = %s, key = %s", request->guid().c_str(), request->key().c_str());
    brpc::ClosureGuard done_guard(done);
    
    std::shared_ptr<mkIOpsState> pState = _pStateFactory->Find(request->guid());
    if(pState) {
        string value;
        pState->Get(request->key(), value);
        response->set_value(value);
    }
}

void 
mkOpsHandler::Delete(::google::protobuf::RpcController* controller,
                   const ::mkops::RequestDelete* request,
                   ::mkops::ResponseDelete* response,
                   ::google::protobuf::Closure* done)
{
    MK_PRINT("guid = %s, key = %s", request->guid().c_str(), request->key().c_str());
    brpc::ClosureGuard done_guard(done);
    
    std::shared_ptr<mkIOpsState> pState = _pStateFactory->Find(request->guid());
    if(pState) {
        pState->Delete(request->key());
    }
}

void 
mkOpsHandler::List(::google::protobuf::RpcController* controller,
                   const ::mkops::RequestList* request,
                   ::mkops::ResponseList* response,
                   ::google::protobuf::Closure* done)
{
    MK_PRINT("guid = %s, key = %s", request->guid().c_str(), request->key().c_str());
    brpc::ClosureGuard done_guard(done);
    
    std::shared_ptr<mkIOpsState> pState = _pStateFactory->Find(request->guid());
    if(pState) {
        vector<std::string> values;
        pState->List(request->key(), values);
        for(const auto& value : values) {
            response->add_value(value);
        }
    }
}