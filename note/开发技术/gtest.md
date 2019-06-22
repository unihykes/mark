
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

    2. ASSERT_* 失败时，直接在当前函数中返回，当前函数中ASSERT_*后面的语句将不会执行。