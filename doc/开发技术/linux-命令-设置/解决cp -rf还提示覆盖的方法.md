```
cp是linux里的拷贝命令

-r 是用于目录拷贝时的递归操作

-f 是强制覆盖，如果存在相同参数时

-i 是与-f相反，存在重复覆盖时，会提示

可是在linux里，使用cp -rf 时 有时还是会提示，要一个个确认非常麻烦。

原因是 此时的cp 实际上是 cp -i的别名。

使用alias 可以查看

解决方法 恢复cp

alias cp =’cp

—————————————————————————————————————-

vi ~/.bashrc

# .bashrc

# User specific aliases and functions

alias rm=’rm -i’
#alias cp=’cp -i’
alias mv=’mv -i’

# Source global definitions
if [ -f /etc/bashrc ]; then
. /etc/bashrc
fi



:wq!   保存退出,重新登录ssh生效
```