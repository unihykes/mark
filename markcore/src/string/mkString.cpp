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
#include<boost/algorithm/string.hpp>
#include"mkString.h"

std::string 
boostStringHelper::to_upper_copy(const string& src)
{
    return boost::algorithm::to_upper_copy(src);
    
    /*
    string result;
    boost::algorithm::to_upper_copy(std::back_inserter(result), boost::make_iterator_range(src));
    return result;
    */
}

void 
boostStringHelper::to_upper(string& src)
{
    //todo:
    //boost::algorithm::to_upper(boost::make_iterator_range(src));
}
