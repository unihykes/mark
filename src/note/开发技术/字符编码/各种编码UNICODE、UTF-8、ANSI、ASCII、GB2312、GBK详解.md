工具：
ascii编码表
https://baike.baidu.com/item/ASCII/309296?fr=aladdin


GB2312编码查询：
http://www.knowsky.com/resource/gb2312tbl.htm
http://www.mytju.com/classCode/tools/encode_gb2312.asp

unicode编码表：
中日韩汉字unicode编码表：http://www.chi2ko.com/tool/CJK.htm
unicode官网：http://www.unicode.org/
unicode官方编码表：http://www.unicode.org/Public/UCD/latest/charts/

全角字符unicode码对应表
http://blog.csdn.net/lvwx369/article/details/39294265


参考资料：

转载： 字符编码详解
https://www.cnblogs.com/QQ931697811/p/3968033.html


http://blog.csdn.net/wabil/article/details/50807240

http://www.cnblogs.com/KevinYang/archive/2010/06/18/1760597.html


大端小端,ascii,unicode,utf8,utf16,utf32,gb2312,gbk,gb18030等字符编码问题
http://blog.csdn.net/ztsinghua/article/details/44277833


utf8-bom
utf8无bom
http://blog.csdn.net/sinat_29529157/article/details/74897751


Unicode和多字节字符集 (MBCS) 杂谈
http://blog.sina.com.cn/s/blog_72e928910100yklp.html
字节码问题--wchar和char的区别以及wchar和char之间的相互转换字符编码转换等方法及函数介绍
http://www.cnblogs.com/MichaelOwen/articles/2128771.html
 他附录的几个内容也是可供学习的：
网上不错的资源：
C/C++ 编程中多国语言处理
http://www.ibm.com/developerworks/cn/linux/l-cn-ccppglb/index.html?ca=drs-
彻底解密C++宽字符：1、从char到wchar_t
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740615.aspx
彻底解密C++宽字符：2、Unicode和UTF
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740616.aspx
彻底解密C++宽字符：3、利用C运行时库函数转换
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740618.aspx
彻底解密C++宽字符：4、利用codecvt和use_facet转换
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740620.aspx
彻底解密C++宽字符：5、利用fstream转换
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740621.aspx
彻底解密C++宽字符：6、国际化策略
http://blog.csdn.net/wallaceli1981/archive/2010/07/16/5740622.aspx
C 源文件内的中文(1)
http://hi.baidu.com/cyclone/blog/item/e48c76099b002ca22eddd4c3.html
C 源文件内的中文(2)
http://hi.baidu.com/cyclone/blog/item/25b262d973e9d72111df9bcf.html
UTF-8 and Unicode FAQ for Unix/Linux
http://blog.csdn.net/lovekatherine/archive/2007/08/30/1765903.aspx


C++11新特性转换GB2312(ANSI)、UTF8、Unicode编码文件
http://www.jianshu.com/p/338fb8eaf2b4
http://www.cppblog.com/mythma/archive/2012/09/11/wstring_convert_utf8.html


在计算机中为何不直接使用UTF8编码进行存储，而要使用Unicode再转换成UTF8？
https://www.zhihu.com/question/52346583


C++中宽字符类型（wchar_t）的编码一定是Unicode？
http://blog.csdn.net/foxfire881/article/details/42563757


Windows代码页、区域
https://www.cnblogs.com/hanford/p/6113359.html

关于Unicode，字符集，字符编码，每个程序员都应该知道的事
https://www.cnblogs.com/Jack47/p/unicode-utf8-character_set-encoding.html


前面说了要知道具体是哪种编码方式,需要判断文本开头的标志,下面是所有编码对应的开头标志
EF BB BF　　　 UTF-8
FE FF　　　　　UTF-16/UCS-2, little endian
FF FE　　　　　UTF-16/UCS-2, big endian
FF FE 00 00　　UTF-32/UCS-4, little endian.
00 00 FE FF　　UTF-32/UCS-4, big-endian.
其中的UCS就是前面说的ISO制定的标准,和Unicode是完全一样的,只不过名字不一样.ucs-2对应utf-16,ucs-4对应UTF-32.UTF-8是没有对应的UCS



来，看看记事本里会变成乱码的字……不仅仅是“联通”而已……
http://blog.csdn.net/yimengqiannian/article/details/7060565



占4字节的utf-8字符示例：
🞀


编码表：1550页 常见标志
编码表：1519页 扑克牌
编码表：1515页 麻将。。
windows下，cfl的printMessage()实现时，是简单的将unicode字符转为ansi字符，然和用printf输出；

char* str = xxxx;
什么时候用String(str);
什么时候用String ret = toCFLString(string(str));
