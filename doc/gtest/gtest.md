
github地址：
https://github.com/google/googletest

官方文档见：
https://github.com/google/googletest/blob/master/googletest/docs/Primer.md

https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md





## 相关链接:

1.玩转Google开源C++单元测试框架Google Test系列(gtest)之一 - 初识gtest
http://www.cnblogs.com/coderzh/archive/2009/03/31/1426758.html

2.玩转Google开源C++单元测试框架Google Test系列(gtest)之二 - 断言
http://www.cnblogs.com/coderzh/archive/2009/04/06/1430364.html


3.玩转Google开源C++单元测试框架Google Test系列(gtest)之三 - 事件机制
http://www.cnblogs.com/coderzh/archive/2009/04/06/1430396.html

4.玩转Google开源C++单元测试框架Google Test系列(gtest)之四 - 参数化
http://www.cnblogs.com/coderzh/archive/2009/04/08/1431297.html

5.玩转Google开源C++单元测试框架Google Test系列(gtest)之五 - 死亡测试
http://www.cnblogs.com/coderzh/archive/2009/04/08/1432043.html

6.玩转Google开源C++单元测试框架Google Test系列(gtest)之六 - 运行参数
http://www.cnblogs.com/coderzh/archive/2009/04/10/1432789.html

7.玩转Google开源C++单元测试框架Google Test系列(gtest)之七 - 深入解析gtest
http://www.cnblogs.com/coderzh/archive/2009/04/11/1433744.html

8.玩转Google开源C++单元测试框架Google Test系列(gtest)之八 - 打造自己的单元测试框架
http://www.cnblogs.com/coderzh/archive/2009/04/12/1434155.html



    1. EXPECT_*  失败时，案例继续往下执行。

    2. ASSERT_* 失败时，直接在当前函数中返回，当前函数中ASSERT_*后面的语句将不会执行
    

## 代码覆盖率
#### windows

1.Windows下需要安装OpenCppCoverage这个软件
2.编写ut;
3.运行ut;
    xxxx/OpenCppCoverag 
    --sources xxx\client 
    -- xxUT.exe  --gtest_filter=ncxxUT.*
4.执行命令后，会在可执行文件所在目录生成一个代码覆盖率报告;

#### linux
1.需要将待测试源码编译到ut中;
2. buildpath=xx/build/Linux_el7_x64/Debug/src/client/test/ut//Build/CMakeFiles/xxx.dir/src 根据不同编译位置生成的位置也会有所不同，不过都会在build目录下。
3. 到可执行目录运行ut;
4.运行过后会在buildpath生成覆盖率文件;
5. 在可执行目录里输入命令lcov -c --rc lcov_branch_coverage=1 -d $build_path -o res.info 
其中
-d代表gcda和gcno文件所在位置，
-o代表输出文件名res.info，
--rc lcov_branch_coverage=1 代表启动分支覆盖， 
-c代表捕捉覆盖率文件。
6. 然而得到的res.info可能包含了很多不需要的模块，
因此可以使用正则表达式对需要的模块进行提取或者排除，lcov -e res.info *backup/src* --rc lcov_branch_coverage=1 -o res.ref，
这个命令的作用是将res.info里将匹配*backup/src*的文件提取出来，这是-e参数的作用，
如果采用-r参数则是移除匹配的文件。这个命令可以迭代使用从而精确过滤到你想要的代码模块。
7. 最后执行命令genhtml res.ref --legend --branch-coverage -o result，
--legend代表生成图例。这个命令会将结果输出到result这个目录中，
然后进入此目录打开index.html即可浏览代码覆盖率。