```cpp
由于课程大实验需要使用c++操作MySQL数据库，经过一番研究终于成功实现VS2008中与MySQL的连接。

环境设置：
安装完MySQL之后，将安装目录中的include目录下的libmysql.lib文件拷到VS2008安装目录中的VC\lib\下，然后在 项目-选项-c/c++-常规 中的附加包含目录以及 链接器-常规 中的附加库目录中加入“c:\MySQL\include\”，并且在 链接器-输入 中的附加依赖项内添加“libmysql.lib”，这样即可使编译器找到mysql.h头文件，并可在程序中使用c语言的mysql API来操作数据库。（如果MySQL安装目录中无include目录，可到MySQL官网下载并安装MySQL connector for C，并修改include目录路径）
代码示例：
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <iostream>
using namespace std;

int main()
{
    const char user[] = "root";         //username
    const char pswd[] = "root";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "test";        //database
    unsigned int port = 3306;           //server port       
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    MYSQL_FIELD *fd;
    char column[32][32];
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,"select * from samples");//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result)
            {
                int i,j;
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//获取列名
                {
                    strcpy(column[i],fd->name);
                }
                j=mysql_num_fields(result);
                for(i=0;i<j;i++)
                {
                    printf("%s\t",column[i]);
                }
                printf("\n");
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
                    for(i=0;i<j;i++)
                    {
                        printf("%s\n",sql_row[i]);
                    }
                    printf("\n");
                }
            }
        }
        else
        {
            cout<<"query sql failed!"<<endl;
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return 0;
}
使用总结：
1.#include<mysql.h>之前一定要加上#include<windows.h>否则会产生如下错误：

1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(191) : error C2146: 语法错误 : 缺少“;”(在标识符“fd”的前面)
1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(191) : error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(191) : error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(366) : error C2065: “SOCKET”: 未声明的标识符
1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(366) : error C2146: 语法错误 : 缺少“)”(在标识符“s”的前面)
1>d:\my documents\visual studio 2008\projects\testmysql\testmysql\mysql\mysql_com.h(367) : error C2059: 语法错误 : “)”


2.总结一下常用MySQL命令：
Code
测试环境：MySQL 5.1.35
安装MySQL之后，打开MySQL Command Line Client，输入root密码，即可操作数据库

//查看MySQL版本
mysql> select version();

//显示所有数据库
mysql> show databases;

//使用数据库
mysql> use database_name;

//显示所有数据表
mysql> show tables;

//显示数据表结构
mysql> describe table_name;

//创建数据库
mysql> create database database_name;

//删除数据库
mysql> drop database database_name;

//创建数据表
mysql> use database_name;
mysql> create table table_name (字段名 VARCHAR(20), 字段名 CHAR(1));

//删除数据表
mysql> drop table table_name;

//查询记录
mysql> select * from table_name;

//导入.sql文件
mysql> use database_name;
mysql> source c:/mysql.sql

//修改root密码
mysql> UPDATE mysql.user SET password=PASSWORD('新密码') WHERE User='root';

//退出
mysql> quit

```