

## 关系
```plantuml
!include %getenv("C4_HEADER")\c4_header.puml

Boundary(binary_tree, "二叉树(Binary tree)") {
    Component(二叉树, 二叉树) {
    }
    Component(满二叉树, 满二叉树) {
    }
    Component(完全二叉树, 完全二叉树) {
    }
    Component(平衡二叉树, 平衡二叉树) {
    }
    Component(哈弗曼树, 哈弗曼树\n最优二叉树) {
    }
}

```

```plantuml
!include %getenv("C4_HEADER")\c4_header.puml

Boundary(binary_server_tree, "二叉查找树(Binary Search Tree)") {
    Component(BST, 二叉查找树(BST) \n二叉搜索树) {    
    }
    Component(AVL, 平衡二叉查找树(AVL)) {
    }
    Component(红黑树, 红黑树\n 自平衡二叉查找树) {
    }
}
```


## 可视化动图:
https://www.cs.usfca.edu/~galles/visualization/Algorithms.html


