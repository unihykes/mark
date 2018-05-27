/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// FibonacciUT
//

class FibonacciUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

//递归
uint64_t imp_Fibonacci_recursion(const uint64_t& n)
{
	if(n<=2) {
		return n;
	}
	
	return imp_Fibonacci_recursion(n -1) + imp_Fibonacci_recursion(n -2);
};

TEST_F(FibonacciUT, Fibonacci_recursion)
{
	//递归性能太差,计算到i=40左右的时候,就快跑不动了.
	for(int64_t i = 0; i != 100; ++i) {
		cout << "step" << i << "=" << imp_Fibonacci_recursion(i) <<endl;
	}
}

TEST_F(FibonacciUT, Fibonacci_normal)
{
	auto imp_Fibonacci = [&](const uint64_t& n) ->uint64_t{
		if(n<=2) {
			return n;
		}
		//i>92的话,返回值会越界
		
		uint64_t fibone=1;
		uint64_t fibtwo=2;
		uint64_t fibN=0;
		
		for(uint64_t i=3; i<=n; ++i){
			fibN=fibone+fibtwo;
			fibone=fibtwo;
			fibtwo=fibN;
		}
		return fibN;
	};
	
	for(uint64_t i = 0; i != 92; ++i) {
		cout << "step" << i << "=" << imp_Fibonacci(i) <<endl;
	}
}

TEST_F(FibonacciUT, Fibonacci_safe)
{
	unsigned int uintmax = ~0;//4294967295
	auto imp_Fibonacci = [&](unsigned int n) ->unsigned int{
		if(n<=2) {
			return n;
		}
		
		unsigned int fibone=1;
		unsigned int fibtwo=2;
		unsigned int fibN=0;
		
		for(unsigned int i=3; i<=n; ++i){
			if(uintmax - fibtwo < fibone) {
				cout<<"maxstep = " << i-1 <<endl;//step46=2971215073, step47就unsigned int越界了
				return -1;
			}
			else {
				fibN=fibone+fibtwo;
				fibone=fibtwo;
				fibtwo=fibN;
			}
		}
		return fibN;
	};
	
	
	for(unsigned int i = 0; i != 1000; ++i) {
		unsigned int ret = imp_Fibonacci(i);
		if(ret == -1) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;
	}
}

template<typename T>
T imp_Fibonacci_T(const T& n, const T& maxValue)
{
	if(n<=2) {
		return n;
	}
	
	T fibone=1;
	T fibtwo=2;
	T fibN=0;
	
	for(T i=3; i<=n; ++i){
		if(maxValue - fibtwo < fibone) {
			cout<<"maxstep = " << i-1 <<endl;
			return maxValue;
		}
		else {
			fibN=fibone+fibtwo;
			fibone=fibtwo;
			fibtwo=fibN;
		}
	}
	return fibN;
}

TEST_F(FibonacciUT, Fibonacci_T)
{
	//short
	for(short i = 0; i != 1000; ++i) {
		short ret = imp_Fibonacci_T(i, short(SHRT_MAX));
		if(ret == short(SHRT_MAX)) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 22, 下一阶,ret就越界了
	}
	
	//unsigned short
	for(unsigned short i = 0; i != 1000; ++i) {
		unsigned short ret = imp_Fibonacci_T(i, unsigned short(USHRT_MAX));
		if(ret == unsigned short(USHRT_MAX)) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 23, 下一阶,ret就越界了
	}
	
	//int
	for(int i = 0; i != 1000; ++i) {
		int ret = imp_Fibonacci_T(i, int(INT_MAX));
		if(ret == int(INT_MAX)) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 45, 下一阶,ret就越界了
	}
	
	//unsigned int
	for(unsigned int i = 0; i != 1000; ++i) {
		unsigned int ret = imp_Fibonacci_T(i, unsigned int(UINT_MAX));
		if(ret == unsigned(-1)) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 46, 下一阶,ret就越界了
	}
	
	//long long
	for(int64_t i = 0; i != 1000; ++i) {
		int64_t ret = imp_Fibonacci_T(i, int64_t(LLONG_MAX));
		if(ret == int64_t(LLONG_MAX)) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 91, 下一阶,ret就越界了
	}
	
	//unsigned long long
	for(uint64_t i = 0; i != 1000; ++i) {
		uint64_t ret = imp_Fibonacci_T(i, uint64_t(ULLONG_MAX));
		if(ret == uint64_t(ULLONG_MAX) ) {
			break;
		}
		cout << "step" << i << "=" << ret <<endl;//max step = 92, 下一阶,ret就越界了
	}
}

