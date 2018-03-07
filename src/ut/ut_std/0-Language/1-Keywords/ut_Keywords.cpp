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

class ut_Keywords : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
};

///C++ 关键词 C++ Keywords 
TEST_F(ut_Keywords, Keywords)
{
	#if 0
		alignas (C++11 起)			do						reinterpret_cast
		alignof (C++11 起)			double					register(2)
		and							dynamic_cast			requires (C++20 起)
		and_eq						else					return
		asm							enum					short
		atomic_cancel (TM TS)		explicit				signed
		atomic_commit (TM TS)		export(1)				sizeof(1)
		atomic_noexcept (TM TS)		extern(1)				static
		auto(1)						false					static_assert (C++11 起)
		bitand						float					static_cast
		bitor						for						struct(1)
		bool						friend					switch
		break						goto					synchronized (TM TS)
		case						if						template
		catch						import (模块 TS)		this
		char						inline(1)				thread_local (C++11 起)
		char16_t (C++11 起)			int						throw
		char32_t (C++11 起)			long					true
		class(1)					module (模块 TS)		try
		compl						mutable(1)				typedef
		concept (C++20 起)			namespace				typeid
		const						new						typename
		constexpr (C++11 起)		noexcept (C++11 起)		union
		const_cast					not						unsigned
		continue					not_eq					using(1)
		co_await (协程 TS)			nullptr (C++11 起)		virtual
		co_return (协程 TS)			operator				void
		co_yield (协程 TS)			or						volatile
		decltype (C++11 起)			or_eq					wchar_t
		default(1)					private					while
		delete(1)					protected				xor
									public					xor_eq
	#endif
	/**
	标注(1):C++11 中含义改变或添加新含义。注意：关键词 export 亦为模块 TS 所用。 
	标注(2):C++17 中含义改变。 
	*/
}

///在C++11中有修改
TEST_F(ut_Keywords, Modify_In_Cplusplus11)
{
	#if 0
	// C++11 中含义改变或添加新含义
	auto(1)		class(1)	default(1)	delete(1)	export(1)	extern(1)	inline(1)
	mutable(1)	sizeof(1)	struct(1)	using(1)
	
	// c++17中含义改变
	register(2)
	#endif
	
	//delete ([]{return new int; })(); // OK
	//delete []{return new int; }(); // 剖析错误
}

///C++11中新增
TEST_F(ut_Keywords, Add_In_Cplusplus11)
{
	#if 0
	//c++11起
	alignas (C++11 起)		alignof (C++11 起)		char16_t (C++11 起)		char32_t (C++11 起)
	constexpr (C++11 起)	decltype (C++11 起)		noexcept (C++11 起)		nullptr (C++11 起)
	static_assert(C++11 起)	thread_local (C++11 起)
	#endif
}

TEST_F(ut_Keywords, Demo)
{
	struct alignas(8) S {};
}