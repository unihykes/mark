
一、用模板安装VMware-vCenter-Server-Appliance

1、在vsphere client指定资源池中部署模板
VMware-vCenter-Server-Appliance-5.5.0.5100-1312297_OVF10.ov
安装完成后，账号：root，密码vmware

2、在命令行模式下输入
/opt/vmware/share/vami/vami_config_net
分别选择6, 2, 4, 0配置IP地址、网关、FQDN名和查看配置信息；
网络配置完成，通过浏览器访问https://vcsa-ip-address:5480做VCSA的初始化；


2、1输入6选择ip配置


2.2、设置ip和netmask



2.3、输入2，配置gateway，IPv6不用输


2.4、DNS不设置

2.5、输入1退出脚本设置界面

3、打开控制台web做VCSA的初始化；
https://192.168.92.57:5480
账号：root 密码：vmware





Configuring SSO和Starting vCenter Server可能会卡住很久，耐心等待；

4、配置完成，进入主界面：


5、用vsphere client登录192.168.92.57 root vmware



注册方式：
1Z018-AK35M-48458-4A3E4-8PH4A




AS上有个生成的


