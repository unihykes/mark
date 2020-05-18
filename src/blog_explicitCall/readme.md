# 显式指定函数模板参数为引用类型﻿
>转载请注明出处: https://blog.csdn.net/WOW542621126/article/details/80474681

摘要:<br>

* 某些场景下,显式指定函数模板参数为引用类型, 触发引用折叠, 会有一些反直觉的情况发生,特此记录一下:


# 例1:const T&

```cpp
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

template<typename T>
void funcCall_A(const T& param)
{
    param += 10;
    
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(ut_explicitCall, funcCall_A)
{
    int n = 1;
    
    funcCall_A<int&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
    
    funcCall_A<int&&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
}

```
### 执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528105550366?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



# 例2:const T&&
```cpp
template<typename T>
void funcCall_B(const T&& param)
{
    param += 10;
    
    MK_PRINT_MSG("T is %s, type of param is %s", 
        type_id_with_cvr<T>().pretty_name().c_str(),
        type_id_with_cvr<decltype(param)>().pretty_name().c_str());
}

TEST(ut_explicitCall, funcCall_B)
{
    int n = 5;
    
    funcCall_B<int&>(n);//const被丢弃
    MK_PRINT_MSG("n = %d", n);
    
    funcCall_B<int&&>(100);//const被丢弃, 修改了一个临时对象(右值)
}
```

### 执行结果:<br>
![这里写图片描述](https://img-blog.csdn.net/20180528105601267?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dPVzU0MjYyMTEyNg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
