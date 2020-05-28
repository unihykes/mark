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
#include "mkUniqueProfilePoint.h"

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
    int loopCount = 1000000;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            /*shared_ptr<char> str = */Format("Format__%d__%s",333,"ffffff");
            //cout<<str.get()<<endl;
            //MK_PRINT_MSG(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            Format0{}("Format0__%d__%s",333,"ffffff");
            //cout<<str<<endl;
            //MK_PRINT_MSG(str.c_str());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            Format1024{}("Format1024__%d__%s",333,"bbbbb");
            //cout<<str<<endl;
            //MK_PRINT_MSG(str.c_str());
        }
    }
    cout<<usedSecond<<endl;
    
    
    return;
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            /*shared_ptr<wchar_t> str = */Format(L"FormatW__%d__%s", 333, L"ffffff");
            //wcout<<str.get()<<endl;
            //MK_PRINT_MSG(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            Format0W{}(L"Format0W__%d__%s",333,L"ffffff");
            //wcout<<str<<endl;
            //MK_PRINT_MSG(str.c_str());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            Format1024W{}(L"Format1024W__%d__%s",333,L"ddddd");
            //wcout<<str<<endl;
            //MK_PRINT_MSG(str.c_str());
        }
    }
    cout<<usedSecond<<endl;
}
