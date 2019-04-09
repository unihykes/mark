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

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkString.h"
#include "mkFormat.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_mkString : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
    
protected:
};

TEST_F(ut_mkString, null)
{
    mkString str;
    wstring xx = str;
}


TEST_F(ut_mkString, format)
{
    string str = Format1024{}("aaaaaa%d%s",333,"bbbbb");
    cout<<str<<endl;
    MK_PRINT_MSG(str.c_str());
    
    wstring strW = Format1024W{}(L"ccccc%d%s",333,L"ddddd");
    wcout<<strW<<endl;
    MK_PRINT_MSG(strW.c_str());
}
