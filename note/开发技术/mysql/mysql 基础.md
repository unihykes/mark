基本命令：
本地登录：mysql -uroot -p
远程登录：mysql -h 192.168.100.41 -u root -p xxxxxxxxx

显示数据库列表：show databases;
创建新的数据库：create database xxx；
使用库/打开库：use xxx；
显示数据表：show tables；
显示数据表的结构：describe 表名xx；
建表：create table xxx(字段设定列表)；
删除数据库：drop database 库名；
删除数据表：drop table 表名；
将表中记录清空：delete from 表名；
显示表中的记录：select * from 表名；
在一个表中插入字段：insert into 表名values('','glchengang','深圳一中','1976-10-10'); //括号内根据表内容填写


7.重命名表:ALTER TABLE t1 RENAME t2;


示例：


三、一个建库和建表以及插入数据的实例
drop database if exists school; //如果存在SCHOOL则删除
create database school; //建立库SCHOOL
use school; //打开库SCHOOL
create table teacher //建立表TEACHER
(
id int(3) auto_increment not null primary key,
name char(10) not null,
address varchar(50) default '深圳',
year date
); //建表结束
//以下为插入字段
insert into teacher values('','glchengang','深圳一中','1976-10-10');
insert into teacher values('','jack','深圳一中','1975-12-23');

注：在建表中
(1) 将ID设为长度为3的数字字段:int(3)，并让它每个记录自动加一: auto_increment，并不能为空:not null，而且让它成为主字段primary key
(2) 将NAME设为长度为10的字符字段
(3) 将ADDRESS设为长度50的字符字段，而且缺省值为深圳。varchar和char有什么区别呢，只有等以后的文章再说了。
(4) 将YEAR设为日期字段。
如果你在mysql提示符键入上面的命令也可以，但不方便调试。 你可以将以上命令
原样写入一个文本文件中假设为school.sql，然后复制到c:下，并在DOS状态进入目录
mysql\bin，然后键入以下命令：
mysql -uroot -p密码 < c:\school.sql
如果成功，空出一行无任何显示；如有错误，会有提示。（以上命令已经调试，你只要将//的注释去掉即可使用）。
