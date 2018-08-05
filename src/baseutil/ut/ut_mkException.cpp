/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include "mkException.h"

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
