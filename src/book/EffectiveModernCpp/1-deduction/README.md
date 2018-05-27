
<<示例详解----C++类型推导>>
>转载请注明出处: https://blog.csdn.net/WOW542621126/article/details/80474681



暂且只讲函数模板和auto的类型推导,decltype的类型推导略过不谈;<br>
内容不多,直接开始:<br>

# 1.函数模板类型推导


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

### 函数模板类型推导规则:
对于函数模板,T的类型推导,不仅依赖实参expr的类型,还依赖形参ParamType的类型, 具体分三种情形:

* 1.形参类型ParamType具有指针或引用类型,但不是universal引用;
> 推导规则:
>> 若实参expr具有引用类型,先将引用部分忽略;<br>
>> 然后,对实参expr和形参ParamType类型执行模式匹配,决定T的类型;<br>

* 2.形参类型ParamType是一个universal引用;
> 推导规则:
>> 如果expr是个左值,T和ParamType都会被推导为左值引用;<br>
>> 如果expr是个右值,则应用常规规则(同情形1);<br>

* 3.形参类型ParamType既非指针也非引用;
> 推导规则:
>> 若expr具有引用类型,则忽略其引用部分;<br>
>> 忽略引用性之后,若expr是个const对象或volatile对象,也忽略之;<br>


### 示例--情形1


* 模板形参类型:T&
```cpp

/** 1.形参类型ParamType具有指针或引用类型,但不是universal引用;
    推导规则:
    若实参expr具有引用类型,先将引用部分忽略;
    然后,对实参expr和形参ParamType类型执行模式匹配,决定T的类型;
*/

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

template<typename T>
void func1(T& param)
{
    MK_PRINT_MSG("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(ut_deduction, func1)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func1(x);   //实参类型为int,        T类型推导为int,       形参类型int&
    func1(cx);  //实参类型为const int,  T类型推导为const int, 形参类型const int&
    func1(rx);  //实参类型为const int&, T类型推导为const int, 形参类型const int&
}
```

执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052801012890?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



* 模板形参类型:const T&
```cpp
template<typename T>
void func2(const T& param)
{
    MK_PRINT_MSG("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(ut_deduction, func2)
{
    int x = 11;
    const int cx = x;
    const int& rx = x;
    
    
    func2(x);   //实参类型为int,        T类型推导为int, 形参类型const int&
    func2(cx);  //实参类型为const int,  T类型推导为int, 形参类型const int&
    func2(rx);  //实参类型为const int&, T类型推导为int, 形参类型const int&
}
```

执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010256816?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 示例--情形2:


```cpp
/** 2.形参类型ParamType是一个universal引用;
    推导规则:
    如果expr是个左值,T和ParamType都会被推导为左值引用;
    如果expr是个右值,则应用常规规则(同情形1);
*/

template<typename T>
void func3(T&& param)
{
    MK_PRINT_MSG("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(ut_deduction, func3)
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

执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010309814?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 示例--情形3:

```cpp
/** 3.形参类型ParamType既非指针也非引用(按值传递);
    推导规则:
    若expr具有引用类型,则忽略其引用部分;
    忽略引用性之后,若expr是个const对象或volatile对象,也忽略之;
*/

template<typename T>
void func4(T param)
{
    MK_PRINT_MSG("T is : %s", type_id_with_cvr<T>().pretty_name().c_str());
}

TEST(ut_deduction, func4)
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

执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010330264?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)




# 2.auto类型推导


### auto类型推导规则:
对于auto变量声明, auto的类型推导,与函数模版推导类似, 也分为三种情况:
    1.变量类型是指针或者引用,但不是universal引用;
    2.变量类型是universal引用;
    3.变量类型既非指针也非引用;
    
    但是有一个特例,当用于auto声明变量的表达式是用大括号{}时,推导的类型是std::initializer_list<>;


### 示例--情形1:

```cpp
TEST(ut_deduction, func5)
{
    int x =11;
    
    const auto& rx1 = x;//情况1,auto推导为int,所声明的变量类型为const int&
    MK_PRINT_MSG("type of rx1 is : %s", type_id_with_cvr<decltype(rx1)>().pretty_name().c_str());
    
    
    auto& rx2 = rx;//情况1,auto推导为const int,所声明的变量类型为const int&
    MK_PRINT_MSG("type of rx2 is : %s", type_id_with_cvr<decltype(rx2)>().pretty_name().c_str());
}

```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010349315?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)




### 示例--情形2:

```cpp
TEST(ut_deduction, func6)
{
    int x = 11;
    const int cx = x;
    
    auto&& ur1 = x; //情况2,auto推导为int&,所声明的变量类型为int&
    MK_PRINT_MSG("type of ur1 is : %s", type_id_with_cvr<decltype(ur1)>().pretty_name().c_str());
    
    
    auto&& ur2 = cx;//情况2,auto推导为const int&,所声明的变量类型为 const int&
    MK_PRINT_MSG("type of ur2 is : %s", type_id_with_cvr<decltype(ur2)>().pretty_name().c_str());
    
    
    auto&& ur3 = 11;//情况2,auto推导为int,,所声明的变量类型为int&&
    MK_PRINT_MSG("type of ur3 is : %s", type_id_with_cvr<decltype(ur3)>().pretty_name().c_str());
}

```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010359359?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 示例--情形3:

```cpp
TEST(ut_deduction, func7)
{
    auto x = 11;        //情况3,auto推导为int,所声明的变量类型为int
    MK_PRINT_MSG("type of x is : %s", type_id_with_cvr<decltype(x)>().pretty_name().c_str());
    
    const auto cx = x;//情况3,auto推导为int,所声明的变量类型为const int
    MK_PRINT_MSG("type of cx is : %s", type_id_with_cvr<decltype(cx)>().pretty_name().c_str());
}
```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010408297?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 示例--特例:
当用于auto声明变量的表达式是用大括号{}时,推导的类型是std::initializer_list<>;

```cpp
TEST(ut_deduction, func8)
{
    auto v1 = 11;
    MK_PRINT_MSG("type of v1 is : %s", type_id_with_cvr<decltype(v1)>().pretty_name().c_str());//int
    
    auto v2(11);
    MK_PRINT_MSG("type of v2 is : %s", type_id_with_cvr<decltype(v2)>().pretty_name().c_str());//int
    
    auto v3 = {11};
    //std::initializer_list<int> 
    MK_PRINT_MSG("type of v3 is : %s", type_id_with_cvr<decltype(v3)>().pretty_name().c_str());
    
    auto v4{11};
    //vs2015执行结果是int,gcc结果是std::initializer_list<int> 
    MK_PRINT_MSG("type of v4 is : %s", type_id_with_cvr<decltype(v4)>().pretty_name().c_str());
}
```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528010421454?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)








