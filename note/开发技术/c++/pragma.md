

#msvc/gcc:中用#pragma指令关闭特定警告(warning)
http://blog.csdn.net/10km/article/details/51726778
```cpp




msvc下的用法是这样的

#ifdef _MSC_VER
// 关闭编译CImg.h时产生的警告
#pragma  warning( push ) 
#pragma  warning( disable: 4267 4319 )
#endif
#include "CImg.h"
#ifdef _MSC_VER
#pragma  warning(  pop  ) 
#endif123456789

gcc下的用法是这样的：



#ifdef __GNUC__
// 关闭 using  _Base::_Base; 这行代码产生的警告
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winherited-variadic-ctor"
#endif
.....
namespace cimg_library {
template<typename T>
class CImgWrapper:public CImg<T> {
public:
    using   _Base =CImg<T>;
    using  _Base::_Base; // 继承基类构造函数
    ......
}
} /* namespace cimg_library */
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif




有时候加了仍然没用；
此时可以修改CMakeLists：
SET(CMAKE_CXX_FLAGS "-Wno-literal-suffix ${CMAKE_CXX_FLAGS}")



```