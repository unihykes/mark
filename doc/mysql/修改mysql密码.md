在丢失root密码的时候，可以这样
     service mysqld stop
　　mysqld_safe --skip-grant-tables&
　　mysql -u root mysql
　　mysql> 
               UPDATE user SET password=PASSWORD("new password") WHERE user='root';

　　mysql> 
               FLUSH PRIVILEGES;

     service mysqld stop
     service mysqld start