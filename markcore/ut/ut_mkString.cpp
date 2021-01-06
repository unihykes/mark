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
	#ifdef __WINDOWS__
    	wstring xx = str;
	#else
		string xx = str;
	#endif
}


TEST_F(ut_mkString, format)
{
    double usedSecond = 0;
    int loopCount = 100;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            shared_ptr<char> str = mkSharedFormat::fmt("[%d]:mkSharedFormat::%s",i,"ffffff");
            MK_PRINT_MSG(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            unique_ptr<char[]> str = mkUniqueFormat::fmt("[%d]:mkUniqueFormat::%s", i,"ffffff");
            MK_PRINT_MSG(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            mkFixedFormat<1024> fmt;
            auto str1 = fmt("[%d]:Format102::%s",i,"aaaaa");
            MK_PRINT_MSG(str1);
        }
    }
    cout<<usedSecond<<endl;
}
