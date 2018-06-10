# ut_std
using google test;

## 语言 0-Language
* 基本概念 0-BasicConcepts
* C++ 关键字 1-Keywords
* 预处理器 2-Preprocessor
* 表达式 3-Expressions
* 声明 4-Declaration
* 初始化 5-Initialization
* 函数 6-Functions
* 语句 7-Statements
* 类 8-Classes
* 模板 9-Templates
* 异常 10-Exceptions
* 杂项 11-Miscellaneous



## 头文件 1-Headers




## 库概念 2-Library concepts




## 语言支持库 3-Language support library
* 类型支持 Type support
* 类型特性 traits (C++11)
* 程序工具 Program utilities
* 关系运算符 Relational comparators (C++20)
* numeric_limits
* type_info
* initializer_list (C++11)




## 诊断库 4-Diagnostics library




## 通用工具库 5-General utilities library
* 智能指针与分配器 Smart pointers and allocators
* 日期和时间 Date and time
* 函数对象 Function objects
* hash (C++11)
* 字符串转换 String conversions (C++17)
* 工具函数 Utility functions
* pair
* tuple (C++11)
* optional (C++17)
* any (C++17)
* variant (C++17) 




## 字符串库 6-Strings library
* basic_string
* basic_string_view (C++17)
* 空终止字符串 Null-terminated strings
	* 字节 byte
	* 多字节 multibyte
	* 宽 wide




## 容器库 7-Containers library
* 顺序容器 Sequence containers
* 关联容器 Associative containers
* 无序关联容器 Unordered associative containers
* 容器适配器 Container adaptors




## 迭代器库 8-Iterators library




## 算法库 9-Algorithms library




## 数值库 10-Numerics library
* 常用数学函数 Common math functions
* 特殊数学函数 Special math functions (C++17)
* 数值算法 Numeric algorithms
* 伪随机数生成 Pseudo-random number generation
* 浮点环境 Floating-point environment (C++11)
* complex
* valarray 




## 输入/输出库 11-Input output library
* 基于流的I/O Stream-based I/O
* 同步的输出 Synchronized output(C++20)
* I/O 操纵符 I/O manipulators




## 本地化库 12-Localizations library




## 正则表达式库 13-Regular expressions library (C++11)




## 原子操作库 14-Atomic operations library (C++11)




## 线程支持库 15-Thread support library (C++11)




## 文件系统库 16-Filesystem library (C++17)





# C++概念

```C++
## 基础
DefaultConstructible    指定该类型对象可以默认构造
MoveConstructible       指定该类型对象可以从右值构造
CopyConstructible       指定该类型对象可以从左值构造
MoveAssignable          指定该类型对象可以从右值赋值
CopyAssignable          指定该类型对象可以从左值赋值
Destructible            指定该对象可以析构


## 布局
TriviallyCopyable       拥有平凡复制、赋值及析构器的类
TrivialType             拥有平凡构造器、赋值及析构器的类
StandardLayoutType      仅包含其他标准布局 (StandartLayout) 成员的非虚类，都有相同的访问控制
PODType                 POD（简旧数据）结构体，与 C struct 兼容


## 库所属 
可比较相等              operator== 是等价关系
可比较小于              operator< 是严格弱序关系
可交换                  可用非限定非成员函数调用 swap() 交换的类型
可值交换                解引用到可交换 (Swappable) 类型的迭代器 (Iterator)
可空指针                支持空置的类指针类型
哈希                    输入值相异，相同输出概率低的函数对象 (FunctionObject)
分配器                  包含分配信息的类类型
函数对象                能以函数调用语法调用的对象
可调用                  定义了调用操作的类型
Predicate               有单参数，且不修改它，返回值可转换为 bool 的函数对象 (FunctionObject)
BinaryPredicate         有双参数，且不修改它，返回值可转换为 bool 的函数对象 (FunctionObject)
Compare                 建立顺序关系的二元谓词 (BinaryPredicate)


## 容器  
容器                    允许通过迭代器访问元素的数据结构
可逆容器                使用双向迭代器的容器
具分配器容器            使用分配器的容器
顺序容器                元素线性存储的容器
相接容器                元素存储于相邻内存地址的容器
关联容器                通过将元素关联到关键存储它们的容器
无序关联容器            通过将元素关联到关键以将它们存储于桶中的容器


## 容器元素  
可默认插入              可在未初始化存储默认构造的元素
可复制插入              可在未初始化存储中复制构造的元素
可移动插入              可在未初始化存储中移动构造的函数
可原位构造              可在未初始化存储中构造的元素
可擦除                  可用分配器销毁的元素


## 迭代器 
迭代器                  在一些数据结构内访问数据的通用概念
输入迭代器              可用于读数据的迭代器
输出迭代器              可用于写数据的迭代器
向前迭代器              可用于多次读数据的迭代器
双向迭代器              可增减的迭代器
随机访问迭代器          可在常数时间内增加的迭代器
相接迭代器              指向相继分配元素的迭代器


## 流 I/O 函数 
无格式输入函数          不跳过前导空格并对处理字符计数的流输入函数
有格式输入函数          跳过前导空格的流输入函数
无格式输出函数          基本流输出函数
有格式输出函数          设置失败位并返回流引用的流输出函数


## 随机数生成   
种子序列                投入一个整数序列，产出一个 32 位无符号值的序列
均匀随机位生成器        返回均匀分布的随机无符号整数
随机数引擎              由种子定义的确定性均匀随机位生成器 (UniformRandomBitGenerator)
随机数引擎适配器        转换另一个随机数引擎 (RandomNumberEngine) 输出的随机数引擎 (RandomNumberEngine)
随机数分布              返回服从给定数学概率密度分布函数的随机数


## 并发  
基础可锁                为执行代理（即线程）提供独占所有权语义
可锁                    支持有意锁获取的基础可锁 (BasicLockable)
定时可锁                支持定时锁获取的可锁 (Lockable)
互斥                    保护数据免受数据竞争和顺序一致同步影响的可锁 (Lockable)
定时互斥                保护数据免受数据竞争和顺序一致同步影响的可定时锁 (TimedLockable)
共享互斥                支持共享所有权语义的互斥 (Mutex)
共享定时互斥            支持共享所有权语义的定时互斥 (TimedMutex)


## 其他  
一元类型特性            描述类型的属性
二元类型特性            描述二个类型间的关系
变换特性                修改类型属性
时钟                    将时期、时间点，以及取得当前时间点的函数聚合
平凡时钟                不抛异常的时钟 (Clock)
字符特性                为字符类型定义类型和函数
位掩码类型              位集、整数或枚举
数值类型                初始化效率上等于赋值的类型
正则表达式特性          用正则表达式库定义类型和函数
字面类型                拥有 constexpr 构造函数的类型
```
