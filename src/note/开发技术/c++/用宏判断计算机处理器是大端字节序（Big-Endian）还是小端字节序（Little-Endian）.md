
http://blog.chinaunix.net/uid-25367385-id-188322.html

```cpp

实现同样的功能，我们来看看Linux 操作系统中相关的源代码是怎么做的：
static union { char c[4]; unsigned long mylong; } endian_test = {{ 'l', '?', '?', 'b' }};

#define ENDIANNESS ((char)endian_test.mylong)
Linux 的内核作者们仅仅用一个union 变量和一个简单的宏定义就实现了一大段代码同样的功能！由以上一段代码我们可以深刻领会到Linux 源代码的精妙之处！(如果ENDIANNESS=’l’表示系统为little endian,
为’b’表示big endian )



```