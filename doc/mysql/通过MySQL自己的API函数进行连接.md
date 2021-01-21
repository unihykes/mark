```cpp
1、使用API的方式连接，需要加载mysql的头文件和lib文件。
在VS2010的附加包含目录中添加\MySQL\MySQL Server 5.1\include。在安装MySql的目录下找。 把libmysql.dll和libmysql.lib文件拷贝到所建的工程目录下。然后在头文件里包含以下内容：
	1. 
//mysql所需的头文件和库文件
	2. 
#include "winsock.h"
	3. 
#include "mysql.h"
	4. 
#pragma comment(lib,"libmySQL.lib")


2、进行编码
（1）连接mysql数据库
头文件里定义数据源指针 MYSQL m_sqlCon;
//连接MySql数据库
	1. 
try
	2. 
{
	3. 
mysql_init(&m_sqlCon);
	4. 
// localhost:服务器 root为账号密码 test为数据库名 3306为端口
	5. 
if(!mysql_real_connect(&m_sqlCon, "localhost","root","root","test",3306,NULL,0))
	6. 
{
	7. 
AfxMessageBox(_T("数据库连接失败!"));
	8. 
return FALSE;
	9. 
}
	10. 
return TRUE;
	11. 
}
	12. 
catch (...)
	13. 
{
	14. 
return FALSE;
	15. 
}


（2）关闭数据库
	1. 
mysql_close(&m_sqlCon);


（3）创建表
	1. 
char* pQuery = "create table if not exists DS_Building( ID VARCHAR(10),Name VARCHAR(255),Descs VARCHAR(255),PRIMARY KEY (ID))"
	2. 
if(mysql_real_query(&m_sqlCon,pQuery,(UINT)strlen(pQuery))!=0)
	3. 
{
	4. 
const char* pCh = mysql_error(&m_sqlCon);
	5. 
return FALSE;
	6. 
}


附MySQL的API接口：
	1. 
mysql_affected_rows() 返回被最新的UPDATE, DELETE或INSERT查询影响的行数。
	2. 
mysql_close() 关闭一个服务器连接。
	3. 
mysql_connect() 连接一个MySQL服务器。该函数不推荐；使用mysql_real_connect()代替。
	4. 
mysql_change_user() 改变在一个打开的连接上的用户和数据库。
	5. 
mysql_create_db() 创建一个数据库。该函数不推荐；而使用SQL命令CREATE DATABASE。
	6. 
mysql_data_seek() 在一个查询结果集合中搜寻一任意行。
	7. 
mysql_debug() 用给定字符串做一个DBUG_PUSH。
	8. 
mysql_drop_db() 抛弃一个数据库。该函数不推荐；而使用SQL命令DROP DATABASE。
	9. 
mysql_dump_debug_info() 让服务器将调试信息写入日志文件。
	10. 
mysql_eof() 确定是否已经读到一个结果集合的最后一行。这功能被反对; mysql_errno()或mysql_error()可以相反被使用。
	11. 
mysql_errno() 返回最近被调用的MySQL函数的出错编号。
	12. 
mysql_error() 返回最近被调用的MySQL函数的出错消息。
	13. 
mysql_escape_string() 用在SQL语句中的字符串的转义特殊字符。
	14. 
mysql_fetch_field() 返回下一个表字段的类型。
	15. 
mysql_fetch_field_direct () 返回一个表字段的类型，给出一个字段编号。
	16. 
mysql_fetch_fields() 返回一个所有字段结构的数组。
	17. 
mysql_fetch_lengths() 返回当前行中所有列的长度。
	18. 
mysql_fetch_row() 从结果集合中取得下一行。
	19. 
mysql_field_seek() 把列光标放在一个指定的列上。
	20. 
mysql_field_count() 返回最近查询的结果列的数量。
	21. 
mysql_field_tell() 返回用于最后一个mysql_fetch_field()的字段光标的位置。
	22. 
mysql_free_result() 释放一个结果集合使用的内存。
	23. 
mysql_get_client_info() 返回客户版本信息。
	24. 
mysql_get_host_info() 返回一个描述连接的字符串。
	25. 
mysql_get_proto_info() 返回连接使用的协议版本。
	26. 
mysql_get_server_info() 返回服务器版本号。
	27. 
mysql_info() 返回关于最近执行得查询的信息。
	28. 
mysql_init() 获得或初始化一个MYSQL结构。
	29. 
mysql_insert_id() 返回有前一个查询为一个AUTO_INCREMENT列生成的ID。
	30. 
mysql_kill() 杀死一个给定的线程。
	31. 
mysql_list_dbs() 返回匹配一个简单的正则表达式的数据库名。
	32. 
mysql_list_fields() 返回匹配一个简单的正则表达式的列名。
	33. 
mysql_list_processes() 返回当前服务器线程的一张表。
	34. 
mysql_list_tables() 返回匹配一个简单的正则表达式的表名。
	35. 
mysql_num_fields() 返回一个结果集合重的列的数量。
	36. 
mysql_num_rows() 返回一个结果集合中的行的数量。
	37. 
mysql_options() 设置对mysql_connect()的连接选项。
	38. 
mysql_ping() 检查对服务器的连接是否正在工作，必要时重新连接。
	39. 
mysql_query() 执行指定为一个空结尾的字符串的SQL查询。
	40. 
mysql_real_connect() 连接一个MySQL服务器。
	41. 
mysql_real_query() 执行指定为带计数的字符串的SQL查询。
	42. 
mysql_reload() 告诉服务器重装授权表。
	43. 
mysql_row_seek() 搜索在结果集合中的行，使用从mysql_row_tell()返回的值。
	44. 
mysql_row_tell() 返回行光标位置。
	45. 
mysql_select_db() 连接一个数据库。
	46. 
mysql_shutdown() 关掉数据库服务器。
	47. 
mysql_stat() 返回作为字符串的服务器状态。
	48. 
mysql_store_result() 检索一个完整的结果集合给客户。
	49. 
mysql_thread_id() 返回当前线程的ID。
	50. 
mysql_use_result() 初始化一个一行一行地结果集合的检索。


```