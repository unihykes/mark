
## 相关链接:
比较全面的gdb调试命令
http://www.cnblogs.com/mfryf/p/5390442.html



gdb使用及原理
https://blog.csdn.net/kernel_learner/article/details/7335516


gdb 命令列表
https://blog.csdn.net/yangzhao0001/article/details/49178949

GDB 常用命令
https://www.jianshu.com/p/e6af28e2566f


使用gdb调试程序完全教程
https://blog.csdn.net/gatieme/article/details/51671430

## gdb查看进程堆栈

	//加载进程
	./gdb attach xxx(进程号)

	//查看堆栈
	bt 

	//查看所有线程堆栈
	thread apply all bt

	//断开连接
	detach

## gdb调试正在运行的进程
```
方式一：
# gdb name（进程名）  555


方式二：
先用file命令加载调试时所需的符号表，然后再通过“attach”命令进行连接：
(gdb) file /home/xiaowp/debugme
            Reading symbols from /home/xiaowp/debugme...done.
            (gdb) attach 555
            ……

在完成调试之后，不要忘记用detach命令断开连接，让被调试的进程可以继续正常运行。
```

## gdb打印变量内存地址
```
显示结构体数据
set print pretty on
p xxx

打印变量内存地址：
x /16bx  str
16表示打印的长度,x表示16进制,b表示byte单字节;




单字节16进制打印address地址处的长度为16的空间的内存，16表示空间长度，不是16进制，x表示16进制，b表示byte单字节

可以使用examine命令(简写是x)来查看内存地址中的值。x命 令的语 法如下所示：
详解：
x/<n/f/u> <addr>
n、f、u是可选的参数。
n是一个正整数，表示需要显示的内存单元的个数， 也就是说从当前地址向后显示几个 内存单元的内容，一个内存单元的大小由后面的u定义。
f 表示显示的格式，参见下面。如果地址所指的是字符串，那么格式可以是s，如果地十是指令地址，那么格式可以是i。
u 表示从当前地址往后请求的字节数，如果不指定的话，GDB默认是4个bytes。u参数可以用下面的字符来代替，b表示单字节，h表示双字节，w表示四字 节，g表示八字节。当我们指定了字节长度后，GDB会从指内存定的内存地址开始，读写指定字节，并把其当作一个值取出来。
<addr>表示一个内存地址。 

```

gdb调试
```
gdb添加参数：
gdb xxxx
set args a b c

gdb flmengine
(gdb)  r
(gdb) shell rm FLMEngine.pid -rf
(gdb) r
(gdb) b xxxx.cpp:101


（01） 首先，输入gdb test
（02） 进入到gdb的调试界面之后，输入list，即可看到test.c源文件
（03） 设置断点，输入 b main
（04） 启动test程序，输入run
（05） 程序在main开始的地方设置了断点，所以程序在printf处断住
（06） 这时候，可以单步跟踪。s单步可以进入到函数，而n单步则越过函数
（07） 如果希望从断点处继续运行程序，输入c
（08） 希望程序运行到函数结束，输入finish
（09） 查看断点信息，输入 info break
（10） 如果希望查看堆栈信息，输入bt
（11） 希望查看内存，输入 x/64xh + 内存地址
（12） 删除断点，则输入delete break + 断点序号
（13） 希望查看函数局部变量的数值，可以输入print + 变量名
（14）希望修改内存值，直接输入 print + *地址 = 数值
（15） 希望实时打印变量的数值，可以输入display + 变量名
（16） 查看函数的汇编代码，输入 disassemble + 函数名
（17） 退出调试输入quit即可
```