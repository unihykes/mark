```
# vi /etc/sysconfig/iptables

在其后添加规则：
# -A RH-Firewall-1-INPUT -m state --state NEW -m tcp -p tcp --dport 3306 -j ACCEPT

重启Iptables
# service iptables restart

重启后发现不行，最终测试发现记录要添加在 -A RH-Firewall-1-INPUT -p icmp --icmp-type any -j ACCEPT 这一条前面。
修改后重启，顺利开启mysql连接。


刘浩备注：
根据实测，上述操作不行。
首先需要执行
mysql -u root 进入数据库操作，再执行
update mysql.user set host="%" where user="root" and host="localhost";
重启mysql。
在 vi /etc/sysconfig/iptables，在端口22后面加一条，然后service iptables restart：
-A INPUT -m state --state NEW -m tcp -p tcp --dport 3306 -j ACCEPT
```