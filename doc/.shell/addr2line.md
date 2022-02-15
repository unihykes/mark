addr2line排查崩溃所在代码行数

addr2line 4005f5 -e xxx.so -f -s -C

参数
-a --addresses：在函数名、文件和行号信息之前，显示地址，以十六进制形式。
-b --target=<bfdname>：指定目标文件的格式为bfdname。
-e --exe=<executable>：指定需要转换地址的可执行文件名。
-i --inlines ： 如果需要转换的地址是一个内联函数，则输出的信息包括其最近范围内的一个非内联函数的信息。
-j --section=<name>：给出的地址代表指定section的偏移，而非绝对地址。
-p --pretty-print：使得该函数的输出信息更加人性化：每一个地址的信息占一行。
-s --basenames：仅仅显示每个文件名的基址（即不显示文件的具体路径，只显示文件名）。
-f --functions：在显示文件名、行号输出信息的同时显示函数名信息。
-C --demangle[=style]：将低级别的符号名解码为用户级别的名字。
-h --help：输出帮助信息。
-v --version：输出版本号。

作者：猿佑
链接：https://www.jianshu.com/p/c2e2b8f8ea0d
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
