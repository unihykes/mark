

#real-workd-plantuml
https://real-world-plantuml.com/?type=component


# 架构图


## Archimat:
https://github.com/ebbypeter/Archimate-PlantUML

```plantuml
!includeurl https://raw.githubusercontent.com/ebbypeter/Archimate-PlantUML/master/Archimate.puml

```

## C4
https://github.com/RicardoNiepel/C4-PlantUML

```plantuml
!includeurl https://raw.githubusercontent.com/RicardoNiepel/C4-PlantUML/release/1-0/C4_Container.puml

```


## 语法示例:
```plantuml
!include C:/unihykes/mark/3rd_Party/c4-plantuml/C4_Component.puml
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

Enterprise_Boundary(Enterprise_Boundary,"Enterprise_Boundary"){
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