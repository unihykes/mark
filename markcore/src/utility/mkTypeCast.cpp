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

#include <mkheaders.h>
#include"mkTypeCast.h"

//http://blog.csdn.net/sunnyfans/article/details/8286906
//OUT size must >= 2 bytes
void 
mkTypeCast::shortToBytes (short v, unsigned char* buf)
{
    *buf++ = ((int)(v >> 8) & 0xFF);
    *buf++ = ((int)(v >> 0) & 0xFF);
}

//OUT size must >= 2 bytes
void 
mkTypeCast::ushortToBytes (unsigned short v, unsigned char* buf)
{
    *buf++ = ((int)(v >> 8) & 0xFF);
    *buf++ = ((int)(v >> 0) & 0xFF);
}

//IN size must >= 2 bytes
unsigned short 
mkTypeCast::bytesToUShort (const unsigned char* buf)
{
    int v1 = buf[0];
    int v2 = buf[1];
    
    return ((unsigned short) ((v1 << 8) + (v2 << 0)));
}

//OUT size must >= 4 bytes
void 
mkTypeCast::intToBytes (int i, unsigned char* b)
{
    b[0] = ((unsigned char)(i >> 24) & 0xFF);
    b[1] = ((unsigned char)(i >> 16) & 0xFF);
    b[2] = ((unsigned char)(i >> 8) & 0xFF);
    b[3] = ((unsigned char)(i >> 0) & 0xFF);
}

//OUT size must >= 4 bytes
void 
mkTypeCast::uintToBytes (unsigned int u, unsigned char* b)
{
    b[0] = ((int)(u >> 24) & 0xFF);
    b[1] = ((int)(u >> 16) & 0xFF);
    b[2] = ((int)(u >> 8) & 0xFF);
    b[3] = ((int)(u >> 0) & 0xFF);
}

//IN size must >= 4 bytes
unsigned int 
mkTypeCast::bytesToUInt (const unsigned char* buf)
{
    int v1 = buf[0];
    int v2 = buf[1];
    int v3 = buf[2];
    int v4 = buf[3];
    
    return ((unsigned int) ((v1 << 24) + (v2 << 16) + (v3 << 8) + (v4 << 0)));
}

//IN size must >= 4 bytes
int 
mkTypeCast::bytesToInt (const unsigned char* buf)
{
    return (int) (bytesToUInt (buf));
}

//OUT size must >= 8 bytes
void 
mkTypeCast::int64ToBytes (int64 u, unsigned char* b)
{
    b[0] = ((int)(u >> 56) & 0xFF);
    b[1] = ((int)(u >> 48) & 0xFF);
    b[2] = ((int)(u >> 40) & 0xFF);
    b[3] = ((int)(u >> 32) & 0xFF);
    b[4] = ((int)(u >> 24) & 0xFF);
    b[5] = ((int)(u >> 16) & 0xFF);
    b[6] = ((int)(u >> 8) & 0xFF);
    b[7] = ((int)(u >> 0) & 0xFF);
}

//OUT size must >= 8 bytes
void 
mkTypeCast::uint64ToBytes (uint64 u, unsigned char* b)
{
    b[0] = ((int)(u >> 56) & 0xFF);
    b[1] = ((int)(u >> 48) & 0xFF);
    b[2] = ((int)(u >> 40) & 0xFF);
    b[3] = ((int)(u >> 32) & 0xFF);
    b[4] = ((int)(u >> 24) & 0xFF);
    b[5] = ((int)(u >> 16) & 0xFF);
    b[6] = ((int)(u >> 8) & 0xFF);
    b[7] = ((int)(u >> 0) & 0xFF);
}

//IN size must >= 8 bytes
uint64 
mkTypeCast::bytesToUInt64 (const unsigned char* buf)
{
    uint64 v,t;
    v = t = buf[0];
    v <<= 56;

    t = buf[1];
    v |= (t << 48);

    t = buf[2];
    v |= (t << 40);

    t = buf[3];
    v |= (t << 32);

    t = buf[4];
    v |= (t << 24);

    t = buf[5];
    v |= (t << 16);

    t = buf[6];
    v |= (t << 8);

    t = buf[7];
    v |= t;

    return v;
}

//IN size must >= 8 bytes
int64 
mkTypeCast::bytesToInt64 (const unsigned char* buf)
{
    return (int64)bytesToUInt64 (buf);
}