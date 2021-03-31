
[toc]

# /unihykes/C++/类型推导
摘要:
>暂且只讲函数模板和auto的类型推导,decltype的类型推导略过不谈;<br>


## 一.函数模板类型推导

如下是一个简单的函数模板及调用方式;<br>
```cpp
template<typename T>
void func(ParamType param)
{
}

int main()
{
    int expr = 100;
    func(expr);
}
```
对于这个函数模板中**T**的类型推导,不仅依赖实参expr的类型,还依赖形参ParamType的类型, 具体分三种情形:

- 1.形参类型ParamType具有指针或引用类型,但不是universal引用;
    >推导规则:
    若实参expr具有引用类型,先将引用部分忽略;
    然后,对实参expr和形参ParamType类型执行模式匹配,决定T的类型;

* 2.形参类型ParamType是一个universal引用;
    >推导规则:
    如果expr是个左值,T和ParamType都会被推导为左值引用;
    如果expr是个右值,则应用常规规则(同情形1);

* 3.形参类型ParamType既非指针也非引用;
    > 推导规则:
    若expr具有引用类型,则忽略其引用部分;
    忽略引用性之后,若expr是个const对象或volatile对象,也忽略之;


#### 情形1:T& 和 const T&

```cpp
template<typename T>
void func1(T& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func1)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func1(x);   //实参类型为int,        T类型推导为int,       形参类型int&
    func1(cx);  //实参类型为const int,  T类型推导为const int, 形参类型const int&
    func1(rx);  //实参类型为const int&, T类型推导为const int, 形参类型const int&
}

template<typename T>
void func2(const T& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func2)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func2(x);   //实参类型为int,        T类型推导为int, 形参类型const int&
    func2(cx);  //实参类型为const int,  T类型推导为int, 形参类型const int&
    func2(rx);  //实参类型为const int&, T类型推导为int, 形参类型const int&
}
```

执行结果:
```txt
[ RUN      ] use_template.func1
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:52) func1() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:52) func1() T is : int const
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:52) func1() T is : int const
[       OK ] use_template.func1 (2 ms)
[ RUN      ] use_template.func2
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:70) func2() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:70) func2() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:70) func2() T is : int
[       OK ] use_template.func2 (7 ms)
```



#### 情形2:T&&

```cpp
template<typename T>
void func3(T&& param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func3)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func3(x);   //实参x是左值,       T类型推导为int&, 形参类型int&
    func3(cx);  //实参cx是左值,      T类型推导为const int&, 形参类型const int&
    func3(rx);  //实参rx是左值,      T类型推导为const int&, 形参类型const int&
    func3(11);  //实参11是右值,      T类型推导为int,        形参类型int&&
}
```

执行结果:
```txt
[ RUN      ] use_template.func3
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:97) func3() T is : int & __ptr64
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:97) func3() T is : int const & __ptr64
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:97) func3() T is : int const & __ptr64
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:97) func3() T is : int
[       OK ] use_template.func3 (4 ms)
```

#### 情形3:T

```cpp
template<typename T>
void func4(T param)
{
    MK_PRINT("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(use_template, func4)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    func4(x);   //T类型推导为int, 形参类型int
    func4(cx);  //T类型推导为int, 形参类型int
    func4(rx);  //T类型推导为int, 形参类型int
    func4(11);  //T类型推导为int, 形参类型int
}

```

执行结果:
```
[ RUN      ] use_template.func4
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:125) func4() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:125) func4() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:125) func4() T is : int
[use_cpp_deduction] [Wed Mar 31 23:40:18 2021]: (use_template.cpp:125) func4() T is : int
[       OK ] use_template.func4 (3 ms)
```


## 二.auto类型推导
对于auto变量声明, auto的类型推导,与函数模版推导类似, 也分为几种情况:
* 1.变量类型是指针或者引用,但不是universal引用;
* 2.变量类型是universal引用;
* 3.变量类型既非指针也非引用;
* 4.有一个特例,当用于auto声明变量的表达式是用大括号{}时,推导的类型是std::initializer_list<>;


#### 情形1: auto& 和 const auto&

```cpp
TEST(use_auto, func5)
{
    int x =11;
    
    const auto& rx1 = x;//情况1,auto推导为int,所声明的变量类型为const int&
    MK_PRINT("type of rx1 is : %s", type_id_with_cvr<decltype(rx1)>().pretty_name().c_str());
    
    
    auto& rx2 = rx1;//情况1,auto推导为const int,所声明的变量类型为const int&
    MK_PRINT("type of rx2 is : %s", type_id_with_cvr<decltype(rx2)>().pretty_name().c_str());
}

```

执行结果:
```txt
[ RUN      ] use_auto.func5
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:39) TestBody() type of rx1 is : int const & __ptr64
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:43) TestBody() type of rx2 is : int const & __ptr64
[       OK ] use_auto.func5 (0 ms)
```




#### 情形2: auto&&

```cpp
TEST(use_auto, func6)
{
    int x = 11;
    const int cx = x;
    
    auto&& ur1 = x; //情况2,auto推导为int&,所声明的变量类型为int&
    MK_PRINT("type of ur1 is : %s", type_id_with_cvr<decltype(ur1)>().pretty_name().c_str());
    
    
    auto&& ur2 = cx;//情况2,auto推导为const int&,所声明的变量类型为 const int&
    MK_PRINT("type of ur2 is : %s", type_id_with_cvr<decltype(ur2)>().pretty_name().c_str());
    
    
    auto&& ur3 = 11;//情况2,auto推导为int,,所声明的变量类型为int&&
    MK_PRINT("type of ur3 is : %s", type_id_with_cvr<decltype(ur3)>().pretty_name().c_str());
}
```
执行结果:
```txt
[ RUN      ] use_auto.func6
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:53) TestBody() type of ur1 is : int & __ptr64
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:57) TestBody() type of ur2 is : int const & __ptr64
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:61) TestBody() type of ur3 is : int && __ptr64
[       OK ] use_auto.func6 (5 ms)
```


#### 情形3: auto

```cpp
TEST(use_auto, func7)
{
    auto x = 11;        //情况3,auto推导为int,所声明的变量类型为int
    MK_PRINT("type of x is : %s", type_id_with_cvr<decltype(x)>().pretty_name().c_str());
    
    const auto cx = x;//情况3,auto推导为int,所声明的变量类型为const int
    MK_PRINT("type of cx is : %s", type_id_with_cvr<decltype(cx)>().pretty_name().c_str());
}
```
执行结果:
```txt
[ RUN      ] use_auto.func7
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:68) TestBody() type of x is : int
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:71) TestBody() type of cx is : int const
[       OK ] use_auto.func7 (3 ms)
```


#### 情形4: 特例 {}
当用于auto声明变量的表达式是用大括号{}时,推导的类型是std::initializer_list<>;

```cpp
TEST(use_auto, func8)
{
    auto v1 = 11;
    MK_PRINT("type of v1 is : %s", type_id_with_cvr<decltype(v1)>().pretty_name().c_str());//int
    
    auto v2(11);
    MK_PRINT("type of v2 is : %s", type_id_with_cvr<decltype(v2)>().pretty_name().c_str());//int
    
    auto v3 = {11};
    //std::initializer_list<int> 
    MK_PRINT("type of v3 is : %s", type_id_with_cvr<decltype(v3)>().pretty_name().c_str());
    
    auto v4{11};
    //vs2015执行结果是int,gcc结果是std::initializer_list<int> 
    MK_PRINT("type of v4 is : %s", type_id_with_cvr<decltype(v4)>().pretty_name().c_str());
}

```
执行结果:
```
[ RUN      ] use_auto.func8
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:78) TestBody() type of v1 is : int
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:81) TestBody() type of v2 is : int
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:85) TestBody() type of v3 is : class std::initializer_list<int>
[use_cpp_deduction] [Thu Apr  1 00:11:14 2021]: (use_auto.cpp:89) TestBody() type of v4 is : int
[       OK ] use_auto.func8 (8 ms)
```







