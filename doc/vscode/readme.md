## 【vscode】ssh出现 open failed：administratively prohibited：open failed
https://blog.csdn.net/ccw_922/article/details/126115180

step2
vim /etc/ssh/sshd_config
将AllowTcpForwarding yes #注释去掉，改成 yes
重启 sshd服务：systemctl restart sshd



##免密登陆
将windoes C://user/xx/.ssh/id_rsa.pub上传到服务器
cd ~/.ssh
cat id_rsa.pub > authorized_keys