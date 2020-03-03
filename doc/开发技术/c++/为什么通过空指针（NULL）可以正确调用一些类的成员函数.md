http://blog.csdn.net/g5dsk/article/details/7017387

```cpp


// xx.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <vector>
using namespace std;
struct ncABC
{
       ncABC()
              :i(100)
       {
       }
       
       void fun()
       {
              int* b = &i;
       }
       
       int                        i;
};
int _tmain(int argc, _TCHAR* argv[])
{
       ncABC* a = NULL;
       a->fun();
       
       int *b = &(a->i);
       return 0;

}

```