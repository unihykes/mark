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

//关键字
TEST_F(utLanguage, Keywords)
{
	#if 0
	alignas (C++11 起)
	alignof (C++11 起)
	and
	and_eq
	asm
	atomic_cancel (TM TS)
	atomic_commit (TM TS)
	atomic_noexcept (TM TS)
	auto(1)
	bitand
	bitor
	bool
	break
	case
	catch
	char
	char16_t (C++11 起)
	char32_t (C++11 起)
	class(1)
	compl
	concept (C++20 起)
	const
	constexpr (C++11 起)
	const_cast
	continue
	co_await (协程 TS)
	co_return (协程 TS)
	co_yield (协程 TS)
	decltype (C++11 起)
	default(1)
	delete(1)
	do
	double
	dynamic_cast
	else
	enum
	explicit
	export(1)
	extern(1)
	false
	float
	for
	friend
	goto
	if
	import (模块 TS)
	inline(1)
	int
	long
	module (模块 TS)
	mutable(1)
	namespace
	new
	noexcept (C++11 起)
	not
	not_eq
	nullptr (C++11 起)
	operator
	or
	or_eq
	private
	protected
	public
	reinterpret_cast
	register(2)
	requires (C++20 起)
	return
	short
	signed
	sizeof(1)
	static
	static_assert (C++11 起)
	static_cast
	struct(1)
	switch
	synchronized (TM TS)
	template
	this
	thread_local (C++11 起)
	throw
	true
	try
	typedef
	typeid
	typename
	union
	unsigned
	using(1)
	virtual
	void
	volatile
	wchar_t
	while
	xor
	xor_eq 
	#endif
}

//预处理器
TEST_F(utLanguage, preprocessor)
{
	///#line
	cout<<__LINE__<<endl;//正确行数
	//更改当前行号为777
	#line 777
	cout<<__LINE__<<endl;//777
	cout<<__LINE__<<endl;//778
	
	
	cout<<__FILE__<<":"<<__LINE__<<endl;//D:\monk\src\ut\ut_std\ut_language.cpp:781
	//更改当前行号为777,并且文件名改为test.cpp
	#line 777 "test.cpp"
	cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:777
	cout<<__FILE__<<":"<<__LINE__<<endl;//test.cpp:778
	
	//恢复行号
	#line 255
	
	/**
	#define 标识符 替换列表(可选) (1) 
	#define 标识符( 形参 ) 替换列表(可选) (2) 
	#define 标识符( 形参, ... ) 替换列表(可选) (3) (C++11 起) 
	#define 标识符( ... ) 替换列表(可选) (4) (C++11 起) 
	#undef 标识符 (5) 
	*/
	
	/**
	# 与 ## 运算符
	标识符前的 # 运算符经通过标识符运行形参替换，并将结果以引号环绕，等效地创建字符串字面量
	# 出现于 __VA_ARGS__ 前时，整个展开的 __VA_ARGS__ 被包在引号中： 
	## 运算符在二个标识符（首先未被宏展开）上运行形参替换，然后连接结果。此操作被称为“连接”或“记号粘贴”
	*/
	#define showlist(...) printf(#__VA_ARGS__)
	showlist(xx\n);            // 展开成 printf("xx\n")
	
	#define FUNCTION(name, a) int fun_##name() { return a;}
	
	/**
	下列宏名已预定义于任何翻译单元中。 
	__cplusplus
	指代所用的 C++ 标准版本，展开成值 199711L(C++11 前) 、 201103L(C++11) 、 201402L(C++14) 或 201703L(C++17) 
	(宏常量) 
	__STDC_HOSTED__(C++11)
	若实现有宿主（运行在 OS 下）则展开成整数常量 1 ，若独立（不随 OS 运行）则展开成 ​0​ 
	(宏常量) 
	__FILE__
	展开成当前文件名，作为字符串字面量，能以 #line 指令更改 
	(宏常量) 
	__LINE__
	展开成源文件行号，整数常量，能以 #line 指令更改 
	(宏常量) 
	__DATE__
	展开成翻译日期，形式为 "Mmm dd yyyy" 的字符串。若月的日数小于 10 则 "dd" 的首字符为空格。月份名如同以 std::asctime() 生成 
	(宏常量) 
	__TIME__
	展开成翻译时间，形式为 "hh:mm:ss" 的字符串字面量 
	(宏常量) 
	__STDCPP_DEFAULT_NEW_ALIGNMENT__(C++17)
	展开成 std::size_t 字面量，其值为调用不具对齐的 operator new 所保证的对齐（更大的对齐将传递给具对齐重载，如 operator new(std::size_t, std::align_val_t)） 
	(宏常量) 
	下列附加宏名可能为实现所预定义。 
	__STDC__
	若存在则为实现定义值，典型地用于指示 C 一致性 
	(宏常量) 
	__STDC_VERSION__(C++11)
	若存在则为实现定义值 
	(宏常量) 
	__STDC_ISO_10646__(C++11)
	若 wchar_t 使用 Unicode ，则展开成 yyyymmL 形式的整数常量，日期指示受支持 Unicode 的最近版本 
	(宏常量) 
	__STDC_MB_MIGHT_NEQ_WC__(C++11)
	若基础字符集的宽字符编码可以不等于其窄编码，则展开成 1 ，如在为 wchar_t 使用 Unicode 的基于 EBCDIC 的系统上。 
	(宏常量) 
	__STDCPP_STRICT_POINTER_SAFETY__(C++11)
	若实现支持严格 std::pointer_safety 则展开成 1 
	(宏常量) 
	__STDCPP_THREADS__(C++11)
	若程序能拥有多于一个执行线程则展开成 1 
	(宏常量) 
	*/
	
}














