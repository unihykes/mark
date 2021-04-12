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

#ifndef __mkIReplaceValue
#define __mkIReplaceValue

//数据结构:piece
class mkIReplacePiece
{
public:
    virtual int GetOffset() = 0;
    virtual int GetLength() = 0;
    virtual const char* GetBuffer() = 0;
};

//数据结构:value
class mkIReplaceValue
{
public:
    virtual void write(const string& in)
    {
        //按需重载
    }
    virtual void read(string& out)
    {
        //按需重载
    }
    
    virtual std::shared_ptr<mkIReplacePiece> GetPiece(const int& offset, const int& length)
    {
        //按需重载
    }
    
    virtual void ListPieces(vector<std::shared_ptr<mkIReplacePiece> >& out)
    {
        //按需重载
    }
};

class mkIReplaceValueBuilder
{
public:
    virtual std::shared_ptr<mkIReplaceValue> Create(const int& key) = 0;
};

#endif