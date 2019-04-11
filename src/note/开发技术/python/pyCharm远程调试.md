```py
远程调试:
http://blog.csdn.net/ll641058431/article/details/53049453

调试类：
F8 跳过
F7 进入
Shift + F8 退出
Alt + F9 运行游标
Alt + F8 验证表达式
Ctrl + Alt + F8 快速验证表达式
F9 恢复程序
Ctrl + F8 断点开关
Ctrl + Shift + F8 查看断点





远程配置:
1,打开Tools | Deployment | Configuration点击左边的“+”添加一个部署配置，输入名字，类型选SFTP

点击ok


2,配置远程服务器的ip、端口、用户名和密码。
root path是文件上传的根目录，注意这个目录必须用户名有权限创建文件。
配置连接:


配置映射:
local path是你的工程目录，就是需要将本地这个目录同步到服务器上面，我填的是项目根目录。 Deploy path on server 这里填写相对于root path的目录，下面那个web path不用管先



还有一个设置，打开Tools | Deployment | Options，将”Create Empty directories”打上勾，要是指定的文件夹不存在，会自动创建。



配置远程解释器:
选择File | Settings，选择Project | Project Interpreter，然后在右边，点击那个小齿轮设置，如下


下载文件:
选择 Tools | Deployment | Upload to sftp(这个是刚刚配置的部署名称)



添加待调试目标:


配置启动命令和环境变量:

```