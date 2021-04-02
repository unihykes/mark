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
#include"aiString.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
///构造
aiString::aiString()
{
}

aiString::aiString(aiString&& source)
{
    _pImp = std::move(source._pImp);
}

#ifdef __WINDOWS__
aiString::aiString(const char* ptr)
{
    //todo
}

aiString::aiString(const char *ptr, size_t count)
{
    //todo
}
#endif

aiString::aiString(const mkChar* ptr)
    : _pImp(nullptr)
{
    //todo
}

aiString::aiString(const aiString& source)
{
    if(source._pImp) {
        _pImp.reset(new mkString(source._pImp->c_str()));
    }
}

aiString::~aiString()
{
    //todo
}

aiString::operator const mkString& () const
{
    return *_pImp;
}

///元素访问
size_t 
aiString::getLength() const
{
    //todo
    return 0;
}

///操作

int 
aiString::compare (const aiString& source) const
{
    //todo
    return -1;
}

int 
aiString::compare (const mkChar *ptr) const
{
    //todo
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __WINDOWS__
bool operator== (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) == 0); 
}

bool operator== (const char* s1, const aiString& s2)
{ 
    return (s2.compare (s1) == 0); 
}
bool operator!= (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) != 0); 
}

bool operator!= (const char* s1, const aiString& s2)
{
    return (s2.compare (s1) != 0); 
}
bool operator< (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) <  0); 
}

bool operator< (const char* s1, const aiString& s2)
{ 
    return (s2.compare(s1) >  0);
}
bool operator<= (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const char* s1, const aiString& s2)
{ 
    return (s2.compare (s1) >= 0); 
}
bool operator> (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const char* s1, const aiString& s2)
{ 
    return (s2.compare (s1) <  0); 
}
bool operator>= (const aiString& s1, const char* s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const char* s1, const aiString& s2)
{ 
    return (s2.compare (s1) <= 0); 
}
#endif

bool operator== (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) == 0); 
}

bool operator== (const mkChar* s1, const aiString& s2)
{ 
    return (s2.compare (s1) == 0); 
}

bool operator== (const aiString& s1, const aiString& s2)
{ 
    return (s1.getLength () == s2.getLength()) && (s1.compare (s2) == 0); 
}

bool operator!= (const aiString& s1, const aiString& s2)
{
    return (s1.getLength() != s2.getLength()) || (s1.compare (s2) != 0);
}

bool operator!= (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) != 0); 
}

bool operator!= (const mkChar* s1, const aiString& s2)
{
    return (s2.compare (s1) != 0); 
}

bool operator< (const aiString& s1, const aiString& s2)
{ 
    return (s1.compare (s2) < 0); 
}

bool operator< (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) <  0); 
}

bool operator< (const mkChar* s1, const aiString& s2)
{ 
    return (s2.compare(s1) >  0);
}

bool operator<= (const aiString& s1, const aiString& s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) <= 0); 
}

bool operator<= (const mkChar* s1, const aiString& s2)
{ 
    return (s2.compare(s1) >= 0); 
}

bool operator> (const aiString& s1, const aiString& s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) >  0); 
}

bool operator> (const mkChar* s1, const aiString& s2)
{ 
    return (s2.compare (s1) <  0); 
}

bool operator>= (const aiString& s1, const aiString& s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const aiString& s1, const mkChar* s2)
{ 
    return (s1.compare (s2) >= 0); 
}

bool operator>= (const mkChar* s1, const aiString& s2)
{ 
    return (s2.compare (s1) <= 0); 
}
