/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class utLanguage : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

TEST_F(utLanguage, ASCII)
{
	unsigned char ch = 0;
	for(int i = 0; i != 128; ++i) {
		MK_PRINT_MSG("%d = 0x%02x = %c", i, i, ch);
		++ch;
	}
}

//基础类型:std::is_fundamental
TEST_F(utLanguage, fundamental_types)
{
	//void类型:std::is_void
	cout << "sizeof(void*) = " << sizeof(void*) <<endl;
	
	//null类型:std::is_null_pointer 
	cout << "sizeof(std::nullptr_t) = " << sizeof(std::nullptr_t) <<endl;//c++11
	
	//算术类型:std::is_arithmetic 
	{
		//浮点类型:std::is_floating_point 
		{
			cout << "sizeof(float) = " << sizeof(float) <<endl;
			cout << "sizeof(double) = " << sizeof(double) <<endl;
			cout << "sizeof(long double) = " << sizeof(long double) <<endl;
		}
		//整数类型: std::is_integral
		{
			//bool
			cout << "sizeof(bool) = " << sizeof(bool) <<endl;
			
			//字符类型
			{
				//窄字符类型
				cout << "sizeof(char) = " << sizeof(char) <<endl;
				cout << "sizeof(signed char) = " << sizeof(signed char) <<endl;
				cout << "sizeof(unsigned char) = " << sizeof(unsigned char) <<endl;
				
				//宽字符类型
				cout << "sizeof(char16_t) = " << sizeof(char16_t) <<endl;//c++11
				cout << "sizeof(char32_t) = " << sizeof(char32_t) <<endl;//c++11
				cout << "sizeof(wchar_t) = " << sizeof(wchar_t) <<endl;
			}
			
			//有符号整数类型
			cout << "sizeof(short int) = " << sizeof(short int) <<endl;
			cout << "sizeof(int) = " << sizeof(int) <<endl;
			cout << "sizeof(long int) = " << sizeof(long int) <<endl;
			cout << "sizeof(long long int) = " << sizeof(long long int) <<endl;
			
			//无符号类型
			cout << "sizeof(unsigned short int) = " << sizeof(unsigned short int) <<endl;
			cout << "sizeof(unsigned int) = " << sizeof(unsigned int) <<endl;
			cout << "sizeof(unsigned long int) = " << sizeof(unsigned long int) <<endl;
			cout << "sizeof(unsigned long long int) = " << sizeof(unsigned long long int) <<endl;
		}
	}
	
}

//合成类型:std::is_compound 
TEST_F(utLanguage, compound_types)
{
	//引用类型:std::is_reference
		//左值引用:std::is_lvalue_reference
		//右值引用:std::is_rvalue_reference
	
	//指针类型:std::is_pointer 
		//指向对象指针
		//指向函数指针
		
	//指向成员指针类型:std::is_member_pointer
		//指向数据成员指针:std::is_member_object_pointer
		//指向成员函数指针:std::is_member_function_pointer
	
	//数组类型:std::is_array 
	
	//函数类型:std::is_function
	
	//枚举类型:std::is_enum
	
	//类类型
		//非联合类型:std::is_class 
		//联合类型:std::is_union
}


TEST_F(utLanguage, volatile)
{
	//防止优化编译器把变量从内存装入CPU寄存器中
	//volatile的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值
	volatile int i = 0x10;
	int a = i;
	MK_PRINT_MSG("i = %d", a);
	//do something
	int b = i;
	MK_PRINT_MSG("i = %d", b);
	
	
	
	//这个语句用来测试空循环的速度的, 但是编译器肯定要把它优化掉，根本就不执行
	for ( int i=0; i<100000; i++); 
	//如果添加volatile,它就会执行了
	for ( volatile int i=0; i<100000; i++); 
}

//这是 C++ 中的保留字列表。因为它们为语言所用，故这些关键词不可用于重定义或重载。
TEST_F(utLanguage, Keywords)
{
	#if 0
		//c++11前
		asm			bool		char		double		enum		float		int			long
		short		signed		union		unsigned	void		wchar_t
		const		explicit	static		virtual		volatile
		template	typename	friend		private		protected	public
		and			or			not			and_eq		or_eq		not_eq		bitand		bitor
		xor			xor_eq		true		false
		try			catch		throw		namespace
		do			while		for			goto		continue	break		return
		new			compl		operator	this		typeid		typedef
		if			else		switch		case
		const_cast	dynamic_cast			reinterpret_cast		static_cast
		
		// C++11 中含义改变或添加新含义
		auto(1)		class(1)	default(1)	delete(1)	export(1)	extern(1)	inline(1)
		mutable(1)	sizeof(1)	struct(1)	using(1)
		//delete ([]{return new int; })(); // OK
		//delete []{return new int; }(); // 剖析错误
		
		// c++17中含义改变
		register(2)
		
		//c++11起
		alignas (C++11 起)
		alignof (C++11 起)
		char16_t (C++11 起)
		char32_t (C++11 起)
		constexpr (C++11 起)
		decltype (C++11 起)
		noexcept (C++11 起)
		nullptr (C++11 起)
		static_assert (C++11 起)
		thread_local (C++11 起)
		
		//(C++20 起)
		concept (C++20 起)
		requires (C++20 起)
		
		//TM TS
		atomic_cancel (TM TS)
		atomic_commit (TM TS)
		atomic_noexcept (TM TS)
		synchronized (TM TS)
		
		//(协程 TS)
		co_await (协程 TS)
		co_return (协程 TS)
		co_yield (协程 TS)
		
		//(模块 TS)
		import (模块 TS)
		module (模块 TS)
	
	#endif
}

//预处理器
TEST_F(utLanguage, define)
{
	/**
	///#line
	cout<<__LINE__<<endl;//正确行数
	//更改当前行号为777
	#line 777
	cout<<__LINE__<<endl;
	cout<<__LINE__<<endl;
	
	cout<<__FILE__<<":"<<__LINE__<<endl;//D:\monk\src\ut\ut_std\ut_language.cpp:xxx
	//更改当前行号为xxx,并且文件名改为test.cpp
	#line 777 "test.cpp"
	cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:xxx
	cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:xxx
	
	//恢复行号
	#line 211
	*/
	
	//# 与 ## 运算符
	#define showlist(...) printf(#__VA_ARGS__)
	showlist(xx\n);			   // 展开成 printf("xx\n")
	
	#define FUNCTION(name, a) int fun_##name() { return a;}
}


//直接赋值
TEST_F(utLanguage, assign)
{
	int i = 100;
	int j = {};
	int k = {100};
}



//直接赋值
TEST_F(utLanguage, sizeof)
{
	int i = 100;
	cout << sizeof(int)<<endl;
	cout << sizeof(i) <<endl;
	cout << sizeof i <<endl;
}


struct mk_Foo
{
	int		i;
	float	f;
	char	c;
};
struct mk_Empty {};
struct alignas(64) mk_Empty64 {};

//查询类型的对齐要求:c++11
TEST_F(utLanguage, alignof)
{
	std::cout << "Alignment of"	 "\n"
		"- char				: " << alignof(char)		<< "\n"
		"- pointer			: " << alignof(int*)		<< "\n"
		"- class mk_Foo		: " << alignof(mk_Foo)		<< "\n"
		"- empty class		: " << alignof(mk_Empty)	<< "\n"
		"- alignas(64) Empty: " << alignof(mk_Empty64)	<< "\n";
}

struct Base {}; // 非多态
struct Derived : Base {};
struct Base2 { virtual void foo() {} }; // 多态
struct Derived2 : Base2 {};


//typeid
TEST_F(utLanguage, typeid)
{
	int myint = 50;
	std::string mystr = "string";
	double *mydoubleptr = nullptr;

	std::cout << "myint has type: " << typeid(myint).name() << '\n'
			  << "mystr has type: " << typeid(mystr).name() << '\n'
			  << "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';

	// std::cout << myint 为多态类型的泛左值表达式；求值它
	const std::type_info& r1 = typeid(std::cout << myint);
	std::cout << '\n' << "std::cout<<myint has type : " << r1.name() << '\n';

	// std::printf() 不是多态类型的泛左值表达式；不求值
	const std::type_info& r2 = typeid(std::printf("%d\n", myint));
	std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n';

	// 非多态左值为静态类型
	Derived d1;
	Base& b1 = d1;
	std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

	Derived2 d2;
	Base2& b2 = d2;
	std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';

	try {
		// 解引用空指针：对于非多态表达式 OK
		std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n'; 
		// 解引用空指针：对多态左值不 OK
		Derived2* bad_ptr = nullptr;
		std::cout << "bad_ptr points to... ";
		std::cout << typeid(*bad_ptr).name() << '\n';
	} catch (const std::bad_typeid& e) {
		 std::cout << " caught " << e.what() << '\n';
	}
}


//显式类型转换
TEST_F(utLanguage, Conversions)
{
	/**
	( new_type ) expression (1) 
	new_type ( expression ) (2) 
	new_type ( expressions ) (3) 
	new_type ( ) (4) 
	new_type { expression-list(可选) } (5) (C++11 起) 
	template ( expressions(可选) ) (6) (C++17 起) 
	template { expressions(可选) } (7) (C++17 起)
	*/
}

//字符
TEST_F(utLanguage, character)
{
	char ch1 = 'a';
	char ch2 = u8'a';//utf8
	
	char16_t ch3 = u'中';
	char32_t ch4 = U'中';
	
	wchar_t ch5 = L'中';
	int ch6 = '中';
	
	//todo:输出目前不准确
	cout<<ch1 <<endl;
	cout<<ch2 <<endl;
	cout<<ch3 <<endl;
	cout<<ch4 <<endl;
	cout<<ch5 <<endl;
	cout<<ch6 <<endl;
	
	const char* str1 = "abc";
	const char* str2 = u8"abc";//utf8
	
	const char16_t* str3 = u"中文";
	const char32_t* str4 = U"中文";
	
	const wchar_t* str5 = L"中文";
	const char* str6 = R"foo(www)foo";
	
	//todo:输出目前不准确
	cout<<str1 <<endl;
	cout<<str2 <<endl;
	cout<<str3 <<endl;
	cout<<str4 <<endl;
	cout<<str5 <<endl;
	cout<<str6 <<endl;
}

//用户定义字面量 (C++11 起)
// 用作转换
constexpr long double operator"" _deg ( long double deg )
{
	return deg*3.141592/180;
}
// 用于自定义类型
struct mytype
{
	mytype ( unsigned long long m):m(m){}
	unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
	return mytype(n);
}
// 用作副效应
void operator"" _print ( const char* str )
{
	std::cout << str;
}

//字面量运算符:C++11
TEST_F(utLanguage, userdefined)
{
	double x = 90.0_deg;
	std::cout << std::fixed << x << '\n';
	mytype y = 123_mytype;
	std::cout << y.m << '\n';
	0x123ABC_print;
}


//当你需要管理多个版本的类库的时候，可以用inline修饰namespace，来达到指定默认版本的目的，
namespace mk{
	namespace mk_utLanguage1
	{
		struct A
		{
			int _val;
			A():_val(10){}
		};
	}
	
	inline namespace mk_utLanguage2
	{
		struct A
		{
			int _val;
			A():_val(23){}
		};
	}
}
//命名空间别名
namespace mk_lan1 = mk::mk_utLanguage1;
namespace mk_lan2 = mk::mk_utLanguage2;

//inline namespace: C++11
TEST_F(utLanguage, inlinenamespace)
{
	//A a1;		//编译错误: 未声明的标识符
	
	mk::mk_utLanguage1::A a2;//使用mk_utLanguage1
	cout<<a2._val<<endl;
	
	mk::A a3;	//默认使用 mk_utLanguage2
	cout<<a3._val<<endl;
	
	mk::mk_utLanguage2::A a4;//显示指定 mk_utLanguage2
	cout<<a4._val<<endl;
}

//左值引用,右值引用
TEST_F(utLanguage, Lvalue_rvalue)
{
	//c++11
	//引用折叠
	//容许通过模板或 typedef 中的类型操作组成到引用的引用，该情况下应用引用折叠规则：
	//到右值引用的右值引用折叠成右值引用，
	//所有其他组合折叠成左值引用： 
	typedef int&  lref;
	typedef int&& rref;
	int n = 100;
	lref&  r1 = n; // 到左值引用的左值引用, r1 的类型是 int&
	lref&& r2 = n; // 到左值引用的右值引用, r2 的类型是 int&
	rref&  r3 = n; // 到右值引用的左值引用, r3 的类型是 int&
	rref&& r4 = 1; // 到右值引用的右值引用, r4 的类型是 int&&
	
	//int&& r5 = n;	//error C2440: “初始化”: 无法从“int”转换为“int &&”
	//int&&& r6 = n;	//error C2529: “r6”: 引用的引用非法 
	//int&&& r7 = n;	//error C2529: “r7”: 引用的引用非法
	//int&&&& r8 = 1;	//error C2529: “r8”: 引用的引用非法
	
	
	//转发引用
	//todo:
	
	
	//悬垂引用
	//注意右值引用和到 const 的左值引用能延长临时对象的生存期（参阅临时量生存期的规则和例外）。 
	
}


