markdown 学习
=======

## markdown preview enhanced文档（简体中文版）
https://www.bookstack.cn/read/mpe/zh-cn-_sidebar.md

# 画图
```plantuml
!include %getenv("C4_HEADER")\c4_header.puml
hide stereotype

title 示例

Boundary(Boundary, "Boundary"){
}

System_Boundary(System_Boundary, "System_Boundary") {    
    Person(Person0, "Person")
    Person(Person1, "Person", "do something")
    
    Person_Ext(Person_Ext0, "Person_Ext")
    Person_Ext(Person_Ext1, "Person_Ext", "do something")
    
    System(System0, "System")
    System(System1, "System", "do something")
    
    System_Ext(System_Ext0, "System_Ext")
    System_Ext(System_Ext1, "System_Ext", "do something")
    
    SystemDb(SystemDb0, "SystemDb")
    SystemDb(SystemDb1, "SystemDb", "do something")
    
    SystemDb_Ext(SystemDb_Ext0, "SystemDb_Ext")
    SystemDb_Ext(SystemDb_Ext1, "SystemDb_Ext", "do something")
    
    Container(Container0, "Container", "技术")
    Container(Container1, "Container", "技术", "do something")
    
    ContainerDb(ContainerDb0, "ContainerDb", "技术")
    ContainerDb(ContainerDb1, "ContainerDb", "技术", "do something")
    
    Component(Component0,"Component","sss")
    Component(Component1,"Component","sss", "do something")
    
    ComponentDb(ComponentDb0,"ComponentDb","sss")
    ComponentDb(ComponentDb1,"ComponentDb","sss", "do something")
}

Enterprise_Boundary(Enterprise_Boundary,"Enterprise_Boundary") {
}


Container_Boundary(Container_Boundary, "Container_Boundary") {
}


'Rel(personAlias, containerAlias, "Uses", "HTTPS")
'Rel_Down(personAlias, containerAlias, "Uses", "HTTPS")
'Rel_Up(personAlias, containerAlias, "Uses", "HTTPS")
'Rel_Left(personAlias, containerAlias, "Uses", "HTTPS")
'Rel_Right(personAlias, containerAlias, "Uses", "HTTPS")

Rel_Down(Boundary, System_Boundary, "Uses", "HTTPS")
Rel_Down(System_Boundary, Enterprise_Boundary, "Uses", "HTTPS")
Rel_Left(Enterprise_Boundary, Container_Boundary, "Uses", "HTTPS")

LAYOUT_WITH_LEGEND()

```