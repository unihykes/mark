XPCOM是在运时加载？

接口和契约式编程(Interface and Programming by Contract)
一个接口就是组件和客户端之间的契约。 没有代码强迫执行这个契约，但是忽略他们可能是致命的。在组件化编程中，
 组件应该确保它提供的接口是不可变的(他们会在不同的版本里针对相同的方法提供相同的访问方式)建立一个契约。在这
 方面，基于接口的编程通常被称为契约是编程


在基于接口和组件的编程中有两个最基本的问题：组件的生命周期(也叫做对象所有权)和接口查询，或者说能够在运行时获得组件支持的接口。


我们往往要面对一些真实的问题，例如，一个客户在使用完接口后，忘记了递减引用计数。 当这种情况发生时，接口就永远不会被释放，导致内存泄漏。



在C++里，你可以使用dynamic_cast<>，如果Shape对象不能转换为Circle，他会抛出异常。 但是开启exceptions和RTTI会带来性能上问题，并且还需要考虑在不同平台上的兼容性，因此XPCOM没有这么做。


XPCOM不直接支持C++ exceptions。 在组件内产生的异常必须在传递到接口边界之前全部由组件自己处理掉。在XPCOM里所有的接口方法应该返回一个nsresult值，记录错误代码。 有错误代码返回，表示XPCOM处理出现异常。

 替代C++的RTTI，XPCOM使用了特别的QueryInterface方法，他会把对象转换为相应的接口，前提是支持这个接口。

 每一个接口需要被分配一个唯一的标识符（可以通过uuidgen工具生成）。 这个标识符是唯一的，128-bit的数字。 在接口上下文中进行使用，他通常被叫做IID。

 当一个客户想发现对象支持的接口时，客户把接口的IID，传递给对象的QueryInterface方法。 如果对象支持请求的接口，它会返回指向接口的指针，并递增相应的引用计数。 不支持，则返回错误码。


class nsISupports {
public:
long QueryInterface(const nsIID & uuid,
void **result) = 0;
long AddRef(void) = 0;
long Release(void) = 0;
};

QueryInterface方法的第一个参数nsIID是对IID的一个封装，它包含了3个方法，Equals，Parse和ToString.Equals使用最多，因为他在接口的查询过程中，用于比较两个接口。

 当你实现nsISupports类时，你必须要确保QueryInterface返回一个有效值。QueryInterface因该支持组件支持的所有接口。

 在实现QueryInterface函数时，IID参数会被检查。 如果匹配，则返回对象的指针（转换为void）,并增加引用计数。 不匹配，类就返回一个错误码，指针为NULL。

 在上面的例子中，使用C-style转换就可以了。 


























