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

Time:2017-9

info:

***************************************************************************************************/
#include <markcore.h>
#include <gtest/gtest.h>
#include <boost/timer/timer.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/atomic/atomic.hpp>
//#include <boost/pool/object_pool.hpp>
#include<boost/exception/all.hpp>

TEST(timer, run)
{
    //boost::timer::auto_cpu_timer t;
    //MK_PRINT("is_stopped = %d", t.is_stopped());
    MK_PRINT("xxx");
    
    boost::shared_ptr<int> p(new int(111));
    boost::atomics::atomic_int64_t  val(1024);
}
#define DEFINE_NC_ERROR_INFO(type,name)									\
	typedef boost::error_info<struct nc_tag_##name, type> set_##name;	\
																				\
	type name() const															\
	{																			\
		const type* result = boost::get_error_info<set_##name>(*this);		\
		if (result) {															\
			return *result;													\
		}																		\
		else																	\
			return type();													\
	}
class ncException : virtual public std::exception, virtual public boost::exception
{
public:
	DEFINE_NC_ERROR_INFO(int, errId);
	DEFINE_NC_ERROR_INFO(string, errMsg);
	DEFINE_NC_ERROR_INFO(string, errPath);
	DEFINE_NC_ERROR_INFO(string, errFun);
	DEFINE_NC_ERROR_INFO(int, errLine);
	DEFINE_NC_ERROR_INFO(ncException, parentErr);
	
public:
	string toFullString() const
	{
		if(errMsg().empty()) {
			return what();
		}
		
		char buf[1024];
		sprintf(buf,"%s\n（errId:%d,errPath:%s,errFun:%s,errLine:%d）"
				,errMsg().c_str(),errId(), errPath().c_str(),errFun().c_str(),errLine());
		string result = buf;
		return result;
	}
};
#define NC_THROW(id,msg)													\
	do {																		\
		ncException __e;														\
		__e << ncException::set_errId (id);								\
		__e << ncException::set_errMsg (msg);								\
		__e << ncException::set_errPath(string(__FILE__));				\
		__e << ncException::set_errFun(string(__func__));			\
		__e << ncException::set_errLine(__LINE__);						\
		throw __e;																\
	}while (0);

#define NC_RETHROW(id,msg,parentErr)										\
	do {																		\
		ncException __re;														\
		__re << ncException::set_errId (id);								\
		__re << ncException::set_errMsg (msg);							\
		__re << ncException::set_errPath(string(__FILE__));				\
		__re << ncException::set_errFun(string(__func__));			\
		__re << ncException::set_errLine(__LINE__);						\
		__re << ncException::set_parentErr(parentErr);					\
		throw __re;															\
	}while (0);
	

	

void nctestException()
{
	try {
		try {
			NC_THROW (10, "xxxx");
		}
		catch (ncException& e) {
			NC_RETHROW (11, "other info", e);
		}
	}
	catch (ncException& e) {
		cout << e.toFullString()<<endl;
		
		ncException parent = e.parentErr();
		cout << parent.toFullString()  <<endl;
		
		ncException parent2 = parent.parentErr();
		cout << parent2.toFullString()  <<endl;	

	}
}


/*
void nc_pool ()
{
    struct A
    {
        int a,b,c;
        A(int x =1, int y =2, int z =3)
            :a (x)
            ,b (y)
            ,c (z)
        {
        }
    };
	// pool
	pool<> ipool(sizeof(int));
	int* p = static_cast<int*>(ipool.malloc());
	if (p) {
		if (ipool.is_from(p)) {
			cout << "p is from ipool" <<endl;
		}
		else {
			cout << "p is not from ipool" <<endl;
		}
		//cout << *p <<endl;
	}
	else {
		cout<< "p is null" <<endl;
	}
	ipool.free(p);
	
	// object_pool
	object_pool<A> aPool;
	A* pa = aPool.malloc();
	new (pa) A(6,7,7);
	
	if (aPool.is_from(pa)) {
		cout <<pa->a <<endl;
	}
	// object_pool的construct函数最多3个参数，如需要扩展，可以执行/boost/pool/detail下的2个脚本
	// ./pool_construct_simple.sh 6
	// ./pool construct.sh 6
	pa = aPool.construct(7,8,9);
	cout<<pa->a<<endl;
	
	A* pb = aPool.construct(5,6,7);
	cout <<pb->a<<endl;
}
*/



/*
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/uuid/uuid_io.hpp>
using namespace boost::uuids;

void ncUUID ()
{
	// nil生成器
	uuid u = nil_uuid();
	if (u.is_nil()) {
		cout<<u <<endl;
	}
	else {
		cout<<"见鬼了"<<endl;
	}
	
	// 字符串生成器
	string_generator sgen;
	uuid us = sgen("0123456789abcdef0123456789abcdef");
	cout<<us<<endl;
	
	// 名字生成器
	uuid basename = string_generator()("0123456789abcdef0123456789abcdef");
	name_generator ngen(basename);
	uuid u1 = ngen("liuhao");
	uuid u2 = ngen("hello");
	cout<< "u1="<<u1 << endl;
	cout <<"u2="<<u2 << endl;
	
	// 随机生成器
	random_generator rgen;
	uuid u3 = rgen ();
	cout << "u3="<<u3<<endl;
	uuid u4 = rgen ();
	cout <<"u4="<<u4 <<endl;
	
	// 转换为字符串
	string myuuid = to_string(u3);
	cout <<"myuuid="<<myuuid<<endl;
}

#include <boost/uuid/sha1.hpp>
using namespace boost::uuids::detail;
void ncSha ()
{
	sha1 sha;
	char msg[]  = "hello world!";
	sha.process_bytes(msg, strlen(msg));
	unsigned int digest [5];
	sha.get_digest(digest);
	for (int i = 0; i != 5; ++i) {
		cout << hex << digest[i] <<endl;
		cout << dec << endl;
		//cout << oct <<endl;//8进制输出
		//cout << dec <<endl;// 10进制输出
	}
}

*/
////////////////////////////////////////////////////////////////////////////////
// 
//

/*

////////////////////////////////////////////////////////////////////////////////
// 
//
#include<boost/lexical_cast.hpp>
void ncLexical_cast()
{
	int x = lexical_cast<int> ("100");
	long y = lexical_cast<long> ("2000");
	float pi = lexical_cast<float> ("3.14159e5");
	double e = lexical_cast<double> ("2.71828");
	string str1 = lexical_cast<string> ("456");
	string str2 = lexical_cast<string> ("1.14");
	string str3 = lexical_cast<string> (0x10);
	bool bx = lexical_cast<bool>("1");
	
}

////////////////////////////////////////////////////////////////////////////////
// 
//
#include<boost/xpressive/xpressive_dynamic.hpp>

#include<boost/assert.hpp>
void ncRegex()
{
	using namespace boost::xpressive;	
	cregex reg = cregex::compile("a.c");
	BOOST_ASSERT(regex_match("abc", reg));//匹配
	BOOST_ASSERT(regex_match("ac", reg));//不匹配
}

*/
////////////////////////////////////////////////////////////////////////////////
// main
//

/*
int main()
{
	nc_progress_timer();
	nc_progress_display();
	nc_Date();
	nc_Ptr();
//	nc_pool();
//	ncUUID();
//	ncSha ();
//	nctestException();
//	ncLexical_cast();
//	ncRegex();
}
*/

/*
#include <mkheaders.h>
#include <boost/date_time/posix_time/posix_time.hpp>

void isBoostDateTimeWorks ()
{
	boost::posix_time::ptime pt(boost::posix_time::second_clock::local_time());
	boost::gregorian::date d = pt.date ();
	boost::posix_time::time_duration td = pt.time_of_day ();

	String curTimeStr;
	curTimeStr.format (_T("%04d-%02d-%02d %02d:%02d:%02d"),
		d.year (), d.month (), d.day (),
		td.hours (), td.minutes (), td.seconds ());

	printMessage2(_T("%s\n"), curTimeStr.getCStr ());
	printMessage2 (_T("isBoostDateTimeWorks success\n"));
}

int main (int argc, char** argv)
{

	isBoostDateTimeWorks ();

	return 0;
}
*/