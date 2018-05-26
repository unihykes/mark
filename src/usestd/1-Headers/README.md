win10下,

标准C头文件:
C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt

标准C++头文件:
C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include

## 工具库
```c++
<cstdlib>                        通用工具：程序控制、动态内存分配、随机数、排序与查找 
<csignal>                        信号管理的函数与宏常量 
<csetjmp>                        保存到执行环境的宏，及跳到执行环境的函数 
<cstdarg>                        变长参数列表的处理 
<typeinfo>                       运行时类型信息工具 
<typeindex> (C++11 起)           std::type_index 
<type_traits> (C++11 起)         编译时类型信息 
<bitset>                         std::bitset 类模板 
<functional>                     函数对象、函数调用、绑定操作、引用包装 
<utility>                        多种工具组件 
<ctime>                          C 风格时间/日期工具 
<chrono> (C++11 起)              C++ 时间工具 
<cstddef>                        标准宏和类型定义 
<initializer_list> (C++11 起)    std::initializer_list 类模板 
<tuple> (C++11 起)               std::tuple 类模板 
<any> (C++17 起)                 std::any 类 
<optional> (C++17 起)            std::optional 类模板 
<variant> (C++17 起)             std::variant 类模板 
<compare> (C++20 起)             三路比较运算符支持 
<version> (C++20 起)             提供依赖实现的库信息 
```

## 动态内存管理 
```c++
<new>                            低层内存管理工具 
<memory>                         高层内存管理工具 
<scoped_allocator> (C++11 起)    嵌套分配器类 
<memory_resource> (C++17 起)     多态分配器及内存资源 
```

## 数值极限
```c++
<climits>                        整数类型极限 
<cfloat>                         浮点类型极限 
<cstdint> (C++11 起)             定长整数及其他类型的极限 
<cinttypes> (C++11 起)           格式化宏、 intmax_t 及 uintmax_t 数学工具及转换 
<limits>                         查询算术类型属性的标准化方式 
```

## 错误处理
```c++
<exception>                      异常处理工具
<stdexcept>                      标准异常对象
<cassert>                        将其参数与零比较的条件性编译宏
<system_error> (C++11 起)        定义std::error_code，平台依赖的错误码
<cerrno>                         含有最近一次错误号的宏
```

## 字符串库 
```c++
<cctype>                         确定字符数据中所含类型的函数
<cwctype>                        确定宽字符数据中所含类型的函数
<cstring>                        多种窄字符串处理函数
<cwchar>                         多种宽及多字节字符串处理函数
<cuchar> (C++11 起)              C 风格 Unicode 字符转换函数
<string>                         std::basic_string 类模板
<string_view> (C++17 起)         std::basic_string_view 类模板
<charconv> (C++17 起)            std::to_chars 与 std::from_chars
```

## 容器库 
```c++
<array> (C++11 起)               std::array 容器
<vector>                         std::vector 容器
<deque>                          std::deque 容器
<list>                           std::list 容器
<forward_list> (C++11 起)        std::forward_list 容器
<set>                            std::set 及 std::multiset 关联容器
<map>                            std::map 及 std::multimap 关联容器
<unordered_set> (C++11 起)       std::unordered_set 及 std::unordered_multiset 无序关联容器
<unordered_map> (C++11 起)       std::unordered_map 及 std::unordered_multimap 无序关联容器
<stack>                          std::stack 容器适配器
<queue>                          std::queue 及 std::priority_queue 容器适配器
```

## 算法库 
```c++
<algorithm>                      操作于容器上的算法
<execution> (C++17)              算法并行版本的预定义执行策略
```

## 迭代器库 
```c++
<iterator>                       容器迭代器
```

## 数值库 
```c++
<cmath>                          常用数学函数
<complex>                        复数类型
<valarray>                       表示和操作值的数组的类
<random> (C++11 起)              随机数生成器及分布
<numeric>                        容器中值的数值运算
<ratio> (C++11 起)               编译时有理数算术
<cfenv> (C++11 起)               浮点环境访问函数
```

## 输入/输出库 
```c++
<iosfwd>                        所有输入/输出库中的类的前置声明
<ios>                           std::ios_base 类、std::basic_ios 类模板及数个 typedef
<istream>                       std::basic_istream 类模板及数个 typedef
<ostream>                       std::basic_ostream 、 std::basic_iostream 类模板及数个typedef
<iostream>                      数个标准流对象
<fstream>                       std::basic_fstream 、 std::basic_ifstream 、 std::basic_ofstream 类模板及数个typedef
<sstream>                       std::basic_stringstream 、 std::basic_istringstream 、 std::basic_ostringstream 类模板及数个 typedef
<syncstream> (C++20 起)         std::basic_osyncstream 、 std::basic_syncbuf 及 typedef
<strstream> (弃用)              std::strstream 、 std::istrstream 、 std::ostrstream
<iomanip>                       控制输入输出格式的帮助函数
<streambuf>                     std::basic_streambuf 类模板
<cstdio>                        C 风格输入输出函数
```

## 本地化库 
```c++
<locale>                        本地化工具
<clocale>                       C 本地化工具
<codecvt> (C++11 起)            (C++17 中弃用)  Unicode 转换设施
```

## 正则表达式库 
```c++
<regex> (C++11 起)              支持正则表达式处理的类、算法及迭代器
```

## 原子操作库 
```c++
<atomic> (C++11 起)             原子操作库
```

## 线程支持库 
```c++
<thread> (C++11 起)             std::thread 类及支持函数
<mutex> (C++11 起)              互斥原语
<shared_mutex> (C++14 起)       共享的互斥原语
<future> (C++11 起)             异步计算的原语
<condition_variable> (C++11 起) 线程等待条件
```


## 文件系统库 
```c++
<filesystem> (C++17 起)         std::path 类及支持函数
```

## C 兼容头文件
```c++
<assert.h> (弃用) 表现如同每个来自 <cassert> 的名称被放入全局命名空间
<ctype.h> (弃用)  表现如同每个来自 <cctype> 的名称被放入全局命名空间
<errno.h> (弃用)  表现如同每个来自 <cerrno> 的名称被放入全局命名空间
<fenv.h> (弃用)   表现如同每个来自 <cfenv> 的名称被放入全局命名空间
<float.h> (弃用)  表现如同每个来自 <cfloat> 的名称被放入全局命名空间
<inttypes.h> (弃用)   表现如同每个来自 <cinttypes> 的名称被放入全局命名空间
<limits.h> (弃用) 表现如同每个来自 <climits> 的名称被放入全局命名空间
<locale.h> (弃用) 表现如同每个来自 <clocale> 的名称被放入全局命名空间
<math.h> (弃用)   表现如同每个来自 <cmath> 的名称被放入全局命名空间，除了数学特殊函数的名称
<setjmp.h> (弃用) 表现如同每个来自 <csetjmp> 的名称被放入全局命名空间
<signal.h> (弃用) 表现如同每个来自 <csignal> 的名称被放入全局命名空间
<stdarg.h> (弃用) 表现如同每个来自 <cstdarg> 的名称被放入全局命名空间
<stddef.h> (弃用) 表现如同每个来自 <cstddef> 的名称被放入全局命名空间，除了 std::byte 及其相关函数的名称
<stdint.h> (弃用) 表现如同每个来自 <cstdint> 的名称被放入全局命名空间
<stdio.h> (弃用)  表现如同每个来自 <cstdio> 的名称被放入全局命名空间
<stdlib.h> (弃用) 表现如同每个来自 <cstdlib> 的名称被放入全局命名空间
<string.h> (弃用) 表现如同每个来自 <cstring> 的名称被放入全局命名空间
<time.h> (弃用)   表现如同每个来自 <ctime> 的名称被放入全局命名空间
<uchar.h> (弃用)  表现如同每个来自 <cuchar> 的名称被放入全局命名空间
<wchar.h> (弃用)  表现如同每个来自 <cwchar> 的名称被放入全局命名空间
<wctype.h> (弃用) 表现如同每个来自 <cwctype> 的名称被放入全局命名空间
```

#### 不受支持的 C 头文件
```c++
C 头文件 <stdatomic.h> 、 <stdnoreturn.h> 及 <threads.h> 不包含于 C++ 且无 cxxx 等价版本。
```

#### 空 C 头文件
```c++
头文件 <complex.h> 、 <ccomplex> 、 <tgmath.h> 及 <ctgmath> 不含有任何来自 C 标准库的内容，
而且不过是包含其他来自 C++ 标准库的头文件。 C++ 中这些头文件的使用均为被弃用。 

<ccomplex> (C++11 起)(C++17 中弃用)     简单地包含<complex>
<complex.h> (弃用)                      简单地包含头文件 <complex>
<ctgmath> (C++11 起)(C++17 中弃用)      简单地包含 <complex> 及 <cmath> ：
                                        等价于 C 头文件 tgmath.h 内容的重载已经提供于那些头文件
<tgmath.h> (弃用)                       简单地包含头文件 <ctgmath>
```


#### 无意义的 C 头文件 
```c++
头文件 <ciso646> 、 <cstdalign> 及 <cstdbool> 在 C++ 中无意义，因为它们在 C 中提供的宏是 C++ 的关键词。
<ciso646>                              空头文件。C 中出现于 iso646.h 的宏是 C++ 的关键词
<iso646.h>                             (弃用) 表现如同每个来自 <ciso646> 的名称被放入全局命名空间
<cstdalign> (C++11 起)(C++17 中弃用)   定义一个兼容性宏常量
<stdalign.h> (弃用)                    表现如同每个来自 <cstdalign> 的名称被放入全局命名空间
<cstdbool> (C++11 起)(C++17 中弃用)    定义一个兼容性宏常量
<stdbool.h> (弃用)                     表现如同每个来自 <cstdbool> 的名称被放入全局命名空间
```








