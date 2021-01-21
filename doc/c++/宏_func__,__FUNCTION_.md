_func__  __FUNCTION__

```cpp
__func__
windows下只输出函数名称；
linux下只输出函数名称；

__FUNCTION__
windows下输出命名空间::类名::函数名称
linux下只输出函数名称；






扩展：
__func__   C99的标准，
GCC只输出函数名称。
__FUNCTION__  同__func__，
__PRETTY_FUNCTION__  非标准宏。这个宏比__FUNCTION__功能更强,  若用g++编译C++程序, __FUNCTION__只能输出类的成员名,不会输出类名;而__PRETTY_FUNCTION__则会以 <return-type>  <class-name>::<member-function-name>(<parameters-list>) 的格式输出成员函数的详悉信息(注: 只会输出parameters-list的形参类型, 而不会输出形参名).若用gcc编译C程序,__PRETTY_FUNCTION__跟__FUNCTION__的功能相同.
而VC.NET提供的函数宏为：
__FUNCTION__ 函数，提供类名和函数名称的输出。

```