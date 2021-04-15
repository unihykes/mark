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

#ifndef __mkIOpsState
#define __mkIOpsState


class mkIOpsState
{
public:
    struct Config
    {
        std::string      _guid;
        std::string      _name;
    };
    virtual ~mkIOpsState(){}
    virtual mkIOpsState::Config GetConfig() const = 0;
    virtual void Put(const std::string& key, const std::string& value) = 0;
    virtual bool Get(const std::string& key, std::string& value) = 0;
    virtual void Delete(const std::string& key) = 0;
    virtual void List(const std::string& key, vector<std::string>& values) = 0;
};


#endif