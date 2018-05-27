/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>
#include <bitset>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ZigzagUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

// zigzag
//ZigZag数组就是形如下图的，依次沿对角线增加->减小交替变换的数组

//0       1       5       6       14      15      27      28

//2       4       7       13      16      26      29      42
//3       8       12      17      25      30      41      43
//9       11      18      24      31      40      44      53
//10      19      23      32      39      45      52      54
//20      22      33      38      46      51      55      60
//21      34      37      47      50      56      59      61
//35      36      48      49      57      58      62      63
static const int N=10;
void zigzag()
{
	int a[N][N];
	int b=0;
	for(int i=0;i<N;i++)//上三角和对角线
	{
		if(i%2!=0)//分奇偶数 上下数
		{
		   for(int j=i;j>=0;j--)
			  a[i-j][j]=b++;
		}
		else
		{
			for(int j=i;j>=0;j--)
				a[j][i-j]=b++;
		}
	}
	for(int i=1;i<=N-1;i++)//下三角
	{
		if(i%2==0)
		{
			for(int j=i;j<N;j++)
				a[N+i-1-j][j]=b++;  //注意此时i坐标
		}
		else
		{
			for(int j=i;j<N;j++)
				a[j][N+i-1-j]=b++;
		}
	}
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<N;j++)
		   cout<<a[i][j]<<'\t';
		cout<<endl;
	}
}

TEST_F(ZigzagUT, Start)
{
	zigzag();
}

