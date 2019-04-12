

从Centos7以后采用target概念来定义运行级别，分为3级、5级，含义如下：
3级->multi-user.target
5级->graphical.target

- 相关命令如下
- 查看当前运行的级别
runlevel

- 修改开机默认运行级别命令
systemctl set-default multi-user.target或graphical.target

查看开机默认运行级别:
systemctl get-default

修改默认运行级别为图形方式:
systemctl set-default graphical.target

修改默认运行级别为命令行方式:
 systemctl set-default multi-user.target