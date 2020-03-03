SVN下载
https://tortoisesvn.net/


## svn图标别其他程序覆盖
	[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\]下的项是否超过了15个

	3.打开regedit.exe，准备修改注册表
	 找到 HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Explorer
	 新建一个“字符串值”名称为 “Max Cached Icons” 值是 “2000”
	 重启一下电脑，图标就显示了。
	 
	 
	 
## svn打的patch中存在nonexistent
	解决办法:把patch中的nonexistent修改为"revision 0"就行了;

## svn打patch中出现中文导致无法使用
	最近参与工作中需要使用SVN的patch功能来code review.安装了1.7.9版本的TortoiseSVN以后发现修改代码以后然后打patch,patch中的中文会变成乱码。

	不解，询问同事以后被告知先试试安装中文包，不行再换个版本。似乎他们以前也有类似问题。

	照做以后依然没法解决乱码问题。然后上网查询发现看到有说要加环境变量LANG=zh-CN.UTF-8

	(即我的电脑-右键属性-高级系统设置-高级-环境变量-新建(XX的用户变量/系统变量)-变量名：LANG变量值:en_US .UTF8。


## win10的svn打的patch在Review Board中无法使用
	经过多次测试，发现是win10操作系统问题,在svn1.8.11版本中,打的patch中有中文;
	手动将patch中的"版本 30787"改为"revision 30787"就行了;
	将win10的语言包改成英文的，也可以解决；


## svn命令
	svn提交：svn commit -m “xxx” xx.cpp

	客户端更新代码：
	svn checkout svn://192.168.xx.xx/code
	
## linux下创建svn代码库
```
1.建立代码库。
#svnadmin create /code/testDir

2.修改配置文件
svnserve.conf
anon-access = none
auth-access = write
password-db = passwd 

//其中passwd是一个文件，默认是当前文件夹下的passwd，如果要用其他的passwd需要制定路径名

3.配置passwd文件
添加用户名和密码:
liuhao = xxxxx

4.启动svnserve服务
参考【linux常用命令】；

5.linux客户端更新代码：
svn checkout svn://192.168.xx.xx/testDir

6.linux客户端添加文件：
svn add test.h

7,将添加的文件提交
svn commit -m "log" test.h


```

## svn 清理失败 (cleanup 失败) 的解决方法

```
解决方法：
   	step1: 到 sqlite官网 (http://www.sqlite.org/download.html) 下载 sqlite3.exe      
    	找到 Precompiled Binaries for Windows，
		点击 sqlite-shell-win32-x86-3080500.zip 下载，300KB左右
   	step2: 将下载到的 sqlite3.exe 文件复制到 本地磁盘的某个临时目录下  
		（我的svn源代码放在共享磁盘中，发现 sqlite老是找不到 svn的 wc.db文件），
   	step3:  然后 设置 svn源代码 文件夹 及文件 显示 所有文件（包括隐藏文件），
		会发现 .svn/wc.db 文件， 将 其复制到 step2的临时目录下
   	step4:  开始 -> 运行 -> 打开 cmd命令
  		打开 wc.db
         执行 delete from work_queue;
    step 5: 将 wc.db 覆盖到 svn源代码目录的 .svn目录下
    step 6: 对 svn源代码目录 右键, clean up, 稍等1至5分钟左右，然后会提示 清理成功。
                   如图所示：
   （结束）
```