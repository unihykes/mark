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
#include "benchmark_helpers.h"

TEST(mkString, constructor)
{
    mkCharAlloc alloc;
    
    mkString str0_a;
    mkString str0_b(alloc);
    
    mkString mockStr;
    mockStr = _T("str1");
    mkString str1(mockStr);
    
    mockStr = _T("str2");
    
#ifdef __WINDOWS__
    mkString str2(mockStr, alloc);//c++11新增,但是gcc4.8.5未实现
#endif
    
    mkString moveStr = _T("str3");
    mkString str3(std::move(moveStr));
    
    mockStr = _T("str4");
    mkString str4_a(mockStr, size_t(0));
    mkString str4_b(mockStr, 0, 2);
    mkString str4_c(mockStr, 0, 3, alloc);
    
    mkString str5_a(4, _T('a'));//与 String 版本的形参顺序不同
    mkString str5_b(4, _T('b'), alloc);//与 String 版本的形参顺序不同
    
    mkString str6_a(_T("str6_a"));
    mkString str6_b(_T("str6_b"), alloc);
    
    mkString str7_a(_T("str7_a"), 2);
    mkString str7_b(_T("str7_b"), 3, alloc);
    
#ifdef __WINDOWS__
    mkString str8_a(mkStringHelper::conv("str8_a").get());
    mkString str8_b(mkStringHelper::conv("str8_b").get(), alloc);
    
    mkString str9_a(mkStringHelper::conv("str9_a").get(), 4);
    mkString str9_b(mkStringHelper::conv("str9_b").get(), 4, alloc);
#endif
    
    MK_PRINT(str0_a.c_str());EXPECT_TRUE(str0_a == _T(""));
    MK_PRINT(str0_b.c_str());EXPECT_TRUE(str0_b == _T(""));
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("str1"));
#ifdef __WINDOWS__
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("str2"));
#endif
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("str3"));
    MK_PRINT(str4_a.c_str());EXPECT_TRUE(str4_a == _T("str4"));
    MK_PRINT(str4_b.c_str());EXPECT_TRUE(str4_b == _T("st"));
    MK_PRINT(str4_c.c_str());EXPECT_TRUE(str4_c == _T("str"));
    MK_PRINT(str5_a.c_str());EXPECT_TRUE(str5_a == _T("aaaa"));
    MK_PRINT(str5_b.c_str());EXPECT_TRUE(str5_b == _T("bbbb"));
    MK_PRINT(str6_a.c_str());EXPECT_TRUE(str6_a == _T("str6_a"));
    MK_PRINT(str6_b.c_str());EXPECT_TRUE(str6_b == _T("str6_b"));
    MK_PRINT(str7_a.c_str());EXPECT_TRUE(str7_a == _T("st"));
    MK_PRINT(str7_b.c_str());EXPECT_TRUE(str7_b == _T("str"));
#ifdef __WINDOWS__
    MK_PRINT(str8_a.c_str());EXPECT_TRUE(str8_a == _T("str8_a"));
    MK_PRINT(str8_b.c_str());EXPECT_TRUE(str8_b == _T("str8_b"));
    MK_PRINT(str9_a.c_str());EXPECT_TRUE(str9_a == _T("str9"));
    MK_PRINT(str9_b.c_str());EXPECT_TRUE(str9_b == _T("str9"));
#endif
}


TEST(mkString, getx)
{
    mkString str(_T("0123456789"));
    
    auto alloc = str.get_allocator();
    auto len = str.length();
    auto cap = str.capacity();
    auto maxSize = str.max_size();
    auto isEmpty = str.empty();
    
    MK_PRINT("%lld", len);EXPECT_TRUE(len == 10);
    MK_PRINT("%lld", cap);EXPECT_TRUE(cap >= 10);
    MK_PRINT("%llud < %llud", maxSize, mkString::npos);EXPECT_TRUE(maxSize < mkString::npos);
    MK_PRINT("%lld", isEmpty);EXPECT_TRUE(isEmpty == false);
}

TEST(mkString, assign)
{
    mkString mockStr = _T("0123456789");
    mkString moveStr = _T("xyz");
    
    mkString str0;str0.assign(mockStr);
    mkString str1;str1.assign(mockStr, 2, 2);
    mkString str2;str2.assign(_T("0123456789"), 3);
    mkString str3;str3.assign(_T("0123"));
    mkString str4;str4.assign(5, _T('a'));//与 String 版本的形参顺序不同
    mkString str5;str5.assign(std::move(moveStr));
    #ifdef __WINDOWS__
        mkString str6;str6.assign(mkStringHelper::conv("0123456789").get(), 6);
        mkString str7;str7.assign(mkStringHelper::conv("0123456").get());
    #endif
    
    MK_PRINT(str0.c_str());EXPECT_TRUE(str0 == _T("0123456789"));
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("23"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("012"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("0123"));
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T("aaaaa"));
    MK_PRINT(str5.c_str());EXPECT_TRUE(str5 == _T("xyz"));
#ifdef __WINDOWS__
    MK_PRINT(str6.c_str());EXPECT_TRUE(str6 == _T("012345"));
    MK_PRINT(str7.c_str());EXPECT_TRUE(str7 == _T("0123456"));
#endif
}

TEST(mkString, append)
{
    mkString mockStr = _T("0123");
    mkString dest;
    
    dest.append(mockStr);mkString str0 = dest;
    dest.append(mockStr, 2, 2);mkString str1 = dest;
    dest.append(_T("45678"), 3);mkString str2 = dest;
    dest.append(_T("789"));mkString str3 = dest;
    dest.append(3, _T('a'));mkString str4 = dest;//与 String 版本的形参顺序不同
    #ifdef __WINDOWS__
        dest.append(mkStringHelper::conv("bcdef").get(), 3);mkString str6 = dest;
        dest.append(mkStringHelper::conv("ef").get());mkString str7 = dest;
    #endif
    
    MK_PRINT(str0.c_str());EXPECT_TRUE(str0 == _T("0123"));
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("012323"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("012323456"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("012323456789"));
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T("012323456789aaa"));
#ifdef __WINDOWS__
    MK_PRINT(str6.c_str());EXPECT_TRUE(str6 == _T("012323456789aaabcd"));
    MK_PRINT(str7.c_str());EXPECT_TRUE(str7 == _T("012323456789aaabcdef"));
#endif
}

TEST(mkString, at)
{
    const mkString str1(_T("ABCD"));
    mkString str2(_T("1234"));
    str2.at(0) = _T('X');
    
    EXPECT_TRUE(str1.at(0) == _T('A'));
    EXPECT_TRUE(str2.at(0) == _T('X'));
}

TEST(mkString, getCStr)
{
    const mkString str1(_T("0123456789"));
    auto ret = str1.c_str();
    
    EXPECT_TRUE(*ret == _T('0'));
}

TEST(mkString, remove)
{
    mkString str1(_T("0123456789"));
    str1.erase();
    
    mkString str2(_T("0123456789"));
    str2.erase(4);
    
    mkString str3(_T("0123456789"));
    str3.erase(4, 2);
    
    mkString str4(_T("0123456789"));
    str4.clear();
    
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T(""));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("0123"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("01236789"));
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T(""));
}

TEST(mkString, swap)
{
    mkString str1(_T("0123456789"));
    mkString str2(_T("9876543210"));
    str1.swap(str2);
    
    EXPECT_TRUE(str1 == _T("9876543210"));
    EXPECT_TRUE(str2 == _T("0123456789"));
}

TEST(mkString, reserve)
{
    mkString str1(_T("0123456789"));
    str1.reserve();auto cap1 = str1.capacity();
    str1.reserve(1024);auto cap2 = str1.capacity();
    
    MK_PRINT("%d", cap1);EXPECT_TRUE(cap1 >= 10);
    MK_PRINT("%d", cap2);EXPECT_TRUE(cap2 >= 1024);
}

TEST(mkString, copy)
{
    mkString str(_T("0123456789"));
    mkChar dest[10];
    memset(dest, '\0', sizeof(mkChar)*10);
    
    str.copy(dest, 6);
    MK_PRINT(dest);EXPECT_TRUE(mkString(dest) == _T("012345"));
    
    str.copy(dest, 2, 4);
    MK_PRINT(dest);EXPECT_TRUE(mkString(dest) == _T("452345"));
}

TEST(mkString, resize)
{
    mkString str(_T("0123456789"));
    
    str.resize(8);
    MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("01234567"));
    
    str.resize(10, _T('X'));
    MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("01234567XX"));
}

TEST(mkString, find)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.find(_T("345"));
    auto pos1_b = str.find(_T("345"), 2);
    
    auto pos2_a = str.find(_T('7'));
    auto pos2_b = str.find(_T('7'), 3);
    
    auto pos3_a = str.find(temp);
    auto pos3_b = str.find(temp, 2);
    
    auto pos4 = str.find(_T("345"), 1 , 2);
    

#ifdef __WINDOWS__
    auto pos5_a = str.find(mkStringHelper::conv("345").get());
    auto pos5_b = str.find(mkStringHelper::conv("345").get(), 2);
    auto pos6 = str.find(mkStringHelper::conv("345").get(), 1 , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 3);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == 3);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 7);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 7);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 3);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 3);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 3);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 3);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 3);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 3);
#endif
}

TEST(mkString, rfind)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.rfind(_T("345"));
    auto pos1_b = str.rfind(_T("345"), 2);
    
    auto pos2_a = str.rfind(_T('7'));
    auto pos2_b = str.rfind(_T('7'), 8);
    
    auto pos3_a = str.rfind(temp);
    auto pos3_b = str.rfind(temp, mkString::npos);
    
    auto pos4 = str.rfind(_T("345"), mkString::npos , 1);
    

#ifdef __WINDOWS__
    auto pos5_a = str.rfind(mkStringHelper::conv("345").get());
    auto pos5_b = str.rfind(mkStringHelper::conv("345").get(), mkString::npos);
    auto pos6 = str.rfind(mkStringHelper::conv("345").get(), mkString::npos , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 3);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == -1);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 7);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 7);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 3);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 3);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 3);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 3);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 3);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 3);
#endif
}


TEST(mkString, findFirstOf)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.find_first_of(_T("345"));
    auto pos1_b = str.find_first_of(_T("345"), 2);
    
    auto pos2_a = str.find_first_of(_T('7'));
    auto pos2_b = str.find_first_of(_T('7'), 3);
    
    auto pos3_a = str.find_first_of(temp);
    auto pos3_b = str.find_first_of(temp, 2);
    
    auto pos4 = str.find_first_of(_T("345"), 1 , 2);
    

#ifdef __WINDOWS__
    auto pos5_a = str.find_first_of(mkStringHelper::conv("345").get());
    auto pos5_b = str.find_first_of(mkStringHelper::conv("345").get(), 2);
    auto pos6 = str.find_first_of(mkStringHelper::conv("345").get(), 1 , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 3);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == 3);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 7);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 7);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 3);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 3);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 3);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 3);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 3);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 3);
#endif
}

TEST(mkString, findLastOf)//与 String 版本的返回结果的含义不同,这里返回最后一个字符位置,String 是返回第一个字符位置
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.find_last_of(_T("345"));
    auto pos1_b = str.find_last_of(_T("345"), mkString::npos);
    
    auto pos2_a = str.find_last_of(_T('7'));
    auto pos2_b = str.find_last_of(_T('7'), mkString::npos);
    
    auto pos3_a = str.find_last_of(temp);
    auto pos3_b = str.find_last_of(temp, mkString::npos);
    
    auto pos4 = str.find_last_of(_T("345"), mkString::npos , 2);
    

#ifdef __WINDOWS__
    auto pos5_a = str.find_last_of(mkStringHelper::conv("345").get());
    auto pos5_b = str.find_last_of(mkStringHelper::conv("345").get(), mkString::npos);
    auto pos6 = str.find_last_of(mkStringHelper::conv("345").get(), mkString::npos , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 5);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == 5);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 7);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 7);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 5);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 5);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 4);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 5);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 5);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 4);
#endif
}

TEST(mkString, findFirstNotOf)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.find_first_not_of(_T("345"));
    auto pos1_b = str.find_first_not_of(_T("345"), 2);
    
    auto pos2_a = str.find_first_not_of(_T('7'));
    auto pos2_b = str.find_first_not_of(_T('7'), 3);
    
    auto pos3_a = str.find_first_not_of(temp);
    auto pos3_b = str.find_first_not_of(temp, 2);
    
    auto pos4 = str.find_first_not_of(_T("345"), 1 , 2);
    

#ifdef __WINDOWS__
    auto pos5_a = str.find_first_not_of(mkStringHelper::conv("345").get());
    auto pos5_b = str.find_first_not_of(mkStringHelper::conv("345").get(), 2);
    auto pos6 = str.find_first_not_of(mkStringHelper::conv("345").get(), 1 , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 0);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == 2);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 0);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 3);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 0);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 2);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 1);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 0);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 2);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 1);
#endif
}

TEST(mkString, findLastNotOf)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("345"));
    
    auto pos1_a = str.find_last_not_of(_T("345"));
    auto pos1_b = str.find_last_not_of(_T("345"), mkString::npos);
    
    auto pos2_a = str.find_last_not_of(_T('7'));
    auto pos2_b = str.find_last_not_of(_T('7'), mkString::npos);
    
    auto pos3_a = str.find_last_not_of(temp);
    auto pos3_b = str.find_last_not_of(temp, mkString::npos);
    
    auto pos4 = str.find_last_not_of(_T("345"), mkString::npos , 2);
    

#ifdef __WINDOWS__
    auto pos5_a = str.find_last_not_of(mkStringHelper::conv("345").get());
    auto pos5_b = str.find_last_not_of(mkStringHelper::conv("345").get(), mkString::npos);
    auto pos6 = str.find_last_not_of(mkStringHelper::conv("345").get(), mkString::npos , 2);
#endif

    MK_PRINT("%lld", pos1_a);EXPECT_TRUE(pos1_a == 9);
    MK_PRINT("%lld", pos1_b);EXPECT_TRUE(pos1_b == 9);
    MK_PRINT("%lld", pos2_a);EXPECT_TRUE(pos2_a == 9);
    MK_PRINT("%lld", pos2_b);EXPECT_TRUE(pos2_b == 9);
    MK_PRINT("%lld", pos3_a);EXPECT_TRUE(pos3_a == 9);
    MK_PRINT("%lld", pos3_b);EXPECT_TRUE(pos3_b == 9);
    MK_PRINT("%lld", pos4);EXPECT_TRUE(pos4 == 9);
#ifdef __WINDOWS__
    MK_PRINT("%lld", pos5_a);EXPECT_TRUE(pos5_a == 9);
    MK_PRINT("%lld", pos5_b);EXPECT_TRUE(pos5_b == 9);
    MK_PRINT("%lld", pos6);EXPECT_TRUE(pos6 == 9);
#endif
}

TEST(mkString, findAny)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("479"));
    
    auto pos1 = mkStringHelper::findAny(str, temp);
    auto pos2 = mkStringHelper::findAny(str, 2, temp);
    
    MK_PRINT("%lld", pos1);EXPECT_TRUE(pos1 == 4);
    MK_PRINT("%lld", pos2);EXPECT_TRUE(pos2 == 4);
}

TEST(mkString, findLastOfAny)
{
    mkString str(_T("0123456789"));
    mkString temp(_T("479"));
    
    auto pos1 = mkStringHelper::findLastOfAny(str, temp);
    auto pos2 = mkStringHelper::findLastOfAny(str, 8, temp);
    
    MK_PRINT("%lld", pos1);EXPECT_TRUE(pos1 == 9);
    MK_PRINT("%lld", pos2);EXPECT_TRUE(pos2 == 7);
}

TEST(mkString, subString)
{
    mkString str(_T("0123456789"));
    auto sub1 = str.substr();
    auto sub2 = str.substr(6);
    auto sub3 = str.substr(1, 3);
    
    MK_PRINT(sub1.c_str());EXPECT_TRUE(sub1 == _T("0123456789"));
    MK_PRINT(sub2.c_str());EXPECT_TRUE(sub2 == _T("6789"));
    MK_PRINT(sub3.c_str());EXPECT_TRUE(sub3 == _T("123"));
}

TEST(mkString, compare)//与 String 版本的返回值不同:会返回pos,而不仅限于 1 0 -1
{
    mkString str(_T("0123456789"));
    mkString dest(_T("01234"));
    
    auto com1 = str.compare(dest);
    auto com2 = str.compare(0, 5, dest);
    auto com3 = str.compare(0, 4, dest, 0, 4);
    auto com4 = str.compare(_T("0123456789ABC"));
    //auto com5 = str.compare(_T("01234567890ABC"), 10);//不支持,可用3参数版本代替
    auto com6 = str.compare(0, 3, _T("012"));
    auto com7 = str.compare(0, 2, _T("0123"), 2);
    
    MK_PRINT("%d", com1);EXPECT_TRUE(com1 > 0);
    MK_PRINT("%d", com2);EXPECT_TRUE(com2 == 0);
    MK_PRINT("%d", com3);EXPECT_TRUE(com3 == 0);
    MK_PRINT("%d", com4);EXPECT_TRUE(com4 < 0);
    //MK_PRINT("%d", com5);EXPECT_TRUE(com5 == 0);
    MK_PRINT("%d", com6);EXPECT_TRUE(com6 == 0);
    MK_PRINT("%d", com7);EXPECT_TRUE(com7 == 0);
}

TEST(mkString, compareIgnoreCase)
{
    mkString str(_T("ABCDefg"));
    mkString dest(_T("abc"));
    auto com1 = mkStringHelper::compareIgnoreCase(str, dest);
    auto com2 = mkStringHelper::compareIgnoreCase(str, 0, 3, dest);
    auto com3 = mkStringHelper::compareIgnoreCase(str, 0, 2, dest, 0, 2);
    auto com4 = mkStringHelper::compareIgnoreCase(str, _T("abcdefg12345"));
    auto com5 = mkStringHelper::compareIgnoreCase(str, 0, 3, _T("abc"));
    auto com6 = mkStringHelper::compareIgnoreCase(str, 0, 2, _T("abc"), 2);
    
    MK_PRINT("%d", com1);EXPECT_TRUE(com1 == 1);
    MK_PRINT("%d", com2);EXPECT_TRUE(com2 == 0);
    MK_PRINT("%d", com3);EXPECT_TRUE(com3 == 0);
    MK_PRINT("%d", com4);EXPECT_TRUE(com4 == -1);
    MK_PRINT("%d", com5);EXPECT_TRUE(com5 == 0);
    MK_PRINT("%d", com6);EXPECT_TRUE(com6 == 0);
}

TEST(mkString, replace)
{
    mkString str(_T("abcdefgabc"));
    mkChar oldChar(_T('a'));
    mkChar newChar(_T('1'));
    mkString dest(_T("123456"));
    
    auto str1 = mkStringHelper::replace(str, oldChar, newChar);
    auto str2 = mkStringHelper::replace(str, oldChar, newChar, true);
    auto str3 = str.replace(0, 8, dest);
    auto str4 = str.replace(0, 8, dest, 0, 3);
    auto str5 = str.replace(0, 8, _T("AAAAAA"), 3);
    auto str6 = str.replace(0, 8, _T("BBBBBB"));
    auto str7 = str.replace(0, 8, 6, _T('C'));
    
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("1bcdefgabc"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("1bcdefg1bc"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("123456bc"));
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T("123"));
    MK_PRINT(str5.c_str());EXPECT_TRUE(str5 == _T("AAA"));
    MK_PRINT(str6.c_str());EXPECT_TRUE(str6 == _T("BBBBBB"));
    MK_PRINT(str7.c_str());EXPECT_TRUE(str7 == _T("CCCCCC"));
}

TEST(mkString, insert)
{
    mkString str(_T("0123456789"));
    mkString dest(_T("01234"));
    
    auto ret1 = str.insert(1, dest);
    auto ret2 = str.insert(2, dest, 0, 4);
    auto ret3 = str.insert(3, _T("aaa"), 2);
    auto ret4 = str.insert(4, _T("bbbb"));
    auto ret5 = str.insert(5, 3, _T('c'));//与 String 版本的形参顺序不同
#ifdef __WINDOWS__
    auto ret6 = str.insert(3, mkStringHelper::conv("xxx").get(), 2);
    auto ret7 = str.insert(4, mkStringHelper::conv("yyyy").get());
#endif
    
    MK_PRINT(ret1.c_str());EXPECT_TRUE(ret1 == _T("001234123456789"));
    MK_PRINT(ret2.c_str());EXPECT_TRUE(ret2 == _T("0001231234123456789"));
    MK_PRINT(ret3.c_str());EXPECT_TRUE(ret3 == _T("000aa1231234123456789"));
    MK_PRINT(ret4.c_str());EXPECT_TRUE(ret4 == _T("000abbbba1231234123456789"));
    MK_PRINT(ret5.c_str());EXPECT_TRUE(ret5 == _T("000abcccbbba1231234123456789"));
#ifdef __WINDOWS__
    MK_PRINT(ret6.c_str());EXPECT_TRUE(ret6 == _T("000xxabcccbbba1231234123456789"));
    MK_PRINT(ret7.c_str());EXPECT_TRUE(ret7 == _T("000xyyyyxabcccbbba1231234123456789"));
#endif
}

TEST(mkString, toUpper)
{
    mkString str(_T("abcd1234ABCD"));
    mkStringHelper::toUpper(str);
    
    MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("ABCD1234ABCD"));
}

TEST(mkString, toLower)
{
    mkString str(_T("abcd1234ABCD"));
    mkStringHelper::toLower(str);
    
    MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("abcd1234abcd"));
}

TEST(mkString, trim)
{
    mkString str(_T(" abcd1234ABCD_"));
    auto str1 = mkStringHelper::trim(str);
    auto str2 = mkStringHelper::trim(str, _T('_'));
    
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("abcd1234ABCD_"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T(" abcd1234ABCD"));
}

TEST(mkString, leftString)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::leftString(str, 4);
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("0123"));
}

TEST(mkString, rightString)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::rightString(str, 4);
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("6789"));
}

TEST(mkString, beforeFirst)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::beforeFirst(str, _T('4'));
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("0123"));
}

TEST(mkString, beforeLast)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::beforeLast(str, _T('4'));
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("0123"));
}

TEST(mkString, afterFirst)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::afterFirst(str, _T('4'));
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("56789"));
}

TEST(mkString, afterLast)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::afterLast(str, _T('4'));
    
    MK_PRINT(dest.c_str());EXPECT_TRUE(dest == _T("56789"));
}

TEST(mkString, startsWith)
{
    mkString str(_T("0123456789"));
    mkString prefix(_T("01234"));
    
    auto dest1 = mkStringHelper::startsWith(str, prefix);
    auto dest2 = mkStringHelper::startsWith(str, _T("123"));
    
#ifdef __WINDOWS__
    auto dest3 = mkStringHelper::startsWith(str, mkStringHelper::conv("456").get());
#endif

    MK_PRINT("%d", dest1);EXPECT_TRUE(dest1 == true);
    MK_PRINT("%d", dest2);EXPECT_TRUE(dest2 == false);
#ifdef __WINDOWS__
    MK_PRINT("%d", dest3);EXPECT_TRUE(dest3 == false);
#endif
}

TEST(mkString, shrink)
{
    mkString str(_T("0123456789"));
    str.reserve(1024);
    auto dest1 = str.capacity();
    
    str.shrink_to_fit();
    auto dest2 = str.capacity();
    
    MK_PRINT("%d", dest1);EXPECT_TRUE(dest1 >= 1024);
    MK_PRINT("%d", dest2);EXPECT_TRUE(dest2 < 1024);
}

TEST(mkString, freq)
{
    mkString str(_T("0123456789"));
    auto dest = mkStringHelper::freq(str, _T('4'));
    
    MK_PRINT("%d", dest);EXPECT_TRUE(dest == 1);
}

TEST(mkString, split)
{
    mkString str(_T("0123xy456789"));
    
    mkString separators1(_T("mxn"));
    std::vector<mkString> substrs1;
    mkStringHelper::splitAny(str, separators1, substrs1);
    
    mkString separators2(_T("xy"));
    std::vector<mkString> substrs2;
    mkStringHelper::split(str, separators2, substrs2);
    
    mkChar separator(_T('y'));
    std::vector<mkString> substrs3;
    mkStringHelper::split(str, separator, substrs3);
    
    MK_PRINT(substrs1[0].c_str());EXPECT_TRUE(substrs1[0] == _T("0123"));
    MK_PRINT(substrs1[1].c_str());EXPECT_TRUE(substrs1[1] == _T("y456789"));
    
    MK_PRINT(substrs2[0].c_str());EXPECT_TRUE(substrs2[0] == _T("0123"));
    MK_PRINT(substrs2[1].c_str());EXPECT_TRUE(substrs2[1] == _T("456789"));
    
    MK_PRINT(substrs3[0].c_str());EXPECT_TRUE(substrs3[0] == _T("0123x"));
    MK_PRINT(substrs3[1].c_str());EXPECT_TRUE(substrs3[1] == _T("456789"));
}

TEST(mkString, operator1)
{
    mkString str(_T("0123456789"));
    mkString dest;
    
    auto str1 = dest = str;
    auto str2 = dest = std::move(str);
    auto str3 = dest = _T("ABCD");
    auto str4 = dest = _T('C');
    
#ifdef __WINDOWS__
    auto str5 = dest = mkStringHelper::conv("abcd").get();
#endif
    
    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("0123456789"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("0123456789"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("ABCD"));
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T("C"));
#ifdef __WINDOWS__
    MK_PRINT(str5.c_str());EXPECT_TRUE(str5 == _T("abcd"));
#endif
}

//operator +=
TEST(mkString, operator2)
{
    mkString str(_T("0123456789"));
    mkString dest;
    
    auto str1 = dest += str;
    auto str2 = dest += _T("AAA");
    auto str3 = dest += _T('C');
    
#ifdef __WINDOWS__
    auto str4 = dest += mkStringHelper::conv("aaa").get();;
#endif

    MK_PRINT(str1.c_str());EXPECT_TRUE(str1 == _T("0123456789"));
    MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("0123456789AAA"));
    MK_PRINT(str3.c_str());EXPECT_TRUE(str3 == _T("0123456789AAAC"));
#ifdef __WINDOWS__
    MK_PRINT(str4.c_str());EXPECT_TRUE(str4 == _T("0123456789AAACaaa"));
#endif
}

//operator []
TEST(mkString, operator3)
{
    const mkString str1(_T("0123456789"));
    auto ret1 = str1[0];
    
    mkString str2(_T("0123456789"));
    str2[0] = _T('X');
    
    EXPECT_TRUE(str1[0] == _T('0'));
    EXPECT_TRUE(str2[0] == _T('X'));
}

TEST(mkString, operator4)
{
    mkString str;
    mkString dest(_T("dest"));
    
    //mkString::operator << 不支持,使用append替代
    str.append(mkStringHelper::toString(bool(true)))
        .append(mkStringHelper::toString(int(-1024)))
        .append(mkStringHelper::toString((unsigned int)(1024)))
        .append(mkStringHelper::toString(int64(-2048)))
        .append(mkStringHelper::toString(uint64(2048)))
        .append(mkStringHelper::toString(float(1.2)))
        .append(mkStringHelper::toString(double(2.4)))
        .append(dest)
        .append(_T("ABCDEF"))
        .append(1, _T('Z'))
    #ifdef __WINDOWS__
        .append(mkStringHelper::conv("abcdef").get())
    #endif
        ;
        
    #ifdef __WINDOWS__
        MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("True-10241024-204820481.2000002.400000destABCDEFZabcdef"));
    #else
        MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("True-10241024-204820481.2000002.400000destABCDEFZ"));
    #endif
}

TEST(mkString, format)
{
    mkString str;
    str = mkStringHelper::format(_T("12345"));
    str = mkStringHelper::format(_T("12345%d_%s"), 678, _T("xy"));
    
#ifdef __WINDOWS__
    str = mkStringHelper::format("12345");
    str = mkStringHelper::format("12345%d_%s", 678, "xy");
#endif
    
    MK_PRINT(str.c_str());EXPECT_TRUE(str == _T("12345678_xy"));
}

TEST(mkString, formatv)
{
    //内部使用,暂不支持
}

TEST(mkString, toString)
{
    auto ret0 = mkStringHelper::toString(static_cast<bool>(1));
    auto ret1 = mkStringHelper::toString(static_cast<short>(-2));
    auto ret2 = mkStringHelper::toString(static_cast<unsigned short>(3));
    auto ret3 = mkStringHelper::toString(static_cast<int>(-4));
    auto ret4 = mkStringHelper::toString(static_cast<unsigned int>(5));
    auto ret5 = mkStringHelper::toString(static_cast<int64>(-6));
    auto ret6 = mkStringHelper::toString(static_cast<uint64>(7));
    auto ret7 = mkStringHelper::toString(static_cast<float>(1.2));
    auto ret8 = mkStringHelper::toString(static_cast<double>(2.4));
    
    MK_PRINT(ret0.c_str());EXPECT_TRUE(ret0 == _T("True"));
    MK_PRINT(ret1.c_str());EXPECT_TRUE(ret1 == _T("-2"));
    MK_PRINT(ret2.c_str());EXPECT_TRUE(ret2 == _T("3"));
    MK_PRINT(ret3.c_str());EXPECT_TRUE(ret3 == _T("-4"));
    MK_PRINT(ret4.c_str());EXPECT_TRUE(ret4 == _T("5"));
    MK_PRINT(ret5.c_str());EXPECT_TRUE(ret5 == _T("-6"));
    MK_PRINT(ret6.c_str());EXPECT_TRUE(ret6 == _T("7"));
    MK_PRINT(ret7.c_str());EXPECT_TRUE(ret7 == _T("1.200000"));
    MK_PRINT(ret8.c_str());EXPECT_TRUE(ret8 == _T("2.400000"));
}

TEST(mkString, static)
{
    auto pos = mkString::npos;
    auto empty = mkStringHelper::EMPTY;
    
    MK_PRINT("%lld", pos);EXPECT_TRUE(pos == -1);
    MK_PRINT(empty.c_str());EXPECT_TRUE(empty.size() == 0);
}

TEST(mkString, global_functions)
{
    mkString str1(_T("ABCDEFGH"));
    mkString str2(_T("ABCDEFGH"));
    
    // == 
    bool ret0 = (str1 == str2);
    bool ret1 = (str1 == _T("ABCDE"));
    bool ret2 = (_T("ABCDE") == str1);

    // !=
    bool ret5 = (str1 != str2);
    bool ret6 = (str1 != _T("ABCDE"));
    bool ret7 = (_T("ABCDE") != str1);

    // <
    bool ret10 = (str1 < str2);
    bool ret11 = (str1 < _T("ABCDE"));
    bool ret12 = (_T("ABCDE") < str1);
    
    // >
    bool ret15 = (str1 > str2);
    bool ret16 = (str1 > _T("ABCDE"));
    bool ret17 = (_T("ABCDE") > str1);
    
    // <=
    bool ret20 = (str1 <= str2);
    bool ret21 = (str1 <= _T("ABCDE"));
    bool ret22 = (_T("ABCDE") <= str1);
    
    // >=
    bool ret25 = (str1 >= str2);
    bool ret26 = (str1 >= _T("ABCDE"));
    bool ret27 = (_T("ABCDE") >= str1);
    
    // +
    mkString ret30 = (str1 + str2);
    mkString ret31 = (str1 + _T('x'));
    mkString ret32 = (_T('y') + str1);
    mkString ret33 = (str1 + _T("ABCDE"));
    mkString ret34 = (_T("ABCDE") + str1);

#ifdef __WINDOWS__
    bool ret8 = (str1 != mkStringHelper::conv("ABCDE").get());
    bool ret9  = (mkStringHelper::conv("ABCDE").get() != str1);

    bool ret3 = (str1 == mkStringHelper::conv("ABCDE").get());
    bool ret4 = (mkStringHelper::conv("ABCDE").get() == str1);

    bool ret13 = (str1 < mkStringHelper::conv("ABCDE").get());
    bool ret14  = (mkStringHelper::conv("ABCDE").get() < str1);

    bool ret18 = (str1 > mkStringHelper::conv("ABCDE").get());
    bool ret19  = (mkStringHelper::conv("ABCDE").get() > str1);

    bool ret23 = (str1 <= mkStringHelper::conv("ABCDE").get());
    bool ret24  = (mkStringHelper::conv("ABCDE").get() <= str1);

    bool ret28 = (str1 >= mkStringHelper::conv("ABCDE").get());
    bool ret29  = (mkStringHelper::conv("ABCDE").get() >= str1);

    mkString ret35 = (str1 + mkStringHelper::conv("ABCDE").get());
    mkString ret36  = (mkStringHelper::conv("ABCDE").get() + str1);
#endif

    
    MK_PRINT("%d", ret0);EXPECT_TRUE(ret0 == true);
    MK_PRINT("%d", ret1);EXPECT_TRUE(ret1 == false);
    MK_PRINT("%d", ret2);EXPECT_TRUE(ret2 == false);
    MK_PRINT("%d", ret5);EXPECT_TRUE(ret5 == false);
    MK_PRINT("%d", ret6);EXPECT_TRUE(ret6 == true);
    MK_PRINT("%d", ret7);EXPECT_TRUE(ret7 == true);
    MK_PRINT("%d", ret10);EXPECT_TRUE(ret10 == false);
    MK_PRINT("%d", ret11);EXPECT_TRUE(ret11 == false);
    MK_PRINT("%d", ret12);EXPECT_TRUE(ret12 == true);
    MK_PRINT("%d", ret15);EXPECT_TRUE(ret15 == false);
    MK_PRINT("%d", ret16);EXPECT_TRUE(ret16 == true);
    MK_PRINT("%d", ret17);EXPECT_TRUE(ret17 == false);
    MK_PRINT("%d", ret20);EXPECT_TRUE(ret20 == true);
    MK_PRINT("%d", ret21);EXPECT_TRUE(ret21 == false);
    MK_PRINT("%d", ret22);EXPECT_TRUE(ret22 == true);
    MK_PRINT("%d", ret25);EXPECT_TRUE(ret25 == true);
    MK_PRINT("%d", ret26);EXPECT_TRUE(ret26 == true);
    MK_PRINT("%d", ret27);EXPECT_TRUE(ret27 == false);
    MK_PRINT(ret30.c_str());EXPECT_TRUE(ret30 == _T("ABCDEFGHABCDEFGH"));
    MK_PRINT(ret31.c_str());EXPECT_TRUE(ret31 == _T("ABCDEFGHx"));
    MK_PRINT(ret32.c_str());EXPECT_TRUE(ret32 == _T("yABCDEFGH"));
    MK_PRINT(ret33.c_str());EXPECT_TRUE(ret33 == _T("ABCDEFGHABCDE"));
    MK_PRINT(ret34.c_str());EXPECT_TRUE(ret34 == _T("ABCDEABCDEFGH"));
}