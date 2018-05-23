[toc]

# 1.为什么要了解右值引用?

### 摘要:右值引用至少有以下好处:
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
* 即使你的代码中并不直接使用右值引用，也可以通过标准库，间接从这一新特性中受益




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
ut_rvaluereference\before_after\ut_vector.cpp  
测试环境:
linux: 3.10.0-327.el7.x86_64 #1 
gcc:  4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) 
*/
```

C++98运行结果:
//todo

C++11运行结果:
//todo

数据分析:
//todo

总结:
>代码风格对比:
>>fun_vector2更符合人类思维方式; 
>>如果用fun_vector1实现递归或嵌套调用,非常不友好; 

>性能横向对比: 
>>两个函数在c++11中性能均优于98中的表现; 

>性能纵向对比: 
>>c++98中,fun1性能优于fun2;
>>c++11中,两函数性能旗鼓相当;

>结论:
>>c++11中, fun_vector2风格的函数变为可接受了;


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
ut_rvaluereference\before_after\ut_vector.cpp  
测试环境:
linux: 3.10.0-327.el7.x86_64 #1 
gcc:  4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) 
*/
```

C++98运行结果:
//todo

C++11运行结果:
//todo

数据分析:
//todo



总结:
>性能横向对比:
>>类obj1, 在c++11中性能与c++98中相同;
>>类obj2, 在c++11中性能大幅优于98中的表现;

>性能纵向对比:
>>c++98, obj1性能优于obj2;
>>c++11, constructon1中,两者性能相同;
>>c++11, constructon2中,obj2大幅度优于obj1;

>结论:
某些特殊场景下,使用右值引用会得到不可思议的性能提升;















# 2.左值和右值

左值右值的关系
左值和右值都属于c++表达式, 具体关系如下:
//todo


### 值类别定义

##### 值类别-官方定义:
//todo
参考:
"New" Value Terminology by Bjarne Stroustrup, 2010.
http://www.stroustrup.com/terminology.pdf


##### 值类别-简单定义:
//todo

>简而言之, 一般情况下:
>>左值: 有名字,可以取地址;
>>右值: 没名字,不能取地址;


### 值类别判断
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
备注:
上述函数判断右值的重载添加了const以禁用universal&&;
实际项目中右值引用不会使用const(const右值引用没有实际使用场景);
universal&&的概念后文再述;

源码路径:
ut_rvaluereference\valueType\ut_Lvalue.cpp
*/

```


### 左值示例1
##### 变量、函数或静态数据成员之名，由其名字构成的表达式
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
    {
        int v1 = 0;
        int&& v2 = 100;
        MK_PRINT_MSG("v1                    is %c-value", IsRight(v1));//变量名, 变量的类型是int
        MK_PRINT_MSG("v2                    is %c-value", IsRight(v2));//变量名, 变量的类型是右值引用int&&
        MK_PRINT_MSG("std::cin              is %c-value", IsRight(cin));//变量名
        MK_PRINT_MSG("Categories            is %c-value", IsRight(Categories));//函数名
        MK_PRINT_MSG("ncCategoriesObj::n    is %c-value", IsRight(ncCategoriesObj::n)); //静态数据成员名
    }
}
/*
源码路径:
ut_rvaluereference\valueType\ut_pRvalue.cpp
下同;
*/
```

运行结果:
//todo


### 左值示例2
##### 返回类型是左值引用的函数调用表达式
##### 返回类型是左值引用的重载运算符表达式
```c++
//定义一个返回左值引用的函数
string& Categories(string& val)
{
    val = "str";
    return val;
}

TEST(ut_Lvalue, L_value_2)
{
    {
        string str;
        int i = 0;
        vector<int> v = {1,2,3,4,5};
        auto iter = v.begin();
        MK_PRINT_MSG("Categories(str)       is %c-value", IsRight(Categories(str)));//返回左值引用的函数表达式
        MK_PRINT_MSG("(str = \"test\")        is %c-value", IsRight(str="test"));//返回左值引用的重载运算符
        MK_PRINT_MSG("++iter                is %c-value", IsRight(++iter));//返回左值引用的重载运算符
    }
}
```

运行结果:
//todo

### 左值示例3
##### a = b ， a += b ， a %= b，以及所有其他内建的赋值及复合赋值表达式
##### ++a 及 --a，内建的前置自增与前置自减表达式
##### *p ，内建的间接寻址表达式

```c++
TEST(ut_Lvalue, L_value_3)
{
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
}

```
运行结果:
//todo




### 左值示例4
##### a[n] 及 p[n] ，内建的下标表达式
(除了 a 为数组右值的情况)

```c++
TEST(ut_Lvalue, L_value_4)
{
    {
        int array[4] = {0,1,2,3};
        int* p = &array[0];
        MK_PRINT_MSG("array[2]              is %c-value", IsRight(array[2]));
        MK_PRINT_MSG("p[2]                  is %c-value", IsRight(p[2]));
    }
}

```
运行结果:
//todo




### 左值示例5
##### a.m ,对象的成员表达式
(除了m 为成员枚举符或非静态成员函数,或者a 为右值且 m 为非引用类型的非静态数据成员的情况 )
##### p->m ，内建的指针的成员表达式
(除了 m 为成员枚举符或非静态成员函数的情况) 

```c++
TEST(ut_Lvalue, L_value_5)
{
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
}

//备注:a 为右值且 m 为非引用类型的非静态数据成员的情况在 C++11 前为纯右值,C++11起为亡值
```
运行结果:
//todo




### 左值示例6
##### a.*mp ，对象的成员指针表达式，其中 a 是左值且 mp 是指向数据成员的指针
##### p->*mp ，内建的指针的成员指针表达式，其中 mp 是指向数据成员的指针

```c++
TEST(ut_Lvalue, L_value_6)
{
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
}

```
运行结果:
//todo




### 左值示例7
##### a, b ，内建的逗号表达式，其中 b 是左值
##### a ? b : c ，某些 b 和 c 的三元条件表达式
（例如，它们都是同类型左值时，但细节见定义）

```c++
TEST(ut_Lvalue, L_value_7)
{
    {
        int b = 100;
        MK_PRINT_MSG("a,b                   is %c-value", IsRight((12, b)));
        MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?b:b)));
    }
}

```
运行结果:
//todo






### 左值示例8
##### 字符串字面量
例如 "Hello, world!"； 
```c++
TEST(ut_Lvalue, L_value_8)
{
    {
        MK_PRINT_MSG("\"hello world\"       is %c-value", IsRight("hello world"));
    }
}

```
运行结果:
//todo





### 左值示例9
##### 转换为左值引用类型的转型表达式
例如 static_cast<int&>(x)；

```c++
TEST(ut_Lvalue, L_value_9)
{
    {
        int x = 100;
        MK_PRINT_MSG("static_cast<int&>(x)  is %c-value", IsRight(static_cast<int&>(x)));
    }
}

```
运行结果:
//todo




### 左值示例10
##### 函数调用表达式或重载的运算符表达式，其返回类型是到函数的右值引用
##### 转换为函数的右值引用类型的转型表达式
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
    {
        MK_PRINT_MSG("fun_returnRvalueRef               is %c-value", IsRight(fun_returnRvalueRef()));
    }
    
    {
        MK_PRINT_MSG("static_cast<void(&&)()>(func)     is %c-value", IsRight(static_cast<void(&&)()>(func) ));
    }
}

/*
备注,函数指针和引用的语法:
指向函数的指针:     using funcPtr = void(*)();
到函数的右值引用:   using funcRvalueRef = void(&&)();
*/

```
运行结果:
//todo


### 左值示例汇总
//todo


### 纯右值示例1
除了字符串字面量之外的字面量，例如 42 、 true 或 nullptr
匿名变量/对象;
```c++
TEST(ut_pRvalue, pRvalue1)
{
    {
        MK_PRINT_MSG("42                    is %c-value", IsRight(42));
        MK_PRINT_MSG("true                  is %c-value", IsRight(true));
        MK_PRINT_MSG("nullptr               is %c-value", IsRight(nullptr));
        MK_PRINT_MSG("string()              is %c-value", IsRight(string("")));
    }
}
/*
源码路径:
ut_rvaluereference\valueType\ut_pRvalue.cpp
下同;
*/
```
运行结果:
//todo





### 纯右值示例2
函数调用或重载运算符表达式，其返回类型是非引用，例如 str.substr(1, 2)、str1 + str2 或 it++ 

```c++
TEST(ut_pRvalue, pRvalue2)
{
    /// 函数调用或重载运算符表达式，其返回类型是非引用，例如 str.substr(1, 2)、str1 + str2 或 it++ ； 
    {
        MK_PRINT_MSG("pow(2,2)              is %c-value", IsRight(pow(2,2)));
        
        vector<int> v = {1,2,3,4,5};
        auto iter = v.begin();
        MK_PRINT_MSG("iter++                is %c-value", IsRight(iter++));
    }
}
```

运行结果:
//todo









### 纯右值示例3
a++ 与 a--，内建的后置自增与后置自减表达式

```c++
TEST(ut_pRvalue, pRvalue3)
{
    /// a++ 与 a--，内建的后置自增与后置自减表达式； 
    {
        int a = 100;
        MK_PRINT_MSG("a++                   is %c-value", IsRight(a++));
        MK_PRINT_MSG("a--                   is %c-value", IsRight(a--));
    }
}
```

运行结果:
//todo









### 纯右值示例4
a + b 、 a % b 、 a & b 、 a << b ，以及其他所有内建的算术表达式； 
a && b 、 a || b 、 !a ，内建的逻辑表达式；
a < b 、 a == b 、 a >= b 以及其他所有内建的比较表达式； 
&a，内建的取地址表达式； 

```c++
TEST(ut_pRvalue, pRvalue4)
{
    /// a + b 、 a % b 、 a & b 、 a << b ，以及其他所有内建的算术表达式； 
    /// a && b 、 a || b 、 !a ，内建的逻辑表达式；
    /// a < b 、 a == b 、 a >= b 以及其他所有内建的比较表达式； 
    /// &a，内建的取地址表达式； 
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
}
```

运行结果:
//todo









### 纯右值示例5
a.m，对象成员表达式，其中 m 是成员枚举符或非静态成员函数
p->m，内建的指针成员表达式，其中 m 为成员枚举符或非静态成员函数

```c++
TEST(ut_pRvalue, pRvalue5)
{
    /// a.m，对象成员表达式，其中 m 是成员枚举符或非静态成员函数
    /// p->m，内建的指针成员表达式，其中 m 为成员枚举符或非静态成员函数
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    {
        ncObj obj;
        MK_PRINT_MSG("obj.NC_OBJ_ENUM0      is %c-value", IsRight(obj.NC_OBJ_ENUM0));//成员枚举符:右值
        MK_PRINT_MSG("obj.fun()             is %c-value", IsRight(obj.fun()));//非静态成员函数表达式:右值
        
        ncObj* p = &obj;
        MK_PRINT_MSG("p->NC_OBJ_ENUM0      is %c-value", IsRight(p->NC_OBJ_ENUM0));
        MK_PRINT_MSG("p->fun()             is %c-value", IsRight(p->fun()));
    }
}
```

运行结果:
//todo










### 纯右值示例6
a.*mp，对象的成员指针表达式，其中 mp 是指向成员函数的指针 
p->*mp，内建的指针的成员指针表达式，其中 mp 是指向成员函数的指针 

```c++
TEST(ut_pRvalue, pRvalue6)
{
    /// a.*mp，对象的成员指针表达式，其中 mp 是指向成员函数的指针 
    /// p->*mp，内建的指针的成员指针表达式，其中 mp 是指向成员函数的指针 
    struct ncObj
    {
        enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
        int n;
        int fun(){return 0;}
    };
    {
        //void (ncObj::*pFun)() = &ncObj::fun;
        decltype(&ncObj::fun) pFun = &ncObj::fun;
        
        ncObj obj;
        MK_PRINT_MSG("obj.*pFun             is %c-value", IsRight((obj.*pFun)()) ); //这里如果函数返回void会编译错误,但是返回void的函数表达式也是右值
        
        ncObj* pObj = &obj;
        MK_PRINT_MSG("pObj->*pFun           is %c-value", IsRight((pObj->*pFun)()));
    }
}
```

运行结果:
//todo










### 纯右值示例7
a, b，内建的逗号表达式，其中 b 是右值； 
a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）；

```c++
TEST(ut_pRvalue, pRvalue7)
{
    /// a, b，内建的逗号表达式，其中 b 是右值； 
    /// a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）；  
    {
        int a = 100;
        MK_PRINT_MSG("a,b                   is %c-value", IsRight((a++, 12)));
        MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?32:12)));
    }
}
```

运行结果:
//todo









### 纯右值示例8
转换为非引用类型的转型表达式，例如 static_cast<double>(x)、std::string{} 或 (int)42；

```c++
TEST(ut_pRvalue, pRvalue8)
{    
    /// 转换为非引用类型的转型表达式，例如 static_cast<double>(x)、std::string{} 或 (int)42； 
    {
        short x = 100;
        MK_PRINT_MSG("static_cast<int>(x)   is %c-value", IsRight(static_cast<int>(x)));
        MK_PRINT_MSG("std::string{}         is %c-value", IsRight(std::string{}));
        MK_PRINT_MSG("(int)42               is %c-value", IsRight((int)42));
    }
}
```

运行结果:
//todo









### 纯右值示例9
this 指针

```c++
TEST(ut_pRvalue, pRvalue9)
{
    /// this 指针； 
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
}

```

运行结果:
//todo









### 纯右值示例10
枚举项

```c++
TEST(ut_pRvalue, pRvalue10)
{
    /// 枚举项; 
    {
        enum ncObjEnum
        {
            NC_OBJ_ENUM0,
            NC_OBJ_ENUM1
        };
        
        MK_PRINT_MSG("NC_OBJ_ENUM0          is %c-value", IsRight(NC_OBJ_ENUM0));
    }
}
```

运行结果:
//todo









### 纯右值示例11
Lambda 表达式，例如 [](int x){ return x * x; } 

```c++
TEST(ut_pRvalue, pRvalue11)
{
    /// Lambda 表达式，例如 [](int x){ return x * x; } 
    {
        
        MK_PRINT_MSG("[](int x){ return x * x; }  is %c-value", IsRight([](int x){ return x * x; }) );
        
        auto&& lam = [](int x){ return x * x; };
        bool isRValueRef = std::is_rvalue_reference<decltype(lam)>::value;
        MK_PRINT_MSG("isRValueRef = %d", isRValueRef);
    }
}
```

运行结果:
//todo









### 纯右值示例汇总






### 亡值示例1
函数调用或重载运算符表达式，其返回类型为右值引用，例如 std::move(x)

```c++
TEST(ut_xRvalue, xRvalue1)
{
    /// 函数调用或重载运算符表达式，其返回类型为右值引用，例如 std::move(x) ； 
    {
        int x = 100;
        MK_PRINT_MSG("std::move(x)          is %c-value", IsRight(std::move(x)));
    }
}
/*
源码路径:
ut_rvaluereference\valueType\ut_xRvalue.cpp
下同
*/
```

运行结果:
//todo










### 亡值示例2
a[n]，内建的下标表达式，其操作数之一是数组右值

```c++
TEST(ut_xRvalue, xRvalue2)
{
    /// a[n]，内建的下标表达式，其操作数之一是数组右值； 
    {
        using arrType = int[4];
        MK_PRINT_MSG("arrType{0,1,2,3}      is %c-value", IsRight(arrType{0,1,2,3}) );
        MK_PRINT_MSG("arrType{0,1,2,3}[2]   is %c-value", IsRight(arrType{0,1,2,3}[2]));
    }
}
```

vs2015运行结果:
//todo

gcc -4.8.5运行结果:
//todo

备注:
vs-2015环境下,   arrType{0,1,2,3}是左值, arrType{0,1,2,3}[2]是左值;
gcc-4.8.5环境下, arrType{0,1,2,3}是右值, arrType{0,1,2,3}[2]是左值;
测试结果与C++11标准规定的结果不符.



### 亡值示例3
a.m，对象成员表达式，其中 a 是右值且 m 是非引用类型的非静态数据成员；

```c++
TEST(ut_xRvalue, xRvalue3)
{    
    /// a.m，对象成员表达式，其中 a 是右值且 m 是非引用类型的非静态数据成员； 
    {
        struct ncObj
        {
            enum ncObjEnum{NC_OBJ_ENUM0,NC_OBJ_ENUM1};
            int n;
            int fun(){return 0;}
        };
        
        MK_PRINT_MSG("ncObj().n             is %c-value", IsRight(ncObj().n));///在vs2015测试, 这里是左值,g++测试是右值
    }
}
```

vs2015运行结果:
//todo

gcc -4.8.5运行结果:
//todo

备注:
VS-2015环境下,    ncObj().n 是左值;
gcc-4.8.5环境下,   ncObj().n 是右值; 
VS2015的测试结果与C++11标准规定的结果不符, 可能是vs2015的兼容性问题;



### 亡值示例4
a.*mp，对象的成员指针表达式，其中 a 为右值且 mp 为指向数据成员的指针；

```c++
TEST(ut_xRvalue, xRvalue4)
{   
    /// a.*mp，对象的成员指针表达式，其中 a 为右值且 mp 为指向数据成员的指针； 
    {
        struct ncObj
        {
            int n;
            int fun(){return 0;}
        };
        
        int ncObj::*pn = &ncObj::n;
        MK_PRINT_MSG("ncObj().*pn           is %c-value", IsRight(ncObj().*pn));///在vs2015测试, 这里是左值,g++测试是右值
    }
}
```

vs2015运行结果:
//todo

gcc -4.8.5运行结果:
//todo

备注:
VS-2015环境下,    ncObj().*pn 是左值;
gcc-4.8.5环境下,   ncObj().*pn 是右值; 
VS2015的测试结果与C++11标准规定的结果不符, 可能是vs2015的兼容性问题;




### 亡值示例5
a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）；

```c++
TEST(ut_xRvalue, xRvalue5)
{   
    /// a ? b : c ，某些 b 和 c 的三元条件表达式（细节见定义）； 
    {
        string a = "hello";
        string b = "world";
        MK_PRINT_MSG("a?b:c                 is %c-value", IsRight((true?std::move(a):std::move(b))));
    }
}
```

运行结果:
//todo



### 亡值示例6
转换为对象的右值引用类型的转型表达式，例如 static_cast<char&&>(x)

```c++
TEST(ut_xRvalue, xRvalue6)
{   
    /// 转换为对象的右值引用类型的转型表达式，例如 static_cast<char&&>(x)； 
    {
        char x = 'a';
        MK_PRINT_MSG("static_cast<char&&>(x)          is %c-value", IsRight(static_cast<char&&>(x)));
    }    
}
```

运行结果:
//todo




### 亡值示例-汇总
//todo




# 3.左值引用和右值引用

###值和引用是两个概念
//todo

示例:
右值       是表达式的值,   例如42;
右值引用,  是表达式的类型, 例如int&&

### 左右值与表达式类型没有直接关系，它们都是表达式的属性
右值引用类型的具名变量/对象是左值,  例如下面例子中的num
右值引用类型的匿名变量/对象是右值,  例如下面例子中的func_R()
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
ut_rvaluereference\referenceType\ut_RvalueRef.cpp
*/
```

运行结果:
//todo

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
ut_rvaluereference\referenceType\ut_RvalueRef.cpp
*/
```
总结:
//todo
常量左值引用是个“万能”的引用类型。它可以接受非常量左值、常量左值、右值对其进行初始化。
常量左值引用可以使用右值进行初始化，这时它可以像右值引用一样将右值的生命期延长(但所引用的右值在之后的生命周期内是只读);



# 4.如何使用右值引用



# 5.universal引用



# 6.完美转发


# 7.右值引用在STL中的使用举例

