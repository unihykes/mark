
linux清理mysql数据库日志文件

清理数据库日志(cd /sysvol/etc/data下有很多数据库日志文件)
/usr/local/mysql/bin/mysql -u evergreen -p

密码： xxxxx
mysql> reset master;    (需要分号)



http://www.jiucool.com/terror-mysql-bin-0000x-log-file/