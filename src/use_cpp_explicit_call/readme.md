[toc]

# /unihykes/C++/显式指定函数模板参数为引用类型﻿

摘要:<br>
>某些场景下,显式指定函数模板参数为引用类型, 触发引用折叠, 会有一些反直觉的情况发生,特此记录一下:


## 情形1:const T&

```cpp
template<typename T>
void funcCall_A(const T& param)
{
    param += 10;
    
    MK_PRINT("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(use_explicit_call, funcCall_A)
{
    int n = 1;
    
    funcCall_A<int&>(n);//const被丢弃
    MK_PRINT("n = %d", n);
    
    funcCall_A<int&&>(n);//const被丢弃
    MK_PRINT("n = %d", n);
}
```
执行结果:<br>
```txt
[ RUN      ] use_explicit_call.funcCall_A
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:38) funcCall_A() T is int & __ptr64, type of param is int & __ptr64
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:46) TestBody() n = 11
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:38) funcCall_A() T is int && __ptr64, type of param is int & __ptr64
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:49) TestBody() n = 21
[       OK ] use_explicit_call.funcCall_A (10 ms)
```


## 情形2:const T&&
```cpp
template<typename T>
void funcCall_B(const T&& param)
{
    param += 10;
    
    MK_PRINT("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(use_explicit_call, funcCall_B)
{
    int n = 5;
    
    funcCall_B<int&>(n);//const被丢弃
    MK_PRINT("n = %d", n);
    
    funcCall_B<int&&>(100);//const被丢弃, 修改了一个临时对象(右值)
}

```

执行结果:<br>
```txt
[ RUN      ] use_explicit_call.funcCall_B
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:62) funcCall_B() T is int & __ptr64, type of param is int & __ptr64
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:70) TestBody() n = 15
[use_cpp_explicit_call] [Thu Apr  1 00:40:03 2021]: (use_explicit_call.cpp:62) funcCall_B() T is int && __ptr64, type of param is int && __ptr64
[       OK ] use_explicit_call.funcCall_B (1 ms)
```
