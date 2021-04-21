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
#include "_STR_.h"

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
    
    mkString str5_a(4, _T('a'));//形参顺序不同
    mkString str5_b(4, _T('b'), alloc);//形参顺序不同
    
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
    //MK_PRINT(str2.c_str());EXPECT_TRUE(str2 == _T("str2"));
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
    mkString str4;str4.assign(5, _T('a'));//形参顺序不同
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
    dest.append(3, _T('a'));mkString str4 = dest;//形参顺序不同
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
    mkString str2(T_CHAR_STR);
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
    memset(dest, '\0', 10);
    
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
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.find(_T("ABC"));
    auto pos1_b = str.find(_T("ABC"), 0);

#ifdef __WINDOWS__
    auto pos2_a = str.find(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.find(mkStringHelper::conv("ABC").get(), 0);
#endif
    
    auto pos3_a = str.find(_T('A'));
    auto pos3_b = str.find(_T('A'), 0);
    
    auto pos4_a = str.find(temp);
    auto pos4_b = str.find(temp, 0);
    
    auto pos5 = str.find(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.find(mkStringHelper::conv("ABC").get(), 0, 4);
#endif
}

TEST(mkString, rfind)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.rfind(_T("ABC"));
    auto pos1_b = str.rfind(_T("ABC"), mkString::npos);

#ifdef __WINDOWS__
    auto pos2_a = str.rfind(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.rfind(mkStringHelper::conv("ABC").get(), mkString::npos);
#endif
    
    auto pos3_a = str.rfind(_T('A'));
    auto pos3_b = str.rfind(_T('A'), mkString::npos);
    
    auto pos4_a = str.rfind(temp);
    auto pos4_b = str.rfind(temp, mkString::npos);
    
    auto pos5 = str.rfind(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.rfind(mkStringHelper::conv("ABC").get(), 0 , 4);
#endif
}


TEST(mkString, findFirstOf)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.find_first_of(_T("ABC"));
    auto pos1_b = str.find_first_of(_T("ABC"), 0);

#ifdef __WINDOWS__
    auto pos2_a = str.find_first_of(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.find_first_of(mkStringHelper::conv("ABC").get(), 0);
#endif
    
    auto pos3_a = str.find_first_of(_T('A'));
    auto pos3_b = str.find_first_of(_T('A'), 0);
    
    auto pos4_a = str.find_first_of(temp);
    auto pos4_b = str.find_first_of(temp, 0);
    
    auto pos5 = str.find_first_of(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.find_first_of(mkStringHelper::conv("ABC").get(), 0 , 4);
#endif
}

TEST(mkString, findLastOf)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.find_last_of(_T("ABC"));
    auto pos1_b = str.find_last_of(_T("ABC"), 0);

#ifdef __WINDOWS__
    auto pos2_a = str.find_last_of(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.find_last_of(mkStringHelper::conv("ABC").get(), 0);
#endif
    
    auto pos3_a = str.find_last_of(_T('A'));
    auto pos3_b = str.find_last_of(_T('A'), 0);
    
    auto pos4_a = str.find_last_of(temp);
    auto pos4_b = str.find_last_of(temp, 0);
    
    auto pos5 = str.find_last_of(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.find_last_of(mkStringHelper::conv("ABC").get(), 0 , 4);
#endif
}

TEST(mkString, findFirstNotOf)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.find_first_not_of(_T("ABC"));
    auto pos1_b = str.find_first_not_of(_T("ABC"), 0);

#ifdef __WINDOWS__
    auto pos2_a = str.find_first_not_of(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.find_first_not_of(mkStringHelper::conv("ABC").get(), 0);
#endif
    
    auto pos3_a = str.find_first_not_of(_T('A'));
    auto pos3_b = str.find_first_not_of(_T('A'), 0);
    
    auto pos4_a = str.find_first_not_of(temp);
    auto pos4_b = str.find_first_not_of(temp, 0);
    
    auto pos5 = str.find_first_not_of(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.find_first_not_of(mkStringHelper::conv("ABC").get(), 0 , 4);
#endif
}

TEST(mkString, findLastNotOf)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1_a = str.find_last_not_of(_T("ABC"));
    auto pos1_b = str.find_last_not_of(_T("ABC"), 0);

#ifdef __WINDOWS__
    auto pos2_a = str.find_last_not_of(mkStringHelper::conv("ABC").get());
    auto pos2_b = str.find_last_not_of(mkStringHelper::conv("ABC").get(), 0);
#endif
    
    auto pos3_a = str.find_last_not_of(_T('A'));
    auto pos3_b = str.find_last_not_of(_T('A'), 0);
    
    auto pos4_a = str.find_last_not_of(temp);
    auto pos4_b = str.find_last_not_of(temp, 0);
    
    auto pos5 = str.find_last_not_of(_T("ABC"), 0 , 4);
    
#ifdef __WINDOWS__
    auto pos6 = str.find_last_not_of(mkStringHelper::conv("ABC").get(), 0 , 4);
#endif
}

TEST(mkString, findAny)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1 = mkStringHelper::findAny(str, temp);
    auto pos2 = mkStringHelper::findAny(str, 0, temp);
}

TEST(mkString, findLastOfAny)
{
    mkString str(T_CHAR_STR);
    mkString temp(_T("ABC"));
    
    auto pos1 = mkStringHelper::findLastOfAny(str, temp);
    auto pos2 = mkStringHelper::findLastOfAny(str, 0, temp);
}

TEST(mkString, subString)
{
    mkString str(T_CHAR_STR);
    auto sub1 = str.substr();
    auto sub2 = str.substr(0);
    auto sub3 = str.substr(0, 8);
}

TEST(mkString, compare)
{
    mkString str(T_CHAR_STR);
    mkString dest(_T("abc"));
    auto com1 = str.compare(dest);
    auto com2 = str.compare(0, 2, dest);
    auto com3 = str.compare(0, 2, dest, 0, 2);
    auto com4 = str.compare(_T("abc"));
    //auto com5 = str.compare(_T("abc"), 3); //不支持,可用3参数版本代替
    auto com6 = str.compare(0, 3, _T("abc"));
    auto com7 = str.compare(0, 2, _T("abc"), 2);
}

TEST(mkString, compareIgnoreCase)
{
    mkString str(T_CHAR_STR);
    mkString dest(_T("ABC"));
    auto com1 = mkStringHelper::compareIgnoreCase(str, dest);
    auto com2 = mkStringHelper::compareIgnoreCase(str, 0, 2, dest);
    auto com3 = mkStringHelper::compareIgnoreCase(str, 0, 2, dest, 0, 2);
    auto com4 = mkStringHelper::compareIgnoreCase(str, _T("abc"));
    auto com6 = mkStringHelper::compareIgnoreCase(str, 0, 3, _T("abc"));
    auto com7 = mkStringHelper::compareIgnoreCase(str, 0, 2, _T("abc"), 2);
}

TEST(mkString, replace)
{
    mkString str(T_CHAR_STR);
    mkChar oldChar(_T('a'));
    mkChar newChar(_T('1'));
    mkString dest(_T("123456"));
    
    mkStringHelper::replace(str, oldChar, newChar);
    mkStringHelper::replace(str, oldChar, newChar, true);
    
    str.replace(0, 8, dest)
    
        .replace(0, 8, dest, 0, 3)
    
        .replace(0, 8, _T("AAAAAA"), 3)
    
        .replace(0, 8, _T("BBBBBB"))
    
        .replace(0, 8, 6, _T('C'));
}

TEST(mkString, insert)
{
    mkString str(T_CHAR_STR);
    mkString dest(_T("123456"));
    
    str.insert(0, dest)
        
        .insert(0, dest, 0, 4)
        
        .insert(0, _T("AAAAAA"), 4)
        
        .insert(0, _T("AAAAAA"))
        
#ifdef __WINDOWS__
        .insert(0, mkStringHelper::conv("BBBBBB").get(), 4)
        .insert(0, mkStringHelper::conv("BBBBBB").get())
#endif
        
        .insert(0, _T('C'), 4);
}

TEST(mkString, toUpper)
{
    mkString str(T_CHAR_STR);
    mkStringHelper::toUpper(str);
}

TEST(mkString, toLower)
{
    mkString str(T_CHAR_STR);
    mkStringHelper::toLower(str);
}

TEST(mkString, trim)
{
    mkString str(T_CHAR_STR);
    auto ret = mkStringHelper::trim(str);
    //str.trim(_T('a'));//不支持
}

TEST(mkString, leftmkString)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::leftString(str, 8);
}

TEST(mkString, rightmkString)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::rightString(str, 8);
}

TEST(mkString, beforeFirst)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::beforeFirst(str, _T('Z'));
}

TEST(mkString, beforeLast)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::beforeLast(str, _T('Z'));
}

TEST(mkString, afterFirst)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::afterFirst(str, _T('Z'));
}

TEST(mkString, afterLast)
{
    mkString str(T_CHAR_STR);
    auto dest = mkStringHelper::afterLast(str, _T('Z'));
}

TEST(mkString, startsWith)
{
    mkString str(T_CHAR_STR);
    mkString prefix(_T("abc"));
    
    auto dest1 = mkStringHelper::startsWith(str, prefix);
    auto dest2 = mkStringHelper::startsWith(str, _T("abc"));
    
#ifdef __WINDOWS__
    auto dest3 = mkStringHelper::startsWith(str, mkStringHelper::conv("abc").get());
#endif
}

TEST(mkString, shrink)
{
    mkString str(T_CHAR_STR);
    str.shrink_to_fit();
}

TEST(mkString, freq)
{
    mkString str(T_CHAR_STR);
    auto ret = mkStringHelper::freq(str, _T('A'));
}

TEST(mkString, split)
{
    mkString str(T_CHAR_STR);
    mkString separators(_T("abc"));
    mkChar separator(_T('a'));
    std::vector<mkString> substrs;
    
    mkStringHelper::split(str, separators, substrs);
    //mkStringHelper::split(str, separators, substrs, true);//不支持
    
    mkStringHelper::split(str, separator, substrs);
}

TEST(mkString, operator1)
{
    mkString str(T_CHAR_STR);
    mkString dest;
    
    dest = str;
    dest = std::move(str);
    
    mkString str2;
    
#ifdef __WINDOWS__
    dest = mkStringHelper::conv("abcd").get();
#endif
    
    const mkChar* ptr2 = _T("ABCD");
    dest = ptr2;
    
    dest = _T('C');
}

//operator +=
TEST(mkString, operator2)
{
    mkString str(T_CHAR_STR);
    mkString dest;
    
    dest += str;
    dest += _T("AAA");
    
#ifdef __WINDOWS__
    dest += mkStringHelper::conv("aaa").get();;
#endif
    
    dest += _T('C');
}

//operator []
TEST(mkString, operator3)
{
    const mkString str1(T_CHAR_STR);
    auto ret1 = str1[0];
    
    mkString str2(T_CHAR_STR);
    str2[0] = _T('X');
}

TEST(mkString, operator4)
{
    mkString str;
    mkString dest(T_CHAR_STR);
    
    //mkString::operator << 不支持,使用append替代
    str.append(mkStringHelper::toString(int(true)))
        .append(mkStringHelper::toString(int(-1024)))
        .append(mkStringHelper::toString((unsigned int)(1024)))
        .append(mkStringHelper::toString(int64(-2048)))
        .append(mkStringHelper::toString(uint64(2048)))
        .append(mkStringHelper::toString(float(1.2)))
        .append(mkStringHelper::toString(double(2.4)))
        .append(dest);
}

TEST(mkString, format)
{
    mkString str = mkStringHelper::format(_T("12345"));
    str = mkStringHelper::format(_T("12345%d"), 678);
    
#ifdef __WINDOWS__
    str = mkStringHelper::format("12345");
    str = mkStringHelper::format("12345%d", 678);
#endif
}

TEST(mkString, formatv)
{
    //todo
}

TEST(mkString, toString)
{
    auto ret0 = mkStringHelper::toString(static_cast<bool>(1));
    auto ret1 = mkStringHelper::toString(static_cast<short>(1));
    auto ret2 = mkStringHelper::toString(static_cast<unsigned short>(1));
    auto ret3 = mkStringHelper::toString(static_cast<int>(1));
    auto ret4 = mkStringHelper::toString(static_cast<unsigned int>(1));
    auto ret5 = mkStringHelper::toString(static_cast<int64>(1));
    auto ret6 = mkStringHelper::toString(static_cast<uint64>(1));
    auto ret7 = mkStringHelper::toString(static_cast<float>(1.2));
    auto ret8 = mkStringHelper::toString(static_cast<double>(1.2));
}

TEST(mkString, static)
{
    auto pos = mkString::npos;
    auto empty = mkStringHelper::EMPTY;
}

TEST(mkString, global_functions)
{
    mkString str1(T_CHAR_STR);
    mkString str2(T_CHAR_STR);
    
    // == 
    bool ret0 = (str1 == str2);
    bool ret1 = (str1 == _T("ABCDE"));
    bool ret2 = (_T("ABCDE") == str1);
    
#ifdef __WINDOWS__
    bool ret3 = (str1 == mkStringHelper::conv("ABCDE").get());
    bool ret4 = (mkStringHelper::conv("ABCDE").get() == str1);
#endif
    
    // !=
    bool ret5 = (str1 != str2);
    bool ret6 = (str1 != _T("ABCDE"));
    bool ret7 = (_T("ABCDE") != str1);
    
#ifdef __WINDOWS__
    bool ret8 = (str1 != mkStringHelper::conv("ABCDE").get());
    bool ret9  = (mkStringHelper::conv("ABCDE").get() != str1);
#endif
    
    // <
    bool ret10 = (str1 < str2);
    bool ret11 = (str1 < _T("ABCDE"));
    bool ret12 = (_T("ABCDE") < str1);
    
#ifdef __WINDOWS__
    bool ret13 = (str1 < mkStringHelper::conv("ABCDE").get());
    bool ret14  = (mkStringHelper::conv("ABCDE").get() < str1);
#endif
    
    // >
    bool ret15 = (str1 > str2);
    bool ret16 = (str1 > _T("ABCDE"));
    bool ret17 = (_T("ABCDE") > str1);
    
#ifdef __WINDOWS__
    bool ret18 = (str1 > mkStringHelper::conv("ABCDE").get());
    bool ret19  = (mkStringHelper::conv("ABCDE").get() > str1);
#endif
    
    // <=
    bool ret20 = (str1 <= str2);
    bool ret21 = (str1 <= _T("ABCDE"));
    bool ret22 = (_T("ABCDE") <= str1);
    
#ifdef __WINDOWS__
    bool ret23 = (str1 <= mkStringHelper::conv("ABCDE").get());
    bool ret24  = (mkStringHelper::conv("ABCDE").get() <= str1);
#endif
    
    // >=
    bool ret25 = (str1 >= str2);
    bool ret26 = (str1 >= _T("ABCDE"));
    bool ret27 = (_T("ABCDE") >= str1);
    
#ifdef __WINDOWS__
    bool ret28 = (str1 >= mkStringHelper::conv("ABCDE").get());
    bool ret29  = (mkStringHelper::conv("ABCDE").get() >= str1);
#endif
    
    // +
    mkString ret30 = (str1 + str2);
    mkString ret31 = (str1 + _T('x'));
    mkString ret32 = (_T('y') + str1);
    mkString ret33 = (str1 + _T("ABCDE"));
    mkString ret34 = (_T("ABCDE") + str1);
#ifdef __WINDOWS__
    mkString ret35 = (str1 + mkStringHelper::conv("ABCDE").get());
    mkString ret36  = (mkStringHelper::conv("ABCDE").get() + str1);
#endif
}