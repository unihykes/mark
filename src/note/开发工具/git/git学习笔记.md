配置：
下载安装包：
msysgit http://msysgit.github.io/
https://msysgit.github.io/


TortoiseGit：
https://download.tortoisegit.org/tgit/

windows下git复用已有key：
ssh -T git@git.oschina.net
会生成文件：C:\Users\33852\.ssh\known_hosts

 将id_rsa文件复制到目录C:\Users\33852\.ssh中；
 



然后clone代码线：
git clone git@git.oschina.net:3385/code.git
git clone git@git.oschina.net:3385/Deps.git



第一次使用git：
进入指定目录：
cd /e/liuhao0705

初始化配置：
git init

创建ssh key：
ssh-keygen -t rsa -C "33852613@163.com"  
之后会要求确认路径和输入密码；
我们这使用默认的一路回车就行。
成功的话会在~/下生成.ssh文件夹，进去，打开id_rsa.pub，复制里面的key。
(C:\Users\Administrator\.ssh)
回到github，进入Account Settings，左边选择SSH Keys，Add SSH Key,title随便填，粘贴key。
为了验证是否成功，在git bash下输入：
ssh -T git@github.com  
ssh -T git@git.oschina.net


配置全局用户名：
git config --global user.name "liuhao0705"

配置全局邮件名：
git config --global user.email "33852613@163.com"

git push 时报错 warning: push.default is unset:
经goolge后，得知‘matching’ 参数是 Git 1.x 的默认行为，其意是如果你执行 git push 但没有指定分支，它将 push 所有你本地的分支到远程仓库中对应匹配的分支。而 Git 2.x 默认的是 simple，意味着执行 git push 没有指定分支时，只有当前分支会被 push 到你使用 git pull 获取的代码。
git config --global push.default matching

git add报警告：warning: LF will be replaced by CRLF
原因分析：
CRLF -- Carriage-Return Line-Feed 回车换行
就是回车(CR, ASCII 13, \r) 换行(LF, ASCII 10, \n)。
这两个ACSII字符不会在屏幕有任何输出，但在Windows中广泛使用来标识一行的结束。而在Linux/UNIX系统中只有换行符。
也就是说在windows中的换行符为 CRLF， 而在linux下的换行符为：LF
使用git来生成一个rails工程后，文件中的换行符为LF， 当执行git add .时，系统提示：LF 将被转换成 CRLF
解决方法：
删除刚刚生成的.git文件
git config --global core.autocrlf false  

git命令：
下载远程代码到本地：
git clone git@github.com:liuhao0705/code.git
git status可以查看文件的差别，
git add 添加要commit的文件，也可以用git add -i来智能添加文件。
git commit -m "xxxx"提交本次修改，
git push上传到github。
git fetch：相当于是从远程获取最新版本到本地，不会自动merge


git常用命令-基本操作
1) 新增文件
新增了Test_1.java
git add Test_1.java
git commit –m “新增了Test_1.java”
git push

2) 修改文件
修改了Test_2.java
git add Test_2.java
git commit –m “修改了Test_2.java”
git push

3) 删除了文件
删除了Test_1.java
git rm Test_1.java
git commit –m “删除了Test_1.java”
git push

删除目录：git rm -r xxxxx

4) 移动了文件
将src/cn/changdai/test/Test_1.java移动到
src/cn/changdai/main/Test.java
git mv src/cn/changdai/test/Test_1.javasrc/cn/changdai/main/Test.java
git commit –m “移动了文件”

5) 从版本库同步代码到本地
git pull origin 分支名
git默认分支名是master
直接git pull的话则是从master分支同步代码到本地

6) 将本地提交同步到版本库
git push origin master

7) 查看日志
git log

8) 查看跟本地仓库做了哪些修改
git status

通常操作是先运行git stats，然后查看修改后再进行版本操作。


