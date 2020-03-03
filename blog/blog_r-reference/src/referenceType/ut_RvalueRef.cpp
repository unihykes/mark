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

Time:2018-4

info:
    [右值引用]
***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

template<class T>
char IsRight(const T& value)
{
    return 'L';
}

template<class T>
char IsRight(const T&& value)//添加const以禁用universal&&
{
    return 'R';
}

int&& func_R()
{
    int ret = 1024;
    return std::move(ret);
}

TEST(ut_RvalueRef, RvalueRef1)
{
    int&& num = 100;
    MK_PRINT_MSG("100             is %c-value", IsRight(100));//字面量
    MK_PRINT_MSG("num             is %c-value", IsRight(num));//具名的[右值引用]类型的[左值]变量
    
    int&& result = func_R();
    MK_PRINT_MSG("func_R          is %c-value", IsRight(func_R));//函数名(函数指针)
    MK_PRINT_MSG("func_R()        is %c-value", IsRight(func_R() ));//函数返回值-匿名对象
    MK_PRINT_MSG("result          is %c-value", IsRight(result));//函数返回值-具名对象
}


TEST(ut_RvalueRef, RvalueRef2)
{
    //T&
    //const T&
    //T&&
    //const T&&
    
    int n = 100;
    const int const_n = 200;
    
    int& L_Ref_to_L = n;                                            //引用自->非const左值

    const int& cL_ref_to_L = n;                                     //引用自->非const左值
    const int& cL_ref_to_cL = const_n;                              //引用自->  const左值
    const int& cL_ref_to_R = static_cast<int&&>(n);                 //引用自->非const右值
    const int& cL_ref_to_cR = static_cast<const int&&>(const_n);    //引用自->  const右值
    
    int&& R_ref_to_R = static_cast<int&&>(n);                       //引用自->非const右值
    
    const int&& cR_ref_to_R = static_cast<int&&>(n);                //引用自->非const右值
    const int&& cR_ref_to_cR = static_cast<const int&&>(const_n);   //引用自->  const右值
}
