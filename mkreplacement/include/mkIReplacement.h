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

#ifndef __mkIReplacement
#define __mkIReplacement

#include "mkIReplaceValue.h"

//接口:汰换器
class MK_DLL_EXPORT mkIReplacement
{
public:
    virtual std::shared_ptr<mkIReplaceValue> Get(const int& key) = 0;
};

class MK_DLL_EXPORT mkIReplacementBuilder
{
public:
    void PushOptions(const string& key, const string& value);
    
    //创建连接,调用失败会抛异常
    std::shared_ptr<mkIReplacement> LIRS(shared_ptr<mkIReplaceValueBuilder> pBuilder);
};

#endif