

```cpp

#include<iostream>
#include<string>
#include <limits>
using namespace std;

int main()
{
cout << "type: \t\t" << "************size**************"<< endl;
cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
cout << "\t最大值：" << (numeric_limits<bool>::max)();
cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;
cout << "char: \t\t" << "所占字节数：" << sizeof(char);
cout << "\t最大值：" << (numeric_limits<char>::max)();
cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;
cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
cout << "\t最大值：" << (numeric_limits<signed char>::max)();
cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;
cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();
cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;
cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();
cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;
cout << "short: \t\t" << "所占字节数：" << sizeof(short);
cout << "\t最大值：" << (numeric_limits<short>::max)();
cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;
cout << "int: \t\t" << "所占字节数：" << sizeof(int);
cout << "\t最大值：" << (numeric_limits<int>::max)();
cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;
cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);
cout << "\t最大值：" << (numeric_limits<unsigned>::max)();
cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;
cout << "long: \t\t" << "所占字节数：" << sizeof(long);
cout << "\t最大值：" << (numeric_limits<long>::max)();
cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;
cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();
cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;
cout << "double: \t" << "所占字节数：" << sizeof(double);
cout << "\t最大值：" << (numeric_limits<double>::max)();
cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;
cout << "long double: \t" << "所占字节数：" << sizeof(long double);
cout << "\t最大值：" << (numeric_limits<long double>::max)();
cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;
cout << "float: \t\t" << "所占字节数：" << sizeof(float);
cout << "\t最大值：" << (numeric_limits<float>::max)();
cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;
cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
cout << "\t最大值：" << (numeric_limits<size_t>::max)();
cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;
cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;
// << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;
cout << "type: \t\t" << "************size**************"<< endl;
return 0;}

/*运行结果分析：
以上结果已经很明白了，一下补充说明几点：
概念、整型：表示整数、字符和布尔值的算术类型合称为整型（integral type）。
关于带符号与无符号类型：整型 int、stort  和  long 都默认为带符号型。要获得无符号型则必须制定该类型为unsigned，比如unsigned long。unsigned int类型可以简写为unsigned，也就是说，unsigned后不加其他类型说明符就意味着是unsigned int。
一字节表示八位，即：1byte = 8 bit;
int: 4byte =  32 bit 有符号signed范围：2^31-1 ~ -2^31即：2147483647 ~ -2147483648无符号unsigned范围：2^32-1 ~ 0即：4294967295 ~ 0
long: 4 byte = 32 bit 同int型
double: 8 byte = 64 bit 范围：1.79769e+308 ~ 2.22507e-308
long double: 12 byte = 96 bit 范围： 1.18973e+4932 ~ 3.3621e-4932
float: 4 byte = 32 bit 范围： 3.40282e+038 ~ 1.17549e-038
int、unsigned、long、unsigned long 、double的数量级最大都只能表示为10亿，即它们表示十进制的位数不超过10个，即可以保存所有9位整数。而short只是能表示5位；

另外对于浮点说而言：使用double类型基本上不会有错。在float类型中隐式的精度损失是不能忽视的，二双精度计算的代价相对于单精度可以忽略。事实上，在有些机器上，double类型比float类型的计算要快得多。float型只能保证6位有效数字，而double型至少可以保证15位有效数字（小数点后的数位），long double型提供的精度通常没有必要，而且还要承担额外的运行代价。
double是8字节共64位，其中小数位占52位，2-^52=2.2204460492503130808472633361816e-16，量级为10^-16，故能够保证2^-15的所有精度。
在有些机器上，用long类型进行计算所付出的运行时代价远远高于用int类型进行同样计算的代价，所以算则类型前要先了解程序的细节并且比较long类型与int类型的实际运行时性能代价。

```