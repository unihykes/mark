# readme


```plantuml

skinparam packageStyle rect

package mkModuleInstance{
    
    class stack
    class trace
    class log
    class gettext
    class profile
    class allocator
    class switch
    class version
    class exception
    
    class mkModuleInstance {
        +GetName()
        +GetVersion()
    }
    gettext <.. mkModuleInstance
    stack <.. mkModuleInstance
    trace <.. mkModuleInstance
    log <.. mkModuleInstance
    profile <.. mkModuleInstance
    allocator <.. mkModuleInstance
    switch <.. mkModuleInstance
    version <.. mkModuleInstance
    exception <.. mkModuleInstance
}

```

```plantuml

package XX{
    
}
package miscellany{
    class assert
}

package path
{
}

package thread
{
}

## todo
unordered


```