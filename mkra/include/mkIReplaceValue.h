﻿/***************************************************************************************************
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

#ifndef __mkIReplaceValue
#define __mkIReplaceValue

//数据结构:piece
class mkIReplacePiece
{
public:
    virtual void SetData(const char* buf, const int& length) = 0;
    virtual void AppendData(const char* buf, const int& length) = 0;
};

//数据结构:value
class mkIReplaceValue
{
public:
    virtual ~mkIReplaceValue(){}
    
    virtual void Hit() = 0;
    virtual int64 GetHitCount() const = 0;
    
    virtual void write(const string& in)
    {
        MK_THROW(1024, "Unimplemented interface");//按需重载
    }
    virtual void read(string& out)
    {
        MK_THROW(1024, "Unimplemented interface");//按需重载
    }
    
    virtual void GetPiece(mkIReplacePiece* out, const int& offset, const int& length)
    {
        MK_THROW(1024, "Unimplemented interface");//按需重载
    }
};

class mkIReplaceValueBuilder
{
public:
    virtual ~mkIReplaceValueBuilder(){}
    
    virtual std::shared_ptr<mkIReplaceValue> Create(const int& key) = 0;
};

#endif