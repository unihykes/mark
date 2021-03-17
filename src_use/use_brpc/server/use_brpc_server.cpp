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
#include <butil/logging.h>
#include <butil/string_printf.h>
#include <brpc/server.h>
#include "echo.pb.h"

class EchoServiceImpl : public example::EchoService {
public:
    EchoServiceImpl() {}
    ~EchoServiceImpl() {};
    
    void Echo(google::protobuf::RpcController* cntl_base,
              const example::EchoRequest* request,
              example::EchoResponse* response,
              google::protobuf::Closure* done) 
    {
        brpc::ClosureGuard done_guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

        // Echo request and its attachment
        response->set_value(request->value());
        if (1) {
            cntl->response_attachment().append(cntl->request_attachment());
        }
    }
};

TEST(use_brpc, default)
{
    brpc::Server server;
    EchoServiceImpl echo_service_impl;
    if (server.AddService(&echo_service_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service";
        return;
    }
    
    // Start the server. 
    brpc::ServerOptions options;
    options.idle_timeout_sec = 60;
    options.max_concurrency = 60;
    if(server.Start(9999, &options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        return;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();
}