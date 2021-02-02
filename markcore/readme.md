# reference


```plantuml

skinparam packageStyle rect

package mkModuleInstance{
    
    class stack
    class trace
    class log
    class gettext
    class perf
    class allocator
    class switch
    class version
    class exception
    
    class mkModuleInstance {
    }
    gettext <.. mkModuleInstance
    stack <.. mkModuleInstance
    trace <.. mkModuleInstance
    log <.. mkModuleInstance
    perf <.. mkModuleInstance
    allocator <.. mkModuleInstance
    switch <.. mkModuleInstance
    version <.. mkModuleInstance
    exception <.. mkModuleInstance
}

```

```plantuml
skinparam packageStyle rect

package gof{
    
}

package utility{
}

package string{
}

package container{
}

package iterator{
}

package algorithms{
}

package numerics {
}


package locale{
}

package io{
    
}

package filesystem{
}

package print{
}

package thread{
    class atomic
}
```


## todo
- 压缩
- 加密
- 随机数
- 管道
- 共享内存
- 字符编码
- 获取硬件信息
    - 内存
    - cpu


