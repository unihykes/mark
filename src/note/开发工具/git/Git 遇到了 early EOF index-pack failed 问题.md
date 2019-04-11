转载:
https://blog.csdn.net/djy1992/article/details/50604937


今天想 clone 一下 boost 在 github 的 repo，结果在 clone 的过程中遇到了下面的错误。我原本以为是网络原因，今天学校网速废成渣了，很多同学都去网吧撸去了，所以就 retry 了一次。还是出现了下面的错误，然后就不得不 google 去了。

$ git clone https://github.com/boostorg/boost.git
Cloning into 'boost'...
remote: Counting objects: 183543, done.
remote: Compressing objects: 100% (69361/69361), done.
fatal: The remote end hung up unexpectedly
fatal: early EOF
fatal: index-pack failed
后来 google 到的参考如下：
	* 
git clone fails with \"index-pack\" failed?
	* 
Git checking out problem [fatal: early EOFs]


特别是第一篇（第一个QA），应该跟我的情况最为符合，不过我尝试了第二个 QA 中Voket 的回答给出的解决方案。因为我在 Windows 下的 Git 作的这个死。在这里就简单记录一下这个解决方案。

# 为 git 添加配置项，通过下面的命令可以简单完成
# 在这之前可以执行 git config -l 命令看看已有配置项有哪些
git config --add core.compression -1
上面是通过命令来完成的，很方便，当然可以直接修改 .gitconfig 文件（在用户目录下），如果你愿意的话。部分内容如下：

[user]
name = Ggicci
email = ...
[core]
compression = -1
在 [core] 这个 section 里面添加 compression 属性即可。至于它的取值可以参考 Git Config Manpage，这个页面你可以通过man git config（Linux） 或者 git config --help（windows）来查看本地版本。core.compression
An integer -1..9, indicating a default compression level. -1 is the zlib default. 0 means no compression, and 1..9 are various speed/size tradeoffs, 9 being slowest. If set, this provides a default to other compression variables, such as core.loosecompression and pack.compression. - From Git Manpage
compression 是压缩的意思，从 clone 的终端输出就知道，服务器会压缩目标文件，然后传输到客户端，客户端再解压。取值为 [-1, 9]，-1 以 zlib 为默认压缩库，0 表示不进行压缩，1..9 是压缩速度与最终获得文件大小的不同程度的权衡，数字越大，压缩越慢，当然得到的文件会越小。
这之后再尝试了一次 clone，works perfectly :)

$ git clone https://github.com/boostorg/boost.git
Cloning into 'boost'...
remote: Counting objects: 183543, done.
remote: Compressing objects: 100% (69361/69361), done.
remote: Total 183543 (delta 113990), reused 183372 (delta 113844)
Receiving objects: 100% (183543/183543), 67.89 MiB | 162.00 KiB/s, don
e.
Resolving deltas: 100% (113990/113990), done.
Checking connectivity... done.