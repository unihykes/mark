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
#include "mkOpsService.h"
#include "mkOpsHandler.h"

mkOpsService::mkOpsService()
    : _server(std::make_shared<brpc::Server>())
{
    MK_PRINT("");
}

mkOpsService::~mkOpsService()
{
    MK_PRINT("");
}

void 
mkOpsService::Init()
{
    MK_PRINT("");
    
    _pStateFactory = std::make_shared<mkOpsStateFactory>();
    _handler = std::make_shared<mkOpsHandler>(_pStateFactory);
    
    //添加service
    if (_server->AddService(_handler.get(), brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        constexpr int errorId = 1234;//todo
        MK_THROW(errorId, "Fail to add _handler");
    }
    
    //开启监听
    string ip_port = "192.168.88.128:9999";//todo
    brpc::ServerOptions options;
    options.num_threads = 8;//todo
    options.idle_timeout_sec = 60;//todo
    options.max_concurrency = 60;//todo
    if(_server->Start(ip_port.c_str(), &options) != 0) {
        constexpr int errorId = 1234;//todo
        MK_THROW(errorId, "Fail to start mkOpsHandler");
    }
}

void 
mkOpsService::Register(std::shared_ptr<mkIOpsState> state)
{
    MK_PRINT("");
    
    if(!_pStateFactory) {
        Init();
    }
    
    if(_pStateFactory) {
        _pStateFactory->Insert(state);
    }
}

void 
mkOpsService::UnRegister(std::shared_ptr<mkIOpsState> state)
{
    MK_PRINT("");
    
    if(_pStateFactory) {
        _pStateFactory->Remove(state);
    }
}

void 
mkOpsService::Fini()
{
    //todo
}
