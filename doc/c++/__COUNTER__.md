__COUNTER__ 是一个计数器，

会从 0 开始计数，然后每次调用加 1，即：

__COUNTER__  // 0
__COUNTER__  // 1
__COUNTER__  // 2

```
如何实现呢？
通常配合 ## 使用，用于构建唯一的标识符(identifiers)。
做法其实很简单，把任意一个标识符与 COUNTER 合并就可以了。

最普遍的做法是，加一个中间层。
合并用的宏：
#define merge_body(a, b) a ## b //合并用的主体
因為 ## 的特性 ( 阻止另一个宏的展开 )，需要中间层：
#define merge(a, b) merge_body(a, b) //中间层
把标识符与 __COUNTER__合并：
#define uniqueVarName(name) merge(name, __COUNTER__)
uniqueVarName() 就可以建立唯一的变数名称了。
Apollo就是使用了这种方法。

第二种方法，使用延迟展开的左括弧：
#define leftBracket (
使用这个的话，就可以把中间层去掉，然后 uniqueVarName() 变成这样：
#define uniqueVarName(name) merge_body leftBracket name, __COUNTER__)

```