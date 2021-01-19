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

Time:2018-8

info:

***************************************************************************************************/

#ifndef __mkString
#define __mkString

#include "string/mkStringView.h"

using mk_char_traits = std::char_traits<mk_char>;
using mk_char_string = std::basic_string<mk_char>;
/*
using mk_char_string_view = std::basic_string_view<mk_char>;
*/

#ifdef __WINDOWS__
// Return the Unicode string of @ptr.
// return the Unicode string buffer, the caller should release it.
inline mk_char* 
getUnicodeString(const char* ptr, size_t num, size_t* outLen)
{
    //todo
    return nullptr;
}

#endif

class MK_DLL_EXPORT mkString
{
///构造
public:
    mkString();
    mkString(mkString&& source);
#ifdef __WINDOWS__
    mkString(const char* ptr);
    mkString(const char *ptr, size_t count);
#endif
    mkString(const mk_char* ptr);
    mkString(const mk_char* ptr, size_t count);
    mkString(const mkString& source);
    mkString(const mkString& source, size_t offset, size_t count = mkString::npos);
    mkString (mk_char ch, size_t count);

///析构
public:
    ~mkString();
    
///赋值
public:
    //operator=
    mkString& operator= (mkString&& source);
#ifdef __WINDOWS__
    mkString& operator= (const char* ptr);
#endif
    mkString& operator= (const mk_char* ptr);
    mkString& operator= (const mkString& source);
    mkString& operator= (mk_char ch);
    
    ///assign
    mkString& assign(mkString&& source);
#ifdef __WINDOWS__
    mkString& assign(const char* ptr);
    mkString& assign(const char* ptr, size_t num);
#endif
    mkString& assign(const mk_char* ptr);
    mkString& assign(const mk_char* ptr, size_t num);
    mkString& assign(const mkString& source);
    mkString& assign(const mkString& source, size_t offset, size_t count);
    mkString& assign(mk_char ch, size_t count);
    
///元素访问
public:
    mk_char& at(size_t n);
    mk_char  at(size_t n) const;
    mk_char& operator[] (size_t n);
    mk_char  operator[] (size_t n) const;
    //front()
    //back()
    //data()
    const mk_char* c_str() const;
    const mk_char* getCStr() const;
    operator mkStringView () const;
    operator const mk_char_string& () const;
    
    ///迭代器
    //begin()
    //end
    //cbegin
    //cend
    //rbegin
    //rend
    
    ///容量
    //empty()
    //size()
    //length()
    //max_size()
    //reserve()
    //capacity()
    //shrink_to_fit()
    bool isEmpty () const;
    size_t getLength() const;
    size_t getCapacity() const;
    size_t getMaxSize() const;
    void reserve (size_t newSiz = 0);
    void shrink (void);
    
///操作
public:
    void clear (void);
#ifdef __WINDOWS__
    mkString& insert (size_t offset, const char* ptr);
    mkString& insert (size_t offset, const char* ptr, size_t count);
#endif
    mkString& insert (size_t offset, const mk_char *ptr);
    mkString& insert (size_t offset, const mk_char *ptr, size_t count);
    mkString& insert (size_t offset, const mkString& source);
    mkString& insert (size_t offset, const mkString& source, size_t roffset, size_t count);
    mkString& insert(size_t offset, mk_char ch, size_t count);
    //erase
    mkString& remove (size_t offset = 0, size_t count = npos);
    //push_back
    //pop_back
    
    mkString& append(mkString&& source);
#ifdef __WINDOWS__
    mkString& append (const char* ptr);
    mkString& append (const char* ptr, size_t count);
#endif
    mkString& append (const mk_char* ptr);
    mkString& append (const mk_char* ptr, size_t count);
    mkString& append (const mkString& source);
    mkString& append (const mkString& source, size_t offset, size_t count);
    mkString& append (mk_char ch, size_t count);
    
    //operator+=
#ifdef __WINDOWS__
    mkString& operator+=(const char* ptr);
#endif
    mkString& operator+=(const mk_char* ptr);
    mkString& operator+= (const mkString& source);
    mkString& operator+=(mk_char ch);
    
    //compare
    int compare (const mkString& source) const;
    int compare (const mk_char *ptr) const;
    int compare (const mk_char *ptr, size_t len) const;
    int compare (size_t offset, size_t number, const mk_char *ptr) const;
    int compare (size_t offset, size_t number, const mk_char* ptr, size_t count ) const;
    int compare (size_t offset, size_t number, const mkString& source) const;
    int compare (size_t offset, size_t number, const mkString& source, size_t roffset, size_t count) const;
    
    //compareIgnoreCase
    int compareIgnoreCase (const mkString& source) const;
    int compareIgnoreCase (size_t offset, size_t number, const mkString& source) const;
    int compareIgnoreCase (size_t offset, size_t number, const mkString& source, size_t roffset, size_t count) const;
    int compareIgnoreCase(const mk_char *ptr) const;
    int compareIgnoreCase (size_t offset, size_t number, const mk_char *ptr) const;
    int compareIgnoreCase (size_t offset, size_t number, const mk_char* ptr, size_t count ) const;
    
    //startsWith
#ifdef __WINDOWS__
    bool startsWith (const char* prefix) const;
#endif
    bool startsWith (const mkString& prefix) const;
    bool startsWith (const mk_char* prefix) const;
    
    //ends_with
    
    //contains
  
    //replace
    mkString& replace (mk_char oldValue, mk_char newValue, bool replaceAll = false);
    mkString& replace (size_t offset, size_t number, const mkString& source);
    mkString& replace (size_t offset,size_t number, const mkString& source, size_t roffset, size_t count);
    mkString& replace (size_t offset,	size_t number, const mk_char *ptr, size_t count);
    mkString& replace (size_t offset, size_t number, const mk_char *ptr);
    mkString& replace (size_t offset, size_t number, size_t count, mk_char ch);
    
    mkString subString (size_t offset = 0, size_t count = npos) const;
    mkString trim (mk_char ch = _T(' ')) const;
    mkString leftString (size_t count) const;
    mkString rightString (size_t count) const;
    mkString beforeFirst (mk_char ch) const;
    mkString beforeLast (mk_char ch) const;
    mkString afterFirst (mk_char ch) const;
    mkString afterLast(mk_char ch) const;
    size_t copy (mk_char* ptr, size_t count, size_t offset = 0) const;
    void resize (size_t newSiz, mk_char ch = 0);
    void swap (mkString& source);
    
///查找
public:
    //find
#ifdef __WINDOWS__
    size_t find (const char* ptr, size_t offset = 0) const;
    size_t find (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t find (const mk_char* ptr, size_t offset = 0) const;
    size_t find (const mk_char* ptr, size_t offset, size_t count) const;
    size_t find (const mkString& source, size_t offset = 0) const;
    size_t find (mk_char ch, size_t offset = 0) const;
    
    //rfind
#ifdef __WINDOWS__
    size_t rfind (const char* ptr, size_t offset = 0) const;
    size_t rfind (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t rfind (const mk_char* ptr, size_t offset = npos) const;
    size_t rfind (const mk_char* ptr, size_t offset, size_t count) const;
    size_t rfind (const mkString& source, size_t offset = npos) const;
    size_t rfind (mk_char ch, size_t offset = npos) const;
    
    //findFirstOf
#ifdef __WINDOWS__
    size_t findFirstOf (const char* ptr, size_t offset = 0) const;
    size_t findFirstOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findFirstOf (const mk_char* ptr, size_t offset = 0) const;
    size_t findFirstOf (const mk_char* ptr, size_t offset, size_t count) const;
    size_t findFirstOf (const mkString& source, size_t offset = 0) const;
    size_t findFirstOf (mk_char ch, size_t offset = 0) const;
    
    //findFirstNotOf
#ifdef __WINDOWS__
    size_t findFirstNotOf (const char* ptr, size_t offset = 0) const;
    size_t findFirstNotOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findFirstNotOf (const mk_char* ptr, size_t offset = 0) const;
    size_t findFirstNotOf (const mk_char* ptr, size_t offset, size_t count) const;
    size_t findFirstNotOf (const mkString& source, size_t offset = 0) const;
    size_t findFirstNotOf (mk_char ch, size_t offset = 0) const;
    
    //findLastOf
#ifdef __WINDOWS__
    size_t findLastOf (const char* ptr, size_t offset = 0) const;
    size_t findLastOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findLastOf (const mk_char *ptr, size_t offset = npos) const;
    size_t findLastOf (const mk_char* ptr, size_t offset, size_t count) const;
    size_t findLastOf (const mkString& source, size_t offset = npos) const;
    size_t findLastOf (mk_char ch, size_t offset = npos) const;
    
    //findLastNotOf
#ifdef __WINDOWS__
    size_t findLastNotOf (const char* ptr, size_t offset = 0) const;
    size_t findLastNotOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findLastNotOf (const mk_char* ptr, size_t offset = npos) const;
    size_t findLastNotOf (const mk_char* ptr, size_t offset, size_t count) const;
    size_t findLastNotOf (const mkString& source, size_t offset = npos) const;
    size_t findLastNotOf (mk_char ch, size_t offset = npos) const;
    
    //findAny
    size_t findAny (const mkString& chars) const;
    size_t findAny (size_t offset, const mkString& chars) const;
    
    //findLastOfAny
    size_t findLastOfAny (const mkString& chars) const;
    size_t findLastOfAny (size_t offset, const mkString& chars) const;
    
///常量
public:
    static const size_t npos = -1;
    static const mkString EMPTY;
    
///扩展
public:
    void toUpper (void);
    void toLower (void);
    int freq (mk_char ch) const;
    void split (const mkString& separators, std::vector<mkString>& substrs, bool oneInSeparators = true) const;
    void split (mk_char separator, std::vector<mkString>& substrs) const;
#ifdef __WINDOWS__
    void format(const char* fmt, ...);
    void formatv(const char* fmt, va_list ap);
#endif
    void format (const mk_char* fmt, ...);
    void formatv (const mk_char* fmt, va_list ap);
    
#ifdef __WINDOWS__
    mkString& operator<< (const char* ptr);
#endif
    mkString& operator<< (const mk_char* ptr);
    mkString& operator<<(bool b);
    mkString& operator<<(int i);
    mkString& operator<<(unsigned int ui);
    mkString& operator<<(const int64& l);
    mkString& operator<<(const uint64& ul);
    mkString& operator<<(float f);
    mkString& operator<<(double d);
    mkString& operator<< (mk_char ch);
    mkString& operator<< (const mkString& source);
    
//static
public:
    static mkString toString (bool b);
    static mkString toString (short s);
    static mkString toString (unsigned short us);
    static mkString toString (int i);
    static mkString toString (unsigned int ui);
    static mkString toString (const int64& l);
    static mkString toString (const uint64& ul);
    static mkString toString (float f);
    static mkString toString (double d);
    
private:
    std::unique_ptr<mk_char_string>    _pImp;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
///非成员函数
// operator+
#ifdef __WINDOWS__
MK_DLL_EXPORT mkString operator+(const mkString& str, const char* ptr);
MK_DLL_EXPORT mkString operator+(const char* ptr, const mkString& str);
MK_DLL_EXPORT bool operator== (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator== (const char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator!= (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator!= (const char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator< (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator< (const char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator<= (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator<= (const char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator> (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator> (const char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator>= (const mkString& s1, const char* s2);
MK_DLL_EXPORT bool operator>= (const char* s1, const mkString& s2);
#endif

MK_DLL_EXPORT mkString operator+(const mkString& str1,  const mkString& str2);
MK_DLL_EXPORT mkString operator+(const mkString& str, mk_char ch);
MK_DLL_EXPORT mkString operator+(mk_char ch, const mkString& str);
MK_DLL_EXPORT mkString operator+(const mkString& str, const mk_char* ptr);
MK_DLL_EXPORT mkString operator+(const mk_char *ptr, const mkString& str);
MK_DLL_EXPORT bool operator== (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator== (const mk_char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator== (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator!= (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator!= (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator!= (const mk_char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator< (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator< (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator< (const mk_char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator<= (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator<= (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator<= (const mk_char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator> (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator> (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator> (const mk_char* s1, const mkString& s2);
MK_DLL_EXPORT bool operator>= (const mkString& s1, const mkString& s2);
MK_DLL_EXPORT bool operator>= (const mkString& s1, const mk_char* s2);
MK_DLL_EXPORT bool operator>= (const mk_char* s1, const mkString& s2);

#endif //__mkString
