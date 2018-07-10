/***************************************************************************************************
Author:liu.hao

Time:2017-9

info:

***************************************************************************************************/

#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// 
//
#include<boost/timer.hpp>
using namespace boost;

void nc_progress_timer()
{
	// timer
	//stringstream ss;
	{
		//timer t(ss);
        timer t;
		cout<<"max timespan:" << t.elapsed_max()/3600 << "h" << endl;
		cout <<"min timespan" << t.elapsed_min() <<"s" << endl;
		cout <<"now time elapsed:" << t.elapsed () << "s" << endl;
	}
	//cout<<"xx" <<ss.str();
}

////////////////////////////////////////////////////////////////////////////////
// 
//
void nc_progress_display()
{
    /*
	//progress_display
	vector<int> v(100);
	progress_display pd(long(v.size()));
	for(int i = 0; i != 100; ++i) {
		++pd;
		//sleep(1);
	}
    */
}

////////////////////////////////////////////////////////////////////////////////
// 
//
#include<boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
void nc_Date()
{
	// date
	date d1;
	date d2(2014, 12, 16);
	cout<<d1<<endl;
	cout<<d2<<endl;
}

////////////////////////////////////////////////////////////////////////////////
//        
//
#include<boost/smart_ptr.hpp>
void nc_Ptr()
{
	// scoped_ptr
	int* p = new int(111);
	scoped_ptr<int> ap (p);
	if (ap) {
		cout<<*ap<<endl;
	}
	else {
		cout<<"ap is null"<<endl;
	}
	
	// scoped_array
	int* arr = new int[10];
	scoped_array<int> sArr (arr);
	sArr[0] = 222;
	cout<< sArr[0]<<endl;
	
	
	// shared_ptr
	// 工厂函数make_shared
	boost::shared_ptr<int> sp = boost::make_shared<int>(333);
	if (sp) {
		cout << *sp <<endl;
	}
	else {
		cout<<"sp is null" <<endl;
	}
		
	// static_pointer_cast
	boost::shared_ptr<void> vp (new int(444));
	boost::shared_ptr<int> realp = static_pointer_cast<int>(vp);
	cout<<*realp<<endl;
	
	// shared_array
	shared_array<int> parr(new int[10]);
	parr[0] = 555;
	cout<<parr[0] <<endl;
}

// 工厂模式
class abstract
{
public:
	virtual void fun() = 0;
protected:
	virtual ~abstract()
	{
		//析构函数protected，意味着除了自己和它的子类，其他对象无权调用delete删除它；	
	}
	
};
class imp :public abstract
{
public:
	virtual void fun()
	{
		cout<<"call class imp" <<endl;
	}
};
void nc_create_delete_abstract()
{
	boost::shared_ptr<abstract> p (new imp);
	p->fun();
	//利用工厂模式保证了指针的安全使用
	//delete p.get();		//error:virtual abstract::~abstract()’是保护的
}

////////////////////////////////////////////////////////////////////////////////
// 
//

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

#include<boost/pool/pool.hpp>

/*
#include<boost/pool/object_pool.hpp>

void nc_pool ()
{
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

////////////////////////////////////////////////////////////////////////////////
// 
//
#include<boost/noncopyable.hpp>

class donotcopy : public noncopyable
{
};

////////////////////////////////////////////////////////////////////////////////
// 
//
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
#include<boost/exception/all.hpp>


#define NC_THROW(id,msg)													\
	do {																		\
		ncException __e;														\
		__e << ncException::set_errId (id);								\
		__e << ncException::set_errMsg (msg);								\
		__e << ncException::set_errPath(string(__FILE__));				\
		__e << ncException::set_errFun(string(__FUNCTION__));			\
		__e << ncException::set_errLine(__LINE__);						\
		throw __e;																\
	}while (0);

#define NC_RETHROW(id,msg,parentErr)										\
	do {																		\
		ncException __re;														\
		__re << ncException::set_errId (id);								\
		__re << ncException::set_errMsg (msg);							\
		__re << ncException::set_errPath(string(__FILE__));				\
		__re << ncException::set_errFun(string(__FUNCTION__));			\
		__re << ncException::set_errLine(__LINE__);						\
		__re << ncException::set_parentErr(parentErr);					\
		throw __re;															\
	}while (0);
	
#define DEFINE_NC_ERROR_INFO(type,name)									\
	typedef boost::error_info<struct nc_tag_##name, type> set_##name;	\
																				\
	type name() const															\
	{																			\
		const type* result = get_error_info<set_##name>(*this);		\
		if (result) {															\
			return *result;													\
		}																		\
		else																	\
			return type();													\
	}
	

class ncException : 
	virtual public std::exception, 
	virtual public boost::exception
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