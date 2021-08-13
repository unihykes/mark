---
标题: 设计模式作业题-答案
作者: unihykes (liu.hao@aishu.cn)
日期: 2021/7/16
markdown:
  image_dir: ./assets
  path: exam_answer.md
  ignore_from_front_matter: true
  absolute_image_path: false
---

[toc]

# 原始代码结构:
```plantuml
title 原始代码
object app {
}

class ObjectList {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

class ObjectMap {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

app..>ObjectMap
app..>ObjectList
ObjectMap .r.> ObjectList
ObjectList .l.> ObjectMap
```

# 答案:

#### 可选答案1:
```plantuml
title 中介者
object app {
}

class ObjectList {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

class ObjectMap {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

class media {
}
app..>ObjectMap
app..>ObjectList
ObjectList <.r.> media
media <.r.> ObjectMap 

```

#### 可选答案2:
```plantuml
title 模版方法
object app {
}

interface IListFinder {
    + FindEx(...);
}
interface IMapFinder {
    + FindEx(...);
}

class ObjectList {
    + Put(...);
    + FindRnage(...);
    + Find(...);
}

class ObjectMap {
    + Put(...);
    + FindRnage(...);
    + Find(...);
}

class MapFinder {
    + FindEx(...);
}
class ListFinder {
    + FindEx(...);
}

app ..>ObjectList
app ..>ObjectMap

ObjectList ..>IMapFinder
ObjectMap..>IListFinder

ObjectList <.. ListFinder 
ObjectMap <.. MapFinder

IMapFinder ^.. MapFinder
IListFinder ^.. ListFinder

```

#### 可选答案3:
```plantuml
title 匿名回调
object app {
}

object lambdaListFinder {
}

object lambdaMapFinder {
}

class ObjectList {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

class ObjectMap {
    + Put(...);
    + FindRnage(...);
    - Find(...);
}

app ..> ObjectList
app ..> ObjectMap

ObjectList ..> lambdaMapFinder
ObjectMap ..> lambdaListFinder
ObjectList <.. lambdaListFinder
ObjectMap <.. lambdaMapFinder
```


#### 可选答案4:
```plantuml
title 对类的职责进行重构 + 外观模式

object app {
}

class ObjectList {
    + Put(...);
    + Find(...);
}

class ObjectMap {
    + Put(...);
    + Find(...);
}
class Facade {
    + Put(...);
    ==重构职责,FindRange()在facade层实现==
    + FindRnage(...); 
}

app..>Facade
Facade ..>ObjectList
Facade..>ObjectMap
```

#### 可选答案5:
```plantuml
title 外观+职责链
object app {
}

class Facade {
    + Put(...);
    + FindRnage(...);
}

interface IFinder {
    + Put(...);
    + Find(...);
    + SetNext(...);
}

class ObjectList {
    + Put(...);
    - Find(...);
    + SetNext(...);
}

class ObjectMap {
    + Put(...);
    - Find(...);
    + SetNext(...);
}

app ..> Facade
Facade ..> IFinder
IFinder ..> IFinder
IFinder ^.. ObjectList
IFinder ^.. ObjectMap

```

#### 可选答案6:
```plantuml
title 其他解耦方式...
```