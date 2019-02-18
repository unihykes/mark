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

Time:2018-6

info:
    查找两个范围第一个不同元素的位置 
    返回值:带指向首二个不等价元素的迭代器的 std::pair 。
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


TEST(NMSQ, mismatch1)
{
    vector<int> v1{1,2,3,3,4,6,8};
    vector<int> v2{1,2,3,3,4,5,6};
    auto ret = std::mismatch(v1.begin(), v1.end(), v2.begin());
    
    if(ret.first == v1.end()) {
        MK_PRINT_MSG("end of v1");
    }
    else if(ret.second == v2.end()) {
        MK_PRINT_MSG("end of v2");
    }
    else{
        MK_PRINT_MSG("ret = <%d, %d>", *ret.first, *ret.second);
    }
}

TEST(NMSQ, mismatch2)
{
    vector<int> v1{2,4,6,8,5};
    vector<int> v2{4,8,12,16,5};
    auto ret = std::mismatch(v1.begin(), v1.end(), v2.begin(), [](int n1, int n2){return (n1/2) == (n2/4);});
    
    if(ret.first == v1.end()) {
        MK_PRINT_MSG("end of v1");
    }
    else if(ret.second == v2.end()) {
        MK_PRINT_MSG("end of v2");
    }
    else{
        MK_PRINT_MSG("ret = <%d, %d>", *ret.first, *ret.second);
    }
}

//todo:以下2个用例需要C++14的支持,目前linux测试机gcc版本不够
#ifdef __WINDOWS__
TEST(NMSQ, mismatch3)
{
    auto func = [](vector<int>& v1, vector<int>& v2) {
        auto ret = std::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end());
        
        if(ret.first == v1.end()) {
            MK_PRINT_MSG("end of v1");
        }
        else if(ret.second == v2.end()) {
            MK_PRINT_MSG("end of v2");
        }
        else{
            MK_PRINT_MSG("ret = <%d, %d>", *ret.first, *ret.second);
        }
    };
    
    {
        vector<int> v1{1,2,3,3,4};
        vector<int> v2{1,2,3,3,4,5,6};
        func(v1, v2);
    }
    
    {
        vector<int> v1{1,2,3,3,4,6,8};
        vector<int> v2{1,2,3,3,4};
        func(v1, v2);
    }
}

TEST(NMSQ, mismatch4) 
{
    auto func = [](vector<int>& v1, vector<int>& v2) {
        auto ret = std::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end(), [](int n1, int n2){return (n1/2) == (n2/4);});
        
        if(ret.first == v1.end()) {
            MK_PRINT_MSG("end of v1");
        }
        else if(ret.second == v2.end()) {
            MK_PRINT_MSG("end of v2");
        }
        else{
            MK_PRINT_MSG("ret = <%d, %d>", *ret.first, *ret.second);
        }
    };
    
    {
        vector<int> v1{2,4,6};
        vector<int> v2{4,8,12,16,5};
        func(v1, v2);
    }
    
    {
        vector<int> v1{2,4,6,8,5};
        vector<int> v2{4,8,12};
        func(v1, v2);
    }
}
#endif