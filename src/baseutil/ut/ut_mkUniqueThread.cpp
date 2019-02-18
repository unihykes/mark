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
                if(thread->NeedAbrot()) {
                    MK_PRINT("");
                    break;
                }
            }
            
            MK_PRINT("");
            if(0) {
                thread->SetFinished();
            }
            else {
                throw string("something is wrong!");
            }
        }
    private:
    };
};

TEST_F(ut_mkUniqueThread, lambda)
{
    MK_PRINT("");
    
    auto lam = [](mkUniqueThread* thread, int& a) ->void{
        MK_PRINT("a=%d",a);
        while(true) {
            if(thread->NeedAbrot()) {
                break;
            }
        }
        a = 222;
        thread->SetFinished();
    };
    
    {
        MK_PRINT("");
        int a = 11;
        mkUniqueThread thread(lam, std::ref(a));
        thread.SetAbort();
        thread.Get();
        MK_PRINT("a=%d",a);
    }
    
    MK_PRINT("");
    cout<<endl;
}

TEST_F(ut_mkUniqueThread, normal)
{
    MK_PRINT("");
    
    ncABC abc;
    
    {
        MK_PRINT("");
        mkUniqueThread thread(&ncABC::run, &abc);
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
        mkUniqueThread thread(&ncABC::run, &abc);
        MK_PRINT("");
        
        thread.SetAbort();
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
        mkUniqueThread thread(&ncABC::run, &abc);
        MK_PRINT("");
        try {
            MK_PRINT("");
            thread.SetAbort();
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