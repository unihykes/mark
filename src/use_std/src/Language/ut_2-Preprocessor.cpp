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

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_Preprocessor : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

//预处理器
TEST_F(ut_Preprocessor, define)
{
    //define支持不定长参数列表
    //#define 标识符( 形参, ... ) 替换列表(可选) (C++11 起) 
    //#define 标识符( ... ) 替换列表(可选) (C++11 起) 
    
    //# 与 ## 运算符
    #define showlist(...) printf(#__VA_ARGS__)
    showlist(xx\n);            // 展开成 printf("xx\n")
    
    #define FUNCTION(name, a) int fun_##name() { return a;}
    
    
    //预定义宏
    cout<< "__cplusplus = " << __cplusplus <<endl;
    //cout<< "__STDC_HOSTED__ = " << __STDC_HOSTED__ <<endl; //(C++11) 
    cout<< "__FILE__ = " << __FILE__ <<endl;
    cout<< "__LINE__ = " << __LINE__ <<endl;
    cout<< "__DATE__ = " << __DATE__ <<endl;
    cout<< "__TIME__ = " << __TIME__ <<endl;
    //cout<< "__STDC__ = " << __STDC__ <<endl;
    //cout<< "__STDC_VERSION__ = " << __STDC_VERSION__ <<endl; //(C++11) 
    //cout<< "__STDC_ISO_10646__ = " << __STDC_ISO_10646__ <<endl; //(C++11) 
    //cout<< "__STDC_MB_MIGHT_NEQ_WC__ = " << __STDC_MB_MIGHT_NEQ_WC__ <<endl; //(C++11) 
    //cout<< "__STDCPP_STRICT_POINTER_SAFETY__ = " << __STDCPP_STRICT_POINTER_SAFETY__ <<endl; //(C++11) 
    //cout<< "__STDCPP_THREADS__ = " << __STDCPP_THREADS__ <<endl; //(C++11) 
    
    //每个函数作用域内部，有个特殊的函数局域预定义变量，名为 __func__(C++11 起) 
    cout<< "__func__ = " << __func__ <<endl; //(C++11)
}

TEST_F(ut_Preprocessor, line)
{
    //line 可以更改代码行数宏
    cout<<__LINE__<<endl;//正确行数
    
    //更改当前行号为777
    #line 777
    cout<<__LINE__<<endl;
    cout<<__FILE__<<":"<<__LINE__<<endl;
    
    //更改当前行号为xxx,并且文件名改为test.cpp
    #line 777 "test.cpp"
    cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:xxx
    
    //恢复行号
    #line 73
}