


```cpp

#include<iostream>
#include<stack>
using namespace std;
int main(void)
{
     stack<double>s;//定义一个栈
     for(int i=0;i<10;i++)
          s.push(i);
     while(!s.empty())
     {
          printf("%lf\n",s.top());
          s.pop();
     }
     cout<<"栈内的元素的个数为："<<s.size()<<endl;
     return 0;
}



c++ stl栈stack介绍
C++ Stack（堆栈） 是一个容器类的改编，为程序员提供了堆栈的全部功能，——也就是说实现了一个先进后出（FILO）的数据结构。
c++ stl栈stack的头文件为: 
#include <stack> 
c++ stl栈stack的成员函数介绍
操作 比较和分配堆栈
empty() 堆栈为空则返回真
pop() 移除栈顶元素
push() 在栈顶增加元素
size() 返回栈中元素数目
top() 返回栈顶元素

其他资料：
http://www.cnblogs.com/music-liang/archive/2013/04/10/3011701.html


注意点：

元素入栈
    stack堆栈容器的元素入栈函数为 push 函数。由于 C++ STL 的堆栈函数是不预设大小的，因此，入栈函数就不考虑堆栈空间是否为满，均将元素压入堆栈，从而函数没有标明入栈成功与否的返回值。
    如下是他的使用原型：
    void  push(const value_type& x)
    
    
元素出栈
    stack容器的元素出栈函数为 pop 函数，由于函数并没有判断堆栈是否为空，才进行元素的弹出，因此，需要自行判断堆栈是否为空，才可执行 pop 函数。
    void pop()
    
    下面的示例代码，将堆栈的所有元素全部出栈
    // stack<int>  s;
    while(!s.empty())
    {
        s.pop();// 出栈
    }
    
    
取栈顶元素
    stack容器的栈顶元素的读取函数为 pop 函数，将取出最后入栈的元素，如下是它的使用原型
    value_type&  top()

堆栈非空判断
    随着堆栈元素不断出栈，堆栈可能会出现空的情况，因此，一般需要调用 empty 函数判断是否非空，才作元素出栈和取栈顶元素的操作。
    bool  empty()
    判断堆栈是否为空，返回 true 表示堆栈已空，false 表示堆栈非空。



```