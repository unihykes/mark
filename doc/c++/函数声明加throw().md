加一个throw()到函数中？

这是异常规范，只会出现在声明函数中，表示这个函数可能抛出任何类型的异常

void GetTag() throw(int);表示只抛出int类型异常
void GetTag() throw(int，char);表示抛出in，char类型异常
void GetTag() throw();表示不会抛出任何类型异常
void GetTag() throw(...);表示抛出任何类型异常

void GetTag() throw(int);表示只抛出int类型异常
并不表示一定会抛出异常，但是一旦抛出异常只会抛出int类型，如果抛出非
int类型异常，调用unexsetpion()函数，退出程序。
假如你加一个throw()属性到你的永远不会抛出异常的函数中，编译器会非常聪明的知道代码的意图和决定优化方式
