```cpp
看过很多C或是C＋＋操作MySQL数据库的文章，大部分太吃力了，甚至有一部分根本没有很好的组织文字，初学者比较难以接受，即使是C++或是C高手也是比较难看懂。写这篇文章的目的不是别的，就一个，告诉您用MySQL的C API直接操作MySQL数据，并做了比较高效的封装，可以帮助开发人员大幅度提高采用MySQL的C API操作MySQL数据库的效率。
直接进入主题：
1、准备工作
MySQL数据库安装之后在/MySQL Server 5.0/lib/opt目录下有所需要的各种文件，我们需要的只是以下几个：
libmysql.lib
libmysql.dll
同时需要/MySQL Server 5.0/include目录下的几个文件：
mysql_version.h
my_list.h
mysql_com.h
mysql_time.h
mysql.h
my_alloc.h
typelib.h
准备Socket的基本文件
在VC的安装目录Microsoft Visual Studio/VC98/Lib下找到：
WS2_32.LIB
把这些文件先准备好
2、使用VC的AppWizard建立一个Win32 Console Application,其实可以是Dialog工程或是其他类型工程，比如工程取名CMySQL
3、把刚才准备好的文件拷贝你的工程目录下，和普通的CPP文件在同一个目录即可
4、建立之后，在VC的菜单栏点击Project(项目)->Settings(设置),弹出对话框，选择Link标签进入Link设置，在Object/library modules 的框里面加入
libmysql.lib[有个空格]WS2_32.LIB
5、在工程建立添加以下两个文件：
第一个文件头文件：VspdCTOMySQL.h
/****************************MYSQL IN C*******************************/
/*************************2007 -03 -07 *******************************/
/*************************李克喜**************************************/
#include <stdio.h>
#include <string>
#include <afxsock.h>
#include "mysql.h"
using namespace std;
class VspdCToMySQL
{
public:
//变量
MYSQL mysql;
/*
构造函数和稀构函数
*/
VspdCToMySQL();
~VspdCToMySQL();
/*
主要的功能：
初始化数据库
连接数据库
设置字符集
入口参数：
host ：MYSQL服务器IP
port:数据库端口
Db：数据库名称
user：数据库用户
passwd：数据库用户的密码
charset：希望使用的字符集
Msg:返回的消息，包括错误消息
出口参数：
int ：0表示成功；1表示失败
*/
int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,char * Msg);
/*
主要的功能：
查询数据
入口参数：
SQL：查询的SQL语句
Cnum:查询的列数
Msg:返回的消息，包括错误消息
出口参数：
string 准备放置返回的数据，多条记录则用0x06隔开,多个栏位用0x05隔开
如果 返回的长度＝ 0，责表示舞结果
*/
string SelectData(char * SQL,int Cnum ,char * Msg);
/*
主要功能：
插入数据
入口参数
SQL：查询的SQL语句
Msg:返回的消息，包括错误消息
出口参数：
int ：0表示成功；1表示失败
*/
int InsertData(char * SQL,char * Msg);
/*
主要功能：
修改数据
入口参数
SQL：查询的SQL语句
Msg:返回的消息，包括错误消息
出口参数：
int ：0表示成功；1表示失败
*/
int UpdateData(char * SQL,char * Msg);
/*
主要功能：
删除数据
入口参数
SQL：查询的SQL语句
Msg:返回的消息，包括错误消息
出口参数：
int ：0表示成功；1表示失败
*/
int DeleteData(char * SQL,char * Msg);
/*
主要功能：
关闭数据库连接
*/
void CloseMySQLConn();
};
第二个文件实现文件：VspdCTOMySQL.cpp
/****************************MYSQL IN C*******************************/
/*************************2007 -03 -07 *******************************/
/*************************李克喜**************************************/
#include "stdafx.h"
#include "VspdCTOMySQL.h"
VspdCToMySQL::VspdCToMySQL()
{
}
VspdCToMySQL::~VspdCToMySQL()
{
}
//初始化数据
int VspdCToMySQL::ConnMySQL(char *host,char * port ,char * Db,char * user,char* passwd,char * charset,char * Msg)
{
if( mysql_init(&mysql) == NULL )
{
Msg = "inital mysql handle error";
return 1;
}
if (mysql_real_connect(&mysql,host,user,passwd,Db,0,NULL,0) == NULL)
{
Msg = "Failed to connect to database: Error";
return 1;
}
if(mysql_set_character_set(&mysql,"GBK") != 0)
{
Msg = "mysql_set_character_set Error";
return 1;
}
return 0;
}
//查询数据
string VspdCToMySQL::SelectData(char * SQL,int Cnum,char * Msg)
{
MYSQL_ROW m_row;
MYSQL_RES *m_res;
char sql[2048];
sprintf(sql,SQL);
int rnum = 0;
char rg = 0x06;//行隔开
char cg = {0x05};//字段隔开
if(mysql_query(&mysql,sql) != 0)
{
Msg = "select ps_info Error";
return "";
}
m_res = mysql_store_result(&mysql);
if(m_res==NULL)
{
Msg = "select username Error";
return "";
}
string str("");
while(m_row = mysql_fetch_row(m_res))
{
for(int i = 0;i < Cnum;i++)
{
str += m_row[i];
str += rg;
}
str += rg;
rnum++;
}
mysql_free_result(m_res);
return str;
}
//插入数据
int VspdCToMySQL::InsertData(char * SQL,char * Msg)
{
char sql[2048];
sprintf(sql,SQL);
if(mysql_query(&mysql,sql) != 0)
{
Msg = "Insert Data Error";
return 1;
}
return 0;
}
//更新数据
int VspdCToMySQL::UpdateData(char * SQL,char * Msg)
{
char sql[2048];
sprintf(sql,SQL);
if(mysql_query(&mysql,sql) != 0)
{
Msg = "Update Data Error";
return 1;
}
return 0;
}
//删除数据
int VspdCToMySQL::DeleteData(char * SQL,char * Msg)
{
char sql[2048];
sprintf(sql,SQL);
if(mysql_query(&mysql,sql) != 0)
{
Msg = "Delete Data error";
return 1;
}
return 0;
}
//关闭数据库连接
void VspdCToMySQL::CloseMySQLConn()
{
mysql_close(&mysql);
}
6、 在main函数，（如果是其他工程级不是main了，可能是一个按钮里面的代码块）添加 一些代码，添加之后如下：
#include "stdafx.h"
#include "VspdCTOMySQL.h"
int main(int argc, char* argv[])
{
char* host="MYSQL服务器IP";
char* user="root";
char* port ="3306";
char* passwd="用户密码";
char* dbname="数据库名称";
char* charset = "GBK";//支持中文
char* Msg = "";//消息变量
//初始化
VspdCToMySQL * vspdctomysql = new VspdCToMySQL;
if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
printf("连接成功/r/n");
else
printf(Msg);
//查询
char * SQL = "SELECT ids,username,passwd,address FROM vcaccesstest";
string str = vspdctomysql->SelectData(SQL,4,Msg);
if( str.length() > 0 )
{
printf("查询成功/r/n");
printf(str.data());
printf("/r/n");
}
else
{
printf(Msg);
}
//插入
SQL = "insert into vcaccesstest(ids,username,passwd,address) values(4,'我的','123210','测试地址')";
if(vspdctomysql->InsertData(SQL,Msg) == 0)
printf("插入成功/r/n");
//更新
SQL = "update vcaccesstest set username = '修改了',passwd='2345' where ids = 3 ";
if(vspdctomysql->UpdateData(SQL,Msg) == 0)
printf("更新成功/r/n");
//删除
SQL = "delete from vcaccesstest where ids = 3 ";
if(vspdctomysql->DeleteData(SQL,Msg) == 0)
printf("删除成功/r/n");
vspdctomysql->CloseMySQLConn();
return 0;
}
7、 数据库表确认表存在，（程序中的表和字段是我的数据库里面的内容，你要自己搞定你的SQL语句了，你可以看main函数里面的SQL变量的内容。
8、 编译，运行，一切ok。
9、 总结，你要做的事情很少了，两个主要的文件写好了，你看例子调用即可，其他MySQL的库文件和附加文件别人也为您准备好了，移植到其他系统也是很简单的，比如移植到Linux和Unix下也是很简单的，VspdCTOMySQL.h和VspdCTOMySQL.cpp基本上是采用标准的C＋＋编写的，在别的系统可能需要做少量修改即可。

```