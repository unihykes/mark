virbr0：
1.执行yum groupremove "Virtualization" 命令尝试卸载virbr0设备，
通过ifconfig -a查看virbr0设备是否还存在；

2.如果还是没有卸载掉virbr0网卡，
再执行yum remove libvirt ，
用ifconfig -a查看网卡virbr0是否卸载。

3.如果执行yum报错，可以vi /etc/yum/plugincon.d/rhnplugin.conf
然后将文件中的enable=1改成enable=0，
目的是先禁用此功能，再执行yum remove libvirt进行卸载。
卸载完成重启机器，虚拟网卡就不存在。


我只执行到第2步，virbr0就消失了。
