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

#ifndef __aiString
#define __aiString

#include "mkString.h"

#ifdef __WINDOWS__
// Return the Unicode string of @ptr.
// return the Unicode string buffer, the caller should release it.
inline mkChar* 
getUnicodeString(const char* ptr, size_t num, size_t* outLen)
{
    //todo
    return nullptr;
}

#endif

class MK_DLL_EXPORT aiString
{
///构造
public:
    aiString();
    aiString(aiString&& source);
#ifdef __WINDOWS__
    aiString(const char* ptr);
    aiString(const char *ptr, size_t count);
#endif
    aiString(const mkChar* ptr);
    aiString(const mkChar* ptr, size_t count);
    aiString(const aiString& source);
    aiString(const aiString& source, size_t offset, size_t count = aiString::npos);
    aiString (mkChar ch, size_t count);

///析构
public:
    ~aiString();
    
///赋值
public:
    //operator=
    aiString& operator= (aiString&& source);
#ifdef __WINDOWS__
    aiString& operator= (const char* ptr);
#endif
    aiString& operator= (const mkChar* ptr);
    aiString& operator= (const aiString& source);
    aiString& operator= (mkChar ch);
    
    ///assign
    aiString& assign(aiString&& source);
#ifdef __WINDOWS__
    aiString& assign(const char* ptr);
    aiString& assign(const char* ptr, size_t num);
#endif
    aiString& assign(const mkChar* ptr);
    aiString& assign(const mkChar* ptr, size_t num);
    aiString& assign(const aiString& source);
    aiString& assign(const aiString& source, size_t offset, size_t count);
    aiString& assign(mkChar ch, size_t count);
    
///元素访问
public:
    mkChar& at(size_t n);
    mkChar  at(size_t n) const;
    mkChar& operator[] (size_t n);
    mkChar  operator[] (size_t n) const;
    //front()
    //back()
    //data()
    const mkChar* c_str() const;
    const mkChar* getCStr() const;
    //operator aiStringView () const;
    operator const mkString& () const;
    
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
    aiString& insert (size_t offset, const char* ptr);
    aiString& insert (size_t offset, const char* ptr, size_t count);
#endif
    aiString& insert (size_t offset, const mkChar *ptr);
    aiString& insert (size_t offset, const mkChar *ptr, size_t count);
    aiString& insert (size_t offset, const aiString& source);
    aiString& insert (size_t offset, const aiString& source, size_t roffset, size_t count);
    aiString& insert(size_t offset, mkChar ch, size_t count);
    //erase
    aiString& remove (size_t offset = 0, size_t count = npos);
    //push_back
    //pop_back
    
    aiString& append(aiString&& source);
#ifdef __WINDOWS__
    aiString& append (const char* ptr);
    aiString& append (const char* ptr, size_t count);
#endif
    aiString& append (const mkChar* ptr);
    aiString& append (const mkChar* ptr, size_t count);
    aiString& append (const aiString& source);
    aiString& append (const aiString& source, size_t offset, size_t count);
    aiString& append (mkChar ch, size_t count);
    
    //operator+=
#ifdef __WINDOWS__
    aiString& operator+=(const char* ptr);
#endif
    aiString& operator+=(const mkChar* ptr);
    aiString& operator+= (const aiString& source);
    aiString& operator+=(mkChar ch);
    
    //compare
    int compare (const aiString& source) const;
    int compare (const mkChar *ptr) const;
    int compare (const mkChar *ptr, size_t len) const;
    int compare (size_t offset, size_t number, const mkChar *ptr) const;
    int compare (size_t offset, size_t number, const mkChar* ptr, size_t count ) const;
    int compare (size_t offset, size_t number, const aiString& source) const;
    int compare (size_t offset, size_t number, const aiString& source, size_t roffset, size_t count) const;
    
    //compareIgnoreCase
    int compareIgnoreCase (const aiString& source) const;
    int compareIgnoreCase (size_t offset, size_t number, const aiString& source) const;
    int compareIgnoreCase (size_t offset, size_t number, const aiString& source, size_t roffset, size_t count) const;
    int compareIgnoreCase(const mkChar *ptr) const;
    int compareIgnoreCase (size_t offset, size_t number, const mkChar *ptr) const;
    int compareIgnoreCase (size_t offset, size_t number, const mkChar* ptr, size_t count ) const;
    
    //startsWith
#ifdef __WINDOWS__
    bool startsWith (const char* prefix) const;
#endif
    bool startsWith (const aiString& prefix) const;
    bool startsWith (const mkChar* prefix) const;
    
    //ends_with
    
    //contains
  
    //replace
    aiString& replace (mkChar oldValue, mkChar newValue, bool replaceAll = false);
    aiString& replace (size_t offset, size_t number, const aiString& source);
    aiString& replace (size_t offset,size_t number, const aiString& source, size_t roffset, size_t count);
    aiString& replace (size_t offset,	size_t number, const mkChar *ptr, size_t count);
    aiString& replace (size_t offset, size_t number, const mkChar *ptr);
    aiString& replace (size_t offset, size_t number, size_t count, mkChar ch);
    
    aiString subString (size_t offset = 0, size_t count = npos) const;
    aiString trim (mkChar ch = _T(' ')) const;
    aiString leftString (size_t count) const;
    aiString rightString (size_t count) const;
    aiString beforeFirst (mkChar ch) const;
    aiString beforeLast (mkChar ch) const;
    aiString afterFirst (mkChar ch) const;
    aiString afterLast(mkChar ch) const;
    size_t copy (mkChar* ptr, size_t count, size_t offset = 0) const;
    void resize (size_t newSiz, mkChar ch = 0);
    void swap (aiString& source);
    
///查找
public:
    //find
#ifdef __WINDOWS__
    size_t find (const char* ptr, size_t offset = 0) const;
    size_t find (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t find (const mkChar* ptr, size_t offset = 0) const;
    size_t find (const mkChar* ptr, size_t offset, size_t count) const;
    size_t find (const aiString& source, size_t offset = 0) const;
    size_t find (mkChar ch, size_t offset = 0) const;
    
    //rfind
#ifdef __WINDOWS__
    size_t rfind (const char* ptr, size_t offset = 0) const;
    size_t rfind (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t rfind (const mkChar* ptr, size_t offset = npos) const;
    size_t rfind (const mkChar* ptr, size_t offset, size_t count) const;
    size_t rfind (const aiString& source, size_t offset = npos) const;
    size_t rfind (mkChar ch, size_t offset = npos) const;
    
    //findFirstOf
#ifdef __WINDOWS__
    size_t findFirstOf (const char* ptr, size_t offset = 0) const;
    size_t findFirstOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findFirstOf (const mkChar* ptr, size_t offset = 0) const;
    size_t findFirstOf (const mkChar* ptr, size_t offset, size_t count) const;
    size_t findFirstOf (const aiString& source, size_t offset = 0) const;
    size_t findFirstOf (mkChar ch, size_t offset = 0) const;
    
    //findFirstNotOf
#ifdef __WINDOWS__
    size_t findFirstNotOf (const char* ptr, size_t offset = 0) const;
    size_t findFirstNotOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findFirstNotOf (const mkChar* ptr, size_t offset = 0) const;
    size_t findFirstNotOf (const mkChar* ptr, size_t offset, size_t count) const;
    size_t findFirstNotOf (const aiString& source, size_t offset = 0) const;
    size_t findFirstNotOf (mkChar ch, size_t offset = 0) const;
    
    //findLastOf
#ifdef __WINDOWS__
    size_t findLastOf (const char* ptr, size_t offset = 0) const;
    size_t findLastOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findLastOf (const mkChar *ptr, size_t offset = npos) const;
    size_t findLastOf (const mkChar* ptr, size_t offset, size_t count) const;
    size_t findLastOf (const aiString& source, size_t offset = npos) const;
    size_t findLastOf (mkChar ch, size_t offset = npos) const;
    
    //findLastNotOf
#ifdef __WINDOWS__
    size_t findLastNotOf (const char* ptr, size_t offset = 0) const;
    size_t findLastNotOf (const char* ptr, size_t offset, size_t count) const;
#endif
    size_t findLastNotOf (const mkChar* ptr, size_t offset = npos) const;
    size_t findLastNotOf (const mkChar* ptr, size_t offset, size_t count) const;
    size_t findLastNotOf (const aiString& source, size_t offset = npos) const;
    size_t findLastNotOf (mkChar ch, size_t offset = npos) const;
    
    //findAny
    size_t findAny (const aiString& chars) const;
    size_t findAny (size_t offset, const aiString& chars) const;
    
    //findLastOfAny
    size_t findLastOfAny (const aiString& chars) const;
    size_t findLastOfAny (size_t offset, const aiString& chars) const;
    
///常量
public:
    static const size_t npos = -1;
    static const aiString EMPTY;
    
///扩展
public:
    void toUpper (void);
    void toLower (void);
    int freq (mkChar ch) const;
    void split (const aiString& separators, std::vector<aiString>& substrs, bool oneInSeparators = true) const;
    void split (mkChar separator, std::vector<aiString>& substrs) const;
#ifdef __WINDOWS__
    void format(const char* fmt, ...);
    void formatv(const char* fmt, va_list ap);
#endif
    void format (const mkChar* fmt, ...);
    void formatv (const mkChar* fmt, va_list ap);
    
#ifdef __WINDOWS__
    aiString& operator<< (const char* ptr);
#endif
    aiString& operator<< (const mkChar* ptr);
    aiString& operator<<(bool b);
    aiString& operator<<(int i);
    aiString& operator<<(unsigned int ui);
    aiString& operator<<(const int64& l);
    aiString& operator<<(const uint64& ul);
    aiString& operator<<(float f);
    aiString& operator<<(double d);
    aiString& operator<< (mkChar ch);
    aiString& operator<< (const aiString& source);
    
//static
public:
    static aiString toString (bool b);
    static aiString toString (short s);
    static aiString toString (unsigned short us);
    static aiString toString (int i);
    static aiString toString (unsigned int ui);
    static aiString toString (const int64& l);
    static aiString toString (const uint64& ul);
    static aiString toString (float f);
    static aiString toString (double d);
    
private:
    std::unique_ptr<mkString>    _pImp;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
///非成员函数
// operator+
#ifdef __WINDOWS__
MK_DLL_EXPORT aiString operator+(const aiString& str, const char* ptr);
MK_DLL_EXPORT aiString operator+(const char* ptr, const aiString& str);
MK_DLL_EXPORT bool operator== (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator== (const char* s1, const aiString& s2);
MK_DLL_EXPORT bool operator!= (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator!= (const char* s1, const aiString& s2);
MK_DLL_EXPORT bool operator< (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator< (const char* s1, const aiString& s2);
MK_DLL_EXPORT bool operator<= (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator<= (const char* s1, const aiString& s2);
MK_DLL_EXPORT bool operator> (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator> (const char* s1, const aiString& s2);
MK_DLL_EXPORT bool operator>= (const aiString& s1, const char* s2);
MK_DLL_EXPORT bool operator>= (const char* s1, const aiString& s2);
#endif

MK_DLL_EXPORT aiString operator+(const aiString& str1,  const aiString& str2);
MK_DLL_EXPORT aiString operator+(const aiString& str, mkChar ch);
MK_DLL_EXPORT aiString operator+(mkChar ch, const aiString& str);
MK_DLL_EXPORT aiString operator+(const aiString& str, const mkChar* ptr);
MK_DLL_EXPORT aiString operator+(const mkChar *ptr, const aiString& str);
MK_DLL_EXPORT bool operator== (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator== (const mkChar* s1, const aiString& s2);
MK_DLL_EXPORT bool operator== (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator!= (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator!= (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator!= (const mkChar* s1, const aiString& s2);
MK_DLL_EXPORT bool operator< (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator< (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator< (const mkChar* s1, const aiString& s2);
MK_DLL_EXPORT bool operator<= (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator<= (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator<= (const mkChar* s1, const aiString& s2);
MK_DLL_EXPORT bool operator> (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator> (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator> (const mkChar* s1, const aiString& s2);
MK_DLL_EXPORT bool operator>= (const aiString& s1, const aiString& s2);
MK_DLL_EXPORT bool operator>= (const aiString& s1, const mkChar* s2);
MK_DLL_EXPORT bool operator>= (const mkChar* s1, const aiString& s2);

#endif //__mkString
