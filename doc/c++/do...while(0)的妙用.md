

```cpp
在C++中，有三种类型的循环语句：for, while, 和do...while， 但是在一般应用中作循环时， 我们可能用for和while要多一些，do...while相对不受重视。
但是，最近在读我们项目的代码时，却发现了do...while的一些十分聪明的用法，不是用来做循环，而是用作其他来提高代码的健壮性。

1. do...while(0)消除goto语句。
通常，如果在一个函数中开始要分配一些资源，然后在中途执行过程中如果遇到错误则退出函数，当然，退出前先释放资源，我们的代码可能是这样：
version 1

bool Execute()
{
// 分配资源
int *p = new int;
bool bOk(true);

// 执行并进行错误处理
bOk = func1();
if(!bOk) 
{
delete p; 
p = NULL;
return false;
}

bOk = func2();
if(!bOk) 
{
delete p; 
p = NULL;
return false;
}

bOk = func3();
if(!bOk) 
{
delete p; 
p = NULL;
return false;
}

// ..........

// 执行成功，释放资源并返回
delete p; 
p = NULL;
return true;

}



这里一个最大的问题就是代码的冗余，而且我每增加一个操作，就需要做相应的错误处理，非常不灵活。于是我们想到了goto:
version 2

bool Execute()
{
// 分配资源
int *p = new int;
bool bOk(true);

// 执行并进行错误处理
bOk = func1();
if(!bOk) goto errorhandle;

bOk = func2();
if(!bOk) goto errorhandle;

bOk = func3();
if(!bOk) goto errorhandle;

// ..........

// 执行成功，释放资源并返回
delete p; 
p = NULL;
return true;

errorhandle:
delete p; 
p = NULL;
return false;

}



代码冗余是消除了，但是我们引入了C++中身份比较微妙的goto语句，虽然正确的使用goto可以大大提高程序的灵活性与简洁性，但太灵活的东西往往是很危险的，它会让我们的程序捉摸不定，那么怎么才能避免使用goto语句，又能消除代码冗余呢，请看do...while(0)循环：
version3

bool Execute()
{
// 分配资源
int *p = new int;

bool bOk(true);
do
{
// 执行并进行错误处理
bOk = func1();
if(!bOk) break;

bOk = func2();
if(!bOk) break;

bOk = func3();
if(!bOk) break;

// ..........

}while(0);

// 释放资源
delete p; 
p = NULL;
return bOk;

}



“漂亮！”， 看代码就行了，啥都不用说了...

2 宏定义中的do...while(0)
如果你是C++程序员，我有理由相信你用过，或者接触过，至少听说过MFC, 在MFC的afx.h文件里面， 你会发现很多宏定义都是用了do...while(0)或do...while(false)， 比如说：
#define AFXASSUME(cond) do { bool __afx_condVal=!!(cond); ASSERT(__afx_condVal); __analysis_assume(__afx_condVal); } while(0) 
粗看我们就会觉得很奇怪，既然循环里面只执行了一次，我要这个看似多余的do...while(0)有什么意义呢？ 
当然有！
为了看起来更清晰，这里用一个简单点的宏来演示：
#define SAFE_DELETE(p) do{ delete p; p = NULL} while(0)
假设这里去掉do...while(0),
#define SAFE_DELETE(p) delete p; p = NULL;
那么以下代码：
if(NULL != p) SAFE_DELETE(p)
else ...do sth...
就有两个问题，
1) 因为if分支后有两个语句，else分支没有对应的if，编译失败
2) 假设没有else, SAFE_DELETE中的第二个语句无论if测试是否通过，会永远执行。
你可能发现，为了避免这两个问题，我不一定要用这个令人费解的do...while, 我直接用{}括起来就可以了
#define SAFE_DELETE(p) { delete p; p = NULL;}
的确，这样的话上面的问题是不存在了，但是我想对于C++程序员来讲，在每个语句后面加分号是一种约定俗成的习惯，这样的话，以下代码:
if(NULL != p) SAFE_DELETE(p);
else ...do sth...
其else分支就无法通过编译了（原因同上），所以采用do...while(0)是做好的选择了。

也许你会说，我们代码的习惯是在每个判断后面加上{}, 就不会有这种问题了，也就不需要do...while了，如：
if(...) 
{
}
else
{
}
诚然，这是一个好的，应该提倡的编程习惯，但一般这样的宏都是作为library的一部分出现的，而对于一个library的作者，他所要做的就是让其库具有通用性，强壮性，因此他不能有任何对库的使用者的假设，如其编码规范，技术水平等。 

```