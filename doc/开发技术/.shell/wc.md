
# wc -l

```shell
统计当前目录下所有文件代码行数
find . -type f | xargs wc -l
find . -name "*.cpp" | xargs wc -l


统计当前目录下的所有文件行数：
wc -l *

当前目录以及子目录的所有文件行数：
find  . * | xargs wc -l
可以把*改成所要匹配的文件，例如java文件,*.java这样就只统计java源码了。


一个目录下代码总行数以及单个文件行数：
find . -name "*.html" | xargs wc -l
find . -name "*" | xargs wc -l


查询指定后缀名的文件总个数命令：（得到的是html文件的数目）
find . -name "*.html" | wc -l

查询一个目录下代码总行数以及单个文件行数：（得到的是每个及所有html文件中内容的行数）
find . -name "*.html" | xargs wc -l

查询cat过滤某文件输出的条目数：
cat xxx.txt  | grep aaa | wc -l
```