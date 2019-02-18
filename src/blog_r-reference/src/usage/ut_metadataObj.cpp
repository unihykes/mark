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

Time:2018-3

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkUniqueProfilePoint.h"
#include "ncMetadataObj.h"

static double usedSecond = 0;  //用来保存指定作用域所消耗时间

////////////////////////////////////////////////////////////////////////////////////////////////////

//[测试不同的访问方式]访问者不同的访问方式,调用的接口不同;
TEST(ut_metadataObj, push_back)
{
    ncMetadataObj obj;
    
    {
        mkUniqueProfilePoint point(usedSecond);
        ncNewCustomString str("some string...");
        obj.push_back(str);
    }
    MK_PRINT_MSG("push_back--1 usedSecond = %.2f\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        ncNewCustomString str("some string...");
        obj.push_back(std::move(str));
    }
    MK_PRINT_MSG("push_back--2 usedSecond = %.2f\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        obj.push_back(ncNewCustomString("some string..."));
    }
    MK_PRINT_MSG("push_back--3 usedSecond = %.2f\n", usedSecond);
}



//[测试按值返回]: 类自身实现了右值引用拷贝构造函数,才能提升按值返回的性能
ncOldCustomString GetOldString()
{
    ncOldCustomString str("some string");
    return str;
}
ncNewCustomString GetNewString()
{
    ncNewCustomString str("some string");
    return str;
}
TEST(ut_metadataObj, return_Value)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        GetOldString();
    }
    MK_PRINT_MSG("usedSecond = %.2f\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        GetNewString();
    }
    MK_PRINT_MSG("usedSecond = %.2f\n", usedSecond);
}



//[测试按值传参]: 类实现了按值传参函数(本例中是类的构造函数),是否能提升性能,还取决于参数类是否对右值引用做了兼容;
TEST(ut_metadataObj, constructor)
{
    {
        mkUniqueProfilePoint point(usedSecond);
        ncMetadataObj obj1(ncOldCustomString("some string..."));
        obj1.fun();
    }
    MK_PRINT_MSG("obj1 usedSecond = %.2f\n", usedSecond);
    
    {
        mkUniqueProfilePoint point(usedSecond);
        ncMetadataObj obj2(ncNewCustomString("some string..."));
        obj2.fun();
    }
    MK_PRINT_MSG("obj2 usedSecond = %.2f", usedSecond);
}





