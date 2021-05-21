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
#ifdef __WINDOWS__
#else
    #include <uuid.h>
#endif
    
#include <mkheaders.h>
#include "mkGuid.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#ifdef __LINUX__
string mkGuid::Generate()
{
    uuid_t guid;
    uuid_generate(guid);
    
    char buf [40];
    ::memset (buf, 0, sizeof(char) * 40);
    uuid_unparse(guid, buf);
    string result(buf);
    return result;
}
#else
string mkGuid::Generate()
{
    return Generate2();
}
#endif

string 
mkGuid::Generate2()
{
    /*todo
    boost::uuids::uuid _uuid = boost::uuids::random_generator()();
    return boost::uuids::to_string(_uuid);
    */
    return "todo";
}
