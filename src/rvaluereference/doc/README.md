摘要:<br>
&#8195; 突然决定整理一篇c++右值引用相关的文章,内容暂且分为以下几个主题:

* 1.为什么要了解右值引用?
* 2.左值和右值
* 3.左值引用和右值引用
* 4.右值引用的使用方式
* 5.universal引用
* 6.引用折叠
* 7.移动语义和std::move()
* 8.完美转发和std::forward()


备注:<br>

> 1.文中测试代码均为手写, 如发现错误, 请不吝告知 :
>> 作者邮箱: liu.hao@eisoo.com <br>

> 2.转载请注明出处：
>> https://blog.csdn.net/WOW542621126/article/details/80428174

> 3.参考资料:
>> http://en.cppreference.com/w/<br>
>> https://www.cnblogs.com/5iedu/p/7698710.html<br>
>> https://www.cnblogs.com/qicosmos/p/3369940.html<br>
>> 等等...

> 4.流量预警: 
>> 文章很长... <br>
>> 图片很大... <br>
>> 代码很多... <br>



目录:<br>

[toc]


**`...正文开始...`**


# 1.为什么要了解右值引用?

### 例1:按值返回
判断以下2个函数在c++98和c++11中的性能表现:
```c++
void fun_vector1(vector<ncLargeStruct>& vStr)
{
    vStr.clear();
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(ncLargeStruct());
    }
}

vector<ncLargeStruct> fun_vector2()
{
    vector<ncLargeStruct> vStr;
    for(int i = 0; i != loopCount; ++i) {
        vStr.push_back(ncLargeStruct());
    }
    return vStr;
}

TEST(ut_vector, vector)
{
    {
        ncAutoProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr;
        fun_vector1(vStr);
    }
    printf("fun_vector1() usedSecond = %.2fs\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        
        vector<ncLargeStruct> vStr2;
        vStr2 = fun_vector2();
    }
    
    printf("fun_vector2() usedSecond = %.2fs\n", usedSecond);
}
/*
源码路径:
rvaluereference\before_after\ut_vector.cpp  
测试环境:
linux: 3.10.0-327.el7.x86_64 #1 
gcc:  4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) 
*/
```

C++98运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524113803271?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

C++11运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524113815715?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

数据分析:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524113827310?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


例1总结:
>代码风格对比:
>>fun_vector2更符合人类思维方式; 
>>如果用fun_vector1实现递归或嵌套调用,非常不友好; 

>性能横向对比: 
>>两个函数在c++11中性能均优于98中的表现; 

>性能纵向对比: 
>>c++98中,fun1性能优于fun2;
>>c++11中,两函数性能旗鼓相当;

>结论:
>>c++11中, "按值返回"风格的函数变为可接受了;


### 例2:按值传参
判断以下2个类的构造函数在c++98和c++11中的性能表现;

```c++
#ifndef __ENABLE_CXX11__
    #define move(data)   data
#endif

class normalObj1
{
public:
    normalObj1(const ncLargeStruct& data)
        : _data(data)
    {
    }
    void fun(){}
private:
    ncLargeStruct _data;
};

class normalObj2
{
public:
    normalObj2(ncLargeStruct data)
        : _data(move(data))
    {
    }
    void fun(){}
private:
    ncLargeStruct _data;
};


//测试用例 Construction1:
TEST(ut_normalObj, Construction1)
{
    {
        ncAutoProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj1 obj(str);
            obj.fun();
        }
    }
    printf("normalObj1() usedSecond = %.2fs\n", usedSecond);
    
    
    {
        ncAutoProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj2 obj(str);
            obj.fun();
        }
    }
    printf("normalObj2() usedSecond = %.2fs\n", usedSecond);
}

//测试用例 Construction2:
TEST(ut_normalObj, Construction2)
{
    {
        ncAutoProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj1 obj(move(str));
            obj.fun();
        }
    }
    printf("normalObj1() usedSecond = %.2fs\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        for(int i = 0; i != loopCount; ++i) {
            ncLargeStruct str;
            normalObj2 obj(move(str));
            obj.fun();
        }
    }
    printf("normalObj2() usedSecond = %.2fs\n", usedSecond);
}

/*
源码路径:
rvaluereference\before_after\ut_vector.cpp  
测试环境:
linux: 3.10.0-327.el7.x86_64 #1 
gcc:  4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) 
*/
```

C++98运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052417123863?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

C++11运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052417125253?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


数据分析:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524171301132?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


例2总结:
>性能横向对比:
>>类obj1, 在c++11中性能与c++98中相同;
>>类obj2, 在c++11中性能大幅优于98中的表现;

>性能纵向对比:
>>c++98, obj1性能优于obj2;
>>c++11, constructon1中,两者性能相同;
>>c++11, constructon2中,obj2大幅度优于obj1;

>结论:
>>某些特殊场景下,使用右值引用会得到不可思议的性能提升;


### 摘要

右值引用至少有以下好处:

* 降低了”***以右值初始化对象或给对象赋值***”的性能损耗;
* 降低了”***按值传参***”的性能损耗;
* 降低了”***按值返回***”的性能损耗;
* 降低了”***对象存入容器***”的性能损耗;
* 解决了”***vector或其他容器的自增长***”的性能损耗;
* 降低了“***对象交换swap***”操作的性能损耗; 
* 使得***一些标准库功能成为可能*** (例如std::unique_ptr, std::function);
* 使得***std::unique_ptr<T>可以放入容器*** ;
* 实现了”***完美转发***”;
* 代码风格更灵活, 例如返回一个容器或者***返回一个巨大的对象***成为可能;
* 即使你的代码中并不直接使用右值引用，也可以通过标准库，间接从这一新特性中受益;
    


# 2.左值和右值

## 2.1.左值右值的关系
左值和右值都属于c++表达式, 具体关系如下:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052417583090?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


## 2.2.值类别定义

### 值类别-官方定义:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524175843837?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

参考:<br>
>"New" Value Terminology by Bjarne Stroustrup, 2010.<br>
>http://www.stroustrup.com/terminology.pdf<br>


### 值类别-简单定义:
![这里写图片描述](https://img-blog.csdn.net/20180524175854767?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


简而言之, 一般情况下:
>左值: 有名字,可以取地址;<br>
>右值: 没名字,不能取地址;<br>


## 2.3.值类别判断
可以用如下模板函数来判断表达式是左值或右值;
```c++
template<class T>
char IsRight(const T& value)
{
    return 'L';
}

template<class T>
char IsRight(const T&& value)//添加const以禁用universal&&
{
    return 'R';
}

/*
上述函数判断右值的重载添加了const以禁用universal&&;
实际项目中右值引用不会使用const(const右值引用没有实际使用场景);
universal&&的概念后文再述;

源码路径:
rvaluereference\valueType\ut_Lvalue.cpp
*/

```

## 2.4.左值示例

### 左值示例1
**`变量、函数或静态数据成员之名，由其名字构成的表达式 `**<br>
(这里不论该变量的类型,即使变量的类型是右值引用同样符合)

```c++
//定义一个返回左值引用的函数
string& Categories(string& val)
{
    val = "str";
    return val;
}

//定义一个struct
struct ncCategoriesObj
{
    static const int n; 
    void fun(){}
};
const int ncCategoriesObj::n = 0;

TEST(ut_Lvalue, L_value_1)
{
    int v1 = 0;
    int&& v2 = 100;
    MK_PRINT_MSG("v1                    is %c-value", IsRight(v1));//变量名, 变量的类型是int
    MK_PRINT_MSG("v2                    is %c-value", IsRight(v2));//变量名, 变量的类型是右值引用int&&
    MK_PRINT_MSG("std::cin              is %c-value", IsRight(cin));//变量名
    MK_PRINT_MSG("Categories            is %c-value", IsRight(Categories));//函数名
    MK_PRINT_MSG("ncCategoriesObj::n    is %c-value", IsRight(ncCategoriesObj::n)); //静态数据成员名
}
/*
源码路径:
rvaluereference\valueType\ut_pRvalue.cpp
下同;
*/
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180019460?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 左值示例2
**`返回类型是左值引用的函数调用表达式`**<br>
**`返回类型是左值引用的重载运算符表达式`**<br>

```c++
//定义一个返回左值引用的函数
string& Categories(string& val)
{
    val = "str";
    return val;
}

TEST(ut_Lvalue, L_value_2)
{
    string str;
    int i = 0;
    vector<int> v = {1,2,3,4,5};
    auto iter = v.begin();
    MK_PRINT_MSG("Categories(str)       is %c-value", IsRight(Categories(str)));//返回左值引用的函数表达式
    MK_PRINT_MSG("(str = \"test\")        is %c-value", IsRight(str="test"));//返回左值引用的重载运算符
    MK_PRINT_MSG("++iter                is %c-value", IsRight(++iter));//返回左值引用的重载运算符
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180035178?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 左值示例3
**`a = b ， a += b ， a %= b，以及所有其他内建的赋值及复合赋值表达式`**<br>
**`++a 及 --a，内建的前置自增与前置自减表达式`**<br>
**`*p ，内建的间接寻址表达式`**<br>

```c++
TEST(ut_Lvalue, L_value_3)
{
    int a = 10;
    int b = 2;
    MK_PRINT_MSG("a = b                 is %c-value", IsRight(a = b));  //赋值表达式
    MK_PRINT_MSG("a += b                is %c-value", IsRight(a += b)); //复合赋值表达式
    MK_PRINT_MSG("a %%= b                is %c-value", IsRight(a %= b));//复合赋值表达式
    
    MK_PRINT_MSG("++a                   is %c-value", IsRight(++a));
    MK_PRINT_MSG("--a                   is %c-value", IsRight(--a));
    
    int n = 1;
    int* p = &n;
    MK_PRINT_MSG("*p                    is %c-value", IsRight(*p));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180048314?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 左值示例4
**`a[n] 及 p[n] ，内建的下标表达式`**<br>
(除了 a 为数组右值的情况)

```c++
TEST(ut_Lvalue, L_value_4)
{
    int array[4] = {0,1,2,3};
    int* p = &array[0];
    MK_PRINT_MSG("array[2]              is %c-value", IsRight(array[2]));
    MK_PRINT_MSG("p[2]                  is %c-value", IsRight(p[2]));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180100854?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 左值示例5
**`a.m ,对象的成员表达式`**<br>
(除了m 为成员枚举符或非静态成员函数,或者a 为右值且 m 为非引用类型的非静态数据成员的情况 )<br>

**`p->m ，内建的指针的成员表达式`**<br>
(除了 m 为成员枚举符或非静态成员函数的情况) 

```c++
TEST(ut_Lvalue, L_value_5)
{
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    
    ncObj obj;
    MK_PRINT_MSG("obj.n                 is %c-value", IsRight(obj.n));
    
    ncObj* p = &obj;
    MK_PRINT_MSG("p->n                  is %c-value", IsRight(p->n));
}

//a 为右值且 m 为非引用类型的非静态数据成员的情况在 C++11 前为纯右值,C++11起为亡值
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052418011587?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 左值示例6
**`a.*mp ，对象的成员指针表达式，其中 a 是左值且 mp 是指向数据成员的指针`**<br>
**`p->*mp ，内建的指针的成员指针表达式，其中 mp 是指向数据成员的指针`**<br>

```c++
TEST(ut_Lvalue, L_value_6)
{
    struct ncObj
    {
        int n;
    };
    
    int ncObj::*p = &ncObj::n;
    
    ncObj obj;
    MK_PRINT_MSG("obj.*p                is %c-value", IsRight(obj.*p));
    
    ncObj* pObj = &obj;
    MK_PRINT_MSG("pObj->*p              is %c-value", IsRight(pObj->*p));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180130655?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 左值示例7
**`a, b ，内建的逗号表达式，其中 b 是左值`**<br>

**`a ? b : c ，某些 b 和 c 的三元条件表达式`**<br>
（例如，它们都是同类型左值时，但细节见定义）

```c++
TEST(ut_Lvalue, L_value_7)
{
    int b = 100;
    MK_PRINT_MSG("a,b                   is %c-value", IsRight((12, b)));
    MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?b:b)));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180144796?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)







### 左值示例8
**`字符串字面量`**<br>
例如 "Hello, world!"； 

```c++
TEST(ut_Lvalue, L_value_8)
{
    MK_PRINT_MSG("\"hello world\"       is %c-value", IsRight("hello world"));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180159414?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)






### 左值示例9
**`转换为左值引用类型的转型表达式`**<br>
例如 static_cast<int&>(x)；

```c++
TEST(ut_Lvalue, L_value_9)
{
    int x = 100;
    MK_PRINT_MSG("static_cast<int&>(x)  is %c-value", IsRight(static_cast<int&>(x)));
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180210769?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)





### 左值示例10
**`函数调用表达式或重载的运算符表达式，其返回类型是到函数的右值引用`**<br>
**`转换为函数的右值引用类型的转型表达式`**<br>
如 static_cast<void (&&)(int)>(x)

```c++
//定义一个空函数
void func()
{
}

//到函数的右值引用
using funcType = void(&&)();

//返回到函数的右值引用
funcType fun_returnRvalueRef()
{
    return std::move(func);
}

TEST(ut_Lvalue, L_value_10)
{
    MK_PRINT_MSG("fun_returnRvalueRef            is %c-value", IsRight(fun_returnRvalueRef()));
    MK_PRINT_MSG("static_cast<void(&&)()>(func)  is %c-value", IsRight(static_cast<void(&&)()>(func) ));
}

/*
函数指针和引用的语法:
指向函数的指针:     using funcPtr = void(*)();
到函数的右值引用:   using funcRvalueRef = void(&&)();
*/

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180224798?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 左值示例汇总
![这里写图片描述](https://img-blog.csdn.net/20180524180237722?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



## 2.5.纯右值示例

### 纯右值示例1
**`除了字符串字面量之外的字面量`**<br>
例如 42 、 true 或 nullptr

**`匿名变量/对象`**<br>

```c++
TEST(ut_pRvalue, pRvalue1)
{
    MK_PRINT_MSG("42                    is %c-value", IsRight(42));
    MK_PRINT_MSG("true                  is %c-value", IsRight(true));
    MK_PRINT_MSG("nullptr               is %c-value", IsRight(nullptr));
    MK_PRINT_MSG("string()              is %c-value", IsRight(string("")));
}
/*
源码路径:
rvaluereference\valueType\ut_pRvalue.cpp
下同;
*/
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180321990?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)






### 纯右值示例2
**`函数调用或重载运算符表达式，其返回类型是非引用`**<br>
例如 str.substr(1, 2)、str1 + str2 或 it++ 

```c++
TEST(ut_pRvalue, pRvalue2)
{
    MK_PRINT_MSG("pow(2,2)              is %c-value", IsRight(pow(2,2)));
    
    vector<int> v = {1,2,3,4,5};
    auto iter = v.begin();
    MK_PRINT_MSG("iter++                is %c-value", IsRight(iter++));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180333773?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例3
**`a++ 与 a--，内建的后置自增与后置自减表达式`**<br>

```c++
TEST(ut_pRvalue, pRvalue3)
{
    int a = 100;
    MK_PRINT_MSG("a++                   is %c-value", IsRight(a++));
    MK_PRINT_MSG("a--                   is %c-value", IsRight(a--));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052418034645?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例4
**`a + b 、 a % b 、 a & b 、 a << b ，以及其他所有内建的算术表达式`**<br>
**`a && b 、 a || b 、 !a ，内建的逻辑表达式`**<br>
**`a < b 、 a == b 、 a >= b 以及其他所有内建的比较表达式`**<br>
**`&a，内建的取地址表达式`**<br>

```c++
TEST(ut_pRvalue, pRvalue4)
{
    int a = 10;
    int b = 2;
    
    MK_PRINT_MSG("a+b                   is %c-value", IsRight(a+b));
    MK_PRINT_MSG("a%%b                   is %c-value", IsRight(a%b));
    MK_PRINT_MSG("a&b                   is %c-value", IsRight(a&b));
    MK_PRINT_MSG("a<<b                  is %c-value", IsRight(a<<b));
    
    MK_PRINT_MSG("a&&b                  is %c-value", IsRight(a&&b));
    MK_PRINT_MSG("a||b                  is %c-value", IsRight(a||b));
    MK_PRINT_MSG("!a                    is %c-value", IsRight(!a));
    
    MK_PRINT_MSG("a<b                   is %c-value", IsRight(a<b));
    MK_PRINT_MSG("a==b                  is %c-value", IsRight(a==b));
    MK_PRINT_MSG("a>=b                  is %c-value", IsRight(a>=b));
    
    MK_PRINT_MSG("&a                    is %c-value", IsRight(&a));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180401478?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例5
**`a.m，对象成员表达式，其中 m 是成员枚举符或非静态成员函数`**<br>
**`p->m，内建的指针成员表达式，其中 m 为成员枚举符或非静态成员函数`**<br>

```c++
TEST(ut_pRvalue, pRvalue5)
{
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    
    ncObj obj;
    MK_PRINT_MSG("obj.NC_OBJ_ENUM0      is %c-value", IsRight(obj.NC_OBJ_ENUM0));//成员枚举符:右值
    MK_PRINT_MSG("obj.fun()             is %c-value", IsRight(obj.fun()));//非静态成员函数表达式:右值
    
    ncObj* p = &obj;
    MK_PRINT_MSG("p->NC_OBJ_ENUM0      is %c-value", IsRight(p->NC_OBJ_ENUM0));
    MK_PRINT_MSG("p->fun()             is %c-value", IsRight(p->fun()));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180417449?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)











### 纯右值示例6
**`a.*mp，对象的成员指针表达式，其中 mp 是指向成员函数的指针`**<br>
**`p->*mp，内建的指针的成员指针表达式，其中 mp 是指向成员函数的指针 `**<br>

```c++
TEST(ut_pRvalue, pRvalue6)
{
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    
    //void (ncObj::*pFun)() = &ncObj::fun;
    decltype(&ncObj::fun) pFun = &ncObj::fun;
    
    ncObj obj;
    //这里如果函数返回void会编译错误,但是返回void的函数表达式也是右值
    MK_PRINT_MSG("obj.*pFun             is %c-value", IsRight((obj.*pFun)()) ); 
    
    ncObj* pObj = &obj;
    MK_PRINT_MSG("pObj->*pFun           is %c-value", IsRight((pObj->*pFun)()));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180435127?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)











### 纯右值示例7
**`a, b，内建的逗号表达式，其中 b 是右值`**<br>
**`a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）`**<br>

```c++
TEST(ut_pRvalue, pRvalue7)
{
    int a = 100;
    MK_PRINT_MSG("a,b                   is %c-value", IsRight((a++, 12)));
    MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?32:12)));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180448731?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例8
**`转换为非引用类型的转型表达式`**<br>
例如 static_cast<double>(x)、std::string{} 或 (int)42；

```c++
TEST(ut_pRvalue, pRvalue8)
{
    short x = 100;
    MK_PRINT_MSG("static_cast<int>(x)   is %c-value", IsRight(static_cast<int>(x)));
    MK_PRINT_MSG("std::string{}         is %c-value", IsRight(std::string{}));
    MK_PRINT_MSG("(int)42               is %c-value", IsRight((int)42));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052418050265?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例9
**`this 指针`**<br>

```c++
TEST(ut_pRvalue, pRvalue9)
{
    struct ncObj
    {
        void fun()
        {
            MK_PRINT_MSG("this                       is %c-value", IsRight(this));
        }
    };
    
    ncObj().fun();
}

```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180515361?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例10
**`枚举项`**<br>

```c++
TEST(ut_pRvalue, pRvalue10)
{
    enum ncObjEnum
    {
        NC_OBJ_ENUM0,
        NC_OBJ_ENUM1
    };
    
    MK_PRINT_MSG("NC_OBJ_ENUM0          is %c-value", IsRight(NC_OBJ_ENUM0));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180528870?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例11
**`Lambda 表达式`**<br>
例如 [](int x){ return x * x; } 

```c++
TEST(ut_pRvalue, pRvalue11)
{
    MK_PRINT_MSG("[](int x){ return x * x; }  is %c-value", IsRight([](int x){ return x * x; }) );
    
    auto&& lam = [](int x){ return x * x; };
    bool isRValueRef = std::is_rvalue_reference<decltype(lam)>::value;
    MK_PRINT_MSG("isRValueRef = %d", isRValueRef);
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180543745?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)










### 纯右值示例汇总
![这里写图片描述](https://img-blog.csdn.net/20180524180559336?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



## 2.6.亡值示例


### 亡值示例1
**`函数调用或重载运算符表达式，其返回类型为右值引用`**<br>
例如 std::move(x)

```c++
TEST(ut_xRvalue, xRvalue1)
{
    int x = 100;
    MK_PRINT_MSG("std::move(x)          is %c-value", IsRight(std::move(x)));
}
/*
源码路径:
rvaluereference\valueType\ut_xRvalue.cpp
下同
*/
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180646563?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)











### 亡值示例2
**`a[n]，内建的下标表达式，其操作数之一是数组右值`**<br>

```c++
TEST(ut_xRvalue, xRvalue2)
{
    using arrType = int[4];
    MK_PRINT_MSG("arrType{0,1,2,3}      is %c-value", IsRight(arrType{0,1,2,3}) );
    MK_PRINT_MSG("arrType{0,1,2,3}[2]   is %c-value", IsRight(arrType{0,1,2,3}[2]));
}
```

vs2015运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180659385?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

gcc -4.8.5运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180719265?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

备注:<br>
vs-2015环境下,   arrType{0,1,2,3}是左值, arrType{0,1,2,3}[2]是左值;<br>
gcc-4.8.5环境下, arrType{0,1,2,3}是右值, arrType{0,1,2,3}[2]是左值;<br>
测试结果与C++11标准规定的结果不符.<br>



### 亡值示例3
**`a.m，对象成员表达式，其中 a 是右值且 m 是非引用类型的非静态数据成员`**<br>

```c++
TEST(ut_xRvalue, xRvalue3)
{
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    
    MK_PRINT_MSG("ncObj().n             is %c-value", IsRight(ncObj().n));///在vs2015测试, 这里是左值,g++测试是右值
}
```

vs2015运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180737987?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

gcc -4.8.5运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180749980?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


备注:<br>
VS-2015环境下,    ncObj().n 是左值;<br>
gcc-4.8.5环境下,   ncObj().n 是右值; <br>
VS2015的测试结果与C++11标准规定的结果不符, 可能是vs2015的兼容性问题;<br>



### 亡值示例4
**`a.*mp，对象的成员指针表达式，其中 a 为右值且 mp 为指向数据成员的指针`**<br>

```c++
TEST(ut_xRvalue, xRvalue4)
{
    struct ncObj
    {
        int n;
        int fun(){return 0;}
    };
    
    int ncObj::*pn = &ncObj::n;
    MK_PRINT_MSG("ncObj().*pn           is %c-value", IsRight(ncObj().*pn));///在vs2015测试, 这里是左值,g++测试是右值
}
```

vs2015运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180806555?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


gcc -4.8.5运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180821571?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

备注:<br>
VS-2015环境下,    ncObj().*pn 是左值;<br>
gcc-4.8.5环境下,   ncObj().*pn 是右值; <br>
VS2015的测试结果与C++11标准规定的结果不符, 可能是vs2015的兼容性问题;<br>




### 亡值示例5
**`a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）`**<br>

```c++
TEST(ut_xRvalue, xRvalue5)
{
    string a = "hello";
    string b = "world";
    MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?std::move(a):std::move(b))));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180838907?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 亡值示例6
**`转换为对象的右值引用类型的转型表达式`**<br>
例如 static_cast<char&&>(x)

```c++
TEST(ut_xRvalue, xRvalue6)
{
    char x = 'a';
    MK_PRINT_MSG("static_cast<char&&>(x)          is %c-value", IsRight(static_cast<char&&>(x)));
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524180852676?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
<br>


### 亡值示例-汇总
![这里写图片描述](https://img-blog.csdn.net/201805241809045?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
<br>
<br>



# 3.左值引用和右值引用

###值和引用是两个概念
![这里写图片描述](https://img-blog.csdn.net/20180524181026484?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


示例:<br>
右值       是表达式的值,   例如42;<br>
右值引用,  是表达式的类型, 例如int&&<br>


### 左右值与表达式类型没有直接关系，它们都是表达式的属性

右值引用类型的`具名`变量/对象是`左`值,  例如下面例子中的num<br>
右值引用类型的`匿名`变量/对象是`右`值,  例如下面例子中的func_R()<br>

```c++
int&& func_R()
{
    int ret = 1024;
    return std::move(ret);
}

TEST(ut_RvalueRef, RvalueRef1)
{
    int&& num = 100;
    MK_PRINT_MSG("100             is %c-value", IsRight(100));//字面量
    MK_PRINT_MSG("num             is %c-value", IsRight(num));//具名的[右值引用]类型的[左值]变量
    
    int&& result = func_R();
    MK_PRINT_MSG("func_R          is %c-value", IsRight(func_R));//函数名(函数指针)
    MK_PRINT_MSG("func_R()        is %c-value", IsRight(func_R() ));//函数返回值-匿名对象
    MK_PRINT_MSG("result          is %c-value", IsRight(result));//函数返回值-具名对象
}
/*
源码路径:
rvaluereference\referenceType\ut_RvalueRef.cpp
*/
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524181040555?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 引用类型可以引用的值类别
```c++
TEST(ut_RvalueRef, RvalueRef2)
{
    //T&
    //const T&
    //T&&
    //const T&&
    
    int n = 100;
    const int const_n = 200;
    
    int& L_Ref_to_L = n;                                            //引用自->非const左值

    const int& cL_ref_to_L = n;                                     //引用自->非const左值
    const int& cL_ref_to_cL = const_n;                              //引用自->  const左值
    const int& cL_ref_to_R = static_cast<int&&>(n);                 //引用自->非const右值
    const int& cL_ref_to_cR = static_cast<const int&&>(const_n);    //引用自->  const右值
    
    int&& R_ref_to_R = static_cast<int&&>(n);                       //引用自->非const右值
    
    const int&& cR_ref_to_R = static_cast<int&&>(n);                //引用自->非const右值
    const int&& cR_ref_to_cR = static_cast<const int&&>(const_n);   //引用自->  const右值
}
/*
源码路径:
rvaluereference\referenceType\ut_RvalueRef.cpp
*/
```
总结:
![这里写图片描述](https://img-blog.csdn.net/20180524181051655?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
<br>
常量左值引用是个“万能”的引用类型。它可以接受非常量左值、常量左值、右值对其进行初始化。<br>
<br>
<br>







# 4.右值引用的使用方式

### 参与者
C++中, 一个类通常会与其上层和下层打交道, 若要最大化利用右值引用来提升性能,需要做如下工作:
![这里写图片描述](https://img-blog.csdn.net/20180524181139957?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



* 访问者:在恰当的时机, vistor调用classA提供的接受右值引用参数的方法;<br>

* 实现者:实现所有接受右值引用参数的方法;<br>

* 下层类:下层类subClass实现所有接受右值引用参数的方法,供clasA在实现时调用(这时classA相当于vistor的角色了);<br>


### 例1:类访问者
类访问者:在恰当的时机, vistor调用实现者(ncMetadataObj)提供的接受右值引用参数的方法;


**`测试不同的访问方式带来的性能差异`**<br>

```c++
//类实现者
class ncMetadataObj
{
public:
    void push_back(const ncNewCustomString& str)
    {
        _newCustomStr = str;
    }
    
    void push_back(ncNewCustomString&& str)
    {
        _newCustomStr = std::move(str);
    }
    
private:
    ncNewCustomString           _newCustomStr;
};

//类访问者
TEST(ut_metadataObj, push_back)
{
    //访问者不同的访问方式,调用的接口不同;
    ncMetadataObj obj;
    {
        ncAutoProfilePoint point(usedSecond);
        ncNewCustomString str("some string...");
        obj.push_back(str);
    }
    MK_PRINT_MSG("push_back--1 usedSecond = %.2f\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        ncNewCustomString str("some string...");
        obj.push_back(std::move(str));
    }
    MK_PRINT_MSG("push_back--2 usedSecond = %.2f\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        obj.push_back(ncNewCustomString("some string..."));
    }
    MK_PRINT_MSG("push_back--3 usedSecond = %.2f\n", usedSecond);
}

/*
源码路径:
rvaluereference\usage\ut_metadataObj.cpp
*/
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524181155477?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


备注:<br>
访问者不同的访问方式,调用的接口不同, 关键点在于待访问类的具体实现


### 例2:类实现者
类实现者:提供并实现所有接受右值引用参数的方法

```c++
//类实现者
class ncMetadataObj
{
public:
    ncMetadataObj(const ncOldCustomString& str);
    ncMetadataObj(ncOldCustomString&& str);
    
    ncMetadataObj(const ncNewCustomString& str);
    ncMetadataObj(ncNewCustomString&& str);
    
    ncMetadataObj(const ncMetadataObj& source);
    ncMetadataObj& operator = (const ncMetadataObj& source);
    
    ncMetadataObj(ncMetadataObj&& source);
    ncMetadataObj& operator = (ncMetadataObj&& source);

    void push_back(const ncNewCustomString& str);
    void push_back(ncNewCustomString&& str);
    
    //...略
    
private:
    ncOldCustomString           _oldCustomStr;
    ncNewCustomString           _newCustomStr;
};

//const左值引用拷贝构造函数
//指针成员变量深拷贝memcopy---线性时间复杂度
ncMetadataObj::ncMetadataObj(const ncMetadataObj& source)
{
    MK_PRINT_MSG("--(const ncMetadataObj& source)");
    
    _oldCustomStr = source._oldCustomStr;
    _newCustomStr = source._newCustomStr;
    
    //模拟指针对象深拷贝
    //申请内存
    //memcopy(...);
    usleep (LOSS_TIME);//模拟其他数据成员的memcopy
}

//右值引用拷贝构造函数
//指针成员变量浅拷贝----常量时间复杂度;
ncMetadataObj::ncMetadataObj(ncMetadataObj&& source)
{
    MK_PRINT_MSG("--(ncMetadataObj&& source)");
    
    _oldCustomStr = std::move(source._oldCustomStr);
    _newCustomStr = std::move(source._newCustomStr);
    
    //模拟指针对象浅拷贝
    //_p = p;
}
/*
源码路径:
rvaluereference\usage\ncMetadataObj.h
*/
// ...略
```

### 例3 下层类
下层类subClass实现所有接受右值引用参数的方法,供上层类在实现右值方法时调用;


```c++
//类实现者
class ncMetadataObj
{
public:
    ncMetadataObj(const ncOldCustomString& str);
    ncMetadataObj(ncOldCustomString&& str);
    
    ncMetadataObj(const ncNewCustomString& str);
    ncMetadataObj(ncNewCustomString&& str);
    
    ncMetadataObj(const ncMetadataObj& source);
    ncMetadataObj& operator = (const ncMetadataObj& source);
    
    ncMetadataObj(ncMetadataObj&& source);
    ncMetadataObj& operator = (ncMetadataObj&& source);

    void push_back(const ncNewCustomString& str);
    void push_back(ncNewCustomString&& str);
    
    //...略
    
private:
    ncOldCustomString           _oldCustomStr;
    ncNewCustomString           _newCustomStr;
};

//下层类1
class ncOldCustomString
{
public:
    ncOldCustomString(const ncOldCustomString& source);
    ncOldCustomString& operator = (const ncOldCustomString& source);
};

//下层类2
class ncNewCustomString
{
public:
    ncNewCustomString(const ncNewCustomString& source)
    ncNewCustomString& operator = (const ncNewCustomString& source)
    
    ncNewCustomString(ncNewCustomString&& source)
    ncNewCustomString& operator = (ncNewCustomString&& source)
};

```


##### [测试按值返回]: 
类自身实现了右值引用拷贝构造函数,才能提升按值返回的性能
```c++
ncOldCustomString GetOldString()
{
    ncOldCustomString str("some string");
    return str;
}
ncNewCustomString GetNewString()
{
    ncNewCustomString str("some string");
    return str;
}
TEST(ut_metadataObj, return_Value)
{
    {
        ncAutoProfilePoint point(usedSecond);
        GetOldString();
    }
    MK_PRINT_MSG("usedSecond = %.2f\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        GetNewString();
    }
    MK_PRINT_MSG("usedSecond = %.2f\n", usedSecond);
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524181214982?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



##### [测试按值传参]:
类实现了右值引用函数后,是否能提升性能,还取决于下层类是否对右值引用做了兼容;

```c++
TEST(ut_metadataObj, constructor)
{
    {
        ncAutoProfilePoint point(usedSecond);
        ncMetadataObj obj1(ncOldCustomString("some string..."));
        obj1.fun();
    }
    MK_PRINT_MSG("obj1 usedSecond = %.2f\n", usedSecond);
    
    {
        ncAutoProfilePoint point(usedSecond);
        ncMetadataObj obj2(ncNewCustomString("some string..."));
        obj2.fun();
    }
    MK_PRINT_MSG("obj2 usedSecond = %.2f", usedSecond);
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180524181229653?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

说明:<br>
本例中类ncMetadataObj的构造函数对oldString和newString都实现了有右值传参,<br>
但传入oldString的构造函数性能没有明显提升;<br>





# 5.universal引用


### T&&的特性:
实际上T&&并不是一定总是表示右值引用;<br>
当存在类型推导时(例如template参数或者auto类型), 它的引用类型是未定的;<br>
此时的T&&称为universal引用(可以认为它是种通用的引用类型);<br>

即:可能是左值引用也可能是右值引用;

### Universal引用规则:
* 规则1:T&&为universal引用时, 必要条件是有类型推导发生;(反之不成立)<br>
* 规则2:universal references仅仅在T&&下发生，任何一点附加条件都会使之失效，而变成一个右值引用;<br>

备注:
>模板实参推导规则, 参考这里:
>https://blog.csdn.net/WOW542621126/article/details/80474681


### 例1:universal引用(auto推导)

```c++

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

TEST(ut_UniversalRef, auto)
{
    int n = 100;
    auto&& v1 = n;
    MK_PRINT_MSG("type of v1 is  %s", type_id_with_cvr<decltype(v1)>().pretty_name().c_str());
    
    auto&& v2 = 512;
    MK_PRINT_MSG("type of v2 is  %s", type_id_with_cvr<decltype(v2)>().pretty_name().c_str());
}

/*
源码路径:
rvaluereference\referenceType\ut_UniversalRef.cpp
下同
*/
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023741905?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 例2:universal引用(template推导)

```c++
template<typename T> 
void fun_universal_a(T&& param_a)
{
    MK_PRINT_MSG("T is %s, type of param_a is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_a)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_a)
{
    
    int n = 10;
    fun_universal_a(n);//存在类型推导, 是universal引用,可接受左值
    fun_universal_a(10);//存在类型推导, 是universal引用,可接受右值
    
    //fun_universal_a<int>(n);//T类型固定为int,编译错误
    fun_universal_a<int>(10);//T类型固定为int, 非universal引用
    
    
    fun_universal_a<int&>(n);//T类型固定为int&,存在引用折叠(下文再述),非universal引用
    //fun_universal_a<int&>(10);//T类型固定为int&,存在引用折叠(下文再述),非universal引用, 编译错误
    
    //fun_universal_a<int&&>(n);//T类型固定为int&,存在引用折叠, 非universal引用, 编译错误
    fun_universal_a<int&&>(10);//类型固定,存在引用折叠,非universal引用
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023755661?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 例3:非universal引用(不存在类型推导)

```c++
void fun_universal_b(int&& param_b)
{
    MK_PRINT_MSG("type of param_b is %s",   type_id_with_cvr<decltype(param_b)>().pretty_name().c_str());
}
TEST(ut_UniversalRef, fun_universal_b)
{
    int n = 10;
    //fun_universal_b(n);//编译错误,int&&是右值引用类型,不能接受左值
    fun_universal_b(10);//传入右值
}
```

运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023811522?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 例4:非universal引用(const T&& 和T&&的概念不同)
```
template<typename T> 
void fun_universal_c(const T&& param_c)
{
    MK_PRINT_MSG("T is %s, type of param_c is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_c)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_c)
{
    
    int n = 10;
    //fun_universal_c(n);//编译错误,const T&&尽管存在类型推导,但不符合universal规则,编译错误
    fun_universal_c(10);//传入右值,T推导为int,函数形参类型const int&&
    
    //fun_universal_c<int>(n);//T类型固定int,非universal引用,编译错误
    fun_universal_c<int>(10);//T类型固定int,非universal引用, 函数形参类型const int&&
    
    
    //关于这里为何会去掉const,可参考:https://blog.csdn.net/WOW542621126/article/details/80477911
    fun_universal_c<int&>(n);//T为int&, 函数形参类型为int&     形参const被去除
    //fun_universal_c<int&>(10);/param_c的类型为int&,不能接受右值,编译错误
    
    
    //fun_universal_c<int&&>(n);//T为int&&, 函数形参类型为int&&,编译错误,右值引用无法接受左值;
    fun_universal_c<int&&>(10);//T为int&&, 函数形参类型为int&&, 这里函数形参的const被忽略了.
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023823567?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 例5:非universal引用(不存在类型推导)
因为当给func传入实参时，T被推导后vector<T>&&的类型是确定的。

```c++
template<typename T>
void fun_universal_d(vector<T>&& param_d)
{
    MK_PRINT_MSG("T is %s, type of param_d is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_d)>().pretty_name().c_str());
}

TEST(ut_UniversalRef, fun_universal_d)
{
    vector<int> v;
    
    //fun_universal_d(v);//非universal引用,编译错误,无法将左值绑定到右值引用
    fun_universal_d(vector<int>());//非universal引用
}
```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023834803?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)




### 例6:universal引用(Args&&...类型推导)
```c++
struct ncLittleObj
{
    ncLittleObj(int&& a, int&& b)
    {
        MK_PRINT_MSG("type of a is %s", type_id_with_cvr<decltype(a)>().pretty_name().c_str());
    }
    
    ncLittleObj(const int& a, const int& b)
    {
        MK_PRINT_MSG("type of a is %s", type_id_with_cvr<decltype(a)>().pretty_name().c_str());
    }
};

template<class T, class Allocator=allocator<T>>
class Vector_Lite
{
public:
    //虽然push_back的形参符合T&&格式，但不是universal引用
    //因为 Vector_Lite<T> 实例化后，push_back的形参类型就确定下来
    //所以在调用时push_back函数时并不存在类型推导。
    void push_back(T&& param)
    {
        MK_PRINT_MSG("T is %s, type of param is %s", 
            type_id_with_cvr<T>().pretty_name().c_str(),
            type_id_with_cvr<decltype(param)>().pretty_name().c_str());
    }
    
    //Arg&&存在类型推导，所以args的参数是universal引用。
    //因为参数Args独立于vector的类型参数T，所以每次emplace_back被调用的时候，Args必须被推导。
    template<class ...Args>
    void emplace_back(Args&&...  args)
    {
        ncLittleObj obj(std::forward<Args>(args)...);
    }
};


TEST(ut_UniversalRef, Vector_Lite)
{
    Vector_Lite<int> v;
    int n = 1;
    
    //v.push_back(n);//非universal引用
    v.push_back(100);//非universal引用
    
    v.emplace_back(n, n);//universal引用,可接受左值
    v.emplace_back(34, 46);//universal引用,可接受右值
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023845893?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 总结:
1:T&&为universal 引用时的必要条件是有类型推断发生;<br>
2:universal 引用仅仅在T&&下发生，const T&&是一个固定的右值引用;<br>
3.当T&&是universal引用时, Universal引用最终的引用类型, 是与接受的[值]相关;<br>
    接受左值参数,T&&就是左值引用;<br>
    接受右值参数,T&&就是右值引用;<br>




# 6.引用折叠

### 引用折叠规则:
1.引用本身不是一个对象，C++标准不允许直接定义引用的引用。<br>
如“int& & a = b;”（注意两个&中间有空格，不是int&&）这样的语句是编译不过的。<br>

2.容许通过模板或 typedef 中的类型操作组成到引用的引用;<br>
该情况下应用引用折叠规则：<br>
->到右值引用的右值引用折叠成右值引用，X& &、X& &&和X&& &都折叠成类型X&。<br>
->所有其他组合折叠成左值引用, 即类型X&& &&折叠成X&&。<br>

3.引用折叠规则暗示我们，可以将任意类型的实参传递给T&&类型的函数模板参数.<br>
参考上节universal引用的介绍;<br>


### 例1:引用折叠(typedef)

```c++

#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

TEST(ut_ReferenceCollapsing, typedef)
{
    typedef int&  lRef;
    typedef int&& rRef;
    
    int n = 100;
    
    lRef&  r1 = n;
    MK_PRINT_MSG("type of r1 is %s", type_id_with_cvr<decltype(r1)>().pretty_name().c_str());
            
    lRef&& r2 = n;
    MK_PRINT_MSG("type of r2 is %s", type_id_with_cvr<decltype(r2)>().pretty_name().c_str());
    
    rRef&  r3 = n; 
    MK_PRINT_MSG("type of r3 is %s", type_id_with_cvr<decltype(r3)>().pretty_name().c_str());
    
    rRef&& r4 = 1;
    MK_PRINT_MSG("type of r4 is %s", type_id_with_cvr<decltype(r4)>().pretty_name().c_str());
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023903179?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 例2:引用折叠(decltype)

```c++
TEST(ut_ReferenceCollapsing, decltype)
{
    int n = 1;
    int& v1 = n;
    int&& v2 = 100;
    
    MK_PRINT_MSG("type of decltype(v1)& is %s", type_id_with_cvr<decltype(v1)&>().pretty_name().c_str());
    MK_PRINT_MSG("type of decltype(v1)&& is %s", type_id_with_cvr<decltype(v1)&&>().pretty_name().c_str());
    
    MK_PRINT_MSG("type of decltype(v2)& is %s", type_id_with_cvr<decltype(v2)&>().pretty_name().c_str());
    MK_PRINT_MSG("type of decltype(v2)&& is %s", type_id_with_cvr<decltype(v2)&&>().pretty_name().c_str());
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023914834?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 例3:引用折叠(T&)
```c++
template<typename T> 
void fun_collapsing_a(T& param_a)
{
    MK_PRINT_MSG("T is %s , type of param_a is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_a)>().pretty_name().c_str());
}

TEST(ut_ReferenceCollapsing, template1)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    fun_collapsing_a(n);//T推导为int,无需折叠,T&相当于int&
    fun_collapsing_a(nL);//T推导为int,无需折叠,T&相当于int&
    fun_collapsing_a(nR);//T推导为int,无需折叠,T&相当于int&
    //fun_collapsing_a(100);T推导为int,无需折叠,T&相当于int&, 编译错误,左值引用无法接受右值
}
```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023926634?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 例4:引用折叠(T&&)
```c++
template<typename T> 
void fun_collapsing_b(T&& param_b)
{
    MK_PRINT_MSG("T is %s , type of param_b is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_b)>().pretty_name().c_str());
}

TEST(ut_ReferenceCollapsing, template2)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    fun_collapsing_b(n);//n是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(nL);//nL是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(nR);//nR是左值, T推导为int&,形参折叠为int&
    fun_collapsing_b(100);//100是右值, T推导为int,形参无折叠,为int&&
    cout<<endl;
    
    ///fun_collapsing_b<int>(n);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nL);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    ///fun_collapsing_b<int>(nR);//T为int,无折叠,编译错误,无法将左值绑定到右值引用
    fun_collapsing_b<int>(100);//T为int,无折叠
    cout<<endl;
    
    fun_collapsing_b<int&>(n);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nL);//T为int&, 触发引用折叠T&&等价于int&
    fun_collapsing_b<int&>(nR);//T为int&, 触发引用折叠T&&等价于int&
    ///fun_collapsing_b<int&>(100);//T为int&, 触发引用折叠T&&等价于int&, 编译错误,无法将参数 从“int”转换为“int &” 
    cout<<endl;
    
    ///fun_collapsing_b<int&&>(n);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nL);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_b<int&&>(nR);//T为int&&, 引用折叠T&&等价于int&&, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_b<int&&>(100);//T为int&&, 引用折叠T&&等价于int&&
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/2018052802393880?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)




### 例5:引用折叠(const T&&)
```c++
template<typename T> 
void fun_collapsing_c(const T&& param_c)
{
    MK_PRINT_MSG("T is %s , type of param_c is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param_c)>().pretty_name().c_str());
}

TEST(ut_ReferenceCollapsing, template3)
{
    int n = 100;
    int& nL = n;
    int&& nR = 100;
    
    
    ///fun_collapsing_c(n);//T推导为int, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_c(nL);//T推导为int, 编译错误:无法将左值绑定到右值引用
    ///fun_collapsing_c(nR);//T推导为int, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_c(100);//T推导为int 
    
    
    
    //fun_collapsing_c<int>(n);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nL);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    //fun_collapsing_c<int>(nR);//T固定为int,不触发引用折叠, 编译错误:无法将左值绑定到右值引用
    fun_collapsing_c<int>(100);//T固定为int,不触发引用折叠
    
    
    
    //关于这里为何会去掉const,可参考:https://blog.csdn.net/WOW542621126/article/details/80477911
    fun_collapsing_c<int&>(n);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const
    fun_collapsing_c<int&>(nL);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const 
    fun_collapsing_c<int&>(nR);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const
    ///fun_collapsing_c<int&>(100);//T为int&,触发了引用折叠,折叠后变为形参变为int&,去掉了const,编译错误
    
    
    ///fun_collapsing_c<int&&>(n);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nL);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    ///fun_collapsing_c<int&&>(nR);//T为int&&,触发了引用折叠,折叠后等价于int&&,去掉了const, 编译错误,无法左值绑定到右值
    fun_collapsing_c<int&&>(100);//T为int&&,触发了引用折叠,折叠后等价于const int&&,去掉了const
}

```
运行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528023949872?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



### 总结:
引用折叠, 是与接受的[引用类型]相关;<br>
到左值引用类型(lRef)的左值引用&, 折叠为左值引用;<br>
到左值引用类型(lRef)的右值引用&&, 折叠为左值引用;<br>
到右值引用类型(rRef)的左值引用&, 折叠为左值引用;<br>
到右值引用类型(rRef)的右值引用&&, 折叠为右值引用;<br>



# 7.移动语义和std::move()
我们前文中,std::move()函数已经出现过,<br>
简单来说,move函数的功能是将一个左值强制转换为右值, 从而可以调用右值引用类型形参的函数;


> std::move 可能的实现,大致如下面所示:
```cpp
template< class T > 
struct remove_reference
{
    typedef T type;
};

template< class T > 
struct remove_reference<T&>
{
    typedef T type;
};

template< class T > 
struct remove_reference<T&&> 
{
    typedef T type;
};

template<typename T>
typename remove_reference<T>::type&& move(T&& param)
{
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}
```

### 示例1:remove_reference
为了容易理解 remove_reference 的工作原理,我们山寨一个 remove_reference

```cpp
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

template< class T > 
struct my_remove_reference
{
    using type = T;
    static const int id = 1;
};

template< class T > 
struct my_remove_reference<T&>
{
    using type = T;
    static const int id = 2;
};

template< class T > 
struct my_remove_reference<T&&> 
{
    using type = T;
    static const int id = 3;
};

TEST(ut_move, my_remove_reference)
{
   {
        using ReturnType = my_remove_reference<int>::type&&;//int&&
        int id = my_remove_reference<int>::id;//1
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
   
   {
        using ReturnType = my_remove_reference<int&>::type&&;//int&&
        int id = my_remove_reference<int&>::id;//2
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
   
   {
        using ReturnType = my_remove_reference<int&&>::type&&;//int&&
        int id = my_remove_reference<int&&>::id;//3
        MK_PRINT_MSG("id = %d, ReturnType is %s", id, type_id_with_cvr<ReturnType>().pretty_name().c_str());
   }
}
```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528171946410?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


### 示例2:move
为了容易理解 std::move 的工作原理,我们再山寨一个 move 模板函数
```cpp
template<typename T>
typename my_remove_reference<T>::type&& my_move(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(), 
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
     
    using ReturnType = typename my_remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

TEST(ut_move, my_move)
{
    int n = 5;
    auto&& ret1 = my_move(n);
    MK_PRINT_MSG("type of ret1 is %s\n", type_id_with_cvr<decltype(ret1)>().pretty_name().c_str());
    
    const int m = 12;
    auto&& ret2 = my_move(m);
    MK_PRINT_MSG("type of ret2 is %s\n", type_id_with_cvr<decltype(ret2)>().pretty_name().c_str());
    
    auto&& ret3 = my_move(100);
    MK_PRINT_MSG("type of ret3 is %s\n", type_id_with_cvr<decltype(ret3)>().pretty_name().c_str());
    
    int n2 = 11;
    int& nL = n2;
    auto&& ret4 = my_move(nL);
    MK_PRINT_MSG("type of ret4 is %s\n", type_id_with_cvr<decltype(ret4)>().pretty_name().c_str());
}
```
执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528171958969?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)




* 总结:

> 移动语义作用:<br>
>> 替代copy操作,提高性能;<br>
>> 使得创建只移型对象成为可能,例如std::unique_ptr, std::thread;<br>

> std::move()有几个要点:
>> 1.std::move函数中的T&&是个universal引用,可以接受任意左值和右值;<br>
>> 2.std::move实际上并不进行任何移动, 仅仅执行强制类型转换;<br>
>> 3.std::move无条件的将实参强制转为右值; const实参会转为const T&&类型的右值;<br>
>> 4.std::move调用之后,所转移的对象及引用变为未定义状态,不可再次使用;<br>




# 8.完美转发和std::forward()
当我们在一个函数中,希望将自身函数的实参传递给其他函数,却又不希望变更实参的类别时,
(左值仍是左值,右值仍是右值),就会用到std::forward;


> std::forward 可能的实现,大致如下面所示

```cpp
template<typename T>
T&& forward(typename std::remove_reference<T>::type& param)
{
    return static_cast<T&&>(param);
}
```

### 示例1:forward
为了容易理解 std::forward 的工作原理,我们再山寨一个 forward 模板函数

```cpp
template<typename T>
T&& my_forward(typename std::remove_reference<T>::type& param)
{
    MK_PRINT_MSG("T is %s, T&& is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<T&&>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
    
    return static_cast<T&&>(param);
}

template<typename T>
void funcAAA(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
        
    funcBBB(my_forward<T>(param));
}

template<typename T>
void funcBBB(T&& param)
{
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}


TEST(ut_forward, my_forward)
{
    //传给funcAAA的实参为左值;
    int s1 = 100;
    funcAAA(s1);
    
    cout<<endl;
    
    //传给funcAAA的实参为右值
    funcAAA(100);
}
```

执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528172021745?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

总结:

> 完美转发:
>> 转发函数的实参到目标函数, 使目标函数接受到与转发函数完全相同的实参;<br>

> 特性:
>> std::forward并不进行任何转发;<br>
>> std::forward仅在某个特定条件满足时,才会执行强制转换将实参转为右值:<br>
>> 当传入的实参被绑定到左值时,std::forward未做任何事情;<br>
>> 当传入的实参被绑定到右值时,std::forward执行强制转换将实参转为右值;<br>

*****
...全文完...
*****
