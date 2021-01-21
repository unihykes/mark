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
package string{
}

package print{
}

package thread{
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

