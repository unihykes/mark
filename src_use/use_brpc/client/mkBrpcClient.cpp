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
#include <gflags/gflags.h>
#include <bthread/bthread.h>
#include <butil/logging.h>
#include <butil/string_printf.h>
#include <butil/time.h>
#include <butil/macros.h>
#include <brpc/parallel_channel.h>
#include <brpc/server.h>
#include "use_brpc.pb.h"
#include "mkBrpcClient.h"

DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)"); 
DEFINE_bool(same_channel, false, "Add the same sub channel multiple times");
DEFINE_string(server, "0.0.0.0:9999", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(dummy_port, -1, "Launch dummy server at this port");
DEFINE_int32(channel_num, 3, "Number of sub channels");

mkBrpcChannel::mkBrpcChannel()
{
}

mkBrpcChannel::~mkBrpcChannel()
{
}

void
mkBrpcChannel::Init()
{
    brpc::ParallelChannelOptions pchan_options;
    pchan_options.timeout_ms = FLAGS_timeout_ms;//超时时间
    if (channel.Init(&pchan_options) != 0) {
        LOG(ERROR) << "Fail to init ParallelChannel";
        return;
    }
    
    //创建sub channel
    brpc::ChannelOptions sub_options;
    sub_options.protocol = FLAGS_protocol;//协议
    sub_options.connection_type = FLAGS_connection_type;
    sub_options.max_retry = FLAGS_max_retry;
    // Setting sub_options.timeout_ms does not work because timeout of sub 
    // channels are disabled in ParallelChannel.
    
    if (FLAGS_same_channel) {
        // For brpc >= 1.0.155.31351, a sub channel can be added into a ParallelChannel more than once.
        brpc::Channel* sub_channel = new brpc::Channel;
        // Initialize the channel, NULL means using default options. 
        // options, see `brpc/channel.h'.
        if (sub_channel->Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &sub_options) != 0) {
            LOG(ERROR) << "Fail to initialize sub_channel";
            return;
        }
        for (int i = 0; i < FLAGS_channel_num; ++i) {
            if (channel.AddChannel(sub_channel, brpc::OWNS_CHANNEL, NULL, NULL) != 0) {
                LOG(ERROR) << "Fail to AddChannel, i=" << i;
                return;
            }
        }
    }
    else {
        for (int i = 0; i < FLAGS_channel_num; ++i) {
            brpc::Channel* sub_channel = new brpc::Channel;
            // Initialize the channel, NULL means using default options. 
            // options, see `brpc/channel.h'.
            if (sub_channel->Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &sub_options) != 0) {
                LOG(ERROR) << "Fail to initialize sub_channel[" << i << "]";
                return;
            }
            if (channel.AddChannel(sub_channel, brpc::OWNS_CHANNEL, NULL, NULL) != 0) {
                LOG(ERROR) << "Fail to AddChannel, i=" << i;
                return;
            }
        }
    }
    
    if (FLAGS_dummy_port >= 0) {
        brpc::StartDummyServerAt(FLAGS_dummy_port);
    }
    
    // Normally, you should not call a Channel directly, but instead construct
    // a stub Service wrapping it. stub can be shared by all threads as well.
    _pStub = make_shared<use_brpc::Service_Stub>(static_cast<google::protobuf::RpcChannel*>(&channel));
    
}
