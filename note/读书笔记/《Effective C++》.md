条款1：视C++为一个语言联邦：包含4个子语言：C、C with Classes、template C++、STL；

条款2：尽量以const,enum,inline替换#define；
          对于单纯变量，最好以const对象或者enums替换#defines；
          对于形似函数的宏，最好改用inline函数（或者template inline函数）替换#defines；

条款3：尽可能使用const；
          const char* p = xxx;     // const data，non-const point
          char* const p = xxx;     // const point, non-const data;
          const 出现在星号左边，表示被指物是常量，出现在右边，表示指针自身为常量；
          const char* p 和char const* p是一样的；
          const成员函数可以更改声明为mutable的成员变量；

条款4：确定对象被使用前已先被初始化；

条款5：了解C++默默编写并调用哪些函数；

条款6：若不想使用编译器自动生成的函数，就该明确拒绝；
          若想阻止对象拷贝，可将copy构造函数以及重载赋值操作符声明为private并且不予实现；或者继承一个Uncopyable的基类也是一种办法；

条款7：为多态基类声明virtual析构函数；
          很多人的心得是：只有当class内含有至少一个virtual函数，才为它声明virtual析构函数；
          纯虚析构函数和普通纯虚函数的区别在于，纯虚析构函数需要提供函数的实现，而一般纯虚函数不能有实现；
          这样的原因在于，纯虚析构函数最终需要被调用，以析构基类对象，虽然是抽象类没有实体。
          而如果不提供该析构函数的实现，将使得在析构过程中，析构无法完成而导致析构异常的问题；
          
条款8：别让异常逃离析构函数；
          别让析构函数抛出异常，有2个办法：一种是析构时发现异常就调用std::abort()函数结束程序；另一种是吞下异常；
          当然最好的策略是重新设计接口，将会抛出异常的操作提供一个单独函数（例如close（））给客户代码调用，由客户层代码觉得异常的处理；

条款9：绝不在构造和析构过程中调用virtual函数；
          例如：基类构造函数调用其virtual函数fun（），则当继承类对象创建时，先调用base class的构造函数；
          在base class构造期间，调用的fun（）函数不是派生类的fun（）函数。。。
          对象在derived class构造函数开始执行前不会成为一个derived class对象；

条款10：令operator=返回一个reference to *this；

条款11：在operator=中处理“自我赋值”
          可以在operator=函数首行做一个“证同测试”
          if(this == &rhs) 
               return *this;

条款12：复制对象时勿忘其每一个成分；
          copying函数应该确保复制对象内的所有成员变量及所有base class成分；
          不要尝试以某个copying函数实现另一个copying函数；应该将共同功能放进第三个函数中，并由2个copying函数共同调用；

条款13：以对象管理资源；
         
条款14：在资源管理类中小心copying 行为；















