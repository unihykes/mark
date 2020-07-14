http://daiheeq.blog.51cto.com/876282/1440074




	1. 
重启vCenter Server Appliance的主机。


	2. 
当出现下列系统列表时，先把vmware vcenter server appliance.
（liuhao备注：如果这个界面一闪而过，可以强制先从bios启动，然后biosF10保存重启可以看到该界面；）




	3. 
按P编辑，要输入以前管理密码。如果没有修改，默认密码为vmware.
	4. 

按E，进行编辑启动项




	5. 

把启动项放在 kernel...进行，编辑。


	6. 

按E，可修改启动项内容。在最后面添加init=/bin/bash。


	7. 
按ENTER，确认启动项内容。在按B进行重启。

	8. 
当出现命令提示时，输入passwd root，输入2次新密码。

	9. 
最后输入reboot，进行重启。如果没有reboot命令直接强制关机重启；


