/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkString.h"

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
