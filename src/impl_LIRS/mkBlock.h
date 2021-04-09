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

#ifndef __mkBlock
#define __mkBlock

//数据块状态
enum mkBlockState
{
    STATE_LIR               = 0,//热数据块，已经被访问两次的数据块
    STATE_HIR_resident      = 1,//冷数据块，还仅仅只被访问一次的数据块,有缓存 
    STATE_HIR_nonResident   = 2,//冷数据块，还仅仅只被访问一次的数据块,无缓存
    STATE_Invalid           = 3 //无效数据块
};

struct mkBlockBuffer
{
    
};

//数据块
struct mkBlock
{
    mkBlock(const int& key, const mkBlockState& state)
        :_key(key) 
        ,_state(state)
    {
    }
    
    int             _key;
    mkBlockState    _state;
    std::shared_ptr<mkBlockBuffer>  _pBuf;
};

#endif