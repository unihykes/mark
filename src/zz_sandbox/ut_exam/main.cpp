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

#include <gtest/gtest.h>

#include <mkheaders.h>
#include <thread>
#include <mutex>

int main(int argc, char** argv) 
{
	// 获取输入参数
	if(argc == 1) {
		printf("eg: ./test --gtest_filter=aaaUT.*    or: ./test --gtest_filter=aaaUT.*:bbbUT.*");
		return 0;
	}
	
	testing::InitGoogleTest(&argc, argv); 
	
	int ret = RUN_ALL_TESTS ();
	return ret;
}


TEST(FUN, t1)
{
	int i = 1024;
    unsigned char str[4];
	str[0] = ((unsigned char)(i >> 24) & 0xFF);
	str[1] = ((unsigned char)(i >> 16) & 0xFF);
	str[2] = ((unsigned char)(i >> 8) & 0xFF);
	str[3] = ((unsigned char)(i >> 0) & 0xFF);
    cout<<i<<endl;
}

template<class T>
char func(const T& value)
{
    return 'a';
}

template<class T>
char func(const T&& value)
{
    return 'b';
}

TEST(FUN, t2)
{
    int&& v1 = 16;
    int v2 = 32;
    int v3 = 64;
    
    cout<<func(nullptr)<<func(v1)<<func(++v2)<<func(v3++)<<endl;
}

TEST(FUN, t3)
{
    struct alignas(4) AAA
    {
        int a;
        short b;
        char c;
        int d;
    };
    
    struct alignas(8) BBB
    {
        int a;
        short b;
        char c;
        int d;
    };
    
    cout<<sizeof(AAA)<<"-"<<sizeof(BBB)<<endl;
}

TEST(FUN, t4)
{
    int a = 32;
    
    auto func = [&a](int& b)
    {
        b = a++;
        cout<<a<<"-"<<b<<endl;
    };
    
    func(a);
}


TEST(FUN, t5)
{
    class A
    {
    public:
        A(){cout<<"1";}
        ~A(){cout<<"2";}
    };
    
    
    class B: public A
    {
    public:
        B(){cout<<"3";}
        ~B(){cout<<"4";}
    };
    
    do{
        std::unique_ptr<A> a(new B);
    }while(false);
    
    cout<<endl;
}

void func6(int v)
{
    cout<<v<<endl;
}

TEST(FUN, t6)
{
    int v1 = 7;
    int v2 = 8;
    
    #define MAC(a,b)  #a###b
    cout<<MAC(v1,v2)<<endl;
}

TEST(FUN, t7)
{
    class A
    {
    public:
        A(){cout<<"1";f();}
        virtual ~A(){cout<<"2";}
        
        virtual void f() = 0;
    };
    
    
    class B: public A
    {
    public:
        B(){cout<<"3";f();}
        ~B(){cout<<"4";}
        
        virtual void f()
        {
            cout<<"bbb"<<endl;
        }
    };
    
    do{
        std::unique_ptr<A> a(new B);
    }while(false);
    cout<<endl;
    
}
