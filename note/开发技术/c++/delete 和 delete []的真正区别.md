
http://blog.csdn.net/cbnotes/article/details/38900799


```cpp


c++中对new申请的内存的释放方式有delete和delete[两种方式，到底这两者有什么区别呢？


1.我们通常从教科书上看到这样的说明：
delete 释放new分配的单个对象指针指向的内存
delete[] 释放new分配的对象数组指针指向的内存
那么，按照教科书的理解，我们看下下面的代码：
int *a = new int[10];
 delete a;        //方式1
 delete [] a;     //方式2
肯定会有很多人说方式1肯定存在内存泄漏，是这样吗？

（1）. 针对简单类型 使用new分配后的不管是数组还是非数组形式内存空间用两种方式均可 如：
   int *a = new int[10];
    delete a;
    delete [] a;
    此种情况中的释放效果相同，原因在于：分配简单类型内存时，内存大小已经确定，系统可以记忆并且进行管理，在析构时，系统并不会调用析构函数，
   它直接通过指针可以获取实际分配的内存空间，哪怕是一个数组内存空间(在分配过程中 系统会记录分配内存的大小等信息，此信息保存在结构体_CrtMemBlockHeader中，
   具体情况可参看VC安装目录下CRT\SRC\DBGDEL.cpp)

（2）. 针对类Class，两种方式体现出具体差异
    当你通过下列方式分配一个类对象数组：
   class A
    {
    private:
       char *m_cBuffer;
       int m_nLen;
    public:
       A(){ m_cBuffer = new char[m_nLen]; }
       ~A() { delete [] m_cBuffer; }
    };
    A *a = new A[10];
    delete a;         //仅释放了a指针指向的全部内存空间 但是只调用了a[0]对象的析构函数 剩下的从a[1]到a[9]这9个用户自行分配的m_cBuffer对应内存空间将不能释放 从而造成内存泄漏
   delete [] a;      //调用使用类对象的析构函数释放用户自己分配内存空间并且   释放了a指针指向的全部内存空间
所以总结下就是，如果ptr代表一个用new申请的内存返回的内存空间地址，即所谓的指针，那么：
   delete   ptr   代表用来释放内存，且只用来释放ptr指向的内存。
    delete[]   rg   用来释放rg指向的内存，！！还逐一调用数组中每个对象的destructor！！
   对于像int/char/long/int*/struct等等简单数据类型，由于对象没有destructor，所以用delete 和delete [] 是一样的！但是如果是C++对象数组就不同了！

关于 new[] 和 delete[]，其中又分为两种情况：(1) 为基本数据类型分配和回收空间；(2) 为自定义类型分配和回收空间。

对于 (1)，上面提供的程序已经证明了 delete[] 和 delete 是等同的。但是对于 (2)，情况就发生了变化。



我们来看下面的例子，通过例子的学习了解C++中的delete和delete[]的使用方法

#include <iostream>
 using namespace std;
 /////////class Babe
 class Babe
 {
 public:
     Babe()
     {
         cout << \"Create a Babe to talk with me\" << endl;
     }
     ~Babe()
     {
         cout << \"Babe don\'t Go away,listen to me\" << endl;
     }
 };
 //////////main function
 int main()
 {
     Babe* pbabe = new Babe[3];
     delete pbabe;
     pbabe = new Babe[3];
     delete pbabe[];
     return 0;
 }


结果是:

Create a babe to talk with me

Create a babe to talk with me

Create a babe to talk with me

Babe don\'t go away,listen to me

Create a babe to talk with me

Create a babe to talk with me

Create a babe to talk with me

Babe don\'t go away,listen to me

Babe don\'t go away,listen to me

Babe don\'t go away,listen to me

=================================================

大家都看到了，只使用delete的时候只出现一个 Babe don\'t go away,listen to me，而使用delete[]的时候出现3个 Babe don\'t go away,listen to me。不过不管使用delete还是delete[]那三个对象的在内存中都被删除，既存储位置都标记为可写，但是使用delete的时候只调用了pbabe[0]的析构函数，而使用了delete[]则调用了3个Babe对象的析构函数。你一定会问，反正不管怎样都是把存储空间释放了，有什么区别。答：关键在于调用析构函数上。此程序的类没有使用操作系统的系统资源（比如：Socket、File、Thread等），所以不会造成明显恶果。如果你的类使用了操作系统资源，单纯把类的对象从内存中删除是不妥当的，因为没有调用对象的析构函数会导致系统资源不被释放，如果是Socket则会造成Socket资源不被释放，最明显的就是端口号不被释放，系统最大的端口号是65535(216 _ 1，因为还有0)，如果端口号被占用了，你就不能上网了，呵呵。如果File资源不被释放，你就永远不能修改这个文件，甚至不能读这个文件(除非注销或重器系统)。如果线程不被释放，这它总在后台运行，浪费内存和CPU资源。这些资源的释放必须依靠这些类的析构函数。所以，在用这些类生成对象数组的时候，用delete[]来释放它们才是王道。而用delete来释放也许不会出问题，也许后果很严重，具体要看类的代码了.

````