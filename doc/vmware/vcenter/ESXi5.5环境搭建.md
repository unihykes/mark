注意:ESXi有硬件限制,内存最低4GB,cpu最少2核,否则安装失败

一,安装系统
加载安装光盘





如果一个ESXI被vcenter管理，并且设置了锁定模式（无法通过vsphereclient访问）；

当vcenter无法登录的时候，可以直接在ESXi主机上，通过按F2进入设置界面，修改锁定模式为disable；
则可以通过vsphereclient登录访问了；









