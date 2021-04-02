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

TEST(mkString, util)
{
    string text{"  abc中文DEF  "};
    MK_PRINT(text.c_str());
    
    MK_PRINT("to_upper = %s", string_utility<string>::to_upper(text).c_str());
    MK_PRINT("to_lower = %s", string_utility<string>::to_lower(text).c_str());
    MK_PRINT("trim_left = %s", string_utility<string>::trim_left(text).c_str());
    MK_PRINT("trim_right = %s", string_utility<string>::trim_right(text).c_str());
    MK_PRINT("trim = %s", string_utility<string>::trim(text).c_str());
    
    MK_PRINT("starts_with = %s", string_utility<string>::starts_with(text, "abc") ? "true" : "false");
    MK_PRINT("starts_with = %s", string_utility<string>::starts_with(text, "  abc") ? "true" : "false");
    
    MK_PRINT("ends_with = %s", string_utility<string>::ends_with(text, "DEF") ? "true" : "false");
    MK_PRINT("ends_with = %s", string_utility<string>::ends_with(text, "DEF  ") ? "true" : "false");
    
    MK_PRINT("equals_ignore_case = %s", string_utility<string>::equals_ignore_case(text, string_utility<string>::to_upper(text)) ? "true" : "false");
    
    MK_PRINT("starts_with_ignore_case = %s", string_utility<string>::starts_with_ignore_case(text, "  abc") ? "true" : "false");
    MK_PRINT("starts_with_ignore_case = %s", string_utility<string>::starts_with_ignore_case(text, "  AbC") ? "true" : "false");
    
    MK_PRINT("ends_with_ignore_case = %s", string_utility<string>::ends_with_ignore_case(text, "DEF  ") ? "true" : "false");
    MK_PRINT("ends_with_ignore_case = %s", string_utility<string>::ends_with_ignore_case(text, "DeF  ") ? "true" : "false");
    
    text = "true";
    MK_PRINT("from_string = %u", string_utility<string>::from_string(text));
    
    text = "a";
    MK_PRINT("from_string = %d", string_utility<string>::from_string<char>(text));
    
    text = "1024";
    MK_PRINT("from_string = %d", string_utility<string>::from_string<int>(text));
    
    text = "a";
    MK_PRINT("from_hex_string = %d", string_utility<string>::from_hex_string<int>(text));
    
    
    MK_PRINT("to_string = %s", string_utility<string>::to_string<int>(true).c_str());
    MK_PRINT("to_string = %s", string_utility<string>::to_string<int>(1024).c_str());
    
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 1).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 2).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 3).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 4).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 5).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 6).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 7).c_str());
    MK_PRINT("to_hex_string = 0x%s", string_utility<string>::to_hex_string<int>(1024, 8).c_str());
    
    text = "/a/b/c/d/e/f";
    vector<string> vRet = string_utility<string>::split(text, "/");
    for(const auto& elem : vRet) {
        MK_PRINT("%s", elem.c_str());
    }
}

TEST(mkString, format)
{
    double usedSecond = 0;
    int loopCount = 100;
    
    {
        mkPerfPoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            shared_ptr<char> str = mkSharedFormat::fmt("[%d]:mkSharedFormat::%s",i,"ffffff");
            MK_PRINT(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkPerfPoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            unique_ptr<char[]> str = mkUniqueFormat::fmt("[%d]:mkUniqueFormat::%s", i,"ffffff");
            MK_PRINT(str.get());
        }
    }
    cout<<usedSecond<<endl;
    
    {
        mkPerfPoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            mkFixedFormat<1024> fmt;
            auto str1 = fmt("[%d]:Format102::%s",i,"aaaaa");
            MK_PRINT(str1);
        }
    }
    cout<<usedSecond<<endl;
}


TEST(mkString, mkString)
{
    {
        mkString str;
    	#ifdef __WINDOWS__
        	wstring xx = str;
    	#else
    		string xx = str;
    	#endif
    }
    
    {
        mkString str(_T("abc中文DEF"));
        str += _T("abc中文DEF");
        MK_PRINT(_T("%s"), str.c_str());
    }
}

