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


////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_mkException : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
    
protected:
};

TEST_F(ut_mkException, null)
{
    try {
        try {
            throw mkException(string("aaa"), __FILE__, __LINE__, 128);
        }
        catch(mkException& e) {
            MK_PRINT(e.what());
            throw mkException("bbb", __FILE__, __LINE__, 128, e);
        }
    }
    catch(mkException& e) {
        MK_PRINT(e.what());
    }
}
