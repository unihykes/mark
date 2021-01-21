sql server 2008 代理服务提供的凭据无效
sql server 2008 代理服务提供的凭据无效
在Windows Server 2008安装SQL Server 2008出现的问题：

安装时在“服务器配置”环节出现以下问题：
为sql server代理服务提供的凭据无效
为sql server服务指定的凭据无效
为analysis services服务提供的凭据无效
为reporting services服务提供的凭据无效
为integration services服务提供的凭据无效
解决方法：

SQL Server代理 选 SYSTEM
SQL Server database engine  选 NETWORK SERVICE
SQL Serveranalysis services  选 NETWORK SERVICE
SQL Serverreporting services  选 NETWORK SERVICE
SQL Serverintegration services  选 NETWORK SERVICE
不要设置密码。

