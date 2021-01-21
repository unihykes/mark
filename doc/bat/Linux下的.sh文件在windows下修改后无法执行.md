```
因为大部分人使用的操作系统是windows，同时也因为windows的可视化界面做得比较人性化，所以在修改linux的一个sh文件时，为了方便拉到window上用editplus编辑，上传回linux去后，这个SH却不能运行，错误提示是：: command not found。bad interpreter: No such file or directory。原因是CR/LF问题，在dos/window下按一次回车键实际上输入的是“回车（CR)”和“换行（LF）”，而linux/unix下按一次回车键只输入“换行（LF）”，所以修改的sh文件在每行都会多了一个CR，所以linux下运行时就会报错找不到命令。举出几种解决方法：1、在editplus中“文档->文件格式(CR/LF)->UNIX”，这样linux下就能按unix的格式保存文件   （UltraEdit）：File-->Conversions-->DOS->UNIX即可。2、在vim中，输入:set ff=unix，同样也是转换成unix的格式。

首先要确保文件有可执行权限
#sh>chmod a+x filename

然后修改文件格式
#sh>vi filename

利用如下命令查看文件格式
:set ff 或 :set fileformat

可以看到如下信息
fileformat=dos 或 fileformat=unix

利用如下命令修改文件格式
:set ff=unix 或 :set fileformat=unix
:wq (存盘退出)

最后再执行文件
#sh>./filename
3、在windows下使用UltraEdit中打开.sh文件，按Ctrl+H切换到16位状态，搜索0D，删除之，然后保存就可以了。
转自：http://www.4520.info/post/269/
 
 
经常会遇到这种情况，在windows下写的脚本，py代码会在linux下无法执行，错误就是：
: bad interpreter: No such file or directory
以前一直不知怎么解决，今天终于找到方法了。
1 原因
这通常都是由于windows下对文本文件的保存格式与unix下不同造成的，windows下回车的字符是’＼r＼n’,而linux下是’＼n’。
2 解决方法
vim file(file指的是windows下写的脚本文件)。
在命令模式下，输入 set ff=?（此句语句的意思是查看文件的格式）。
查看文件格式为dos或者unix
set ff=unix（把文件格式设置为：unix文件格式）
命令模式下输入：wq命令保存。
再次输入命令：./file.sh 即可。
 
当在linux下写好一个脚本之后保存在windows上，在windows上修改以后再传到linux上，可能脚本就不能执行了。
出 现这种错误的原因是因为：CR/LF问题，在dos/window下按一次回车键实际上输入的是“回车（CR)”和“换行（LF）”，而linux /unix下按一次回车键只输入“换行（LF）”，所以修改的sh文件在每行都会多了一个CR，所以linux下运行时就会报错找不到命令。
举出两种解决方法：
1、在editplus中“文档->文件格式(CR/LF)->UNIX”，这样linux下就能按unix的格式保存文件
2、在vim中，输入:set ff=unix，同样也是转换成unix的格式。
还有一种方法就是可以在linux上创建sh文件，然后再windows上编辑，这样也是可以的。


```