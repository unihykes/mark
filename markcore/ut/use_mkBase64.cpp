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
#include "utility/mkBase64.h"

TEST(mkBase64, run)
{
    string in = "abcedfghi";
    string out;
    mkBase64::Base64Encode(in,&out);
    MK_PRINT("in = %s, out = %s", in.c_str(), out.c_str());
    
    in = out;
    mkBase64::Base64Decode(in,&out);
    MK_PRINT("in = %s, out = %s", in.c_str(), out.c_str());
}
