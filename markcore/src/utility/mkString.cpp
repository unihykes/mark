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

#include<mkheaders.h>
#include"mkString.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
///构造
mkString::mkString()
{
}

mkString::mkString(mkString&& source)
{
    _pImp = std::move(source._pImp);
}

#ifdef __WINDOWS__
mkString::mkString(const char* ptr)
{
    //todo
}

mkString::mkString(const char *ptr, size_t count)
{
    //todo
}
#endif

mkString::mkString(const mk_char* ptr)
    : _pImp(nullptr)
{
    //todo
}

mkString::mkString(const mkString& source)
{
    if(source._pImp) {
        _pImp.reset(new mk_char_string(source._pImp->c_str()));
    }
}

mkString::~mkString()
{
    //todo
}

mkString::operator const mk_char_string& () const
{
    return *_pImp;
}

///元素访问
size_t 
mkString::getLength() const
{
    //todo
    return 0;
}

///操作

int 
mkString::compare (const mkString& source) const
{
    //todo
    return -1;
}

int 
mkString::compare (const mk_char *ptr) const
{
    //todo
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WINDOWS__
bool operator== (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) == 0); 
}

bool operator== (const char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) == 0); 
}
bool operator!= (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) != 0); 
}

bool operator!= (const char* s1, const mkString& s2)
{
    return (s2.compare (s1) != 0); 
}
bool operator< (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) <  0); 
}

bool operator< (const char* s1, const mkString& s2)
{ 
    return (s2.compare(s1) >  0);
}
bool operator<= (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) >= 0); 
}
bool operator> (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) <  0); 
}
bool operator>= (const mkString& s1, const char* s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) <= 0); 
}
#endif

bool operator== (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) == 0); 
}

bool operator== (const mk_char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) == 0); 
}

bool operator== (const mkString& s1, const mkString& s2)
{ 
    return (s1.getLength () == s2.getLength()) && (s1.compare (s2) == 0); 
}

bool operator!= (const mkString& s1, const mkString& s2)
{
    return (s1.getLength() != s2.getLength()) || (s1.compare (s2) != 0);
}

bool operator!= (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) != 0); 
}

bool operator!= (const mk_char* s1, const mkString& s2)
{
    return (s2.compare (s1) != 0); 
}

bool operator< (const mkString& s1, const mkString& s2)
{ 
    return (s1.compare (s2) < 0); 
}

bool operator< (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) <  0); 
}

bool operator< (const mk_char* s1, const mkString& s2)
{ 
    return (s2.compare(s1) >  0);
}

bool operator<= (const mkString& s1, const mkString& s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const mk_char* s1, const mkString& s2)
{ 
    return (s2.compare(s1) >= 0); 
}

bool operator> (const mkString& s1, const mkString& s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const mk_char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) <  0); 
}

bool operator>= (const mkString& s1, const mkString& s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const mkString& s1, const mk_char* s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const mk_char* s1, const mkString& s2)
{ 
    return (s2.compare (s1) <= 0); 
}
