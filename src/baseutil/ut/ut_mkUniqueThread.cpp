/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <mkUniqueThread.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_mkUniqueThread : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
    class ncABC
    {
    public:
        void run(mkUniqueThread* thread)
        {
            MK_PRINT("");
            while(true) {
                MK_PRINT("");
                if(thread->NeedStop()) {
                    MK_PRINT("");
                    break;
                }
            }
            
            MK_PRINT("");
            throw string("something is wrong!");
        }
    private:
    };
};



TEST_F(ut_mkUniqueThread, normal)
{
    MK_PRINT("");
    ncABC abc;
    {
        MK_PRINT("");
        mkUniqueThread thread;
        thread.RunWithCallback(&ncABC::run, &abc);
        MK_PRINT("");
    }
    MK_PRINT("");
    cout<<endl;
}

TEST_F(ut_mkUniqueThread, Get)
{
    MK_PRINT("");
    ncABC abc;
    {
        MK_PRINT("");
        mkUniqueThread thread;
        thread.RunWithCallback(&ncABC::run, &abc);
        MK_PRINT("");
        
        thread.SetStop();
        thread.Get();
    }
    MK_PRINT("");
    cout<<endl;
}

TEST_F(ut_mkUniqueThread, exception)
{
    MK_PRINT("");
    ncABC abc;
    {
        MK_PRINT("");
        mkUniqueThread thread;
        thread.RunWithCallback(&ncABC::run, &abc);
        MK_PRINT("");
        try {
            MK_PRINT("");
            thread.SetStop();
            thread.Get();
            MK_PRINT("");
        }
        catch(std::string& errmsg){
            MK_PRINT("%s", errmsg.c_str());
        }
    }
    MK_PRINT("");
    cout<<endl;
}