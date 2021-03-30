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

DEFINE_int32(thread_num, 50, "Number of threads to send requests");
DEFINE_int32(attachment_size, 0, "Carry so many byte attachment along with requests");
DEFINE_bool(dont_fail, false, "Print fatal when some call failed");

TEST(use_brpc, default)
{
    // 初始化全局记数器
    bvar::LatencyRecorder g_latency_recorder("client");
    bvar::Adder<int> g_error_count("client_error_count");
    
    // 初始化subchannel的记数器
    map<int, shared_ptr<bvar::LatencyRecorder> > mapSublatency;
    std::mutex mapSublatencyMutex;
    
    //初始化附件
    std::string g_attachment;
    if (FLAGS_attachment_size > 0) {
        g_attachment.resize(FLAGS_attachment_size, 'a');
    }
    
    mkBrpcChannel brpcChannel;
    brpcChannel.Init();
    auto client = brpcChannel.CreateClient();
    
    //开启多个发送线程
    vector<std::shared_ptr<std::thread>> vThreads;
    for (int i = 0; i < FLAGS_thread_num; ++i) {
        auto sendThread = std::make_shared<std::thread>( [&]() {
            int log_id = 0;
            while (!brpc::IsAskedToQuit()) {
                use_brpc::ReadResponse response;//设置 response
                use_brpc::ReadRequest request;//设置 request
                request.set_value(log_id++);
                brpc::Controller cntl;//设置 cntl
                if (!g_attachment.empty()) {
                    //baidu_std和hulu_pbrpc协议支持附件，这段数据由用户自定义，不经过protobuf的序列化
                    cntl.request_attachment().append(g_attachment);
                }
                
                //第4个参数(Closure* done)设置为NULL表示同步阻塞访问
                client->Read(&cntl, &request, &response, NULL);
                if (!cntl.Failed()) {//成功
                    g_latency_recorder << cntl.latency_us();//记录RPC调用的时延(全局)
                    
                    for (int i = 0; i < cntl.sub_count(); ++i) {
                        if (cntl.sub(i) && !cntl.sub(i)->Failed()) {
                            if(!mapSublatency[i]) {
                                std::lock_guard<std::mutex> lock(mapSublatencyMutex);
                                if(!mapSublatency[i]) {
                                    string name = mkSharedFormat{}("client_sub_%d", i);
                                    mapSublatency[i] = std::make_shared<bvar::LatencyRecorder>(name);
                                }
                            }
                            (*mapSublatency[i]) << cntl.sub(i)->latency_us();//记录RPC调用的时延(sun_channel)
                        }
                    }
                } 
                else {
                    g_error_count << 1;
                    CHECK(brpc::IsAskedToQuit() || !FLAGS_dont_fail)
                        << "error=" << cntl.ErrorText() << " latency=" << cntl.latency_us();
                    // 调用失败
                    bthread_usleep(50000);
                }
            }
        });
        vThreads.push_back(sendThread);
    }
    
    while (!brpc::IsAskedToQuit()) {
        sleep(1);
        string sub_latency;
        for (int i = 0; i < mapSublatency.size(); ++i) {
            sub_latency += mkSharedFormat{}(" latency_%d=%lld", i, mapSublatency[i]->latency(10));
        }
        MK_PRINT("Sending EchoRequest at qps=%lld latency=%lld(us) %s", g_latency_recorder.qps(5), g_latency_recorder.latency(10), sub_latency.c_str());
    }
    LOG(INFO) << "EchoClient is going to quit";
    
    //释放资源
    for(auto & elem : vThreads) {
        elem->join();
    }
}