---
标题: 设计模式分享
作者: unihykes
日期: 2021/7/16
markdown:
  image_dir: ./assets
  path: readme.md
  ignore_from_front_matter: true
  absolute_image_path: false
---

﻿[toc]

# 设计模式是什么?
![ ](./assets/定义.png)


# 设计模式可以做什么?
## 关于复杂度
合理使用设计模式, 可以巧妙的降低代码复杂度

![ ](./assets/复杂度.png)

备注:
    
    人们常常会混淆模式和算法，因为两者在概念上都是已知特定问题的典型解决方案。
    但算法总是明确定义达成特定目标所需的一系列步骤，而模式则是对解决方案的更高层次描述。 
    同一模式在两个不同程序中的实现代码可能会不一样。


## 关于美学
合理使用设计模式, 让代码从无序变为有序, 提升代码美感

![无序](./assets/无序.png)
![有序](./assets/有序.jpg)



# 代码是怎么变复杂的?
![ ](./assets/复杂形成.png)


# 代码复杂性的表现形式?
```plantuml

package 依赖 {
    class "A" as A
    class "B" as B
    A ..> B


    package 实现 {
        class "A" as I
        interface "B" as J
        J ^.. I
        
        package 继承 {
            class "A" as K
            class "B" as L
            L ^-- K
        }
    }
    
    package 关联 {
        class "A" as C
        class "B" as D
        C --> D
        
        package 聚合 {
            class "A" as E
            class "B" as F
            E o--> F
            
            package 组合 {
                class "A" as G
                class "B" as H
                G *--> H
            }
        }
    }

}

```

• 依赖：对类 B 进行修改会影响到类 A 。 
• 关联：对象 A 知道对象 B。类 A 依赖于类 B。 
• 聚合：对象 A 知道对象 B 且由 B 构成。类 A 依赖于类 B。
• 组合：对象 A 知道对象 B 且由 B 构成而且管理着 B 的生命周 期。类 A 依赖于类 B。 
• 实现：类 A 定义的方法由接口 B 声明。对象 A 可被视为对象 B。类 A 依赖于类 B。 
• 继承：类 A 继承类 B 的接口和实现， 但是可以对其进行扩 展。对象 A 可被视为对象 B。类 A 依赖于类 B。


# 比设计模式更重要的是?
```plantuml
!include %getenv("C4_HEADER")\c4_header.puml

Person(程序员,程序员, "")
System(设计模式, "设计模式", "[GRASP]\n[GoF]\n[Actor]\n[MVC]\n[IOC]\n[Producer-Consumer]\n[...]")
Container(设计原则, "设计原则", "[]", "[SOLID]\n[GRASP]\n[DRY]\n[YAGNI]\n[Three rules]\n[SOC]\n[...]")
Container(编程范式, "编程范式", "OOP", "[对象]: 数据 行为 抽象\n [特性]:  封装 继承 多态\n[关系]: 依赖 聚合 组合\n[...]: ...")
Component(设计思想, "设计思想", "玄学")

Rel(程序员, 设计模式, "复用一些模式")
Rel(程序员, 编程范式, " ")
Rel(设计模式, 编程范式, "利用一些语言特性")
Rel(设计模式, 设计原则, "满足一些设计原则")
Rel(编程范式, 设计思想, " ")
Rel(设计原则, 设计思想, " ")
```
- 比模式更重要的是:原则!
  设计模式用来指导你如何使用一些设计原则来解决各种问题


# 一些设计原则
![](./assets/设计原则.png)
## SOLID原则
####  单一职责原则
(Single Responsibility Principle - SRP)
一个类只有一个引起变化的原因。
如果一个类有多个引起变化的原因，当其中一个变化时会影响到其他代码。这样代码的内聚性不好，会导致维护性变差，复用性降低。
用于指导对类的设计，只有一个引起变化的原因，单一职责，设计出高内聚的类（或方法等元素）。

#### 开放封闭原则
(Open Close Principle)
对扩展开放，对修改关闭。在程序需要进行拓展的时候，不能去修改原有的代码，实现一个热插拔的效果。
简言之，是为了使程序的扩展性好，易于维护和升级。想要达到这样的效果，我们需要使用接口和抽象类。

#### 里氏代换原则
(Liskov Substitution Principle)
里氏代换原则是面向对象设计的基本原则之一。
里氏代换原则中说，任何基类可以出现的地方，子类一定可以出现。
LSP 是继承复用的基石，只有当派生类可以替换掉基类，且软件单位的功能不受到影响时，基类才能真正被复用，而派生类也能够在基类的基础上增加新的行为。
里氏代换原则是对开闭原则的补充。实现开闭原则的关键步骤就是抽象化，而基类与子类的继承关系就是抽象化的具体实现，所以里氏代换原则是对实现抽象化的具体步骤的规范。

#### 接口隔离原则
(Interface Segregation Principle)
这个原则的意思是：使用多个隔离的接口，比使用单个接口要好。
它还有另外一个意思是：降低类之间的耦合度。
由此可见，其实设计模式就是从大型软件架构出发、便于升级和维护的软件设计思想，它强调降低依赖，降低耦合。


#### 依赖倒转原则
(Dependence Inversion Principle)
这个原则是开闭原则的基础，具体内容：针对对接口编程，依赖于抽象而不依赖于具体。
```plantuml
class 上层类
class 下层类A
class 下层类B
上层类 --> 下层类A
上层类 --> 下层类B
```

```plantuml
class 上层类
class 下层类A
class 下层类B
interface 抽象接口

上层类 -r-> 抽象接口
抽象接口 ^.. 下层类A
抽象接口 ^.. 下层类B
```

## GRASP原则
https://www.cnblogs.com/itfly8/p/14035074.html
https://blog.csdn.net/wfeii/article/details/80183718
https://blog.csdn.net/u013249965/article/details/51779634

## 代码抽象三原则
#### DRY原则
（Don't repeat yourself）
意思是：不要重复自己。它的涵义是，系统的每一个功能都应该有唯一的实现。也就是说，如果多次遇到相同的问题，就需要抽象出一个通用的解决方案，不要重复开发相同的功能。

用代码举例：如果两个地方需要发送短信的功能，第一个功能是发送提醒短信，第二个是发送验证码短信。则需要把发送短信的公用代码进行提炼。

#### YAGNI原则
（ You aren't gonna need it）
意思是：你不会需要它。出自极限编程的原则，指除了核心功能外，其它功能一概不要部署。背后的指导思想是尽快的让代码运行起来。简单理解是尽量避免不必要的代码，少就是多。比如：过多的日志打印，过多逻辑检查，过多的异常处理等，如果能简化则简化。

####  三次原则
Rule Of Three
Rule of three 称为"三次原则"，指的是当某个功能第三次出现时，才进行"抽象化"。它的含义是：当第一次用到某个功能时，写一个特定的解决方法；第二次又用到的时候，拷贝上一次的代码；第三次出现的时候，才着手"抽象化"，写出通用的解决方法。

三原则之间的关系
DRY强调对通用问题的抽象，
YAGNI强调快速和简单。
Rule Of Three相当于对前两个原则做了一个折衷，提出了应用原则的度量。
三原则的折中，有以下几个好处。
（1）省事，避免过度设计：如果只有一个地方用，就没必要过度抽象，避免过度设计。
（2）容易发现模式：问题出现的场景多，容易找到通用的部分，方便进行抽象，进而找到模式。



## 其他原则
#### 最少知识原则
(Least Knowledge Principle - LKP)
最少知识原则又叫迪米特法则(Demeter Principle)。
一个实体应当尽量少的与其他实体之间发生相互作用，使得系统功能模块相对独立。也就是说一个软件实体应当尽可能少的与其他实体发生相互作用。当一个模块修改时，尽量少的影响其他的模块，容易扩展，这是对软件实体之间通信的限制，要求限制软件实体之间通信的宽度和深度。

#### 关注点分离原则
Separation of Concerns - SOC) 
将一个复杂的问题分离为多个简单的问题,然后逐个解决这些简单的问题,那么这个复杂的问题就解决了

#### 合成复用原则 
(Composite Reuse Principle)
也有翻译为:组合复用原则,聚合复用原则
合成复用原则是指：尽量使用合成/聚合的方式，而不是使用继承。
组合/聚合复用原则（Composition/Aggregation Reuse Principle - CARP）
在设计中，优先考虑使用组合，而不是继承。继承容易产生副作用，组合具有更好的灵活性。如：代理模式、装饰模式、适配器模式等。

#### 无环依赖原则
（Acyclic Dependencies Principle - ADP）
当 A 模块依赖于 B 模块，B 模块依赖于 C 模块，C 依赖于 A 模块，此时将出现循环依赖。
在设计中应该避免这个问题，可通过引入“中介者模式”解决该问题。

#### 共同封装原则
（Common Closure Principle - CCP）
将易变的类放在同一个包里，将变化隔离出来。该原则是“开放-封闭原则”的延伸。

#### 共同重用原则
（Common Reuse Principle - CRP）
如果重用了包中的一个类，那么也就相当于重用了包中的所有类，我们要尽可能减小包的大小。

#### 好莱坞原则
（Hollywood Principle - HP）
好莱坞明星的经纪人一般都很忙，他们不想被打扰，往往会说：Don't call me, I'll call you. 
翻译为：不要联系我，我会联系你。对应于软件设计而言，最著名的就是“控制反转”（或称为“依赖注入”），
我们不需要在代码中主动的创建对象，而是由容器帮我们来创建并管理这些对象。

#### 保持简单与傻瓜
（Keep it simple and stupid - KISS）
不要让系统变得复杂，界面简洁，功能实用，操作方便，要让它足够的简单，足够的傻瓜。

#### 惯例优于配置
（Convention over Configuration - COC）
尽量让惯例来减少配置，这样才能提高开发效率，尽量做到“零配置”。很多开发框架都是这样做的。

#### 命令查询分离
（Command Query Separation - CQS）
在定义接口时，要做到哪些是命令，哪些是查询，要将它们分离，而不要揉到一起。在读写分离或分布式系统中应用较多。

#### 契约式设计
（Design by Contract - DBC）
模块或系统之间的交互，都是基于契约（接口或抽象）的，而不要依赖于具体实现。该原则建议我们要面向契约编程。

# 原则之外的原则
- 遵守设计原则也可能带来额外的复杂性
- 盲目遵守这些原则可能会弊大于利
- 很少有软件能够同时应用所有设计原则
- 设计原则不是成普世教条, 要时刻从实用的角度来权衡


# 设计模式分类
广义的设计模式有成千上万种,例如”GoF”, GRASP, MVC, IOC, Actor, 生产者-消费者, 消息队列, 共享内存, 对象池 等等等等……

而在程序员中最广为流传的当属 GoF设计模式:
《Design Patterns: Elements of Reusable Object-Oriented Software》
![](./assets/GoF分类.png)

# 实践 : 设计模式使用场景示例
- 需求 :
    实现一个基于KV数据库的读写缓存
    
- 功能细节:
    支持增删查改
    支持缓存超时汰换/冷热汰换
    支持查询缓存运行时状态
    支持关键操作记录日志
    等等等…
    
```plantuml
!include %getenv("C4_HEADER")\c4_header.puml

Person_Ext(put, "put")
Person_Ext(get, "get")
Person_Ext(list, "list")
Person_Ext(delete, "delete")
SystemDb_Ext(db,"kvdb", "数据库")
Container(cache, "cache", "[]") {
    Component(schedule, "schedule", "[]")
    Component(write_cache, "write cache", "写缓存")
    Component(read_cache, "read cache", "读缓存")
}
Rel_(put, schedule, " ", ..>)
Rel_(get, schedule, " ", <..)
Rel_(list, schedule, " ", <..)
Rel_(delete, schedule, " ", ..>)

Rel_(schedule, read_cache, " ", ..>)
Rel_(schedule, write_cache, " ", ..>)
Rel_(read_cache, db, " ", +..+)
Rel_(write_cache, db, " ", +..+)

```
---
## v1.0 快速开发
我们很快设计了一套代码结构,并实现了它;

```plantuml
class Cache #8099BF {
    - _pKvApi;          //用来执行数据库相关操作
    - _pReplaceThread;  //用来异步执行缓存汰换
    - _pIndexTable;     //用来管理缓存的索引表
    - _pContainer;      //用来管理缓存的数据
    - _pState;          //用来记录缓存的状态
    - _pLog;            //用来记录日志
    
    --业务操作接口--
    + Put(...);
    + Get(...);
    + List(...);
    + Delete(...);
    --缓存汰换线程--
    -ReplaceTreadStart(...);
    -ReplaceTreadStop(...);
    --数据上传线程--
    -UploadThreadStart(...);
    -UploadThreadStop();
    --数据库管理--
    -KvDbConnect(...);
    -KvDisconnect(...);
    --索引表管理(**key**)--
    -IndexInsert(...);
    -IndexDelete(...);
    -IndexFind(...);
    --业务数据管理(**value**)--
    -DataPush(...);
    -DataDelete(...);
    -DataGet(...);
    --运行状态管理--
    + GetState(...);
    - SetState();
    --日志管理--
    - OpenLogFile(...);
    - writeLog(...);
    - CloseLogFile(...);
}
```

```plantuml
object app {
    上层应用程序
}

package CachePackage {
    class Cache  #8099BF {
        缓存模块的核心类
    }

    class CacheState{
        管理缓存模块的一些状态
    }

    class KvApi {
        Kv数据库的操作接口
    }

    class ReplaceThread {
        缓存汰换线程
    }
    class UploadThread {
        数据上传线程
    }
    class KvIndexTable {
        管理缓存中的索引表
    }

    class DataContainer {
        管理缓存中的业务数据
    }

    class Log {
        日志管理
    }

    database File{
    }
    
    app.>Cache
    
    Cache *--> CacheState
    Cache *--> KvIndexTable
    Cache *..> Log
    Cache *--> DataContainer
    Cache *--> KvApi
    Cache *--> ReplaceThread
    Cache *--> UploadThread

    ReplaceThread-->CacheState
    ReplaceThread-->KvIndexTable
    ReplaceThread-->DataContainer
    ReplaceThread ..> Log
    
    UploadThread-->CacheState
    UploadThread-->KvIndexTable
    UploadThread-->DataContainer
    UploadThread..>Log
    
    KvIndexTable-->KvApi
    KvIndexTable-->CacheState
    KvIndexTable ..> Log

    DataContainer-->KvApi
    DataContainer-->CacheState
    DataContainer ..> Log
    CacheState..>Log
    Log -->File
    KvApi..>Log
}

database Kvdb{
}
KvApi+--+Kvdb
```


    然而几个月后,产品经理过来,抛出几个问题:
    问题1:
        客户A希望操作日志用UI呈现
    问题2:
        客户B替换为mysql数据库了
        客户C需要额外支持oracle数据库
    问题3:
        客户D反馈我们的汰换策略在某些场景下命中率过低
    问题4:
        客户E希望用SSD缓存池替代内存缓存池
    问题5:
        客户F反馈我们的缓存系统在多用户并发访问时太慢
    问题N:
        ……

    程序员: 好的,  我重构, 您请稍等几个月……

---

## v1.1 解耦Log

    前提:
    1.Log的记录和呈现, 与缓存系统关系不大;
    2. Log的入口职责单一;
    3. 缓存系统只需要一个日志管理实例;
    4. 日志需要能用UI呈现;




    解决方案:
    使用单例模式创建Log实例, 
         与缓存系统解耦;

    2. 使用观察者模式通知日志更新到数据库,
        实现UI呈现效果,
        同时兼容本地日志更新;


```plantuml
object app {
    上层应用程序
}
package CachePackage {
    class Cache {
        缓存模块的核心类
    }

    class CacheState{
        管理缓存模块的一些状态
    }

    class KvApi {
        Kv数据库的操作接口
    }

    class ReplaceThread {
        缓存汰换线程
    }
    class UploadThread {
        数据上传线程
    }
    class KvIndexTable {
        管理缓存中的索引表
    }

    class DataContainer {
        管理缓存中的业务数据
    }

    app.>Cache
    
    Cache -> CacheState
    Cache --> KvIndexTable
    Cache --> DataContainer
    Cache --> KvApi
    Cache --> ReplaceThread
    Cache --> UploadThread
    
    ReplaceThread-->CacheState
    ReplaceThread-->KvIndexTable
    ReplaceThread-->DataContainer

    UploadThread-->CacheState
    UploadThread-->KvIndexTable
    UploadThread-->DataContainer
    
    KvIndexTable-->KvApi
    KvIndexTable-->CacheState

    DataContainer-->KvApi
    DataContainer-->CacheState
    
    
    object LogInstance

}
database Kvdb{
}

package LogPackage #8099BF {
    class Log {
        + GetInstance();
        + DelInstance();
        + Write();
        
        --日志发布--
        - Attach();
        - Detach();
        - Notify();
    }
    
    interface Listener {
        --记录日志--
        + Update();
    }
    
    class FileLogListener {
        --记录本地日志--
        + Update();
    }
    
    class DbLogListener {
        --记录远程日志--
        + Update();
    }
    
    database local_file {
    }
    interface dbclient
    
    LogInstance..>Log
    Log ..> Listener
    
    Listener ^.. FileLogListener
    Listener ^.. DbLogListener
    DbLogListener..>dbclient
    FileLogListener..>local_file
}

database remote_db {
}

Cloud console_service {
    Rectangle UI{
    }
}

KvApi+--+Kvdb
dbclient+..+ remote_db
console_service ..> remote_db

```

---






## v1.2 解耦State

    前提:
    1.之前的CacheState类管理的内容太多且杂, 
       有线程状态, 索引表状态,缓存数据状态等;
    2.当发生状态切换时,需要考虑的逻辑分支过多;
    3.查询状态是只读操作, 不会对缓存系统产生影响


    解决方案:
    优化状态模式,将大状态机拆分为多个小状态机;
         使不同类的状态间解耦;
    2. 可使用工厂方法来管理不同层次对象的状态;
        工厂方法也可用于管理已有对象;
    3. 可使用访问者模式来查询不同层次类对象的运行时状态; 


```plantuml
object app {
    上层应用程序
}
namespace StatePackage #8099BF {
    interface IStateFactory {
        + GetState(...);
    }
    
    class StateFactory {
        + GetState(...);
        + Register(...);
        + Unregister(...);
    }
    
    interface IState {
        + Accept (IStateVisitor*)
    }
    
    interface IStateVisitor {
        --运行状态查询--
        + GetCacheState(...);
        + GetReplaceState(...);
        + GetIndexState(...);
        + GetDataContainerState(...);
        + GetKvdbState(...);
    }
    class StateVisitor
    
    IStateFactory ^..StateFactory
    StateFactory ..> IState
    StateFactory ..> StateVisitor
    IStateVisitor ^.. StateVisitor
    IState ..>IStateVisitor
    
}
app ..> StatePackage.IStateFactory

package CachePackage {
    class Cache {
        缓存模块的核心类
    }
    class KvApi {
        Kv数据库的操作接口
    }

    class ReplaceThread {
        缓存汰换线程
    }
    class UploadThread {
        数据上传线程
    }
    class KvIndexTable {
        管理缓存中的索引表
    }

    class DataContainer {
        管理缓存中的业务数据
    }
    
    circle CacheState  #8099BF
    circle ReplaceState  #8099BF
    circle UploadState  #8099BF
    circle IndexState  #8099BF
    circle DataContainerState  #8099BF
    circle KvdbState  #8099BF
    
    app ..> Cache
    Cache ..> CacheState
    Cache --> KvIndexTable
    Cache --> DataContainer
    Cache --> KvApi
    Cache --> ReplaceThread
    Cache --> UploadThread
    
    ReplaceThread..>ReplaceState
    ReplaceThread-->KvIndexTable
    ReplaceThread-->DataContainer
    
    UploadThread..>UploadState
    UploadThread-->KvIndexTable
    UploadThread-->DataContainer
    
    KvIndexTable..>IndexState
    KvIndexTable-->KvApi
    
    DataContainer..>DataContainerState
    DataContainer-->KvApi
    KvApi..>KvdbState
}
database Kvdb{
}

package LogPackage as "日志" {
}
KvApi+--+Kvdb
CachePackage..>LogPackage

```

```plantuml
package StatePackage #8099BF {
    interface IState
}
package CachePackage {
    circle CacheState  #8099BF
    circle ReplaceState  #8099BF
    circle UploadState  #8099BF
    circle IndexState  #8099BF
    circle DataContainerState  #8099BF
    circle KvdbState  #8099BF
    
    IState ^.. CacheState
    IState ^.. ReplaceState
    IState ^.. UploadState
    IState ^.. IndexState
    IState ^.. DataContainerState
    IState ^.. KvdbState
}
```







## v1.3 兼容多种数据库

    前提:
    1.之前的索引表直接引用了原生key数据结构;
    2.之前的数据表直接引用了原生value数据结构;
    3.不同数据库的访问方式不同;



    解决方案:
    抽象出一种通用的索引数据结构,
          支持序列化和反序列化;
    2.  抽象出一种通用的业务数据结构;
         支持序列化和反序列化;
    3.  使用适配器模式兼容多种数据库的API; 


```plantuml
object app {
    上层应用程序
}
package CachePackage {
    class Cache {
        缓存模块的核心类
    }
    
    class ReplaceThread {
        缓存汰换线程
    }
    class UploadThread {
        数据上传线程
    }
    class IndexTable {
        管理缓存中的索引表
    }

    class DataContainer {
        管理缓存中的业务数据
    }
    
    interface IIndex
    interface IData
    
    app ..> Cache
    Cache --> IndexTable
    Cache --> DataContainer
    
    Cache --> ReplaceThread
    Cache --> UploadThread
    
    ReplaceThread-->IndexTable
    ReplaceThread-->DataContainer
    
    UploadThread-->IndexTable
    UploadThread-->DataContainer
    
    IndexTable-->IIndex
    DataContainer-->IData
    

}
package DBPackage #8099BF {
    interface IDbApiAdapter {
        数据库的操作接口
    }
    interface __IIndex as "IIndex"
    interface __IData as "IData"
    
    class KvApiAdapter
    class mysqlApiAdapter
    class oracleApiAdapter
    
    database Kvdb{
    }
    database mysql{
    }
    database oracle{
    }
    interface KvApi
    interface mysqlApi
    interface oracleApi
    
    Cache ..> IDbApiAdapter
    __IIndex <.. IDbApiAdapter
    __IData <.. IDbApiAdapter
    IDbApiAdapter ^.. KvApiAdapter
    IDbApiAdapter ^.. mysqlApiAdapter
    IDbApiAdapter ^.. oracleApiAdapter
    KvApiAdapter ..>KvApi
    mysqlApiAdapter ..> mysqlApi
    oracleApiAdapter ..> oracleApi 
    
    KvApi+..+Kvdb
    mysqlApi+..+mysql
    oracleApi+..+oracle

}
package LogPackage as "日志" {
}
package StatePackage as "状态机" {
}
StatePackage<..app
LogPackage <.. CachePackage
```



## v1.4 扩展缓存汰换策略

    前提:
    1.之前的读写缓存共用同一个Cache类;
    2.读缓存的汰换策略默认只有1种;
      某些场景下不适用;



    解决方案:
    对读写缓存进行分离;
         由于读写缓存内数据可能相互影响,
         因此可使用中介者模式统一调度,
         来解决数据一致性问题;
    2. 使用策略模式将算法抽象为汰换策略;
        另一个独立的模块负责实现各种策略;


```plantuml
object app {
    上层应用程序
}

class Schedule {
    缓存模块的核心类
}

package ReplaceStrategy as "汰换策略package" #8099BF {
    interface IReplaceStrategy
    class LRU {
        汰换策略
    }
    class LRU_K {
        汰换策略
    }
    class 2Q {
        汰换策略
    }
    class LIRS {
        汰换策略
    }
    class ARC {
        汰换策略
    }
    class LFU {
        汰换策略
    }
    class LRFU{
        汰换策略
    }
    class MRU{
        汰换策略
    }
    class FIFO{
        汰换策略
    }
    class Clock{
        汰换策略
    }
    class Random{
        汰换策略
    }
    IReplaceStrategy ^.. LRU
    IReplaceStrategy ^.. LRU_K
    IReplaceStrategy ^.. 2Q
    IReplaceStrategy ^.. LIRS
    IReplaceStrategy ^.. ARC
    IReplaceStrategy ^.. LFU
    IReplaceStrategy ^.. LRFU
    IReplaceStrategy ^.. MRU
    IReplaceStrategy ^.. FIFO
    IReplaceStrategy ^.. Clock
    IReplaceStrategy ^.. Random
    
}

package ReadPackage #8099BF{
    class ReadSchedule
    interface IDbApiAdapter1 as "IDbApiAdapter"
    class ReadIndexTable {
        索引表
    }
    class ReadDataPool  {
        业务数据
    }
    class ReplaceSchedule {
    }
    
    class ReplaceThread {
        缓存汰换线程
        + SetStrategy(..);//设置策略
    }
    ReadSchedule ..> IDbApiAdapter1
    ReadSchedule ..> ReadIndexTable
    ReadSchedule ..> ReadDataPool
    ReplaceThread ..> ReplaceSchedule
    ReplaceThread..>ReadIndexTable
    ReplaceThread..>ReadDataPool
    ReplaceSchedule ..> IReplaceStrategy
}

package WritePackage #8099BF{
    interface IDbApiAdapter2 as "IDbApiAdapter"
    class WriteSchedule
    class WriteIndexTable {
        索引表
    }
    class WriteDataPool {
        业务数据
    }
    class UploadThread {
        数据上传线程
    }
    WriteSchedule ..> WriteIndexTable
    WriteSchedule ..> WriteDataPool
    UploadThread..>WriteIndexTable
    UploadThread..>WriteDataPool
    UploadThread ..>IDbApiAdapter2
}


app ..> Schedule
Schedule..>ReadSchedule
Schedule..>WriteSchedule

```


## v1.5 扩展缓存池类型

    前提:
    1.之前的读写缓存默认仅使用内存;
    某些场景下不适用;


    解决方案:
    抽象出索引表接口
    抽象出数据池接口
    抽象出数据中心
    用内存模式和ssd模式各实现一套缓存池,在不同场景下可灵活切换;
    在构造数据中心时,内存模式和ssd模式接口相似但不完全相同, 
    可使用生成器模式降低构造差异性;


```plantuml
object app {
    上层应用程序
}

class Schedule {
    缓存模块的核心类
}

package ReadPackage{
    class ReadSchedule
    class ReplaceThread
    
    package ReadDataCenter{
        interface IReadIndexTable {
            索引表接口
        }
        
        interface IReadDataPool #8099BF{
            业务数据接口
        }
        
        class ReadIndexTable {
            索引表
        }
        class ReadMemoryPool #8099BF {
            内存缓存,支持随机读写
        }
        class ReadSSDPool #8099BF {
            ssd环形队列缓存,支持顺序追加写
        }
        
        IReadDataPool ^.. ReadMemoryPool
        IReadDataPool ^.. ReadSSDPool
        IReadIndexTable ^.. ReadIndexTable
    }
    
    ReadSchedule ..> ReadDataCenter
    ReplaceThread..>ReadDataCenter
}

package WritePackage{
    class WriteSchedule
    class UploadThread 
    
    package WriteDataCenter{
        interface IWriteIndexTable {
            索引表接口
        }
        
        interface IWriteDataPool #8099BF {
            暂存数据接口
        }
        class WriteIndexTable {
            索引表
        }
        class WriteMemoryPool  #8099BF {
            内存缓存,直接随机读写
        }
        class WriteSSDPool  #8099BF {
            ssd环形队列缓存,支持顺序追加写
        }
        IWriteIndexTable ^.. WriteIndexTable
        IWriteDataPool ^.. WriteMemoryPool
        IWriteDataPool ^.. WriteSSDPool
        
    }
    
    WriteSchedule ..> WriteDataCenter
    UploadThread..>WriteDataCenter
}


app ..> Schedule
Schedule..>ReadSchedule
Schedule..>WritePackage


```





## v1.6 命令队列

    前提:
    1.之前读写缓存接口单一;
    2.读缓存和写缓存之间需要调度解决冲突;
    3.多并发场景下无法设置优先级;
    4.多并发场景下同步调用的方式会阻塞;


    解决方案:
    引入命令模式, 实现为命令队列,异步执行操作;
    可实现重复命令折叠,提升性能;
    可使用优先级队列,为高优先级操作让路;
    可缓存多个可复用命令提升性能;
    不同命令中可使用多条数据库通道,提升性能;


```plantuml
object app1 #228B22
object app2 #228B22
object app3 #228B22
object app4 #228B22
object app5 #228B22
object app6 #228B22
object app7 #228B22

interface ICmd {
    +Execute();
}

class CmdQueue #8099BF {
    命令队列
    +PushCommand();
    +ExecuteCommand();
}

class FormatCmd #8099BF {
    格式化缓存
    +Execute();
}
class LoadCmd #8099BF {
    加载缓存
    +Execute();
}
class PutCmd #8099BF {
    插入数据
    +Execute();
}
class GetCmd #8099BF {
    获取数据
    +Execute();
}

class ListCmd #8099BF {
    批量获取数据
    +Execute();
}
class CopyCmd #8099BF{
    远程拷贝数据
    +Execute();
}
class DeleteCmd #8099BF{
    删除数据
    +Execute();
}

package CacheSchedule as "缓存调度"{
}

CmdQueue ..>ICmd
CmdQueue <..app1
CmdQueue <..app2
CmdQueue <..app3
CmdQueue <..app4
CmdQueue <..app5
CmdQueue <..app6
CmdQueue <..app7

ICmd ^.. FormatCmd
ICmd ^.. LoadCmd
ICmd ^.. PutCmd 
ICmd ^.. GetCmd 
ICmd ^.. ListCmd
ICmd ^.. CopyCmd
ICmd ^.. DeleteCmd

app1 ..>FormatCmd
app2 ..>LoadCmd
app3 ..>PutCmd
app4 ..>GetCmd
app5 ..>ListCmd
app6 ..>CopyCmd
app7 ..>DeleteCmd


FormatCmd ..>CacheSchedule
LoadCmd ..>CacheSchedule
PutCmd ..>CacheSchedule
GetCmd ..>CacheSchedule
ListCmd ..>CacheSchedule
CopyCmd ..>CacheSchedule
DeleteCmd ..>CacheSchedule


```

## 重构之后的代码结构
经过前面几个步骤的重构之后,
我们的代码结构变成了这样;

```plantuml
object app {
    上层应用程序
}
package CmdPackage as "命令接口"{
}

package LogPackage as "日志管理"{
}

package StatePackage as "状态机" {
}

package DBPackage as "各类数据库" {
}

Rectangle Cache as " " {
    package CacheSchedule as "缓存调度" {
    }

    package ReadCachePackage as "读缓存"{
    }

    package WriteCachePackage as "写缓存"{
    }

    package ReplaceStrategy as "汰换策略" {
    }

    app ..>CmdPackage
    app ..>StatePackage
    CmdPackage ..> CacheSchedule
    CacheSchedule ..> WriteCachePackage
    CacheSchedule ..> ReadCachePackage
    ReadCachePackage ..> ReplaceStrategy
}

Cache ..> LogPackage
Cache ..> DBPackage
```

## 总结:
    1. 在整个重构过程中,我们使用了关注点分离原则(SOC)
        将一个复杂的问题分离为多个简单的问题,
        然后逐个解决这些简单的问题,
        那么这个复杂的问题就解决了;

    2.每一个小版本重构后, 我们都可以独立发布, 
        这符合敏捷开发流程;

    3.在不做过度设计的情况下, 
       我们的希望这些问题在v1.0版本就能优雅的解决掉,
       而这就是学习设计模式的意义!


# 参考资料:
- GOF设计模式
    >https://refactoringguru.cn/design-patterns
    
- Why don't the book include the Interpreter pattern?
    >http://blogs.perl.org/users/jeffrey_kegler/2013/03/the-interpreter-design-pattern.html

- C++设计模式
    >http://www.weixueyuan.net/cpp/shejimoshi/

- 面试中的Singleton 
    >http://www.cnblogs.com/loveis715/archive/2012/07/18/2598409.html#!comments

- 设计模式大全:
    >https://www.cnblogs.com/stringarray/p/12793282.html
