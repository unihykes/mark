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

Time:2021-1

info:

***************************************************************************************************/

#include<mkheaders.h>
#include "string/mkString.h"
#include"mkOptionSwitch.h"

mkOptionSwitch::mkOptionSwitch()

{
}

mkOptionSwitch::~mkOptionSwitch()
{
}

//解析执行参数
std::tuple<int, char**, int, char**>
mkOptionSwitch::InitEnv(int argc, char** argv)
{
    throw std::logic_error("do not support mkOptionSwitch::InitEnv(...)");
}

//加载配置文件中的参数
void 
mkOptionSwitch::LoadByConfig(const string& configFileName)
{
    //todo
}

//加载设置的参数
void 
mkOptionSwitch::Applys()
{
    for(const auto& elem : _mapArgs) {
        const string& key = elem.first;
        for(const auto& value : elem.second) {
            this->SetOptions(key, value, false);
        }
    }
    mkIOptionSwitch::Applys();//应用之
}

////////////////////////////////////////////////////////////////////////////////////////////////////

mkExecOptionSwitch::mkExecOptionSwitch()
    : _gtest_argc(0)
    , _gtest_argv(nullptr)
    , _benchmark_argc(0)
    , _benchmark_argv(nullptr)
{
}

mkExecOptionSwitch::~mkExecOptionSwitch()
{
    for(int i = 0; i != _benchmark_argc; ++i) {
        delete [] _benchmark_argv[i];
        _benchmark_argv[i] = nullptr;
    }
    if(_benchmark_argv) {
        delete [] _benchmark_argv;
        _benchmark_argv = nullptr;
    }
    
    for(int i = 0; i != _gtest_argc; ++i) {
        // 这里有个问题,testing::InitGoogleTest(...)后,
        //_gtest_argc中的指针地址被偏移了,因此不能delete
        //delete [] _gtest_argv[i];
        //_gtest_argv[i] = nullptr;
    }
    if(_gtest_argv) {
        delete [] _gtest_argv;
        _gtest_argv = nullptr;
    }
}

//解析执行参数
std::tuple<int, char**, int, char**>
mkExecOptionSwitch::InitEnv(int argc, char** argv)
{
    _vGtestArgs.push_back(string(argv[0]));//可执行程序名称
    _vBenchmarkArgs.push_back(string(argv[0]));//可执行程序名称
    
    for(int i = 1; i != argc; ++i) {
        string arg(argv[i]);
        
        if(mkStringHelper::starts_with<string>(arg, "--cmdg")) {
            string gtestArg = "--gtest_filter=";
            gtestArg += arg.substr(arg.find_first_of('=') + 1) ;
            _vGtestArgs.push_back(gtestArg);
        }
        else if(mkStringHelper::starts_with<string>(arg, "--cmdb")) {
            string benchmarkArg = "--benchmark_filter=";
            benchmarkArg += arg.substr(arg.find_first_of('=') + 1) ;
            _vBenchmarkArgs.push_back(benchmarkArg);
        }
        else if(mkStringHelper::starts_with<string>(arg, "--gtest_")) {
            _vGtestArgs.push_back(arg);
        }
        else if(mkStringHelper::starts_with<string>(arg, "--benchmark_")) {
            _vBenchmarkArgs.push_back(arg);
        }
        else if(mkStringHelper::starts_with<string>(arg, "--cmd")) {
            string gtestArg = "--gtest_filter=";
            gtestArg += arg.substr(arg.find_first_of('=') + 1) ;
            _vGtestArgs.push_back(gtestArg);
            string benchmarkArg = "--benchmark_filter=";
            benchmarkArg += arg.substr(arg.find_first_of('=') + 1) ;
            _vBenchmarkArgs.push_back(benchmarkArg);
        }
        
        //自定义参数
        else {
            string key = arg.substr(0, arg.find_first_of('='));
            string value = arg.substr(arg.find_first_of('=') + 1) ;
            if(!value.empty()) {
                _mapArgs[key].push_back(value);
            }
        }
    }
    
    if(0 == _gtest_argc) {
        _gtest_argv = new char*[_vGtestArgs.size()];
        
        for(auto& elem : _vGtestArgs) {
            char* arg = new char[elem.size() + 1];
            memcpy(arg, elem.c_str(), elem.size());
            arg[elem.size()] = '\0';
            _gtest_argv[_gtest_argc++] = arg;
        }
    }
    if(0 == _benchmark_argc) {
        _benchmark_argv = new char*[_vBenchmarkArgs.size()];
        
        for(auto& elem : _vBenchmarkArgs) {
            char* arg = new char[elem.size() + 1];
            memcpy(arg, elem.c_str(), elem.size());
            arg[elem.size()] = '\0';
            _benchmark_argv[_benchmark_argc++] = arg;
        }
    }
    
    return std::make_tuple(_gtest_argc, _gtest_argv, _benchmark_argc, _benchmark_argv);
}