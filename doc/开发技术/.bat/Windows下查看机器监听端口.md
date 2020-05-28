# Windows下查看机器监听端口 
## 1、查看所有端口占用情况
	在开始-运行-cmd,输入：netstat –ano可以查看所有进程
##2、查看指定端口的占用情况
	netstat -an |findstr :21 
	
	
https://www.iteye.com/blog/wsmajunfeng-1222526


状态:
已建立的连接:ESTABLISHED
监听连接请求:LISTENING
断开连接:CLOSE_WAIT
处于联机等待状态的:TIME_WAIT