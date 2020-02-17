
http://shandian.biz/278.html



```

一、文件简介
.po文件，.mo文件，.pot文件是由gettext程序生成或者使用的源代码和编译结果。

1、.pot文件
是一种模板文件，其实质与.po文件一样，其中包含了从源代码中提取所有的翻译字符串的列表，主要提供给翻译人员使用。

2、.po文件
（1）用程序msginit来分析pot文件，生成各语言对应的po文件，比如中文就是zh_CN.po，法语就是fr.po文件。
（2）PO是Portable Object（可移植对象）的缩写形式，它是面向翻译人员的、提取于源代码的一种资源文件。
（3）.po文件可以用任何编辑器如poEdit，vi，Emacs，editplus打开，交给翻译人员来将其中的文字翻译成本国语言。

3、.mo文件
（1）用msgfmt将.po文件编译成mo文件，这是一个二进制文件，不能直接编辑。
（2）MO是Machine Object（机器对象）的缩写形式，它是面向计算机的、由.po文件通过GNU gettext工具包编译而成的二进制文件，应用程序通过读取.mo文件使自身的界面转换成用户使用的语言，如简体中文。
（3）可以用工具如msgunfmt命令将.mo文件反编译为.po文件。
不止 WordPress ，包括很多桌面应用程序都是是依靠 po 文件或 mo 文件来实现多语言版本。一般情况下，我们在汉化软件的时候会碰上如下几种情况：

二、几种情形
1、如果程序本身提供了.po文件，直接使用poEdit汉化，并自动生成.mo文件。
2、如果程序提供了.pot文件，复制一份并更改后缀名为.po，再使用poEdit汉化，最后生成.mo文件。
3、程序既没有提供.po文件，也没有提供.pot文件，只提供了.mo文件，那么有以下步骤：
（1）使用poEdit安装程序bin文件夹中的msgunfmt程序将.mo文件转换成.po文件，命令类似如下：msgunfmt   d:\demo.mo -o d:\demo.po

注：在命令提示符界面，使用 msgfmt demo.po 命令将po文件编译为可用的 demo.mo 文件，用 msgunfmt demo.mo 命令转回 demo.po 文件，这些命令在 poEdit 的安裝目录下有，可以拷贝msgunfmt.exe 、msgfmt.exe 及相关链接库文件 gettextlib.dll 、gettextsrc.dll 、iconv.dll 、intl.dll 到 c:/windows/system32 目录下使用。
（2）使用poedit汉化，然后生成.mo文件。

三、参考资料
1、在Windows系统搭建Linux软件汉化平台
2、Wordpress语言文件介绍:po文件,mo文件,pot文件
3、如何汉化 po 文件及编译成 mo 文件
如何汉化 po 文件及编译成 mo 文件
本文介绍如何 汉化、翻译 po 文件 及 编译、转换成 mo 文件
我们在使用 WordPress 及其插件时，经常可以找到汉化的版本，一般是通过一个汉化过（翻译过）的 mo 文件来实现（ WordPress 仅可识别 mo 文件），实际上不单 WordPress ，包括很多桌面应用程序都是是依靠 po 文件或 mo 文件来实现多语言版本。如果原作者提供了一个 po 文件或 mo 文件，那么我们就可以通过相关工具来自行汉化，或者翻译成其他语言版本。因为 mo 文件不能直接编辑，所以我们得编辑 po 文件，若仅有 mo 文件，那么就应该先把它转换成 po 文件后再进行编辑翻译。

至于编辑工具，由于 po 文件本身就是一个文本文件，所以任何文本编辑器都可以使用。除了专门编辑 po 文件的 poEdit ，还推荐使用 poEdit 、EditPlus、UltraEdit或者你喜欢的 vi 或 vim。
我们来看一个 po 文件，这是 yskin 制作的 WordPress 2.11 中文版 po 文件 中的一部分

msgid ""
msgstr ""
"Project-Id-Version: WordPress 2.1-1.0\n"
"PO-Revision-Date: 2007-02-22 12:35+0800\n"
"Last-Translator: yskin \n"
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=utf-8\n"
"Content-Transfer-Encoding: 8bit\n"
"X-Poedit-Basepath: d:/wordpress\n"
"X-Poedit-Language: Simplified Chinese\n"
"X-Poedit-Country: China\n"
"X-Poedit-SourceCharset: utf-8\n"
"X-Poedit-KeywordsList: _e;__;__ngettext:1,2\n"
"Language-Team: \n"
"POT-Creation-Date: \n"
"Plural-Forms: nplurals=1; plural=0;\n"
"X-Poedit-SearchPath-0: .\n"

# 第一条要翻译的字符串。
#: wp-comments-post.php:15
msgid "Sorry, comments are closed for this item."
msgstr "对不起，这篇文章禁止评论。"
上面是这个 po 文件的最初部分，各行意思一目了然，注意编码尽可能采用UTF-8。

# 第一条要翻译的字符串。
#: wp-comments-post.php:15
msgid "Sorry, comments are closed for this item."
msgstr "对不起，这篇文章禁止评论。"

这段就是po文件的主体结构了，每一个翻译项占一段。#: wp-comments-post.php:15 说明字符串相应的位置； msgid "Sorry, comments are closed for this item." 翻译前的原文； msgstr "对不起，这篇文章禁止评论。" 翻译后的字符串。以此类推，即可完成所有资源的翻译。非常简单。
那么如何将 po 文件编译成（转换） mo 文件呢？

如果你使用的是 poEdit ，按 Ctrl + s 保存就会自动生成相应的 po 文件和 mo 文件；
或者在命令提示符界面，使用 msgfmt demo.po 命令将po文件编译为可用的 demo.mo 文件，用 msgunfmt demo.mo 命令转回 demo.po 文件，这些命令在 poEdit 的安裝目录下有，可以拷贝msgunfmt.exe 、msgfmt.exe 及相关链接库文件 gettextlib.dll 、gettextsrc.dll 、iconv.dll 、intl.dll 到 c:/windows/system32 目录下，或者安装 .Net 2.0环境。

另外推荐一款 GUI 界面的转化程序 po2mo.exe ，作者的说明：该程序是调用 msgfmt.exe 和 msgunfmt.exe 文件，从而进行po 、mo 文件互转。文件是用C#写的，需要.Net 2.0环境。


```