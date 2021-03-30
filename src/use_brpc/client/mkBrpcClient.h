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

#ifndef __mkBrpcClient
#define __mkBrpcClient

class mkBrpcChannel
{
public:
    mkBrpcChannel();
    ~mkBrpcChannel();
    
    void Init();
    void Fini();
    
    std::shared_ptr<use_brpc::Service_Stub> CreateClient()
    {
        return _pStub;
    }
    
private:
    brpc::ParallelChannel channel;//创建一条线程安全的通道
    std::shared_ptr<use_brpc::Service_Stub> _pStub;
};


















#endif