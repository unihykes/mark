#ifdef __USING_OPENMP__
    #include <omp.h>

#endif


http://baike.baidu.com/link?url=kNePnIInzowjUJwLggUQO5I1kzRjHSBeGwB8PztabiJ2AEFWNiv-DpNxqLbR59B_KAbPBm6GnUpayqPrwpihVK

OpenMP是由OpenMP Architecture Review Board牵头提出的，并已被广泛接受，用于共享内存并行系统的多处理器程序设计的一套指导性编译处理方案(Compiler Directive)[1]  。OpenMP支持的编程语言包括C、C++和Fortran；而支持OpenMp的编译器包括Sun Compiler，GNU Compiler和Intel Compiler等。OpenMp提供了对并行算法的高层的抽象描述，程序员通过在源代码中加入专用的pragma来指明自己的意图，由此编译器可以自动将程序进行并行化，并在必要之处加入同步互斥以及通信。当选择忽略这些pragma，或者编译器不支持OpenMp时，程序又可退化为通常的程序(一般为串行)，代码仍然可以正常运作，只是不能利用多线程来加速程序执行。


要在Visual C++2005 中使用OpenMP其实不难，只要将 Project 的Properties中C/C++里Language的OpenMP Support开启（参数为 /openmp），就可以让VC++2005 在编译时支持OpenMP 的语法了；而在编写使用OpenMP 的程序时，则需要先include OpenMP的头文件：omp.h。

而要将 for 循环并行化处理，该怎么做呢？非常简单，只要在前面加上一行

#pragma omp parallel for

就够了！