
http://eric-gcm.iteye.com/blog/1616110

```cpp

                                                 第一篇
C++ 编程语言是一款功能强大的计算机应用语言。其能够支持很多程序设计风格。我们今天将会在这里为大家详细介绍一下有关C++反射机制的具体实现步骤，大家可以从中获得一些有帮助的内容。
在Java编程中，我们经常要用到反射，通过反射机制实现在配置文件中的灵活配置， 但在C++编程中，对这种方式步提供现有的支持，那么我们怎么才能在配置文件中配置想要调用的对象呢？ 
我们的思路是通过对象名称确定对象实例，把对象名和对象实例通过哈希表进行映射，那么我们就可以实现通过对象名称获取对象了。首先定义一个C++反射机制的结构：
 
Cpp代码 复制代码 收藏代码
struct ClassInfo    
{    
public:    
string Type;    
funCreateObject Fun;    
ClassInfo(string type, funCreateObject fun)    
{    
Type = type;    
Fun = fun;    
Register(this);    
}    
};   
 
其中Register这样定义
bool Register(ClassInfo* ci);
 
然后定义一个类，头文件如下：
Cpp代码 复制代码 收藏代码
class AFX_EXT_CLASS DynBase     
{    
public:    
DynBase();    
virtual ~DynBase();    
public:     
static bool Register(ClassInfo* classInfo);    
static DynBase* CreateObject(string type);    
private:     
static std::map<string,ClassInfo*> m_classInfoMap;    
};   
cpp文件如下：
Cpp代码 复制代码 收藏代码
std::map< string,ClassInfo*> DynBase::m_classInfoMap =   
std::map< string,ClassInfo*>();    
DynBase::DynBase()    
{    
}    
DynBase::~DynBase()    
{    
}    
bool DynBase::Register(ClassInfo* classInfo)    
{     
m_classInfoMap[classInfo->Type] = classInfo;     
return true;     
}    
DynBase* DynBase::CreateObject(string type)    
{    
if ( m_classInfoMap[type] != NULL )     
{     
return m_classInfoMap[type]->Fun();    
}    
return NULL;    
}   
 那么我们在C++反射机制的操作中实现映射的类只要继承于DynBase就可以了，比如由一个类CIndustryOperate
头文件如下：
Cpp代码 复制代码 收藏代码
class CIndustryOperate : public DynBase    
{    
public:    
CIndustryOperate();    
virtual ~CIndustryOperate();    
static DynBase* CreateObject(){return new CIndustryOperate();}
private:    
static ClassInfo* m_cInfo;    
};   
cpp文件如下：
Cpp代码 复制代码 收藏代码
ClassInfo* CIndustryOperate::m_cInfo = new ClassInfo  
("IndustryOperate",(funCreateObject)( CIndustryOperate::  
CreateObject));    
CIndustryOperate::CIndustryOperate()    
{    
}    
CIndustryOperate::~CIndustryOperate()    
{    
}   
 
                                                                        第二篇
       C++语言本身不支持反射机制，但C++对象总是要序列化的，序列化就是存储到磁盘上，将对象变成一定格式的二进制编码，然后要用的时候再将保存在磁盘上 的二进制编码转化成一个内存中的对象，这个过程中总是需要有一个指示来告诉编译器要生成什么样的对象，最简单的方式当然就是类名了，例如：将一个 ClassXXX对象存储到磁盘上，再从磁盘读取的时候让编译器根据“ClassXXX”名称来new一个对象。
但是问题出现了，C++语言本身不支持反射，也就是说不能通过如下方式生成一个对象：
ClassXXX object = new “ClassXXX”；

工厂方法
当然，这样的方法不行，那我们只有另辟蹊径。最简单的就是工厂方法了：
ClassXXX* object = FactoryCreate（“ClassXXX”）；
至于FactoryCreate的设计就很简单了，if的集合就可以了：
if(name = “ClassXXX”)
return new ClassXXX;
if(name = “ClassYYY”)
return new ClassYYY;

看起来不错，来个类名就可以生成对应的对象，功能上解决了根据类名生成对象的问题。
假 如以上所有的代码都有你一个人编写，那当然问题不大，但是假如有一天你的公司扩大了，这部分代码由两个不同的组A和B来维护，啊哈，问题来了，A组每添加 或者修改一个类，都要通知B组更新FactoryCreate函数，也就是说A组的任何关于类的修改，都需要B组来修改，但实际上B的修改不产生任何价 值，而且不胜其烦，永无止尽！！如果哪天来了一个新员工，由于对这个规定还不清楚，忘记了通知，那就完了：编译通不过！
一个公司内都会产生如此多的问题，更何况微软这样的大公司是面对全球的各种各样的客户，如果微软把这部分做进框架代码中，呵呵，那微软所有的人不用干其他事情了，每天处理来自全球的要求修改FactoryCreate函数的邮件和电话就够他们忙的了：）

回调工厂
既然此路不好走，那么我们再考虑其它方法吧，一个可选的方法是将FactoryCreate做成回调函数，框架提供注册接口RegisterFactoryCreate，框架函数如此实现：
typedef CObject* （*FactoryCreate_PTR）(String name);
RegisterFactoryCreate(FactoryCreate_PTR fc_ptr);
应用代码如此实现：
CObject* MyFactoryCreate（String name）;
RegisterFactoryCreate(MyFactoryCreate);
到这里一个框架和应用分离的反射机制基本实现了，你是否长吁一口气，然后准备泡杯咖啡，稍微放松一下呢？确实可以稍微休息一下了，毕竟我们完成了一件非常了不起的事情，让C++实现了反射。

但你只悠闲了一两天，麻烦事就来了。员工张三跑来向你抱怨“老大，李四注册的反射函数把我的覆盖了”！哦，你仔细一看，My god，这个注册函数只能注册一个反射函数，后注册的就把前面的覆盖了！
怎么办？总不可能又要求所有的类的反射函数都在一个工厂里实现吧，那这样就又回到了工厂方法中描述的时代了。
当然，聪明的你估计很快就能想出问题的解决方法，将RegisterFactoryCreate函数稍加修改就能满足要求了，新的实现如下：
RegisterFactoryCreate（FactoryCreate_PTR fc_ptr，String className）
然后要求每个类都单独写自己的FactoryCreate_PTR函数，类似如下方式：
static CObject* ClassXXX::CreateClassXXX (){
       return new ClassXXX;
};

static CObject* ClassYYY::CreateClassYYY(){
       return new ClassYYY;
};

到此为此终于大功告成，通过我们的智慧实现了C++的反射功能！一股自豪感油然升起：）

最后的杀手锏：宏
当你为自己的聪明才智而骄傲的时候，那边却有几个开发的兄弟在发出抱怨“唉，这么多相似的函数，看着都眼花，每个类都要写，烦死了”。
或者有一天，你要在每个类的CreateClass函数中增加一个其它功能（例如日志），那么开发的兄弟真的是要烦“死了”！！！

其实仔细一看，包括函数申明、函数定义、函数注册，每个类的代码除了类名外其它都是一模一样的，有没有简单的方法呢？
肯定是有的，这个方法就是宏了，按照如下方法定义宏：
#define DECLARE_CLASS_CREATE(class_name) \
static CObject* CreateClass## class_name ();

#define IMPL_CLASS_CREATE(class_name) \
static CObject* CreateClass## class_name (){  \
       return new class_name;             \
};

#define REG_CLASS_CREATE(class_name) \
RegisterFactoryCreate(class_name::CreateClass## class_name, #class_name);
注：##是连接符，将两个字符串连接起来，#是将class_name作为字符串处理。

大家可以比较一下，用了宏和不用宏是不是代码感觉完全不一样呢？而且那天需要增加一个简单的功能，只需要改宏定义就ok了，不要全文搜索所有相关函数，然后一个一个的重复添加。

到这里才真正是大功告成！！
 

```