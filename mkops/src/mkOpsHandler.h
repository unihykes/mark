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

#ifndef __mkOpsHandler
#define __mkOpsHandler

#include "mkOpsStateFactory.h"

class mkOpsHandler : public mkops::mkIOpsRpc
{
public:
    mkOpsHandler(std::shared_ptr<mkOpsStateFactory> pStateFactory);
    virtual ~mkOpsHandler();
    
    virtual void ListState(::google::protobuf::RpcController* controller,
                       const ::mkops::RequestListState* request,
                       ::mkops::ResponseListState* response,
                       ::google::protobuf::Closure* done);
                       
    virtual void Put(::google::protobuf::RpcController* controller,
                       const ::mkops::RequestPut* request,
                       ::mkops::ResponsePut* response,
                       ::google::protobuf::Closure* done);
    
    virtual void Get(::google::protobuf::RpcController* controller,
                       const ::mkops::RequestGet* request,
                       ::mkops::ResponseGet* response,
                       ::google::protobuf::Closure* done);
    
    virtual void Delete(::google::protobuf::RpcController* controller,
                       const ::mkops::RequestDelete* request,
                       ::mkops::ResponseDelete* response,
                       ::google::protobuf::Closure* done);
    
    virtual void List(::google::protobuf::RpcController* controller,
                       const ::mkops::RequestList* request,
                       ::mkops::ResponseList* response,
                       ::google::protobuf::Closure* done);

private:
    std::shared_ptr<mkOpsStateFactory> _pStateFactory;
};

#endif
