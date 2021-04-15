/***************************************************************************************************
Author:liu.hao

Time:2021-3

info:
    
***************************************************************************************************/
#include <markcore.h>
#include <brpc/server.h>
#include "bvar/bvar.h"
#include "mkRpcChannel.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

bool 
mkRpcChannelOption::OnSetValue(const string& key, const string& value)
{
    if("--timeout_ms" == key) {
        _options.timeout_ms = std::stoi(value);
        _subOptions.timeout_ms = _options.timeout_ms;
        return true;
    }
    
    if("--load_balancer"  == key) {
        _load_balancer = value;
        return true;
    }
    
    if("--protocol" == key) {
        _subOptions.protocol = value;
        return true;
    }
    
    if("--connection_type" == key) {
        _subOptions.connection_type = value;
        return true;
    }
    if("--max_retry" == key) {
        _subOptions.max_retry = std::stoi(value);
        return true;
    }
    if("--ip_port" == key) {
        _ipPorts.insert(value);
        return true;
    }
    if("--dummy_port" == key) {
        _dummy_port = std::stoi(value);
        return true;
    }
    
    return false;
}

void 
mkRpcChannelOption::OnApply()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void 
mkRpcChannel::Login()
{
    //创建sub channel
    const brpc::ChannelOptions& sub_options = g_switch->GetOption<mkRpcChannelOption>()->_subOptions;
    const string& load_balancer = g_switch->GetOption<mkRpcChannelOption>()->_load_balancer;
    const set<string>& ipPorts = g_switch->GetOption<mkRpcChannelOption>()->_ipPorts;
    for(const auto& server : ipPorts) {
        auto pSubChannel = std::make_shared<brpc::Channel>();
        if (pSubChannel->Init(server.c_str(), load_balancer.c_str(), &sub_options) != 0) {
            LOG(ERROR) << "Fail to initialize pSubChannel[" << server << "]";
            return;
        }
        
        //取第一条连接ok的通道
        _pRpcChannel = pSubChannel;
        break;
    }
    
    //创建计数器
    _pLatency = std::make_shared<bvar::LatencyRecorder>("latency_main");
    
    //是否开启内置服务
    const int& dummy_port = g_switch->GetOption<mkRpcChannelOption>()->_dummy_port;
    if (dummy_port >= 0) {
        brpc::StartDummyServerAt(dummy_port);
    }
}

void 
mkRpcChannel::Logout()
{
}

void 
mkRpcChannel::SetLatency(const brpc::Controller& cntl)
{
    (*_pLatency) << cntl.latency_us();//记录RPC调用的时延(全局)
}

