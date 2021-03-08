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

Time:2018-2

info:

***************************************************************************************************/

#include <markcore.h>
#include <gtest/gtest.h>

TEST(mkTypeCast, shortToBytes)
{
	short v = 123;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::shortToBytes(v, buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}


TEST(mkTypeCast, ushortToBytes)
{
	unsigned short v = 456;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::ushortToBytes(v, buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x", v, buf[0], buf[1]);
}

TEST(mkTypeCast, bytesToUShort)
{
	unsigned short v = 789;
	unsigned char buf[2];
	memset(buf, 0, 2);
	mkTypeCast::ushortToBytes(v, buf);
	unsigned short result = mkTypeCast::bytesToUShort(buf);
	
	MK_PRINT("v = 0x%04x, buf = 0x%02x%02x, result = 0x%04x", v, buf[0], buf[1], result);
}

TEST(mkTypeCast, intToBytes)
{
	int v = 2147483647;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::intToBytes(v, buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST(mkTypeCast, uintToBytes)
{
	unsigned int v = 2147483640;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::uintToBytes(v, buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x", v, buf[0], buf[1], buf[2], buf[3]);
}

TEST(mkTypeCast, bytesToUInt)
{
	unsigned int v = 2147483600;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::uintToBytes(v, buf);
	unsigned int result = mkTypeCast::bytesToUInt(buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST(mkTypeCast, bytesToInt)
{
	int v = 2147483000;
	unsigned char buf[4];
	memset(buf, 0, 4);
	mkTypeCast::intToBytes(v, buf);
	int result = mkTypeCast::bytesToInt(buf);
	
	MK_PRINT("v = 0x%08x, buf = 0x%02x%02x%02x%02x, result = 0x%04x", v, buf[0], buf[1], buf[2], buf[3], result);
}

TEST(mkTypeCast, int64ToBytes)
{
	int64 v = 1234567890123;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::int64ToBytes(v, buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST(mkTypeCast, uint64ToBytes)
{
	uint64 v = 12345678901234;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::uint64ToBytes(v, buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
}

TEST(mkTypeCast, bytesToUInt64)
{
	uint64 v = 123456789012345;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::uint64ToBytes(v, buf);
	uint64 result = mkTypeCast::bytesToUInt64(buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}

TEST(mkTypeCast, bytesToInt64)
{
	int64 v = 1234567890123456;
	unsigned char buf[8];
	memset(buf, 0, 8);
	mkTypeCast::int64ToBytes(v, buf);
	int64 result = mkTypeCast::bytesToInt64(buf);
	
	MK_PRINT("v = 0x%016llx, buf = 0x%02x%02x%02x%02x%02x%02x%02x%02x, result = 0x%016llx"
				, v, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], result);
}
