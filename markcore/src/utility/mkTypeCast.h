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

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkTypeCast
#define __mkTypeCast

class MK_DLL_EXPORT mkTypeCast
{
public:
    //OUT size must >= 2 bytes
    static void shortToBytes (short v, unsigned char* buf);
    
    //OUT size must >= 2 bytes
    static void ushortToBytes (unsigned short v, unsigned char* buf);
    
    //IN size must >= 2 bytes
    static unsigned short bytesToUShort (const unsigned char* buf);
    
    //OUT size must >= 4 bytes
    static void intToBytes (int i, unsigned char* b);
    
    //OUT size must >= 4 bytes
    static void uintToBytes (unsigned int u, unsigned char* b);
    
    //IN size must >= 4 bytes
    static unsigned int bytesToUInt (const unsigned char* buf);
    
    //IN size must >= 4 bytes
    static int bytesToInt (const unsigned char* buf);
    
    //OUT size must >= 8 bytes
    static void int64ToBytes (int64 u, unsigned char* b);
    
    //OUT size must >= 8 bytes
    static void uint64ToBytes (uint64 u, unsigned char* b);
    
    //IN size must >= 8 bytes
    static uint64 bytesToUInt64 (const unsigned char* buf);
    
    //IN size must >= 8 bytes
    static int64 bytesToInt64 (const unsigned char* buf);
};

#endif //__mkMiscellaneous
