/***************************************************************************************************
Author:liu.hao

Time:2021-3

info:
    
***************************************************************************************************/

#ifndef __mkRpcChannel
#define __mkRpcChannel

#include <brpc/parallel_channel.h>

namespace brpc {
    class Controller;
}

namespace bvar {
    class LatencyRecorder;
}

class mkRpcChannelOption : public mkIOption
{
public:
    virtual bool OnSetValue(const string& key, const string& value);
    virtual void OnApply();
    
public:
    brpc::ParallelChannelOptions        _options;
    brpc::ChannelOptions                _subOptions;
    string                              _load_balancer;
    set<string>                         _ipPorts;
    int                                 _dummy_port = -1;
};

class mkRpcChannel
{
public:
    void Login();
    void Logout();
    void SetLatency(const brpc::Controller& cntl);
    
    template<class T>
    std::shared_ptr<T> CreateStub()
    {
        std::shared_ptr<T> pStub = make_shared<T>(static_cast<google::protobuf::RpcChannel*>(_pRpcChannel.get()));
        return pStub;
    }
    
private:
    std::shared_ptr<brpc::Channel>          _pRpcChannel;//线程安全的通道
    std::shared_ptr<bvar::LatencyRecorder>  _pLatency; //计数器
};

#endif
